; Kahan's Floating Point Test "Paranoia" (under construction)

vars	equ	$400
start	equ	$500

	org	start
	jmp	main

	org	0		; page offsets for "vars", not zero page

B	bss	4
E0	bss	4
E1	bss	4
E3	bss	4
E9	bss	4
F1	bss	4		; F1=-1
F2	bss	4		; F2=1/2
F3	bss	4
F6	bss	4
F9	bss	4
O	bss	4		; O=0
O1	bss	4		; O1=1
O2	bss	4		; O2=2
O3	bss	4		; O3=3
O4	bss	4		; O4=4
O8	bss	4		; O8=8
O9	bss	4		; O9=9
P	bss	4
T	bss	4
T2	bss	4		; T2=32
U1	bss	4
U2	bss	4
W	bss	4
X	bss	4
Y	bss	4
Z	bss	4

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
SIGN      EQU  $F3
X2        EQU  $F4
M2        EQU  $F5
X1        EQU  $F8
M1        EQU  $F9
E         EQU  $FC
OVLOC     EQU  $3F5
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
;;;;;

fadd	equ	FADD
fsub	equ	FSUB
fmul	equ	FMUL
fdiv	equ	FDIV
fcompl	equ	FCOMPL
fix	equ	FIX
float	equ	FLOAT

;;;;;

	org	0

t	bss	2

	org	OVLOC

	jmp	ferr

	org	start+3

okstr	db	"ok",10,0
errstr	db	"err $",0
str1160	db	"Searching for radix  B  and precision  P ; ",0
str1230	db	" Radix  B = ",0
str1270	db	"Closest relative separation found is  U1 =",0
str1280	db	"Recalculating radix and precision ",0
str1380	db	" confirms closest relative separation  U1 .",10,0
str1390	db	" gets better closest relative separation  U1 = ",0
str1410	db	"Radix  B  confirmed.",10,0
str1420	db	"MYSTERY: recalculated radix  B = ",0

exit	equ	$fff0
putc	equ	$fff1
print	equ	$fff2

ok	jsr	print
	dw	okstr
	jsr	exit

err	jsr	print
	dw	errstr
	pla			; print address
	sta	t
	pla
	sta	t+1
	sec
	lda	t
	sbc	#2
	sta	t
	lda	t+1
	sbc	#0
	jsr	print1
	lda	t
	jsr	print1
	lda	#10
	jsr	putc
	jsr	exit

print4	lda	vars,x
	jsr	print1
	lda	vars+1,x
	jsr	print1
	lda	vars+2,x
	jsr	print1
	lda	vars+3,x
	jsr	print1
	lda	#10
	jsr	putc
	rts

print1	pha
	lsr	a
	lsr	a
	lsr	a
	lsr	a
	cmp	#10
	bcc	$+4
	adc	#6
	adc	#"0"
	jsr	putc
	pla
	and	#$f
	cmp	#10
	bcc	$+4
	adc	#6
	adc	#"0"
	jsr	putc
	rts

ftest	lda	M1
	bpl	ftest1
	lda	#-1
	rts
ftest1	ora	M1+1
	ora	M1+2
	ora	X1
	beq	ftest2
	lda	#1
ftest2	rts

floata	sta	M1+1
	lda	#0
	sta	M1
	sta	M1+2
	jsr	float
	rts

fload1	lda	vars,x
	sta	X1
	lda	vars+1,x
	sta	M1
	lda	vars+2,x
	sta	M1+1
	lda	vars+3,x
	sta	M1+2
	rts

fload2	lda	vars,x
	sta	X2
	lda	vars+1,x
	sta	M2
	lda	vars+2,x
	sta	M2+1
	lda	vars+3,x
	sta	M2+2
	rts

fsave	lda	X1
	sta	vars,x
	lda	M1
	sta	vars+1,x
	lda	M1+1
	sta	vars+2,x
	lda	M1+2
	sta	vars+3,x
	rts

