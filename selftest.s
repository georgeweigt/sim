halt	equ	$fff0
putc	equ	$fff1
puts	equ	$fff2

zp	equ	0

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

; lda (zp,x)

	lda	#mem
	sta	zp+1
	lda	#mem>>8
	sta	zp+2
	lda	#23
	sta	mem
	lda	#0
	ldx	#1
	lda	(zp,x)
	cmp	#23
	beq	$+5
	jmp	fail

; lda zp

	lda	#24
	sta	zp
	lda	#0
	lda	zp
	cmp	#24
	beq	$+5
	jmp	fail

; lda #imm

	lda	#25
	cmp	#25
	beq	$+5
	jmp	fail

; lda abs

	lda	#26
	sta	mem
	lda	#0
	lda	mem
	cmp	#26
	beq	$+5
	jmp	fail

; lda (zp),y

	lda	#mem
	sta	zp
	lda	#mem>>8
	sta	zp+1
	lda	#27
	sta	mem+7
	lda	#0
	ldy	#7
	lda	(zp),y
	cmp	#27
	beq	$+5
	jmp	fail

; lda zp,x

	lda	#28
	sta	zp+9
	lda	#0
	ldx	#9
	lda	zp,x
	cmp	#28
	beq	$+5
	jmp	fail

; lda abs,y

	lda	#29
	sta	mem+10
	lda	#0
	ldy	#10
	lda	mem,y
	cmp	#29
	beq	$+5
	jmp	fail

; lda abs,x

	lda	#30
	sta	mem+11
	lda	#0
	ldx	#11
	lda	mem,x
	cmp	#30
	beq	$+5
	jmp	fail

; cmp (zp,x)

	lda	#mem
	sta	zp+1
	lda	#mem>>8
	sta	zp+2
	lda	#31
	sta	mem
	ldx	#1
	cmp	(zp,x)
	beq	$+5
	jmp	fail

; cmp zp

	lda	#32
	sta	zp
	cmp	zp
	beq	$+5
	jmp	fail

; cmp #imm

	lda	#33
	cmp	#33
	beq	$+5
	jmp	fail

; cmp abs

	lda	#34
	sta	mem
	cmp	mem
	beq	$+5
	jmp	fail

; cmp (zp),y

	lda	#mem
	sta	zp
	lda	#mem>>8
	sta	zp+1
	lda	#35
	sta	mem+3
	ldy	#3
	cmp	(zp),y
	beq	$+5
	jmp	fail

; cmp zp,x

	lda	#36
	sta	zp+4
	ldx	#4
	cmp	zp,x
	beq	$+5
	jmp	fail

; cmp abs,y

	lda	#37
	sta	mem+8
	ldy	#8
	cmp	mem,y
	beq	$+5
	jmp	fail

; cmp abs,x

	lda	#38
	sta	mem+7
	ldx	#7
	cmp	mem,x
	beq	$+5
	jmp	fail

; asl zp

	lda	#4
	sta	zp
	asl	zp
	lda	zp
	cmp	#8
	beq	$+5
	jmp	fail

; asl a

	lda	#4
	asl	a
	cmp	#8
	beq	$+5
	jmp	fail

; asl abs

	lda	#4
	sta	mem
	asl	mem
	lda	mem
	cmp	#8
	beq	$+5
	jmp	fail

; asl zp,x

	lda	#4
	sta	zp+1
	ldx	#1
	asl	zp,x
	lda	zp+1
	cmp	#8
	beq	$+5
	jmp	fail

; asl abs,x

	lda	#4
	sta	mem+3
	ldx	#3
	asl	mem,x
	lda	mem+3
	cmp	#8
	beq	$+5
	jmp	fail

; rol zp

	lda	#4
	sta	zp
	clc
	rol	zp
	lda	zp
	cmp	#8
	beq	$+5
	jmp	fail

; rol a

	lda	#4
	clc
	rol	a
	cmp	#8
	beq	$+5
	jmp	fail

; rol abs

	lda	#4
	sta	mem
	clc
	rol	mem
	lda	mem
	cmp	#8
	beq	$+5
	jmp	fail

; rol zp,x

	lda	#4
	sta	zp+1
	ldx	#1
	clc
	rol	zp,x
	lda	zp+1
	cmp	#8
	beq	$+5
	jmp	fail

; rol abs,x

	lda	#4
	sta	mem+3
	ldx	#3
	clc
	rol	mem,x
	lda	mem+3
	cmp	#8
	beq	$+5
	jmp	fail

; lsr zp

	lda	#4
	sta	zp
	lsr	zp
	lda	zp
	cmp	#2
	beq	$+5
	jmp	fail

; lsr a

	lda	#4
	lsr	a
	cmp	#2
	beq	$+5
	jmp	fail

; lsr abs

	lda	#4
	sta	mem
	lsr	mem
	lda	mem
	cmp	#2
	beq	$+5
	jmp	fail

; lsr zp,x

	lda	#4
	sta	zp+1
	ldx	#1
	lsr	zp,x
	lda	zp+1
	cmp	#2
	beq	$+5
	jmp	fail

