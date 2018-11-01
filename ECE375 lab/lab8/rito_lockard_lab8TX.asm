;***********************************************************
;*
;*	Tek_Bot Transmitter
;*
;*	This Assembly code transmits the required operational 
;*	commands to an identical Tek_Bot with an reciever assembly
;*	flash. This program has the ability through its IR 
;*	transmitter to send out six differnt commands including:
;*	move foward, move backward, turn right, turn left, halt, 
;*	and freeze.
;*	
;*	This is the TRANSMIT  file for Lab 8 of ECE 375
;*
;***********************************************************
;*
;*	 Author: RJ Lockard & Aron Rito
;*	   Date: 3/13/2017
;*
;***********************************************************

.include "m128def.inc"			; Include definition file

;***********************************************************
;*	Internal Register Definitions and Constants
;***********************************************************
.def	mpr = r16				; Multi-Purpose Register

.def	ilcnt = r18				; Inner Loop Counter
.def	olcnt = r19				; Outer Loop Counter
.def	waitcnt = r20			; Wait Loop Counter

								; Use these commands between the remote and TekBot
								; MSB = 1 thus:
								; commands are shifted right by one and ORed with 0b10000000 = $80

.equ	EngEnR = 4				; Right Engine Enable Bit
.equ	EngEnL = 7				; Left Engine Enable Bit
.equ	EngDirR = 5				; Right Engine Direction Bit
.equ	EngDirL = 6				; Left Engine Direction Bit


.equ	BotID = 00000001		; 8 bit BotID specifies the id in which in which the specific remote will connect to the specific reciever

.equ	Wtime = 50				; intialized wait time

.equ	MovFwd =  (1<<(EngDirR)|1<<(EngDirL))		; Move Forwards Command
.equ	MovBck =  ($00)								; Move Backwards Command
.equ	TurnR =   (1<<(EngDirL))					; Turn Right Command
.equ	TurnL =   (1<<(EngDirR))					; Turn Left Command
.equ	Halt =    (1<<(EngEnR)|1<<(EngEnL))			; Halt Command


;***********************************************************
;*	Start of Code Segment
;***********************************************************
.cseg							; Beginning of code segment

;-----------------------------------------------------------
; Interrupt Vectors
;-----------------------------------------------------------
.org	$0000					; Beginning of IVs
		rjmp 	INIT			; Reset interrupt

.org	$0002					
		rcall 	FreezeTX
		reti

.org	$0004					
		rcall 	HaltTX
		reti

.org	$0006					
		rcall 	tag_sig
		reti

.org	$0046					; End of Interrupt Vectors

;-----------------------------------------------------------
; Program Initialization
;-----------------------------------------------------------
INIT:

								; Stack Pointer (VERY IMPORTANT!!!!)
	ldi		mpr, low(RAMEND)
	out		SPL, mpr			; Load SPL with low byte of RAMEND
	ldi		mpr, high(RAMEND)
	out		SPH, mpr			; Load SPH with high byte of RAMEND



								; I/O Ports
	ldi		mpr, $00			; Initialize Port B for outputs
	out		PORTB, mpr		
	ldi		mpr, $FF		
	out		DDRB, mpr		

	ldi		mpr, $FF			; Initialize Port D for inputs
	out		PORTD, mpr		
	ldi		mpr, $00		
	out		DDRD, mpr		

								; USART1
								; Set baudrate at 2400bps
								; Set the baud rate and enable double data rate
    ldi mpr, $A0
    sts UBRR1L, mpr
    ldi mpr, $01
    sts UBRR1H, mpr
    ldi mpr, (0<<U2X1)
    sts UCSR1A, mpr
								
								; Enable transmitter
    ldi mpr, (1<<TXEN1)
    sts UCSR1B, mpr

								; Set frame format: 8 data bits, 2 stop bits
    ldi mpr, (1<<UCSZ10)|(1<<UCSZ11)|(1<<USBS1)|(1<<UPM01)
    sts UCSR1C, mpr


								; External Interrupts
								; Set the Interrupt to sense for falling edge
								; Set the External Interrupt Mask
	ldi	mpr, 0x0
	out	EICRB, mpr
	ldi	mpr, 0xa
	sts	EICRA, mpr
	ldi	mpr, 0x03
	out	EIMSK, mpr

	clr mpr						; Clear mpr
	out PORTB, mpr

	sei							;Set the External Interrupt Mask