fabs	lda	M1
	bpl	fabs1
	jsr	fcompl
fabs1	rts

ferr	jsr	print
	dw	ferr1
	jsr	exit

ferr1	db	"OVLOC",10,0

;;;;;

main	lda	#0		; O=0
	jsr	floata
	ldx	#O
	jsr	fsave

	lda	#1		; O1=1
	jsr	floata
	ldx	#O1
	jsr	fsave

	lda	#2		; O2=2
	jsr	floata
	ldx	#O2
	jsr	fsave

	lda	#3		; O3=3
	jsr	floata
	ldx	#O3
	jsr	fsave

	lda	#4		; O4=4
	jsr	floata
	ldx	#O4
	jsr	fsave

	lda	#8		; O8=8
	jsr	floata
	ldx	#O8
	jsr	fsave

	lda	#9		; O9=9
	jsr	floata
	ldx	#O9
	jsr	fsave

	lda	#32		; T2=32
	jsr	floata
	ldx	#T2
	jsr	fsave

	ldx	#O1		; F1=-O1
	jsr	fload1
	jsr	fcompl
	ldx	#F1
	jsr	fsave

	ldx	#O1		; F2=1/2
	jsr	fload2
	ldx	#O2
	jsr	fload1
	jsr	fdiv
	ldx	#F2
	jsr	fsave

;1160 PRINT "Searching for radix  B  and precision  P ; ";

L1160	jsr	print
	dw	str1160

;1170 W=O1

L1170	ldx	#O1
	jsr	fload1
	ldx	#W
	jsr	fsave

;1180 W=W+W : Y=W+O1 : Z=Y-W : Y=Z-O1 : IF (F1+ABS(Y)<O) THEN 1180

L1180	ldx	#W		; W=W+W
	jsr	fload1
	ldx	#W
	jsr	fload2
	jsr	fadd
	ldx	#W
	jsr	fsave

	ldx	#W		; Y=W+O1
	jsr	fload1
	ldx	#O1
	jsr	fload2
	jsr	fadd
	ldx	#Y
	jsr	fsave

	ldx	#Y		; Z=Y-W
	jsr	fload2
	ldx	#W
	jsr	fload1
	jsr	fsub
	ldx	#Z
	jsr	fsave

	ldx	#Z		; Y=Z-O1
	jsr	fload2
	ldx	#O1
	jsr	fload1
	jsr	fsub
	ldx	#Y
	jsr	fsave

	ldx	#Y		; IF (F1+ABS(Y)<O) THEN 1180
	jsr	fload1
	jsr	fabs
	ldx	#F1
	jsr	fload2
	jsr	fadd
	ldx	#T
	jsr	fsave
	ldx	#T
	jsr	fload2
	ldx	#O
	jsr	fload1
	jsr	fsub
	jsr	ftest
	bmi	L1180

;1200 P=O :  Y=O1

L1200	ldx	#O		; P=O
	jsr	fload1
	ldx	#P
	jsr	fsave

	ldx	#O1		; Y=O1
	jsr	fload1
	ldx	#Y
	jsr	fsave

;1210 B=W+Y : Y=Y+Y : B=B-W : IF (B=O) THEN 1210

L1210	ldx	#W		; B=W+Y
	jsr	fload1
	ldx	#Y
	jsr	fload2
	jsr	fadd
	ldx	#B
	jsr	fsave

	ldx	#Y		; Y=Y+Y
	jsr	fload1
	ldx	#Y
	jsr	fload2
	jsr	fadd
	ldx	#Y
	jsr	fsave

	ldx	#B		; B=B-W
	jsr	fload2
	ldx	#W
	jsr	fload1
	jsr	fsub
	ldx	#B
	jsr	fsave

	ldx	#B		; IF (B=O) THEN 1210
	jsr	fload2
	ldx	#O
	jsr	fload1
	jsr	fsub
	jsr	ftest
	beq	L1210

;1220 IF (B<O2) THEN B=O1

