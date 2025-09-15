#define T_LABEL  1001
#define T_NAME   1002
#define T_DECSTR 1003
#define T_HEXSTR 1004
#define T_QUOSTR 1005
#define T_CURLOC 1006
#define T_SHR    1007
#define T_SHL    1008
#define T_LF     1009
#define T_REGA   1010
#define T_REGX   1011
#define T_REGY   1012

#define AM_IMM   1
#define AM_ZP    2
#define AM_ZPXI  3
#define AM_ZPIY  4
#define AM_ABS   5
#define AM_ABSX  6
#define AM_ABSY  7
#define AM_REGA  8

#define ORA_ZPXI 0x01
#define ORA_ZP   0x05
#define ORA_IMM  0x09
#define ORA_ABS  0x0d
#define ORA_ZPIY 0x11
#define ORA_ZPX  0x15
#define ORA_ABSY 0x19
#define ORA_ABSX 0x1d

#define AND_ZPXI 0x21
#define AND_ZP   0x25
#define AND_IMM  0x29
#define AND_ABS  0x2d
#define AND_ZPIY 0x31
#define AND_ZPX  0x35
#define AND_ABSY 0x39
#define AND_ABSX 0x3d

#define EOR_ZPXI 0x41
#define EOR_ZP   0x45
#define EOR_IMM  0x49
#define EOR_ABS  0x4d
#define EOR_ZPIY 0x51
#define EOR_ZPX  0x55
#define EOR_ABSY 0x59
#define EOR_ABSX 0x5d

#define ADC_ZPXI 0x61
#define ADC_ZP   0x65
#define ADC_IMM  0x69
#define ADC_ABS  0x6d
#define ADC_ZPIY 0x71
#define ADC_ZPX  0x75
#define ADC_ABSY 0x79
#define ADC_ABSX 0x7d

#define STA_ZPXI 0x81
#define STA_ZP   0x85
#define STA_ABS  0x8d
#define STA_ZPIY 0x91
#define STA_ZPX  0x95
#define STA_ABSY 0x99
#define STA_ABSX 0x9d

#define LDA_ZPXI 0xa1
#define LDA_ZP   0xa5
#define LDA_IMM  0xa9
#define LDA_ABS  0xad
#define LDA_ZPIY 0xb1
#define LDA_ZPX  0xb5
#define LDA_ABSY 0xb9
#define LDA_ABSX 0xbd

#define CMP_ZPXI 0xc1
#define CMP_ZP   0xc5
#define CMP_IMM  0xc9
#define CMP_ABS  0xcd
#define CMP_ZPIY 0xd1
#define CMP_ZPX  0xd5
#define CMP_ABSY 0xd9
#define CMP_ABSX 0xdd

#define SBC_ZPXI 0xe1
#define SBC_ZP   0xe5
#define SBC_IMM  0xe9
#define SBC_ABS  0xed
#define SBC_ZPIY 0xf1
#define SBC_ZPX  0xf5
#define SBC_ABSY 0xf9
#define SBC_ABSX 0xfd

#define ASL_ZP   0x06
#define ASL_REGA 0x0a
#define ASL_ABS  0x0e
#define ASL_ZPX  0x16
#define ASL_ABSX 0x1e

#define ROL_ZP   0x26
#define ROL_REGA 0x2a
#define ROL_ABS  0x2e
#define ROL_ZPX  0x36
#define ROL_ABSX 0x3e

#define LSR_ZP   0x46
#define LSR_REGA 0x4a
#define LSR_ABS  0x4e
#define LSR_ZPX  0x56
#define LSR_ABSX 0x5e

#define ROR_ZP   0x66
#define ROR_REGA 0x6a
#define ROR_ABS  0x6e
#define ROR_ZPX  0x76
#define ROR_ABSX 0x7e

#define STX_ZP   0x86
#define STX_ABS  0x8e
#define STX_ABSX 0x96

#define LDX_IMM  0xa2
#define LDX_ZP   0xa6
#define LDX_ABS  0xae
#define LDX_ZPX  0xb6
#define LDX_ABSX 0xbe

#define DEC_ZP   0xc6
#define DEC_ABS  0xce
#define DEC_ZPX  0xd6
#define DEC_ABSX 0xde

#define INC_ZP   0xe6
#define INC_ABS  0xee
#define INC_ZPX  0xf6
#define INC_ABSX 0xfe

#define STY_ZP   0x84
#define STY_ABS  0x8c
#define STY_ZPX  0x94

#define LDY_IMM  0xa0
#define LDY_ZP   0xa4
#define LDY_ABS  0xac
#define LDY_ZPX  0xb4
#define LDY_ABSX 0xbc

#define CPY_IMM  0xc0
#define CPY_ZP   0xc4
#define CPY_ABS  0xcc

#define CPX_IMM  0xe0
#define CPX_ZP   0xe4
#define CPX_ABS  0xec

#define BIT_ZP   0x24
#define BIT_ABS  0x2c

#define OP_BPL   0x10
#define OP_BMI   0x30
#define OP_BVC   0x50
#define OP_BVS   0x70
#define OP_BCC   0x90
#define OP_BCS   0xb0
#define OP_BNE   0xd0
#define OP_BEQ   0xf0

