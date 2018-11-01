;
; lab7.asm
;
; Created: 2/26/2017 5:44:30 PM
; Author : aaron
;


.def	mpr = r16	
.def	waitcnt = r17			; Wait Loop Counter
.def	ilcnt = r18				; Inner Loop Counter
.def	olcnt = r19				; Outer Loop Counter
.def	speed = r20				; Multi-Purpose Register
.def	speed_out = r21			; Holds the scaler value
.equ	EngEnR = 4				; Right Engine Enable Bit
.equ	EngEnL = 7				; Left Engine Enable Bit
.equ	EngDirR = 5				; Right Engine Direction Bit
.equ	EngDirL = 6				; Left Engine Direction Bit
.equ	MovFwd = (1<<EngDirR|1<<EngDirL)	; Move Forward Command
.equ	WTime = 25				; Time to wait in wait loop
.equ	port_forward = $F		; scaler

.cseg

;--------------------------------------------------------------
; Interrupt Vectors
;--------------------------------------------------------------
.org	$0000					; Beginning of IVs
		rjmp 	INIT			; Reset interrupt

.org INT0addr					; setting up int0
		rcall full_slow			
		reti
.org INT1addr					; setting up int1
		rcall tick_slow
		reti
.org INT2addr					; setting up int2
		rcall tick_fast
		reti
.org INT3addr					; setting up int3
		rcall full_fast
		reti
.org	$0046					; End of Interrupt Vectors

;--------------------------------------------------------------
; Program Initialization
;--------------------------------------------------------------
INIT:
		cli
    ; Initialize the Stack Pointer (VERY IMPORTANT!!!!)
		ldi		mpr, low(RAMEND)
		out		SPL, mpr		; Load SPL with low byte of RAMEND
		ldi		mpr, high(RAMEND)
		out		SPH, mpr		; Load SPH with high byte of RAMEND

    ; Initialize Port B for output
		ldi		mpr, $FF		; Set Port B Data Direction Register
		out		DDRB, mpr		; for output
		ldi		mpr, $00		; Initialize Port B Data Register
		out		PORTB, mpr		; so all Port B outputs are low	
	; timer counters
		ldi		mpr, 0b10100001	; Activate Fast PWM mode with toggle
		out		TCCR1A, mpr
		ldi		mpr, 0b00001101	; Activate Fast PWM mode with toggle
		out		TCCR1B, mpr
		ldi		mpr,250			; Set initial compare value
		out		OCR1AL, mpr
		ldi		mpr, 0x00
		out		OCR1AH, mpr
		ldi		mpr,250			; Set initial compare value
		out		OCR1BL, mpr
		ldi		mpr, 0x00
		out		OCR1BH, mpr
		ldi		r21, $0F		;scaler
		mov		r20, r21		
		out		PORTB, r21		;loading in the intial value

	; Initialize Port D for input
		ldi		mpr, $00		; Set Port D Data Direction Register
		out		DDRD, mpr		; for input
		out		PIND, mpr
		ldi		mpr, $FF		; Initialize Port D Data Register
		out		PORTD, mpr		; so all Port D inputs are Tri-Stat

		; set the Interrupt control state in EIRCA to falling
		ldi mpr, (1 << ISC31) |(1 << ISC21) | (1 << ISC11) | (1 << ISC01)
	    sts EICRA, mpr				

		; Set the External Interrupt Mask for int0,1,2,3
		ldi mpr, 0b00001111
		out EIMSK, mpr
		; Turn on global interrupts
		sei
		
MAIN:
		rjmp    MAIN
Wait:

Loop:	ldi		olcnt, 224		; load olcnt register
OLoop:	ldi		ilcnt, 237		; load ilcnt register
ILoop:	dec		ilcnt			; decrement ilcnt
		brne	ILoop			; Continue Inner Loop
		dec		olcnt			; decrement olcnt
		brne	OLoop			; Continue Outer Loop
		dec		waitcnt			; Decrement wait 
		brne	Loop			; Continue Wait loop	
		ret

full_slow:
		cli
		ldi mpr, 0x00
		out EIMSK, mpr
		out EIFR, mpr
		rcall wait					;debounce
		ldi mpr, 0x00	
		mov r20, mpr				; set the speed to 0
		out PORTB, r20				; update the LED's
		out	OCR1AL, mpr				; update the control registers
		out	OCR1BL, mpr
		ldi mpr, 0b00001111
		out EIMSK, mpr
		out EIFR, mpr
		sei
		ret
tick_slow:
		cli
		ldi mpr, 0x00
		out EIMSK, mpr
		out EIFR, mpr
		rcall wait		;debounce
		cpi r20, 0 
		BREQ skip		; if the speed is already at 0, skip the rest of the function.  
		dec r20			; set the speed to 1 less than it is
		out PORTB, r20	; update teh LED's
		mul r21, r20	; multiply by the scaler
		mov mpr, r0		; update the control registers
		out	OCR1AL, mpr	; update the control registers
		out	OCR1BL, mpr	; update the control registers
		skip:
		ldi mpr, 0b00001111
		out EIMSK, mpr
		out EIFR, mpr
		nop
		sei
		ret
tick_fast:
		cli
		ldi mpr, 0x00
		out EIMSK, mpr
		out EIFR, mpr
		rcall wait		;debounce
		cpi r20, 15 
		BREQ skip1		; if the speed is already at 15, skip the rest of the function.  
		inc r20			; set the speed to 1 more than it is	
		out PORTB, r20	; update the LED's
		mul r21, r20	; multiply by scaler
		mov mpr, r0		; update the control registers
		out	OCR1AL, mpr	; update the control registers
		out	OCR1BL, mpr	; update the control registers
		skip1:
		ldi mpr, 0b00001111
		out EIMSK, mpr
		out EIFR, mpr
		sei
		ret

full_fast:
		cli
		ldi mpr, 0x00
		out EIMSK, mpr
		out EIFR, mpr
		rcall wait
		ldi r20, 0x0F	; set the speed to 15
		out PORTB, r20	; update the LED's
		ldi mpr, 0xFF	; update the control registers to max speed
		out	OCR1AL, mpr	; update the control registers
		out	OCR1BL, mpr	; update the control registers
		ldi mpr, 0b00001111
		out EIMSK, mpr
		out EIFR, mpr
		sei
		ret