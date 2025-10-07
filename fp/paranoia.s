; Kahan's Floating Point Test "Paranoia" (under construction)

exit	equ	$fff0
putc	equ	$fff1
puts	equ	$fff2

SIGN	EQU	$F3
X2	EQU	$F4
M2	EQU	$F5
X1	EQU	$F8
M1	EQU	$F9
E	EQU	$FC

fp1	EQU	X1
fp2	EQU	X2

block	equ	$300

minusone equ	0
zero	equ	4
one	equ	8
two	equ	12
three	equ	16

Radix	equ	124
W	equ	128
Y	equ	132
Z	equ	136

	org	$1000

; minusone = -1.0

	lda	#1
	jsr	float
	jsr	FCOMPL
	ldx	#minusone
	jsr	fsave

; zero = 0.0

	lda	#0
	jsr	float
	ldx	#zero
	jsr	fsave

; one = 1.0

	lda	#1
	jsr	float
	ldx	#one
	jsr	fsave

; two = 2.0

	lda	#2
	jsr	float
	ldx	#two
	jsr	fsave

; three = 3.0

	lda	#3
	jsr	float
	ldx	#three
	jsr	fsave

; zero + zero = zero ?

	ldx	#zero
	jsr	fload1
	ldx	#zero
	jsr	fload2
	jsr	FADD
	ldx	#zero
	jsr	fload2
	jsr	feq
	beq	$+5
	jsr	err

; one - one = zero ?

	ldx	#one
	jsr	fload1
	ldx	#one
	jsr	fload2
	jsr	FSUB
	ldx	#zero
	jsr	fload2
	jsr	feq
	beq	$+5
	jsr	err

; one + one = two ?

	ldx	#one
	jsr	fload1
	ldx	#one
	jsr	fload2
	jsr	FADD
	ldx	#two
	jsr	fload2
	jsr	feq
	beq	$+5
	jsr	err

; -zero = zero ?

	ldx	#zero
	jsr	fload1
	jsr	FCOMPL
	ldx	#zero
	jsr	fload2
	jsr	feq	
	beq	$+5
	jsr	err

; two + one = three?

	ldx	#two
	jsr	fload1
	ldx	#one
	jsr	fload2
	jsr	FADD
	ldx	#three
	jsr	fload2
	jsr	feq
	beq	$+5
	jsr	err

; Searching for Radix and Precision.

	jsr	puts
	word	str1

	ldx	#one		; W = one
	jsr	fload1
	ldx	#W
	jsr	fsave

loop1	ldx	#W		; W = W + W
	jsr	fload1
	ldx	#W
	jsr	fload2
	jsr	FADD
	ldx	#W
	jsr	fsave

	ldx	#W		; Y = W + one
	jsr	fload1
	ldx	#one
	jsr	fload2
	jsr	FADD
	ldx	#Y
	jsr	fsave

	ldx	#Y		; Z = Y - W
	jsr	fload1
	ldx	#W
	jsr	fload2
	jsr	FSUB
	ldx	#Z
	jsr	fsave

	ldx	#Z		; Y = Z - one
	jsr	fload1
	ldx	#one
	jsr	fload2
	jsr	FSUB
	ldx	#Y
	jsr	fsave

	ldx	#Y		; fabs(Y) + minusone
	jsr	fload1
	jsr	fabs
	ldx	#minusone
	jsr	fload2
	jsr	FADD

	lda	M1		; loop if negative
	bmi	loop1

	ldx	#one		; Y = one
	jsr	fload1
	ldx	#Y
	jsr	fsave