; lsr abs,x

	lda	#4
	sta	mem+3
	ldx	#3
	lsr	mem,x
	lda	mem+3
	cmp	#2
	beq	$+5
	jmp	fail

; ror zp

	lda	#4
	sta	zp
	clc
	ror	zp
	lda	zp
	cmp	#2
	beq	$+5
	jmp	fail

; ror a

	lda	#4
	clc
	ror	a
	cmp	#2
	beq	$+5
	jmp	fail

; ror abs

	lda	#4
	sta	mem
	clc
	ror	mem
	lda	mem
	cmp	#2
	beq	$+5
	jmp	fail

; ror zp,x

	lda	#4
	sta	zp+1
	ldx	#1
	clc
	ror	zp,x
	lda	zp+1
	cmp	#2
	beq	$+5
	jmp	fail

; ror abs,x

	lda	#4
	sta	mem+3
	ldx	#3
	clc
	ror	mem,x
	lda	mem+3
	cmp	#2
	beq	$+5
	jmp	fail

; stx zp

	lda	#0
	ldx	#57
	stx	zp
	lda	zp
	cmp	#57
	beq	$+5
	jmp	fail

; stx abs

	lda	#0
	ldx	#57
	stx	mem
	lda	mem
	cmp	#57
	beq	$+5
	jmp	fail

; stx zp,x (actually uses y)

	lda	#0
	ldx	#61
	ldy	#1
	stx	zp,x	; zp,x
	lda	zp+1
	cmp	#61
	beq	$+5
	jmp	fail

	lda	#0
	ldx	#62
	ldy	#1
	stx	zp,y	; zp,y
	lda	zp+1
	cmp	#62
	beq	$+5
	jmp	fail

; ldx #imm

	lda	#0
	ldx	#57
	stx	zp
	lda	zp
	cmp	#57
	beq	$+5
	jmp	fail

; ldx zp

	lda	#11
	sta	zp
	ldx	zp
	txa
	cmp	#11
	beq	$+5
	jmp	fail

; ldx abs

	lda	#21
	sta	mem
	lda	#0
	ldx	mem
	txa
	cmp	#21
	beq	$+5
	jmp	fail

; ldx zp,x (register y)

	lda	#22
	sta	zp+1
	ldy	#1
	ldx	zp,x
	lda	#0	
	txa
	cmp	#22
	beq	$+5
	jmp	fail

; ldx abs,x (register y)

	lda	#23
	sta	mem+3
	ldy	#3
	ldx	mem,x
	txa
	cmp	#23
	beq	$+5
	jmp	fail

; dec zp

	lda	#10
	sta	zp
	dec	zp
	lda	zp
	cmp	#9
	beq	$+5
	jmp	fail

; dec abs

	lda	#10
	sta	mem
	dec	mem
	lda	mem
	cmp	#9
	beq	$+5
	jmp	fail

; dec zp,x

	lda	#10
	sta	zp+1
	ldx	#1
	dec	zp,x
	lda	zp+1
	cmp	#9
	beq	$+5
	jmp	fail

; dec abs,x

	lda	#10
	sta	mem+1
	ldx	#1
	dec	mem,x
	lda	mem+1
	cmp	#9
	beq	$+5
	jmp	fail

; inc zp

	lda	#10
	sta	zp
	inc	zp
	lda	zp
	cmp	#11
	beq	$+5
	jmp	fail

; inc abs

	lda	#10
	sta	mem
	inc	mem
	lda	mem
	cmp	#11
	beq	$+5
	jmp	fail

; inc zp,x

	lda	#10
	sta	zp+1
	ldx	#1
	inc	zp,x
	lda	zp+1
	cmp	#11
	beq	$+5
	jmp	fail

; inc abs,x

	lda	#10
	sta	mem+1
	ldx	#1
	inc	mem,x
	lda	mem+1
	cmp	#11
	beq	$+5
	jmp	fail

; jsr

	jsr	y1
	beq	$+4
y1	nop
	rts

; jmp addr

	lda	#y2
	sta	mem
	lda	#y2>>8
	sta	mem+1
	jmp	(mem)
y2

; sty zp

	ldy	#9
	sty	zp
	lda	zp
	cmp	#9
	beq	$+5
	jmp	fail

; sty abs

	ldy	#11
	sty	mem
	lda	mem
	cmp	#11
	beq	$+5
	jmp	fail

; sty zp,x

	ldx	#1
	ldy	#9
	sty	zp,x
	lda	zp+1
	cmp	#9
	beq	$+5
	jmp	fail

; ldy #imm

	ldy	#1
	tya
	cmp	#1
	beq	$+5
	jmp	fail

; ldy zp

	lda	#7
	sta	zp
	lda	#0
	ldy	zp
	tya
	cmp	#7
	beq	$+5
	jmp	fail

; ldy abs

	lda	#5
	sta	mem
	lda	#0
	ldy	mem
	tya
	cmp	#5
	beq	$+5
	jmp	fail

; ldy zp,x

	lda	#11
	sta	zp+1
	lda	#0
	ldx	#1
	ldy	zp,x
	tya
	cmp	#11
	beq	$+5
	jmp	fail