#define OP_PHP   0x08
#define OP_PLP   0x28
#define OP_PHA   0x48
#define OP_PLA   0x68
#define OP_DEY   0x88
#define OP_TAY   0xa8
#define OP_INY   0xc8
#define OP_INX   0xe8

#define OP_BRK   0x00
#define OP_JSR   0x20
#define OP_RTI   0x40
#define OP_RTS   0x60

#define OP_JMP   0x4c
#define OP_JMPI  0x6c

#define OP_CLC   0x18
#define OP_SEC   0x38
#define OP_CLI   0x58
#define OP_SEI   0x78
#define OP_TYA   0x98
#define OP_CLV   0xb8
#define OP_CLD   0xd8
#define OP_SED   0xf8

#define OP_TXA   0x8a
#define OP_TXS   0x9a
#define OP_TAX   0xaa
#define OP_TSX   0xba
#define OP_DEX   0xca
#define OP_NOP   0xea

#define ZPADDR (where > 0 && where <= curlin && value < 256)

void
scan_file(int k)
{
	pass = k;
	start = -1;
	curloc = 0x200;
	curlin = 1;
	scanptr = buf;
	while (*scanptr) {
		lineptr = scanptr;
		scan_line();
		if (token != T_LF)
			scan_error("unexpected text at end of line");
		curlin++;
	}
}