;-----------------------------------------------------------
; Main Program
;-----------------------------------------------------------
MAIN:

	sbis PIND, 7				; Set move foward command to PIND 7 (button 7)
	rjmp forwardTX
	sbis PIND, 6				; Set move backward command to PIND 6 (button 6)
	rjmp backwardTX
	sbis PIND, 5				; Set turn left command to PIND 5 (button 5)
	rjmp turnLeftTX
	sbis PIND, 4				; Set turn right command to PIND 4 (button 4)
	rjmp turnRightTX
	sbis PIND, 2				; Set test RX bot transmittsion to test freeze and death
	rjmp tag_sig			
	rjmp MAIN

;***********************************************************
;*	Functions and Subroutines
;***********************************************************

sendBotId:
	ldi mpr, BotID				; Send Bot ID command
	sts UDR1, mpr
	rcall waitTX				; rcall to the wait transmition command to ensure no double button press
	ret							; return from subrountine

tag_sig:						; test command to freeze rx, triggered by Pin (button 3)
	ldi waitcnt, Wtime
	rcall wait					; rcall to the wait transmition command to ensure no double button press
	rcall sendBotId
	ldi mpr, 0b01010101			; Loading coresponding action opcode
	sts UDR1, mpr
	out PORTB, mpr				; Port the corresponding command to be transmitted
	rcall waitTX				; rcall to the wait transmition command
	rjmp MAIN					; rjumps back to the main routine

forwardTX:						; Move foward command, triggered by Pin (button 7)
	ldi waitcnt, Wtime
	rcall wait					; rcall to the wait transmition command to ensure no double button press
	rcall sendBotId
	ldi mpr, MovFwd				; Loading coresponding action opcode
	sts UDR1, mpr
	out PORTB, mpr				; Port the corresponding command to be transmitted
	rcall waitTX				; rcall to the wait transmition command
	rjmp MAIN					; rjumps back to the main routine

backwardTX:						; Move backward command, triggered by Pin 6 (button 6)
	ldi waitcnt, Wtime
	rcall wait					; rcall to the wait transmition command to ensure no double button press
	rcall sendBotId
	ldi mpr, MovBck				; Loading coresponding action opcode
	sts UDR1, mpr
	out PORTB, mpr				; Port the corresponding command to be transmitted
	rcall waitTX				; rcall to the wait transmition command
	rjmp MAIN					; rjumps back to the main routine

turnLeftTX:						; Move trunLeft command, triggered by Pin 5 (button 5)
	ldi waitcnt, Wtime
	rcall wait					; rcall to the wait transmition command to ensure no double button press
	rcall sendBotId
	ldi mpr, TurnL				; Loading coresponding action opcode
	sts UDR1, mpr
	out PORTB, mpr				; Port the corresponding command to be transmitted
	rcall waitTX				; rcall to the wait transmition command
	rjmp MAIN					; rjumps back to the main routine

turnRightTX:						; Move turnRight command, triggered by Pin 4 (button 4)
	ldi waitcnt, Wtime
	rcall wait					; rcall to the wait transmition command to ensure no double button press
	rcall sendBotId
	ldi mpr, TurnR				; Loading coresponding action opcode
	sts UDR1, mpr
	out PORTB, mpr				; Port the corresponding command to be transmitted
	rcall waitTX				; rcall to the wait transmition command
	rjmp MAIN					; rjumps back to the main routine

HaltTX:						; Halt command, triggered by interrupt (button 1)
	ldi waitcnt, Wtime
	rcall wait				; rcall to the wait transmition command to ensure no double button press
	rcall sendBotId
	ldi mpr, Halt				; Loading coresponding action opcode
	sts UDR1, mpr
	out PORTB, mpr				; Port the corresponding command to be transmitted
	rcall waitTX				; rcall to the wait transmition command
	ret

FreezeTX:						; FreezeTX command, triggered by interrupt (button 0)
	ldi waitcnt, Wtime
	rcall wait					; rcall to the wait transmition command to ensure no double button press
	rcall sendBotId
	ldi mpr, 0b11111000			; Loading coresponding action opcode
	sts UDR1, mpr
	out PORTB, mpr				; Port the corresponding command to be transmitted
	rcall waitTX				; rcall to the wait transmition command
	ret

waitTX:							; Wait subroutine
	lds mpr, UCSR1A
	sbrs mpr, TXC1
	ret	`						


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