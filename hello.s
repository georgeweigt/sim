exit	equ	$fff0
putc	equ	$fff1

	ldx	#0
loop	lda	str,x
	beq	done
	jsr	putc	; write to console
	inx
	jmp	loop
done	jsr	exit

str	byte	"hello",10,0
