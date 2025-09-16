putc	equ	$fff0
halt	equ	$fff1
zp	equ	$10

; ora (zp,x)

	lda	#mem
	sta	zp+1
	lda	#mem>>8
	sta	zp+2
	lda	#3
	sta	mem
	lda	#5
	ldx	#1
	ora	(zp,x)
	cmp	#7
	beq	$+5
	jmp	fail

; ora zp

	lda	#3
	sta	zp
	lda	#5
	ora	zp
	cmp	#7
	beq	$+5
	jmp	fail

; ora #imm

	lda	#3
	ora	#5
	cmp	#7
	beq	$+5
	jmp	fail

; ora abs

	lda	#3
	sta	mem
	lda	#5
	ora	mem
	cmp	#7
	beq	$+5
	jmp	fail

; ora (zp),y

	lda	#mem
	sta	zp
	lda	#mem>>8
	sta	zp+1
	lda	#3
	sta	mem+1
	ldy	#1
	lda	#5
	ora	(zp),y
	cmp	#7
	beq	$+5
	jmp	fail

; ora zp,x

	lda	#3
	sta	zp+2
	ldx	#2
	lda	#5
	ora	zp,x
	cmp	#7
	beq	$+5
	jmp	fail

; ora abs,y

	lda	#3
	sta	mem+4
	ldy	#4
	lda	#5
	ora	mem,y
	cmp	#7
	beq	$+5
	jmp	fail

; ora abs,x

	lda	#3
	sta	mem+5
	ldx	#5
	lda	#5
	ora	mem,x
	cmp	#7
	beq	$+5
	jmp	fail

; and (zp,x)

	lda	#mem
	sta	zp+1
	lda	#mem>>8
	sta	zp+2
	lda	#3
	sta	mem
	lda	#5
	ldx	#1
	and	(zp,x)
	cmp	#1
	beq	$+5
	jmp	fail

; and zp

	lda	#3
	sta	zp
	lda	#5
	and	zp
	cmp	#1
	beq	$+5
	jmp	fail

; and #imm

	lda	#3
	and	#5
	cmp	#1
	beq	$+5
	jmp	fail

; and abs

	lda	#3
	sta	mem
	lda	#5
	and	mem
	cmp	#1
	beq	$+5
	jmp	fail

; and (zp),y

	lda	#mem
	sta	zp
	lda	#mem>>8
	sta	zp+1
	lda	#3
	sta	mem+1
	ldy	#1
	lda	#5
	and	(zp),y
	cmp	#1
	beq	$+5
	jmp	fail

; and zp,x

	lda	#3
	sta	zp+2
	ldx	#2
	lda	#5
	and	zp,x
	cmp	#1
	beq	$+5
	jmp	fail

; and abs,y

	lda	#3
	sta	mem+4
	ldy	#4
	lda	#5
	and	mem,y
	cmp	#1
	beq	$+5
	jmp	fail

; and abs,x

	lda	#3
	sta	mem+5
	ldx	#5
	lda	#5
	and	mem,x
	cmp	#1
	beq	$+5
	jmp	fail

; eor (zp,x)

	lda	#mem
	sta	zp+1
	lda	#mem>>8
	sta	zp+2
	lda	#3
	sta	mem
	lda	#5
	ldx	#1
	eor	(zp,x)
	cmp	#6
	beq	$+5
	jmp	fail

; eor zp

	lda	#3
	sta	zp
	lda	#5
	eor	zp
	cmp	#6
	beq	$+5
	jmp	fail

; eor #imm

	lda	#3
	eor	#5
	cmp	#6
	beq	$+5
	jmp	fail

; eor abs

	lda	#3
	sta	mem
	lda	#5
	eor	mem
	cmp	#6
	beq	$+5
	jmp	fail

; eor (zp),y

	lda	#mem
	sta	zp
	lda	#mem>>8
	sta	zp+1
	lda	#3
	sta	mem+1
	ldy	#1
	lda	#5
	eor	(zp),y
	cmp	#6
	beq	$+5
	jmp	fail

; eor zp,x

	lda	#3
	sta	zp+2
	ldx	#2
	lda	#5
	eor	zp,x
	cmp	#6
	beq	$+5
	jmp	fail

; eor abs,y

	lda	#3
	sta	mem+4
	ldy	#4
	lda	#5
	eor	mem,y
	cmp	#6
	beq	$+5
	jmp	fail

; eor abs,x

	lda	#3
	sta	mem+5
	ldx	#5
	lda	#5
	eor	mem,x
	cmp	#6
	beq	$+5
	jmp	fail

; adc (zp,x)

	lda	#mem
	sta	zp+1
	lda	#mem>>8
	sta	zp+2
	lda	#3
	sta	mem
	lda	#5
	ldx	#1
	clc
	adc	(zp,x)
	cmp	#8
	beq	$+5
	jmp	fail

; adc zp

	lda	#3
	sta	zp
	lda	#5
	sec
	adc	zp
	cmp	#9
	beq	$+5
	jmp	fail

; adc #imm

	lda	#3
	clc
	adc	#5
	cmp	#8
	beq	$+5
	jmp	fail

; adc abs

	lda	#3
	sta	mem
	lda	#5
	sec
	adc	mem
	cmp	#9
	beq	$+5
	jmp	fail

; adc (zp),y

	lda	#mem
	sta	zp
	lda	#mem>>8
	sta	zp+1
	lda	#3
	sta	mem+1
	ldy	#1
	lda	#5
	clc
	adc	(zp),y
	cmp	#8
	beq	$+5
	jmp	fail

; adc zp,x

	lda	#3
	sta	zp+2
	ldx	#2
	lda	#5
	sec
	adc	zp,x
	cmp	#9
	beq	$+5
	jmp	fail

; adc abs,y

	lda	#3
	sta	mem+4
	ldy	#4
	lda	#5
	clc
	adc	mem,y
	cmp	#8
	beq	$+5
	jmp	fail

; adc abs,x

	lda	#3
	sta	mem+5
	ldx	#5
	lda	#5
	sec
	adc	mem,x
	cmp	#9
	beq	$+5
	jmp	fail






pass	lda	str1
	sta	putc
	sta	halt

fail	lda	str2
	sta	putc
	sta	halt

str1	byte	"pass"
str2	byte	"fail"

mem	equ	$
