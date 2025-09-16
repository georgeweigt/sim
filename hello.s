.def putc $fff0
.def halt $fff1

	.org	$200
	ldx	#0
loop:	lda	str,x
	beq	done
	sta	putc	; write to console
	inx
	jmp	loop
done:	sta	halt
str:	.byte	"hello",10,0