L1220	ldx	#B		; IF (B<O2) THEN B=O1
	jsr	fload2
	ldx	#O2
	jsr	fload1
	jsr	fsub
	jsr	ftest
	bpl	L1230
	ldx	#O1
	jsr	fload1
	ldx	#B
	jsr	fsave

;1230 PRINT " Radix  B = "; B : IF (B=O1) THEN 1270

L1230	jsr	print		; PRINT " Radix  B = "; B
	dw	str1230
	ldx	#B
	jsr	print4

	ldx	#B		; IF (B=O1) THEN 1270
	jsr	fload2
	ldx	#O1
	jsr	fload1
	jsr	fsub
	jsr	ftest
	beq	L1270

;1240 W=O1

L1240	ldx	#O1
	jsr	fload1
	ldx	#W
	jsr	fsave

;1250 P=P+O1 : W=W*B : Y=W+O1 : Z=Y-W : IF (Z=O1) THEN 1250

L1250	ldx	#P		; P=P+O1
	jsr	fload1
	ldx	#O1
	jsr	fload2
	jsr	fadd
	ldx	#P
	jsr	fsave

	ldx	#W		; W=W*B
	jsr	fload1
	ldx	#B
	jsr	fload2
	jsr	fmul
	ldx	#W
	jsr	fsave

	ldx	#W		; Y=W+O1
	jsr	fload1
	ldx	#O1
	jsr	fload2
	jsr	fadd
	ldx	#Y
	jsr	fsave

	ldx	#Y		; Z=Y-W
	jsr	fload2
	ldx	#W
	jsr	fload1
	jsr	fsub
	ldx	#Z
	jsr	fsave

	ldx	#Z		; IF (Z=O1) THEN 1250
	jsr	fload2
	ldx	#O1
	jsr	fload1
	jsr	fsub
	jsr	ftest
	beq	L1250

;1270 U1=O1/W : U2=B*U1 : PRINT "Closest relative separation found is  U1 ="; U1

L1270	ldx	#O1		; U1=O1/W
	jsr	fload2
	ldx	#W
	jsr	fload1
	jsr	fdiv
	ldx	#U1
	jsr	fsave

	ldx	#B		; U2=B*U1
	jsr	fload1
	ldx	#U1
	jsr	fload2
	jsr	fmul
	ldx	#U2
	jsr	fsave

	jsr	print		; PRINT "Closest relative separation found is  U1 ="; U1
	dw	str1270
	ldx	#U1
	jsr	print4

;1280 PRINT : PRINT "Recalculating radix and precision ";

L1280	jsr	print
	dw	str1280

;1290 E0=B : E1=U1 : E9=U2 : E3=P

L1290	ldx	#B		; E0=B
	jsr	fload1
	ldx	#E0
	jsr	fsave

	ldx	#U1		; E1=U1
	jsr	fload1
	ldx	#E1
	jsr	fsave

	ldx	#U2		; E9=U2
	jsr	fload1
	ldx	#E9
	jsr	fsave

	ldx	#P		; E3=P
	jsr	fload1
	ldx	#E3
	jsr	fsave

;1300 X=O4/O3 : F3=X-O1 : F6=F2-F3 : X=F6+F6 : X=ABS(X-F3) : IF (X<U2) THEN X=U2

L1300	ldx	#O4		; X=O4/O3
	jsr	fload2
	ldx	#O3
	jsr	fload1
	jsr	fdiv
	ldx	#X
	jsr	fsave

	ldx	#X		; F3=X-O1
	jsr	fload2
	ldx	#O1
	jsr	fload1
	jsr	fsub
	ldx	#F3
	jsr	fsave

	ldx	#F2		; F6=F2-F3
	jsr	fload2
	ldx	#F3
	jsr	fload1
	jsr	fsub
	ldx	#F6
	jsr	fsave

	ldx	#F6		; X=F6+F6
	jsr	fload1
	ldx	#F6
	jsr	fload2
	jsr	fadd
	ldx	#X
	jsr	fsave

	ldx	#X		; X=ABS(X-F3)
	jsr	fload2
	ldx	#F3
	jsr	fload1
	jsr	fsub
	jsr	fabs
	ldx	#X
	jsr	fsave

	ldx	#X		; IF (X<U2) THEN X=U2
	jsr	fload2
	ldx	#U2
	jsr	fload1
	jsr	fsub
	jsr	ftest
	bpl	L1320
	ldx	#U2
	jsr	fload1
	ldx	#X
	jsr	fsave