void
scan_line(void)
{
	int err = 0, i;
	struct sym *p = NULL;

	scan_token();

	if (token == T_LF)
		return;

	if (token == T_LABEL) {
		p = scan_label();
		scan_token();
	}

	if (token == T_LF)
		return;

	if (token != T_NAME)
		scan_error("opcode expected");

	for (i = 0; i < tokenlen; i++)
		tokenbuf[i] = tolower(tokenbuf[i]);

	if (strcmp(tokenbuf, ".equ") == 0) {
		scan_token();
		scan_value();
		if (pass == 2 && where == 0)
			scan_error("unresolved symbol in EQU");
		if (p) {
			p->value = value;
			p->where = where;
		}
		return;
	}

	if (strcmp(tokenbuf, ".org") == 0) {
		scan_token();
		scan_value();
		if (where == 0)
			scan_error("unresolved symbol in ORG");
		if (p) {
			p->value = value;
			p->where = where;
		}
		curloc = value;
		return;
	}

	switch (*tokenbuf) {

	case '.':
		if (strcmp(tokenbuf, ".bss") == 0) {
			scan_bss();
			break;
		}
		if (strcmp(tokenbuf, ".byte") == 0) {
			scan_byte();
			break;
		}
		if (strcmp(tokenbuf, ".word") == 0) {
			scan_word();
			break;
		}
		err = 1;
		break;

	case 'a':
		if (strcmp(tokenbuf, "adc") == 0) {
			scan_adc();
			break;
		}
		if (strcmp(tokenbuf, "and") == 0) {
			scan_and();
			break;
		}
		if (strcmp(tokenbuf, "asl") == 0) {
			scan_asl();
			break;
		}
		err = 1;
		break;

	case 'b':
		if (strcmp(tokenbuf, "bcc") == 0) {
			scan_bcc();
			break;
		}
		if (strcmp(tokenbuf, "bcs") == 0) {
			scan_bcs();
			break;
		}
		if (strcmp(tokenbuf, "beq") == 0) {
			scan_beq();
			break;
		}
		if (strcmp(tokenbuf, "bit") == 0) {
			scan_bit();
			break;
		}
		if (strcmp(tokenbuf, "bmi") == 0) {
			scan_bmi();
			break;
		}
		if (strcmp(tokenbuf, "bne") == 0) {
			scan_bne();
			break;
		}
		if (strcmp(tokenbuf, "bpl") == 0) {
			scan_bpl();
			break;
		}
		if (strcmp(tokenbuf, "brk") == 0) {
			scan_brk();
			break;
		}
		if (strcmp(tokenbuf, "bvc") == 0) {
			scan_bvc();
			break;
		}
		if (strcmp(tokenbuf, "bvs") == 0) {
			scan_bvs();
			break;
		}
		err = 1;
		break;

	case 'c':
		if (strcmp(tokenbuf, "clc") == 0) {
			scan_clc();
			break;
		}
		if (strcmp(tokenbuf, "cld") == 0) {
			scan_cld();
			break;
		}
		if (strcmp(tokenbuf, "cli") == 0) {
			scan_cli();
			break;
		}
		if (strcmp(tokenbuf, "clv") == 0) {
			scan_clv();
			break;
		}
		if (strcmp(tokenbuf, "cmp") == 0) {
			scan_cmp();
			break;
		}
		if (strcmp(tokenbuf, "cpx") == 0) {
			scan_cpx();
			break;
		}
		if (strcmp(tokenbuf, "cpy") == 0) {
			scan_cpy();
			break;
		}
		err = 1;
		break;

	case 'd':
		if (strcmp(tokenbuf, "dec") == 0) {
			scan_dec();
			break;
		}
		if (strcmp(tokenbuf, "dex") == 0) {
			scan_dex();
			break;
		}
		if (strcmp(tokenbuf, "dey") == 0) {
			scan_dey();
			break;
		}
		err = 1;
		break;

	case 'e':
		if (strcmp(tokenbuf, "eor") == 0) {
			scan_eor();
			break;
		}
		err = 1;
		break;

	case 'i':
		if (strcmp(tokenbuf, "inc") == 0) {
			scan_inc();
			break;
		}
		if (strcmp(tokenbuf, "inx") == 0) {
			scan_inx();
			break;
		}
		if (strcmp(tokenbuf, "iny") == 0) {
			scan_iny();
			break;
		}
		err = 1;
		break;

	case 'j':
		if (strcmp(tokenbuf, "jmp") == 0) {
			scan_jmp();
			break;
		}
		if (strcmp(tokenbuf, "jsr") == 0) {
			scan_jsr();
			break;
		}
		err = 1;
		break;

	case 'l':
		if (strcmp(tokenbuf, "lda") == 0) {
			scan_lda();
			break;
		}
		if (strcmp(tokenbuf, "ldx") == 0) {
			scan_ldx();
			break;
		}
		if (strcmp(tokenbuf, "ldy") == 0) {
			scan_ldy();
			break;
		}
		if (strcmp(tokenbuf, "lsr") == 0) {
			scan_lsr();
			break;
		}
		err = 1;
		break;

	case 'n':
		if (strcmp(tokenbuf, "nop") == 0) {
			scan_nop();
			break;
		}
		err = 1;
		break;

	case 'o':
		if (strcmp(tokenbuf, "ora") == 0) {
			scan_ora();
			break;
		}
		err = 1;
		break;

	case 'p':
		if (strcmp(tokenbuf, "pha") == 0) {
			scan_pha();
			break;
		}
		if (strcmp(tokenbuf, "php") == 0) {
			scan_php();
			break;
		}
		if (strcmp(tokenbuf, "pla") == 0) {
			scan_pla();
			break;
		}
		if (strcmp(tokenbuf, "plp") == 0) {
			scan_plp();
			break;
		}
		err = 1;
		break;

	case 'r':
		if (strcmp(tokenbuf, "rol") == 0) {
			scan_rol();
			break;
		}
		if (strcmp(tokenbuf, "ror") == 0) {
			scan_ror();
			break;
		}
		if (strcmp(tokenbuf, "rti") == 0) {
			scan_rti();
			break;
		}
		if (strcmp(tokenbuf, "rts") == 0) {
			scan_rts();
			break;
		}
		err = 1;
		break;

	case 's':
		if (strcmp(tokenbuf, "sbc") == 0) {
			scan_sbc();
			break;
		}
		if (strcmp(tokenbuf, "sec") == 0) {
			scan_sec();
			break;
		}
		if (strcmp(tokenbuf, "sed") == 0) {
			scan_sed();
			break;
		}
		if (strcmp(tokenbuf, "sei") == 0) {
			scan_sei();
			break;
		}
		if (strcmp(tokenbuf, "sta") == 0) {
			scan_sta();
			break;
		}
		if (strcmp(tokenbuf, "stx") == 0) {
			scan_stx();
			break;
		}
		if (strcmp(tokenbuf, "sty") == 0) {
			scan_sty();
			break;
		}
		err = 1;
		break;

	case 't':
		if (strcmp(tokenbuf, "tax") == 0) {
			scan_tax();
			break;
		}
		if (strcmp(tokenbuf, "tay") == 0) {
			scan_tay();
			break;
		}
		if (strcmp(tokenbuf, "tsx") == 0) {
			scan_tsx();
			break;
		}
		if (strcmp(tokenbuf, "txa") == 0) {
			scan_txa();
			break;
		}
		if (strcmp(tokenbuf, "txs") == 0) {
			scan_txs();
			break;
		}
		if (strcmp(tokenbuf, "tya") == 0) {
			scan_tya();
			break;
		}
		err = 1;
		break;

	default:
		err = 1;
		break;
	}

	if (err)
		scan_error("unknown opcode");
}

struct sym *
scan_label(void)
{
	int i, k;
	struct sym *p;
	k = tolower(*tokenbuf) - 'a';
	for (i = 0; i < NSYM; i++) {
		p = &stab[k][i];
		if (p->name == NULL)
			break;
		if (strcmp(p->name, tokenbuf) == 0) {
			if (pass == 1)
				scan_error("symbol redefined");
			return p;
		}
	}
	if (i == NSYM)
		scan_error("symbol table full");
	p->name = strdup(tokenbuf);
	if (p->name == NULL)
		scan_error("strdup kaput");
	p->value = curloc;
	p->where = curlin;
	return p;
}

