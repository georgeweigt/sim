exit	equ	$fff0
putc	equ	$fff1

	ldx	#0
loop	lda	str,x
	bne	$+5
	jsr	exit
	jsr	putc	; write to console
	inx
	jmp	loop

str	byte	"hello",10,0
