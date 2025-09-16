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


; sbc (zp,x)

	lda	#mem
	sta	zp+1
	lda	#mem>>8
	sta	zp+2
	lda	#3
	sta	mem
	lda	#5
	ldx	#1
	sec
	sbc	(zp,x)
	cmp	#2
	beq	$+5
	jmp	fail

; sbc zp

	lda	#3
	sta	zp
	lda	#5
	sec
	sbc	zp
	cmp	#2
	beq	$+5
	jmp	fail

; sbc #imm

	lda	#5
	sec
	sbc	#3
	cmp	#2
	beq	$+5
	jmp	fail

; sbc abs

	lda	#3
	sta	mem
	lda	#5
	sec
	sbc	mem
	cmp	#2
	beq	$+5
	jmp	fail

; sbc (zp),y

	lda	#mem
	sta	zp
	lda	#mem>>8
	sta	zp+1
	lda	#3
	sta	mem+1
	ldy	#1
	lda	#5
	sec
	sbc	(zp),y
	cmp	#2
	beq	$+5
	jmp	fail

; sbc zp,x

	lda	#3
	sta	zp+2
	ldx	#2
	lda	#5
	sec
	sbc	zp,x
	cmp	#2
	beq	$+5
	jmp	fail

; sbc abs,y

	lda	#3
	sta	mem+4
	ldy	#4
	lda	#5
	sec
	sbc	mem,y
	cmp	#2
	beq	$+5
	jmp	fail

; sbc abs,x

	lda	#3
	sta	mem+5
	ldx	#5
	lda	#5
	sec
	sbc	mem,x
	cmp	#2
	beq	$+5
	jmp	fail

; sta (zp,x)

	lda	#mem
	sta	zp+1
	lda	#mem>>8
	sta	zp+2
	ldx	#1
	lda	#15
	sta	(zp,x)
	lda	mem
	cmp	#15
	beq	$+5
	jmp	fail

; sta zp

	lda	#17
	sta	zp
	lda	#0
	lda	zp
	cmp	#17
	beq	$+5
	jmp	fail

; sta abs

	lda	#18
	sta	mem
	lda	#0
	lda	mem
	cmp	#18
	beq	$+5
	jmp	fail

; sta (zp),y

	lda	#mem
	sta	zp
	lda	#mem>>8
	sta	zp+1
	ldy	#5
	lda	#19
	sta	(zp),y
	lda	#0
	lda	mem+5
	cmp	#19
	beq	$+5
	jmp	fail

; sta zp,x

	lda	#20
	ldx	#5
	sta	zp,x
	lda	#0
	lda	zp+5
	cmp	#20
	beq	$+5
	jmp	fail

; sta abs,y

	lda	#21
	ldy	#1
	sta	mem,y
	lda	#0
	lda	mem+1
	cmp	#21
	beq	$+5
	jmp	fail

; sta abs,x

	lda	#22
	ldx	#3
	sta	mem,x
	lda	#0
	lda	mem+3
	cmp	#22
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