loop2	ldx	#W		; Radix = W + Y
	jsr	fload1
	ldx	#Y
	jsr	fload2
	jsr	FADD
	ldx	#Radix
	jsr	fsave

	ldx	#Y		; Y = Y + Y
	jsr	fload1
	ldx	#Y
	jsr	fload2
	jsr	FADD
	ldx	#Y
	jsr	fsave

	ldx	#Radix		; Radix = Radix - W
	jsr	fload1
	ldx	#W
	jsr	fload2
	jsr	FSUB
	ldx	#Radix
	jsr	fsave

	ldx	#Radix		; loop if Radix = 0
	jsr	fload1
	ldx	#zero
	jsr	fload2
	jsr	feq
	beq	loop2

	ldx	#Radix
	jsr	print4

	ldx	#minusone
	jsr	print4

;;;;; under construction

ok	jsr	puts
	word	okstr
	jsr	exit

err	jsr	puts
	word	errstr
	jsr	exit

okstr	byte	"ok",10,0
errstr	byte	"err",10,0

str1	byte	"Searching for Radix and Precision.",10,0

print4	lda	block,x
	jsr	print41
	lda	block+1,x
	jsr	print41
	lda	block+2,x
	jsr	print41
	lda	block+3,x
	jsr	print41
	lda	#10
	jsr	putc
	rts

print41	pha
	lsr	a
	lsr	a
	lsr	a
	lsr	a
	cmp	#10
	bcc	$+4
	adc	#6
	clc
	adc	#"0"
	jsr	putc
	pla
	and	#$f
	cmp	#10
	bcc	$+4
	adc	#6
	clc
	adc	#"0"
	jsr	putc
	rts

feq	lda	fp1
	cmp	fp2
	bne	feq1
	lda	fp1+1
	cmp	fp2+1
	bne	feq1
	lda	fp1+2
	cmp	fp2+2
	bne	feq1
	lda	fp1+3
	cmp	fp2+3
feq1	rts

float	sta	M1+1
	lda	#0
	sta	M1
	sta	M1+2
	jsr	FLOAT
	rts

fload1	lda	block,x
	sta	fp1
	lda	block+1,x
	sta	fp1+1
	lda	block+2,x
	sta	fp1+2
	lda	block+3,x
	sta	fp1+3
	rts

fload2	lda	block,x
	sta	fp2
	lda	block+1,x
	sta	fp2+1
	lda	block+2,x
	sta	fp2+2
	lda	block+3,x
	sta	fp2+3
	rts

fsave	lda	fp1
	sta	block,x
	lda	fp1+1
	sta	block+1,x
	lda	fp1+2
	sta	block+2,x
	lda	fp1+3
	sta	block+3,x
	rts

fabs	lda	M1
	bpl	$+5
	jsr	FCOMPL
	rts

OVLOC	jsr	puts
	word	OVLOCS
	jsr	exit

OVLOCS	byte	"OVLOC",10,0

;***********************
;*                     *
;*  APPLE-II FLOATING  *
;*   POINT ROUTINES    *
;*                     *
;*  COPYRIGHT 1977 BY  *
;* APPLE COMPUTER INC. *
;*                     *
;* ALL RIGHTS RESERVED *
;*                     *
;*     S. WOZNIAK      *
;*                     *
;***********************
; TITLE "FLOATING POINT ROUTINES"
;SIGN      EQU  $F3
;X2        EQU  $F4
;M2        EQU  $F5
;X1        EQU  $F8
;M1        EQU  $F9
;E         EQU  $FC
;OVLOC     EQU  $3F5
          ORG  $F425
ADD       CLC           ;CLEAR CARRY
          LDX  #$2      ;INDEX FOR 3-BYTE ADD.
ADD1      LDA  M1,X
          ADC  M2,X     ;ADD A BYTE OF MANT2 TO MANT1
          STA  M1,X
          DEX           ;INDEX TO NEXT MORE SIGNIF. BYTE.
          BPL  ADD1     ;LOOP UNTIL DONE.
          RTS           ;RETURN
MD1       ASL  SIGN     ;CLEAR LSB OF SIGN.
          JSR  ABSWAP   ;ABS VAL OF M1, THEN SWAP WITH M2