void
scan_addr(void)
{
	if (token == T_REGA) {
		scan_token();
		addrmode = AM_REGA;
		return;
	}

	if (token == '#') {
		scan_token();
		scan_value();
		addrmode = AM_IMM;
		return;
	}

	// indirect modes (zp,x) and (zp),y

	if (token == '(') {
		scan_token();
		scan_value();
		if (pass == 2 && value > 255)
			scan_error("operand not in zero page");
		switch (token) {
		case ',':
			scan_token();
			if (token != T_REGX)
				break;
			scan_token();
			if (token != ')')
				break;
			scan_token();
			addrmode = AM_ZPXI;
			return;
		case ')':
			scan_token();
			if (token != ',')
				break;
			scan_token();
			if (token != T_REGY)
				break;
			scan_token();
			addrmode = AM_ZPIY;
			return;
		}
		scan_error("expected format (ZP,X) or (ZP),Y");
		return;
	}

	// absolute modes

	scan_value();
	if (token == ',') {
		scan_token();
		switch (token) {
		case T_REGX:
			scan_token();
			addrmode = AM_ABSX;
			break;
		case T_REGY:
			scan_token();
			addrmode = AM_ABSY;
			break;
		default:
			scan_error("expected format ABS,X or ABS,Y");
			break;
		}
	} else
		addrmode = AM_ABS;
}

void
scan_expr(void)
{
	int t = token;

	if (t == '+' || t == '-' || t == '~')
		scan_token();

	scan_term();

	switch (t) {
	case '-':
		stack_neg();
		break;
	case '~':
		stack_cpl();
		break;
	default:
		break;
	}

	while (token == '+' || token == '-' || token == '&' || token == '|' || token == '^' || token == T_SHR || token == T_SHL) {
		t = token;
		scan_token();
		scan_term();
		switch (t) {
		case '+':
			stack_add();
			break;
		case '-':
			stack_sub();
			break;
		case '&':
			stack_and();
			break;
		case '|':
			stack_or();
			break;
		case '^':
			stack_xor();
			break;
		case T_SHR:
			stack_shr();
			break;
		case T_SHL:
			stack_shl();
			break;
		}
	}
}

void
scan_term(void)
{
	int t;
	scan_factor();
	while (token == '*' || token == '/' || token == '%') {
		t = token;
		scan_token();
		scan_factor();
		switch (t) {
		case '*':
			stack_mul();
			break;
		case '/':
			stack_div();
			break;
		case '%':
			stack_rem();
			break;
		}
	}
}

void
scan_factor(void)
{
	int value;
	char *s;
	struct sym *p;

	switch (token) {

	case '(':
		scan_token();
		scan_expr();
		if (token != ')')
			scan_error("')' expected");
		break;

	case T_CURLOC:
		stack_push(curloc);
		break;

	case T_NAME:
		// possible states:
		// 1. in symbol table with known value (label or equ)
		// 2. in symbol table with unknown value (unresolved equ)
		// 3. not in symbol table (forward defn)
		p = scan_lookup();
		if (p && p->where) {
			stack_push(p->value);
			if (where && p->where > where)
				where = p->where;
		} else {
			if (pass == 2)
				scan_error("undefined symbol");
			where = 0; // forward defn
			stack_push(0); // dummy value
		}
		break;

	case T_DECSTR:
		value = 0;
		s = tokenbuf;
		while (*s)
			value = 10 * value + *s++ - '0';
		stack_push(value);
		break;

	case T_HEXSTR:
		value = 0;
		s = tokenbuf;
		while (*s)
			if (*s <= '9')
				value = (value << 4) | (*s++ - '0');
			else
				value = (value << 4) | (tolower(*s++) - 'a' + 10);
		stack_push(value);
		break;

	default:
		scan_error("syntax error");
		break;
	}

	scan_token(); // factor now on stack, eat factor
}

void
scan_error(char *errmsg)
{
	char *s;
	printf("Line %d:\n", curlin);
	s = lineptr;
	while (*s && *s != '\n')
		putchar(*s++);
	putchar('\n');
	puts(errmsg);
	exit(1);
}

struct sym *
scan_lookup(void)
{
	int i, k;
	k = tolower(*tokenbuf) - 'a';
	for (i = 0; i < NSYM; i++) {
		if (stab[k][i].name == NULL)
			break; // not found
		if (strcmp(stab[k][i].name, tokenbuf) == 0)
			return &stab[k][i];
	}
	return NULL;
}

// scanptr points to start of line