;1320 U2=X : Y=F2*U2+T2*U2*U2 : Y=O1+Y : X=Y-O1 : IF (U2>X AND X>O) THEN 1320

L1320	ldx	#X		; U2=X
	jsr	fload1
	ldx	#U2
	jsr	fsave

	ldx	#F2		; Y=F2*U2+T2*U2*U2
	jsr	fload1
	ldx	#U2
	jsr	fload2
	jsr	fmul
	ldx	#T
	jsr	fsave
	ldx	#T2
	jsr	fload1
	ldx	#U2
	jsr	fload2
	jsr	fmul
	ldx	#U2
	jsr	fload2
	jsr	fmul
	ldx	#T
	jsr	fload2
	jsr	fadd
	ldx	#Y
	jsr	fsave

	ldx	#O1		; Y=O1+Y
	jsr	fload1
	ldx	#Y
	jsr	fload2
	jsr	fadd
	ldx	#Y
	jsr	fsave

	ldx	#Y		; X=Y-O1
	jsr	fload2
	ldx	#O1
	jsr	fload1
	jsr	fsub
	ldx	#X
	jsr	fsave

	ldx	#U2		; IF (U2>X AND X>O) THEN 1320
	jsr	fload2
	ldx	#X
	jsr	fload1
	jsr	fsub
	jsr	ftest
	bmi	L1340
	beq	L1340
	ldx	#X
	jsr	fload2
	ldx	#O
	jsr	fload1
	jsr	fsub
	jsr	ftest
	bmi	L1340
	beq	L1340
	jmp	L1320

;1340 X=O2/O3 : F6=X-F2 : F3=F6+F6 : X=F3-F2 : X=ABS(X+F6) : IF (X<U1) THEN X=U1

L1340	ldx	#O2		; X=O2/O3
	jsr	fload2
	ldx	#O3
	jsr	fload1
	jsr	fdiv
	ldx	#X
	jsr	fsave

	ldx	#X		; F6=X-F2
	jsr	fload2
	ldx	#F2
	jsr	fload1
	jsr	fsub
	ldx	#F6
	jsr	fsave

	ldx	#F6		; F3=F6+F6
	jsr	fload1
	ldx	#F6
	jsr	fload2
	jsr	fadd
	ldx	#F3
	jsr	fsave

	ldx	#F3		; X=F3-F2
	jsr	fload2
	ldx	#F2
	jsr	fload1
	jsr	fsub
	ldx	#X
	jsr	fsave

	ldx	#X		; X=ABS(X+F6)
	jsr	fload1
	ldx	#F6
	jsr	fload2
	jsr	fadd
	jsr	fabs
	ldx	#X
	jsr	fsave

	ldx	#X		; IF (X<U1) THEN X=U1
	jsr	fload2
	ldx	#U1
	jsr	fload1
	jsr	fsub
	jsr	ftest
	bpl	L1360
	ldx	#U1
	jsr	fload1
	ldx	#X
	jsr	fsave

;1360 U1=X : Y=F2*U1+T2*U1*U1 : Y=F2-Y : X=F2+Y : Y=F2-X : X=F2+Y : IF (U1>X AND X>O) THEN 1360