ABSWAP    BIT  M1       ;MANT1 NEGATIVE?
          BPL  ABSWAP1  ;NO, SWAP WITH MANT2 AND RETURN.
          JSR  FCOMPL   ;YES, COMPLEMENT IT.
          INC  SIGN     ;INCR SIGN, COMPLEMENTING LSB.
ABSWAP1   SEC           ;SET CARRY FOR RETURN TO MUL/DIV.
SWAP      LDX  #$4      ;INDEX FOR 4 BYTE SWAP.
SWAP1     STY  E-1,X
          LDA  X1-1,X   ;SWAP A BYTE OF EXP/MANT1 WITH
          LDY  X2-1,X   ;EXP/MANT2 AND LEAVE A COPY OF
          STY  X1-1,X   ;MANT1 IN E (3 BYTES).  E+3 USED
          STA  X2-1,X
          DEX           ;ADVANCE INDEX TO NEXT BYTE
          BNE  SWAP1    ;LOOP UNTIL DONE.
          RTS           ;RETURN
FLOAT     LDA  #$8E     ;INIT EXP1 TO 14,
          STA  X1       ;THEN NORMALIZE TO FLOAT.
NORM1     LDA  M1       ;HIGH-ORDER MANT1 BYTE.
          CMP  #$C0     ;UPPER TWO BITS UNEQUAL?
          BMI  RTS1     ;YES, RETURN WITH MANT1 NORMALIZED
          DEC  X1       ;DECREMENT EXP1.
          ASL  M1+2
          ROL  M1+1     ;SHIFT MANT1 (3 BYTES) LEFT.
          ROL  M1
NORM      LDA  X1       ;EXP1 ZERO?
          BNE  NORM1    ;NO, CONTINUE NORMALIZING.
RTS1      RTS           ;RETURN.
FSUB      JSR  FCOMPL   ;CMPL MANT1,CLEARS CARRY UNLESS 0
SWPALGN   JSR  ALGNSWP  ;RIGHT SHIFT MANT1 OR SWAP WITH
FADD      LDA  X2
          CMP  X1       ;COMPARE EXP1 WITH EXP2.
          BNE  SWPALGN  ;IF #,SWAP ADDENDS OR ALIGN MANTS.
          JSR  ADD      ;ADD ALIGNED MANTISSAS.
ADDEND    BVC  NORM     ;NO OVERFLOW, NORMALIZE RESULT.
          BVS  RTLOG    ;OV: SHIFT M1 RIGHT, CARRY INTO SIGN
ALGNSWP   BCC  SWAP     ;SWAP IF CARRY CLEAR,
;*       ELSE SHIFT RIGHT ARITH.
RTAR      LDA  M1       ;SIGN OF MANT1 INTO CARRY FOR
          ASL  A        ;RIGHT ARITH SHIFT.
RTLOG     INC  X1       ;INCR X1 TO ADJUST FOR RIGHT SHIFT
          BEQ  OVFL     ;EXP1 OUT OF RANGE.
RTLOG1    LDX  #$FA     ;INDEX FOR 6:BYTE RIGHT SHIFT.
ROR1      ROR  E+3,X
          INX           ;NEXT BYTE OF SHIFT.
          BNE  ROR1     ;LOOP UNTIL DONE.
          RTS           ;RETURN.
FMUL      JSR  MD1      ;ABS VAL OF MANT1, MANT2
          ADC  X1       ;ADD EXP1 TO EXP2 FOR PRODUCT EXP
          JSR  MD2      ;CHECK PROD. EXP AND PREP. FOR MUL
          CLC           ;CLEAR CARRY FOR FIRST BIT.
MUL1      JSR  RTLOG1   ;M1 AND E RIGHT (PROD AND MPLIER)
          BCC  MUL2     ;IF CARRY CLEAR, SKIP PARTIAL PROD
          JSR  ADD      ;ADD MULTIPLICAND TO PRODUCT.
