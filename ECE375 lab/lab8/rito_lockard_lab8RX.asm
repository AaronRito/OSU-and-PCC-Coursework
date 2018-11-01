;
; lab8.asm
; RX code
; Created: 3/10/2017 12:22:06 PM
; Authors: Aaron Rito, Robert Lockard
;
.include "m128def.inc"			; Include definition file

; Variable and Constant Declarations
.def	mpr = r16				; Multi-Purpose Register
.def	waitcnt = r17			; Wait Loop Counter
.def	ilcnt = r18				; Inner Loop Counter
.def	olcnt = r19				; Outer Loop Counter
.def    current_action = r23	; Holds the current operation.
.def	death_counter = r24		; keeps track of freeze tags
.def    mpr2 = r21				; holds the commands to avoid writing over the opcodes

.equ	WTime = 250				; Time to wait in wait loop
.equ    TurnTime = 100			; A shorter wait time
.equ	WskrR = 0				; Right Whisker Input Bit
.equ	WskrL = 1				; Left Whisker Input Bit
.equ	EngEnR = 4				; Right Engine Enable Bit
.equ	EngEnL = 7				; Left Engine Enable Bit
.equ	EngDirR = 5				; Right Engine Direction Bit
.equ	EngDirL = 6				; Left Engine Direction Bit

;These macros are the values to make the TekBot Move.

.equ	MovFwd = (1<<EngDirR|1<<EngDirL)	; Move Forward Command
.equ	MovBck = $00						; Move Backward Command
.equ	TurnR = (1<<EngDirL)				; Turn Right Command
.equ	TurnL = (1<<EngDirR)				; Turn Left Command
.equ	Halt = (1<<EngEnR|1<<EngEnL)		; Halt Command