; ldy abs,x

	lda	#12
	sta	mem+1
	lda	#0
	ldx	#1
	ldy	mem,x
	tya
	cmp	#12
	beq	$+5
	jmp	fail

; cpy #imm

	ldy	#5
	cpy	#5
	beq	$+5
	jmp	fail

; cpy zp

	ldy	#4
	lda	#4
	sta	zp
	cpy	zp
	beq	$+5
	jmp	fail

; cpy abs

	ldy	#9
	lda	#9
	sta	mem
	cpy	mem
	beq	$+5
	jmp	fail

; cpx #imm

	ldx	#5
	cpx	#5
	beq	$+5
	jmp	fail

; cpx zp

	ldx	#4
	lda	#4
	sta	zp
	cpx	zp
	beq	$+5
	jmp	fail

; cpx abs

	ldx	#9
	lda	#9
	sta	mem
	cpx	mem
	beq	$+5
	jmp	fail

; bpl

	lda	#1
	bpl	$+5
	jmp	fail

; bmi

	lda	#-1
	bmi	$+5
	jmp	fail

; bvc

	lda	#$7e
	clc
	adc	#1
	bvc	$+5
	jmp	fail

; bvs

	lda	#$7e
	sec
	adc	#1
	bvs	$+5
	jmp	fail

; bcc

	lda	#1
	clc
	adc	#$fe
	bcc	$+5
	jmp	fail

; bcs

	lda	#1
	sec
	adc	#$fe
	bcs	$+5
	jmp	fail

; bne

	lda	#1
	bne	$+5
	jmp	fail

; beq

	lda	#0
	beq	$+5
	jmp	fail

; brk FIXME brk caused memory corruption, now seems fixed

;	lda	#y3
;	sta	$fffe
;	lda	#y3>>8
;	sta	$ffff
;	brk
;	jmp	y4
;y3	nop
;	rti
;y4

; bit zp

	lda	#$c0
	sta	zp
	lda	#0
	bit	zp
	bmi	$+5
	jmp	fail
	bvs	$+5
	jmp	fail
	beq	$+5
	jmp	fail

; bit abs

	lda	#$c0
	sta	mem
	lda	#0
	bit	mem
	bmi	$+5
	jmp	fail
	bvs	$+5
	jmp	fail
	beq	$+5
	jmp	fail

; php

	clc
	php
	pla
	and	#1
	beq	$+5
	jmp	fail
	sec
	php
	pla
	and	#1
	bne	$+5
	jmp	fail

; plp

	lda	#0
	pha
	plp
	bcc	$+5
	jmp	fail
	lda	#1
	pha
	plp
	bcs	$+5
	jmp	fail

; pha

	lda	#33
	pha
	cmp	$1ff
	beq	$+5
	jmp	fail
	pla

; pla

	lda	#0
	pha
	lda	#57
	sta	$1ff
	lda	#0
	pla
	cmp	#57
	beq	$+5
	jmp	fail

; inx

	lda	#0
	ldx	#1
	inx
	txa
	cmp	#2
	beq	$+5
	jmp	fail

; iny

	lda	#0
	ldy	#1
	iny
	tya
	cmp	#2
	beq	$+5
	jmp	fail

; dex

	lda	#0
	ldx	#2
	dex
	txa
	cmp	#1
	beq	$+5
	jmp	fail

; dey

	lda	#0
	ldy	#2
	dey
	tya
	cmp	#1
	beq	$+5
	jmp	fail

; sed

	sed
	lda	#7
	clc
	adc	#8
	cld
	cmp	#$15
	beq	$+5
	jmp	fail

; cld

	sed
	php
	lda	$1ff
	and	#8
	bne	$+5
	jmp	fail
	pla
	cld
	php
	lda	$1ff
	and	#8
	beq	$+5
	jmp	fail
	pla

; clv

	lda	#$7f
	clc
	adc	#1
	clv
	php
	pla
	and	#$40
	beq	$+5
	jmp	fail

; sei

	sei
	php
	pla
	and	#4
	bne	$+5
	jmp	fail

; cli

	cli
	php
	pla
	and	#4
	beq	$+5
	jmp	fail

; tsx

	pha
	tsx
	pla
	cpx	#$ff
	beq	$+5
	jmp	fail

; txs

	ldx	#$80
	txs
	lda	#57
	pha
	lda	$17f
	cmp	#57
	beq	$+5
	jmp	fail
	ldx	#0
	txs

; tax

	lda	#3
	tax
	lda	#19
	sta	zp,x
	lda	zp+3
	cmp	#19
	beq	$+5
	jmp	fail

; txa

	ldx	#13
	txa
	cmp	#13
	beq	$+5
	jmp	fail

; tay

	lda	#3
	tay
	lda	#19
	sta	mem,y
	lda	mem+3
	cmp	#19
	beq	$+5
	jmp	fail

; tya

	ldy	#13
	tya
	cmp	#13
	beq	$+5
	jmp	fail

pass	jsr	puts
	word	str1
	jsr	halt

fail	jsr	puts
	word	str2
	jsr	halt

str1	byte	"pass",10,0
str2	byte	"fail",10,0

mem	equ	$
