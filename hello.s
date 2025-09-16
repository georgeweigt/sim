halt	equ	$fff0
putc	equ	$fff1

	org	$200

	ldx	#0
loop	lda	str,x
	beq	done
	jsr	putc	; write to console
	inx
	jmp	loop
done	jsr	halt

str	byte	"hello",10,0