void
scan_token(void)
{
	while (*scanptr == ' ' || *scanptr == '\t')
		scanptr++;

	if (*scanptr == ';')
		while (*scanptr && *scanptr != '\n')
			scanptr++;

	if (*scanptr == 0) {
		token = T_LF;
		return;
	}

	if (*scanptr == '\n') {
		token = T_LF;
		scanptr++;
		return;
	}

	tokenptr = scanptr;

	if (isalpha(*scanptr) || *scanptr == '.') {
		do
			scanptr++;
		while (isalnum(*scanptr));
		tokenlen = scanptr - tokenptr;
		if (tokenlen == 1) {
			switch (tolower(*tokenptr)) {
			case 'a':
				token = T_REGA;
				return;
			case 'x':
				token = T_REGX;
				return;
			case 'y':
				token = T_REGY;
				return;
			}
		}
		if (tokenlen > TOKENBUFLEN)
			scan_error("too long");
		memcpy(tokenbuf, tokenptr, tokenlen);
		tokenbuf[tokenlen] = 0;
		if (*scanptr == ':') {
			scanptr++;
			token = T_LABEL;
		} else
			token = T_NAME;
		return;
	}

	if (isdigit(*scanptr)) {
		while (isdigit(*scanptr))
			scanptr++;
		tokenlen = scanptr - tokenptr;
		if (tokenlen > TOKENBUFLEN)
			scan_error("too long");
		memcpy(tokenbuf, tokenptr, tokenlen);
		tokenbuf[tokenlen] = 0;
		token = T_DECSTR;
		return;
	}

	if (*scanptr == '$') {
		scanptr++;
		if (isxdigit(*scanptr)) {
			while (isxdigit(*scanptr))
				scanptr++;
			tokenlen = scanptr - tokenptr - 1;
			if (tokenlen > TOKENBUFLEN)
				scan_error("too long");
			memcpy(tokenbuf, tokenptr + 1, tokenlen);
			tokenbuf[tokenlen] = 0;
			token = T_HEXSTR;
		} else
			token = T_CURLOC;
		return;
	}

	if (*scanptr == '"') {
		scanptr++;
		while (*scanptr && *scanptr != '"' && *scanptr != '\n')
			scanptr++;
		if (*scanptr != '"')
			scan_error("runaway string");
		scanptr++;
		tokenlen = scanptr - tokenptr - 2;
		if (tokenlen > TOKENBUFLEN)
			scan_error("too long");
		memcpy(tokenbuf, tokenptr + 1, tokenlen);
		tokenbuf[tokenlen] = 0;
		token = T_QUOSTR;
		return;
	}

	if (*scanptr == '>' && scanptr[1] == '>') {
		token = T_SHR;
		scanptr += 2;
		return;
	}

	if (*scanptr == '<' && scanptr[1] == '<') {
		token = T_SHL;
		scanptr += 2;
		return;
	}

	token = *scanptr;
	scanptr++;
}

void
scan_branch(void)
{
	scan_value();
	value = value - curloc - 2;
	if (pass == 2 && (value < -128 || value > 127))
		scan_error("branch range error");
}

void
scan_value(void)
{
	where = curlin;
	stackindex = 0;
	scan_expr();
	value = stack_pop();
}

void
scan_adc(void)
{
	scan_token();
	scan_addr();

	switch (addrmode) {

	case AM_IMM:
		scan_emit(ADC_IMM, 2);
		break;

	case AM_ZPXI:
		scan_emit(ADC_ZPXI, 2);
		break;

	case AM_ZPIY:
		scan_emit(ADC_ZPIY, 2);
		break;

	case AM_ABS:
		if (ZPADDR)
			scan_emit(ADC_ZP, 2);
		else
			scan_emit(ADC_ABS, 3);
		break;

	case AM_ABSX:
		if (ZPADDR)
			scan_emit(ADC_ZPX, 2);
		else
			scan_emit(ADC_ABSX, 3);
		break;

	case AM_ABSY:
		scan_emit(ADC_ABSY, 3);
		break;

	default:
		scan_error("address mode error");
		break;
	}
}

void
scan_and(void)
{
	scan_token();
	scan_addr();

	switch (addrmode) {

	case AM_IMM:
		scan_emit(AND_IMM, 2);
		break;

	case AM_ZPXI:
		scan_emit(AND_ZPXI, 2);
		break;

	case AM_ZPIY:
		scan_emit(AND_ZPIY, 2);
		break;

	case AM_ABS:
		if (ZPADDR)
			scan_emit(AND_ZP, 2);
		else
			scan_emit(AND_ABS, 3);
		break;

	case AM_ABSX:
		if (ZPADDR)
			scan_emit(AND_ZPX, 2);
		else
			scan_emit(AND_ABSX, 3);
		break;

	case AM_ABSY:
		scan_emit(AND_ABSY, 3);
		break;

	default:
		scan_error("address mode error");
		break;
	}
}

void
scan_asl(void)
{
	scan_token();
	scan_addr();

	switch (addrmode) {

	case AM_REGA:
		scan_emit(ASL_REGA, 1);
		break;

	case AM_ABS:
		if (ZPADDR)
			scan_emit(ASL_ZP, 2);
		else
			scan_emit(ASL_ABS, 3);
		break;

	case AM_ABSX:
		if (ZPADDR)
			scan_emit(ASL_ZPX, 2);
		else
			scan_emit(ASL_ABSX, 3);
		break;

	default:
		scan_error("address mode error");
		break;
	}
}

void
scan_bcc(void)
{
	scan_token();
	scan_branch();
	scan_emit(OP_BCC, 2);
}

void
scan_bcs(void)
{
	scan_token();
	scan_branch();
	scan_emit(OP_BCS, 2);
}

void
scan_beq(void)
{
	scan_token();
	scan_branch();
	scan_emit(OP_BEQ, 2);
}

void
scan_bit(void)
{
	scan_token();
	scan_addr();

	switch (addrmode) {

	case AM_ABS:
		if (ZPADDR)
			scan_emit(BIT_ZP, 2);
		else
			scan_emit(BIT_ABS, 3);
		break;

	default:
		scan_error("address mode error");
		break;
	}
}

void
scan_bmi(void)
{
	scan_token();
	scan_branch();
	scan_emit(OP_BMI, 2);
}

void
scan_bne(void)
{
	scan_token();
	scan_branch();
	scan_emit(OP_BNE, 2);
}

void
scan_bpl(void)
{
	scan_token();
	scan_branch();
	scan_emit(OP_BPL, 2);
}