L1360	ldx	#X		; U1=X
	jsr	fload1
	ldx	#U1
	jsr	fsave

	ldx	#F2		; Y=F2*U1+T2*U1*U1
	jsr	fload1
	ldx	#U1
	jsr	fload2
	jsr	fmul
	ldx	#T
	jsr	fsave
	ldx	#T2
	jsr	fload1
	ldx	#U1
	jsr	fload2
	jsr	fmul
	ldx	#U1
	jsr	fload2
	jsr	fmul
	ldx	#T
	jsr	fload2
	jsr	fadd
	ldx	#Y
	jsr	fsave

	ldx	#F2		; Y=F2-Y
	jsr	fload2
	ldx	#Y
	jsr	fload1
	jsr	fsub
	ldx	#Y
	jsr	fsave

	ldx	#F2		; X=F2+Y
	jsr	fload1
	ldx	#Y
	jsr	fload2
	jsr	fadd
	ldx	#X
	jsr	fsave

	ldx	#F2		; Y=F2-X
	jsr	fload2
	ldx	#X
	jsr	fload1
	jsr	fsub
	ldx	#Y
	jsr	fsave

	ldx	#F2		; X=F2+Y
	jsr	fload1
	ldx	#Y
	jsr	fload2
	jsr	fadd
	ldx	#X
	jsr	fsave

	ldx	#U1		; IF (U1>X AND X>O) THEN 1360
	jsr	fload2
	ldx	#X
	jsr	fload1
	jsr	fsub
	jsr	ftest
	bmi	L1380
	beq	L1380
	ldx	#X
	jsr	fload2
	ldx	#O
	jsr	fload1
	jsr	fsub
	jsr	ftest
	bmi	L1380
	beq	L1380
	jmp	L1360

;1380 IF (U1=E1) THEN PRINT " confirms closest relative separation  U1 ."

L1380	ldx	#U1
	jsr	fload2
	ldx	#E1
	jsr	fload1
	jsr	fsub
	jsr	ftest
	bne	L1390
	jsr	print
	dw	str1380

;1390 IF (U1><E1) THEN PRINT " gets better closest relative separation  U1 = "; U1

L1390	ldx	#U1
	jsr	fload2
	ldx	#E1
	jsr	fload1
	jsr	fsub
	jsr	ftest
	beq	L1400
	jsr	print
	dw	str1390
	ldx	#U1
	jsr	print4

;1400 W=O1/U1 : F9=(F2-U1)+F2

L1400	ldx	#O1		; W=O1/U1
	jsr	fload2
	ldx	#U1
	jsr	fload1
	jsr	fdiv
	ldx	#W
	jsr	fsave

	ldx	#F2		; F9=(F2-U1)+F2
	jsr	fload2
	ldx	#U1
	jsr	fload1
	jsr	fsub
	ldx	#F2
	jsr	fload2
	jsr	fadd
	ldx	#F9
	jsr	fsave

;1410 B=INT(.01 + U2/U1) : IF (B=E0) THEN PRINT "Radix  B  confirmed."

L1410	lda	#100		; B=INT(.01 + U2/U1)
	jsr	floata
	ldx	#T
	jsr	fsave
	ldx	#O1
	jsr	fload2
	ldx	#T
	jsr	fload1
	jsr	fdiv
	ldx	#T
	jsr	fsave
	ldx	#U2
	jsr	fload2
	ldx	#U1
	jsr	fload1
	jsr	fdiv
	ldx	#T
	jsr	fload2
	jsr	fadd
	jsr	fix
	lda	#0
	sta	M1+2
	jsr	float
	ldx	#B
	jsr	fsave

	ldx	#B		; IF (B=E0) THEN PRINT "Radix  B  confirmed."
	jsr	fload2
	ldx	#E0
	jsr	fload1
	jsr	fsub
	jsr	ftest
	bne	L1420
	jsr	print
	dw	str1410

;1420 IF (B><E0) THEN PRINT "MYSTERY: recalculated radix  B = "; B

L1420	ldx	#B
	jsr	fload2
	ldx	#E0
	jsr	fload1
	jsr	fsub
	jsr	ftest
	beq	L1430
	jsr	print
	dw	str1420
	ldx	#B
	jsr	print4

L1430

	jmp	ok
