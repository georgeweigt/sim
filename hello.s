	.org	$200
	ldx	#0
loop:	lda	str,x
	beq	done
	sta	$fff0	; write to console
	inx
	jmp	loop
done:	sta	$fff1	; power off
str:	.byte	"hello",10,0