MUL2      DEY           ;NEXT MUL ITERATION.
          BPL  MUL1     ;LOOP UNTIL DONE.
MDEND     LSR  SIGN     ;TEST SIGN LSB.
NORMX     BCC  NORM     ;IF EVEN,NORMALIZE PROD,ELSE COMP
FCOMPL    SEC           ;SET CARRY FOR SUBTRACT.
          LDX  #$3      ;INDEX FOR 3 BYTE SUBTRACT.
COMPL1    LDA  #$0      ;CLEAR A.
          SBC  X1,X     ;SUBTRACT BYTE OF EXP1.
          STA  X1,X     ;RESTORE IT.
          DEX           ;NEXT MORE SIGNIFICANT BYTE.
          BNE  COMPL1   ;LOOP UNTIL DONE.
          BEQ  ADDEND   ;NORMALIZE (OR SHIFT RT IF OVFL).
FDIV      JSR  MD1      ;TAKE ABS VAL OF MANT1, MANT2.
          SBC  X1       ;SUBTRACT EXP1 FROM EXP2.
          JSR  MD2      ;SAVE AS QUOTIENT EXP.
DIV1      SEC           ;SET CARRY FOR SUBTRACT.
          LDX  #$2      ;INDEX FOR 3-BYTE SUBTRACTION.
DIV2      LDA  M2,X
          SBC  E,X      ;SUBTRACT A BYTE OF E FROM MANT2.
          PHA           ;SAVE ON STACK.
          DEX           ;NEXT MORE SIGNIFICANT BYTE.
          BPL  DIV2     ;LOOP UNTIL DONE.
          LDX  #$FD     ;INDEX FOR 3-BYTE CONDITIONAL MOVE
DIV3      PLA           ;PULL BYTE OF DIFFERENCE OFF STACK
          BCC  DIV4     ;IF M2<E THEN DON'T RESTORE M2.
          STA  M2+3,X
DIV4      INX           ;NEXT LESS SIGNIFICANT BYTE.
          BNE  DIV3     ;LOOP UNTIL DONE.
          ROL  M1+2
          ROL  M1+1     ;ROLL QUOTIENT LEFT, CARRY INTO LSB
          ROL  M1
          ASL  M2+2
          ROL  M2+1     ;SHIFT DIVIDEND LEFT
          ROL  M2
          BCS  OVFL     ;OVFL IS DUE TO UNNORMED DIVISOR
          DEY           ;NEXT DIVIDE ITERATION.
          BNE  DIV1     ;LOOP UNTIL DONE 23 ITERATIONS.
          BEQ  MDEND    ;NORM. QUOTIENT AND CORRECT SIGN.
MD2       STX  M1+2
          STX  M1+1     ;CLEAR MANT1 (3 BYTES) FOR MUL/DIV.
          STX  M1
          BCS  OVCHK    ;IF CALC. SET CARRY,CHECK FOR OVFL
          BMI  MD3      ;IF NEG THEN NO UNDERFLOW.
          PLA           ;POP ONE RETURN LEVEL.
          PLA
          BCC  NORMX    ;CLEAR X1 AND RETURN.
MD3       EOR  #$80     ;COMPLEMENT SIGN BIT OF EXPONENT.
          STA  X1       ;STORE IT.
          LDY  #$17     ;COUNT 24 MUL/23 DIV ITERATIONS.
          RTS           ;RETURN.
OVCHK     BPL  MD3      ;IF POSITIVE EXP THEN NO OVFL.
OVFL      JMP  OVLOC
          ORG  $F63D
FIX1      JSR  RTAR
FIX       LDA  X1
          BPL  UNDFL
          CMP  #$8E
          BNE  FIX1
          BIT  M1
          BPL  FIXRTS
          LDA  M1+2
          BEQ  FIXRTS
          INC  M1+1
          BNE  FIXRTS
          INC  M1
FIXRTS    RTS
UNDFL     LDA  #$0
          STA  M1
          STA  M1+1
          RTS
