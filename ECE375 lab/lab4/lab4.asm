;***********************************************************
;*	Lab 4 ECE375
;*	LCD usage
;***********************************************************
;*	 Author: Aaron Rito
;*	   Date: 2/2/17
;***********************************************************
.include "m128def.inc"			; Include definition file
;***********************************************************
;*	Internal Register Definitions and Constants
;***********************************************************
.def	mpr = r16				; Multipurpose register is required for LCD Driver
.equ RAM_START = 0x0100			; Marking the start of sram, where the LCD will read from
;***********************************************************
;*	Start of Code Segment
;***********************************************************
.cseg							; Beginning of code segment
;***********************************************************
;*	Interrupt Vectors
;***********************************************************
.org	$0000					; Beginning of IVs
		rjmp INIT				; Reset interrupt
.org	$0046					; End of Interrupt Vectors
;***********************************************************
;*	Program Initialization
;***********************************************************
INIT:							; The initialization routine
		ldi		mpr, low(RAMEND)	; initialize Stack Pointer
		out		SPL, mpr			
		ldi		mpr, high(RAMEND)
		out		SPH, mpr
		rcall LCDInit	; Initialize LCD Display
		; Move strings from Program Memory to Data Memory
		ldi ZL, low(STRING_BEG<<1) ;setting Z pointer to the strings
		ldi ZH, high(STRING_BEG<<1)
		ldi YL, low(RAM_START)  ;setting Y pointer to the start of SRAM
		ldi YH, high(RAM_START)
		ldi XL, low(STRING_END<<1) ; setting X pointer to the end of the strings
		ldi XH, high(STRING_END<<1)
		LOOP:
			LPM R17, Z+	
			ST Y+, R17
			cp r31, r27	;check if the high pointer registers are equal 
			BREQ LOW_CHECK
			rjmp LOOP
		LOW_CHECK:
			cp r30, r26 ;check if the low pointer registers are equal 
			BRNE LOOP ; if not return to loop to next space in mem
		ldi YL, low(RAM_START) ; set the y pointer back to the start of the sram
		ldi YH, high(RAM_START) 

;***********************************************************
;*	Main Program
;***********************************************************
MAIN:							
		rcall LCDWrite	;push the data to the LCD
		call CYCLE_MEM	;rotate the letters in a moving marquee
		rcall MY_DELAY  ;a simple delay
		rjmp	MAIN	;repeat
;***********************************************************
;*	Functions and Subroutines
;***********************************************************
; A standard delay function, this one is approx 1/3 second. 
MY_DELAY:				   
	ldi  r18, 20
    ldi  r19, 8
    ldi  r20, 150
L1: dec  r20
    brne L1
    dec  r19
    brne L1
    dec  r18
    brne L1
	ret						
;This function cycles through the memory spaces used by the LCD in a moving marquee fashion
;It takes the last value of the line word, and stores in a temp register until all the other
;values have been moved one spaces to the right. The temp value then goes into the first postion. 
CYCLE_MEM:ldi YL, 0x0f  ;set the Y pointer to the last value of line 1
	ldi YH, 0x01		
	LD r17, Y			; save the last value of line 1 into temp
	CYC:	LD r18, -Y	; get the preceeding value 
		INC r28			; return to next space in mem	
		ST Y, r18		; place preceeding value in next space
		DEC r28			; return to prev space
		cpi r28, 0x00	; check if end of line
		BRNE CYC		; if not, repeat
		ST Y, r17		; place the saved last value from the line to the first position
	ldi YL, 0x1F		; same process for line 2, starting at the last location
	ldi YH, 0x01
	LD r17, Y
	CYC1: LD r18, -Y
		INC r28
		ST Y, r18	
		DEC r28
		cpi r28, 0x10
		BRNE CYC1
		ST Y, r17
	ret	
;***********************************************************
;*	Stored Program Data
;***********************************************************
STRING_BEG:
.DB		"Aaron Rito      ", "Hello World!    "		; Declaring data in ProgMem
STRING_END:
;***********************************************************
;*	Additional Program Includes
;***********************************************************
.include "LCDDriver.asm"		; Include the LCD Driver