void
scan_brk(void)
{
	scan_token();
	scan_emit(OP_BRK, 1);
}

void
scan_bvc(void)
{
	scan_token();
	scan_branch();
	scan_emit(OP_BVC, 2);
}

void
scan_bvs(void)
{
	scan_token();
	scan_branch();
	scan_emit(OP_BVS, 2);
}

void
scan_clc(void)
{
	scan_token();
	scan_emit(OP_CLC, 1);
}

void
scan_cld(void)
{
	scan_token();
	scan_emit(OP_CLD, 1);
}

void
scan_cli(void)
{
	scan_token();
	scan_emit(OP_CLI, 1);
}

void
scan_clv(void)
{
	scan_token();
	scan_emit(OP_CLV, 1);
}

void
scan_cmp(void)
{
	scan_token();
	scan_addr();

	switch (addrmode) {

	case AM_IMM:
		scan_emit(CMP_IMM, 2);
		break;

	case AM_ZPXI:
		scan_emit(CMP_ZPXI, 2);
		break;

	case AM_ZPIY:
		scan_emit(CMP_ZPIY, 2);
		break;

	case AM_ABS:
		if (ZPADDR)
			scan_emit(CMP_ZP, 2);
		else
			scan_emit(CMP_ABS, 3);
		break;

	case AM_ABSX:
		if (ZPADDR)
			scan_emit(CMP_ZPX, 2);
		else
			scan_emit(CMP_ABSX, 3);
		break;

	case AM_ABSY:
		scan_emit(CMP_ABSY, 3);
		break;

	default:
		scan_error("address mode error");
		break;
	}
}

void
scan_cpx(void)
{
	scan_token();
	scan_addr();

	switch (addrmode) {

	case AM_IMM:
		scan_emit(CPX_IMM, 2);
		break;

	case AM_ABS:
		if (ZPADDR)
			scan_emit(CPX_ZP, 2);
		else
			scan_emit(CPX_ABS, 3);
		break;

	default:
		scan_error("address mode error");
		break;
	}
}

void
scan_cpy(void)
{
	scan_token();
	scan_addr();

	switch (addrmode) {

	case AM_IMM:
		scan_emit(CPY_IMM, 2);
		break;

	case AM_ABS:
		if (ZPADDR)
			scan_emit(CPY_ZP, 2);
		else
			scan_emit(CPY_ABS, 3);
		break;

	default:
		scan_error("address mode error");
		break;
	}
}

void
scan_dec(void)
{
	scan_token();
	scan_addr();

	switch (addrmode) {

	case AM_ABS:
		if (ZPADDR)
			scan_emit(DEC_ZP, 2);
		else
			scan_emit(DEC_ABS, 3);
		break;

	case AM_ABSX:
		if (ZPADDR)
			scan_emit(DEC_ZPX, 2);
		else
			scan_emit(DEC_ABSX, 3);
		break;

	default:
		scan_error("address mode error");
		break;
	}
}

void
scan_dex(void)
{
	scan_token();
	scan_emit(OP_DEX, 1);
}

void
scan_dey(void)
{
	scan_token();
	scan_emit(OP_DEY, 1);
}

void
scan_eor(void)
{
	scan_token();
	scan_addr();

	switch (addrmode) {

	case AM_IMM:
		scan_emit(EOR_IMM, 2);
		break;

	case AM_ZPXI:
		scan_emit(EOR_ZPXI, 2);
		break;

	case AM_ZPIY:
		scan_emit(EOR_ZPIY, 2);
		break;

	case AM_ABS:
		if (ZPADDR)
			scan_emit(EOR_ZP, 2);
		else
			scan_emit(EOR_ABS, 3);
		break;

	case AM_ABSX:
		if (ZPADDR)
			scan_emit(EOR_ZPX, 2);
		else
			scan_emit(EOR_ABSX, 3);
		break;

	case AM_ABSY:
		scan_emit(EOR_ABSY, 3);
		break;

	default:
		scan_error("address mode error");
		break;
	}
}

void
scan_inc(void)
{
	scan_token();
	scan_addr();

	switch (addrmode) {

	case AM_ABS:
		if (ZPADDR)
			scan_emit(INC_ZP, 2);
		else
			scan_emit(INC_ABS, 3);
		break;

	case AM_ABSX:
		if (ZPADDR)
			scan_emit(INC_ZPX, 2);
		else
			scan_emit(INC_ABSX, 3);
		break;

	default:
		scan_error("address mode error");
		break;
	}
}

void
scan_inx(void)
{
	scan_token();
	scan_emit(OP_INX, 1);
}

void
scan_iny(void)
{
	scan_token();
	scan_emit(OP_INY, 1);
}

void
scan_jmp(void)
{
	scan_token();
	if (token == '(') {
		scan_token();
		scan_value();
		if (token != ')')
			scan_error("closing ) expected");
		scan_token();
		scan_emit(OP_JMPI, 3);
	} else {
		scan_value();
		scan_emit(OP_JMP, 3);
	}
}

void
scan_jsr(void)
{
	scan_token();
	scan_value();
	scan_emit(OP_JSR, 3);
}