.equ	BotAddress = 1						;(Enter your robot's address here (8 bits))

;These macros are the values to make the TekBot Move. The action codes have been set to match them. 

.equ	MovFwdR =  (1<<EngDirR|1<<EngDirL)	;0b01100000 Move Forward Action Code
.equ	MovBckR =  $00						;0b00000000 Move Backward Action Code
.equ	TurnRR =   (1<<EngDirL)				;0b01000000 Turn Right Action Code
.equ	TurnLR =   (1<<EngDirR)				;0b00100000 Turn Left Action Code
.equ	HaltR =    (1<<EngEnR|1<<EngEnL)	;0b10010000 Halt Action Code
.equ	freeze_msg =   0b11111000			;send the freeze out message code
.equ    freeze_sig=    0b01010101			;freeze from any source
.equ	ser_buffer = $0100					;a buffer for the UDR1 register

.cseg
.org	$0000					; Beginning of IVs
		rjmp 	INIT			; Reset interrupt

.org INT0addr					; setting up int0
		rcall HitRight
		reti

.org INT1addr					; setting up int1
		rcall HitLeft
		reti

.org $003C						; USART signal recieved 
	rcall recieve_command
	reti
.org	$0046					; End of Interrupt Vectors

INIT:
	cli
	; Stack Pointer
	ldi		mpr, low(RAMEND)
	out		SPL, mpr		
	ldi		mpr, high(RAMEND)
	out		SPH, mpr		

	;USART1 Set baudrate at 2400bps
    ldi mpr, $A0
    sts UBRR1L, mpr
    ldi mpr, $01
    sts UBRR1H, mpr
    ldi mpr, (0<<U2X1)
    sts UCSR1A, mpr

    ; Enable receive interrupt
    ldi mpr, (1<<RXCIE1)|(1<<RXEN1)
	sts UCSR1B, mpr

	; Set frame format: 8 data bits, 2 stop bits
	; 2 stop bits is USBS1, data bits are UCCSZ*
    ldi mpr, (1<<UCSZ10)|(1<<UCSZ11)|(1<<USBS1)|(1<<UPM01)
    sts UCSR1C, mpr

    ; Initialize Port B for output
	ldi		mpr, $FF		; Set Port B Data Direction Register
	out		DDRB, mpr		; for output
	ldi		mpr, $00		; Initialize Port B Data Register
	out		PORTB, mpr		; so all Port B outputs are low	

	; Initialize Port D for input
	ldi		mpr, $00		; Set Port D Data Direction Register
	out		DDRD, mpr		; for input
	ldi		mpr, $FF		; Initialize Port D Data Register
	out		PORTD, mpr		; so all Port D inputs are Tri-State

	; Initialize TekBot Forward Movement
	ldi		mpr, MovFwd		; Load Move Forward Command
	out		PORTB, mpr		; Send command to motor

	; set the Interrupt control state in EIRCA to falling
	ldi mpr, (1 << ISC11) | (1 << ISC01)
	sts EICRA, mpr				

	; Set the External Interrupt Mask for int0 and int1
	in mpr, EIMSK 
	ori mpr, (1<<INT0) | (1<<INT1)
	out EIMSK, mpr
	ldi mpr, $03
	MOV death_counter, mpr 
	ldi current_action, 0b10010000
	sei

;main loop
MAIN:
	
	out PORTB, current_action	; sets PORTB to the saved action in case of freeze or whisker hit
	rjmp MAIN					; loop back, interrupts do the rest

;USART recieve opcode command
recieve_command:
	
	ldi XL, low(ser_buffer)		;set X pointer to point at UDR1 (not sure I need this)
	ldi XH, high(ser_buffer)	
	lds mpr2, UDR1				;load the opcode

	;the following compares the recieved opcode with the motor fucntions and calls the appropriate action
	cpi mpr2, MovFwdR
	breq move_forward_call

	cpi mpr2, MovBckR
	breq move_back

	cpi mpr2, TurnRR
	breq HitRight_call

	cpi mpr2, TurnLR
	breq HitLeft_call

	cpi mpr2, Halt
	breq Halt_now

	cpi mpr2, freeze_sig
	breq freeze

	cpi mpr2, freeze_msg
	breq msg_out

	ret

;ran out of space on the interrupt vector space, need calls for calls
HitLeft_call:
	rcall   save_action
	rcall HitLeft
	ret
HitRight_call:
	rcall   save_action
	rcall HitRight
	ret
move_forward_call:
	rcall move_forward
	ret
;death loop after 3 freeze tags
death_loop:
	ldi mpr, $FF	;setPORTB to all on death signal
	out PORTB, mpr
	rjmp death_loop

;Halt action
Halt_now:
	rcall   save_action			; save the action so we can return to it
	ldi		mpr, HaltR
	out		PORTB, mpr
	ldi		waitcnt, Wtime
	rcall	wait
	ret

;freeze as a slave
freeze:
	cli
	ldi mpr, $00		;disable the interrupts			
	out EIMSK, mpr
	out EIFR, mpr
	ldi mpr, $0F
	out PORTB, mpr		; show the freeze signal on PORTB
	ldi	waitcnt, WTime 	; Wait for 1 second
	rcall wait 
	dec death_counter	; decrement the tag counter
	cpi death_counter, $00
	breq death_loop		; die if taqgged 3 times
	in mpr, EIMSK		;re-enable interrpus
	ori mpr, (1<<INT0) | (1<<INT1)
	out EIMSK, mpr
	out EIFR, mpr
	sei
	ret

;freeze as a middle man
msg_out:

	ldi mpr, (0<<RXCIE1)|(0<<RXEN1) | (1<<TXEN1)	;disable the reciever, enable the transmitter
	sts UCSR1B, mpr									
	ldi mpr, 0b01010101								; send out the freeze tag signal
	sts UDR1, mpr
	out PORTB, mpr	
	ldi	waitcnt, TurnTime 							; Wait for 1 second for the transmit to finish
	rcall Wait
	ldi mpr, (1<<RXCIE1)|(1<<RXEN1) | (0<<TXEN1)	;disable transmitter, enable reciever, avoids race condition
	sts UCSR1B, mpr
	ret

;move backwards		
move_back:
	rcall   save_action		; save the action command
	ldi		mpr, MovBck		; Load Move back Command
	out		PORTB, mpr		; Send command to motors
	ldi		waitcnt, TurnTime 	; Wait for 1 second
	rcall	Wait			; Call wait function
	ret
;move forward
move_forward:
	rcall   save_action		;save the action command
	ldi		mpr, MovFwd		; Load Move Forward Command 
	out		PORTB, mpr		; Send command to motors
	ldi		waitcnt, TurnTime 	; Wait for 1 second
	rcall	Wait			; Call wait function
	ret
;turn right, the action command is saved in the action call in case the whiskers are using the fucntion
HitRight:
	cli				;disable interrrupts
	ldi mpr, $00
	out EIMSK, mpr
	out EIFR, mpr
			
	; Move Backwards for a second
	ldi		mpr, MovBck	; Load Move Backward command
	out		PORTB, mpr	; Send command to port
	ldi		waitcnt, TurnTime 	; Wait for 1 second
	rcall	Wait			; Call wait function

	; Turn left for a second
	ldi		mpr, TurnRR	; Load Turn Left Command
	out		PORTB, mpr	; Send command to port
	ldi		waitcnt, TurnTime	; Wait for 1 second
	rcall	Wait			; Call wait function

	in mpr, EIMSK					;re-enable interrupts
	ori mpr, (1<<INT0) | (1<<INT1)
	out EIMSK, mpr
	out EIFR, mpr
	sei
	ret				; Return from subroutine

;turn left, the action command is saved in the action call in case the whiskers are using the fucntion
HitLeft:
	cli
	ldi mpr, $00
	out EIMSK, mpr
	out EIFR, mpr

	; Move Backwards for a second
	ldi		mpr, MovBck	; Load Move Backward command
	out		PORTB, mpr	; Send command to port
	ldi		waitcnt,TurnTime 	; Wait for 1 second
	rcall	Wait			; Call wait function

	; Turn right for a second
	ldi		mpr, TurnLR	; Load Turn Left Command
	out		PORTB, mpr	; Send command to port
	ldi		waitcnt, TurnTime	; Wait for 1 second
	rcall	Wait			; Call wait function

	in mpr, EIMSK					;re-enable interrupts
	ori mpr, (1<<INT0) | (1<<INT1)
	out EIMSK, mpr
	out EIFR, mpr
	sei
	ret				

;the same wait function from the other labs
Wait:
		push	waitcnt			; Save wait register
		push	ilcnt			; Save ilcnt register
		push	olcnt			; Save olcnt register

Loop:	ldi		olcnt, 224		; load olcnt register
OLoop:	ldi		ilcnt, 237		; load ilcnt register
ILoop:	dec		ilcnt			; decrement ilcnt
		brne	ILoop			; Continue Inner Loop
		dec		olcnt			; decrement olcnt
		brne	OLoop			; Continue Outer Loop
		dec		waitcnt			; Decrement wait 
		brne	Loop			; Continue Wait loop	

		pop		olcnt			; Restore olcnt register
		pop		ilcnt			; Restore ilcnt register
		pop		waitcnt			; Restore wait register
		ret						; Return from subroutine

; saves the action codes for certain actions. 
save_action:
	MOV current_action, mpr2
	ret