void
scan_lda(void)
{
	scan_token();
	scan_addr();

	switch (addrmode) {

	case AM_IMM:
		scan_emit(LDA_IMM, 2);
		break;

	case AM_ZPXI:
		scan_emit(LDA_ZPXI, 2);
		break;

	case AM_ZPIY:
		scan_emit(LDA_ZPIY, 2);
		break;

	case AM_ABS:
		if (ZPADDR)
			scan_emit(LDA_ZP, 2);
		else
			scan_emit(LDA_ABS, 3);
		break;

	case AM_ABSX:
		if (ZPADDR)
			scan_emit(LDA_ZPX, 2);
		else
			scan_emit(LDA_ABSX, 3);
		break;

	case AM_ABSY:
		scan_emit(LDA_ABSY, 3);
		break;

	default:
		scan_error("address mode error");
		break;
	}
}

void
scan_ldx(void)
{
	scan_token();
	scan_addr();

	switch (addrmode) {

	case AM_IMM:
		scan_emit(LDX_IMM, 2);
		break;

	case AM_ABS:
		if (ZPADDR)
			scan_emit(LDX_ZP, 2);
		else
			scan_emit(LDX_ABS, 3);
		break;

	case AM_ABSX:
	case AM_ABSY:
		if (ZPADDR)
			scan_emit(LDX_ZPX, 2);
		else
			scan_emit(LDX_ABSX, 3);
		break;

	default:
		scan_error("address mode error");
		break;
	}
}

void
scan_ldy(void)
{
	scan_token();
	scan_addr();

	switch (addrmode) {

	case AM_IMM:
		scan_emit(LDY_IMM, 2);
		break;

	case AM_ABS:
		if (ZPADDR)
			scan_emit(LDY_ZP, 2);
		else
			scan_emit(LDY_ABS, 3);
		break;

	case AM_ABSX:
		if (ZPADDR)
			scan_emit(LDY_ZPX, 2);
		else
			scan_emit(LDY_ABSX, 3);
		break;

	default:
		scan_error("address mode error");
		break;
	}
}

void
scan_lsr(void)
{
	scan_token();
	scan_addr();

	switch (addrmode) {

	case AM_REGA:
		scan_emit(LSR_REGA, 1);
		break;

	case AM_ABS:
		if (ZPADDR)
			scan_emit(LSR_ZP, 2);
		else
			scan_emit(LSR_ABS, 3);
		break;

	case AM_ABSX:
		if (ZPADDR)
			scan_emit(LSR_ZPX, 2);
		else
			scan_emit(LSR_ABSX, 3);
		break;

	default:
		scan_error("address mode error");
		break;
	}
}

void
scan_nop(void)
{
	scan_token();
	scan_emit(OP_NOP, 1);
}

void
scan_ora(void)
{
	scan_token();
	scan_addr();

	switch (addrmode) {

	case AM_IMM:
		scan_emit(ORA_IMM, 2);
		break;

	case AM_ZPXI:
		scan_emit(ORA_ZPXI, 2);
		break;

	case AM_ZPIY:
		scan_emit(ORA_ZPIY, 2);
		break;

	case AM_ABS:
		if (ZPADDR)
			scan_emit(ORA_ZP, 2);
		else
			scan_emit(ORA_ABS, 3);
		break;

	case AM_ABSX:
		if (ZPADDR)
			scan_emit(ORA_ZPX, 2);
		else
			scan_emit(ORA_ABSX, 3);
		break;

	case AM_ABSY:
		scan_emit(ORA_ABSY, 3);
		break;

	default:
		scan_error("address mode error");
		break;
	}
}

void
scan_pha(void)
{
	scan_token();
	scan_emit(OP_PHA, 1);
}

void
scan_php(void)
{
	scan_token();
	scan_emit(OP_PHP, 1);
}

void
scan_pla(void)
{
	scan_token();
	scan_emit(OP_PLA, 1);
}

void
scan_plp(void)
{
	scan_token();
	scan_emit(OP_PLP, 1);
}

void
scan_rol(void)
{
	scan_token();
	scan_addr();

	switch (addrmode) {

	case AM_REGA:
		scan_emit(ROL_REGA, 1);
		break;

	case AM_ABS:
		if (ZPADDR)
			scan_emit(ROL_ZP, 2);
		else
			scan_emit(ROL_ABS, 3);
		break;

	case AM_ABSX:
		if (ZPADDR)
			scan_emit(ROL_ZPX, 2);
		else
			scan_emit(ROL_ABSX, 3);
		break;

	default:
		scan_error("address mode error");
		break;
	}
}

void
scan_ror(void)
{
	scan_token();
	scan_addr();

	switch (addrmode) {

	case AM_REGA:
		scan_emit(ROR_REGA, 1);
		break;

	case AM_ABS:
		if (ZPADDR)
			scan_emit(ROR_ZP, 2);
		else
			scan_emit(ROR_ABS, 3);
		break;

	case AM_ABSX:
		if (ZPADDR)
			scan_emit(ROR_ZPX, 2);
		else
			scan_emit(ROR_ABSX, 3);
		break;

	default:
		scan_error("address mode error");
		break;
	}
}

void
scan_rti(void)
{
	scan_token();
	scan_emit(OP_RTI, 1);
}

void
scan_rts(void)
{
	scan_token();
	scan_emit(OP_RTS, 1);
}

void
scan_sbc(void)
{
	scan_token();
	scan_addr();

	switch (addrmode) {

	case AM_IMM:
		scan_emit(SBC_IMM, 2);
		break;

	case AM_ZPXI:
		scan_emit(SBC_ZPXI, 2);
		break;

	case AM_ZPIY:
		scan_emit(SBC_ZPIY, 2);
		break;

	case AM_ABS:
		if (ZPADDR)
			scan_emit(SBC_ZP, 2);
		else
			scan_emit(SBC_ABS, 3);
		break;

	case AM_ABSX:
		if (ZPADDR)
			scan_emit(SBC_ZPX, 2);
		else
			scan_emit(SBC_ABSX, 3);
		break;

	case AM_ABSY:
		scan_emit(SBC_ABSY, 3);
		break;

	default:
		scan_error("address mode error");
		break;
	}
}

void
scan_sec(void)
{
	scan_token();
	scan_emit(OP_SEC, 1);
}

void
scan_sed(void)
{
	scan_token();
	scan_emit(OP_SED, 1);
}

void
scan_sei(void)
{
	scan_token();
	scan_emit(OP_SEI, 1);
}

void
scan_sta(void)
{
	scan_token();
	scan_addr();

	switch (addrmode) {

	case AM_ZPXI:
		scan_emit(STA_ZPXI, 2);
		break;

	case AM_ZPIY:
		scan_emit(STA_ZPIY, 2);
		break;

	case AM_ABS:
		if (ZPADDR)
			scan_emit(STA_ZP, 2);
		else
			scan_emit(STA_ABS, 3);
		break;

	case AM_ABSX:
		if (ZPADDR)
			scan_emit(STA_ZPX, 2);
		else
			scan_emit(STA_ABSX, 3);
		break;

	case AM_ABSY:
		scan_emit(STA_ABSY, 3);
		break;

	default:
		scan_error("address mode error");
		break;
	}
}

void
scan_stx(void)
{
	scan_token();
	scan_addr();

	switch (addrmode) {

	case AM_ABS:
		if (ZPADDR)
			scan_emit(LDX_ZP, 2);
		else
			scan_emit(LDX_ABS, 3);
		break;

	case AM_ABSX:
	case AM_ABSY:
		if (ZPADDR)
			scan_emit(LDX_ZPX, 2);
		else
			scan_error("STX with X requires zero page address");
		break;

	default:
		scan_error("address mode error");
		break;
	}
}

void
scan_sty(void)
{
	scan_token();
	scan_addr();

	switch (addrmode) {

	case AM_ABS:
		if (ZPADDR)
			scan_emit(STY_ZP, 2);
		else
			scan_emit(STY_ABS, 3);
		break;

	case AM_ABSX:
		if (ZPADDR)
			scan_emit(STY_ZPX, 2);
		else
			scan_error("STY with X requires zero page address");
		break;

	default:
		scan_error("address mode error");
		break;
	}
}

void
scan_tax(void)
{
	scan_token();
	scan_emit(OP_TAX, 1);
}

void
scan_tay(void)
{
	scan_token();
	scan_emit(OP_TAY, 1);
}

void
scan_tsx(void)
{
	scan_token();
	scan_emit(OP_TSX, 1);
}

void
scan_txa(void)
{
	scan_token();
	scan_emit(OP_TXA, 1);
}

void
scan_txs(void)
{
	scan_token();
	scan_emit(OP_TXS, 1);
}

void
scan_tya(void)
{
	scan_token();
	scan_emit(OP_TYA, 1);
}

void
scan_emit(int opcode, int count)
{
	int i, k = curloc, n;
	char *s;

	if (pass == 1) {
		curloc += count;
		return;
	}

	if (start < 0)
		start = curloc;

	mem[curloc++] = opcode;

	if (count > 1)
		mem[curloc++] = value;

	if (count > 2)
		mem[curloc++] = value >> 8;

	// print

	printf("%04x", k);
	n = 4;
	for (i = 0; i < count; i++) {
		printf(" %02x", mem[k + i]);
		n += 3;
	}
	for (i = n; i < 16; i++)
		putchar(' ');
	s = lineptr;
	while (*s && *s != '\n')
		putchar(*s++);
	putchar('\n');
}

void
scan_bss(void)
{
	scan_token();
	scan_value();
	if (where == 0)
		scan_error("unresolved symbol in BSS");
	curloc += value;
}

void
scan_byte(void)
{
	char *s;
	do {
		scan_token();
		if (token == T_QUOSTR) {
			s = tokenbuf;
			while (*s)
				scan_emit_byte(*s++);
			scan_token();
		} else {
			scan_value();
			scan_emit_byte(value);
		}
	} while (token == ',');
}

void
scan_word(void)
{
	do {
		scan_token();
		scan_value();
		scan_emit_word(value);
	} while (token == ',');
}

void
scan_emit_byte(int byte)
{
	if (pass == 2)
		mem[curloc] = byte;
	curloc++;
}

void
scan_emit_word(int word)
{
	if (pass == 2) {
		mem[curloc] = word;
		mem[curloc + 1] = word >> 8;
	}
	curloc += 2;
}
