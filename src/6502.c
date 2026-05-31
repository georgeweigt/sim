void
adc(uint32_t addr)
{
	uint32_t t, h;

	if (flags & C)
		t = (uint32_t) acc + mem[addr] + 1;
	else
		t = (uint32_t) acc + mem[addr];

	if ((t ^ acc) & (t ^ mem[addr]) & 0x80)
		flags |= V;
	else
		flags &= ~V;

	if (flags & D) {
		if (flags & C)
			h = (acc & 0xf) + (mem[addr] & 0xf) + 1;
		else
			h = (acc & 0xf) + (mem[addr] & 0xf);
		if ((t & 0xf) > 9 || (h & 0x10))
			t += 6;
		if ((t & 0xf0) > 0x90 || (t & 0x100))
			t += 0x60;
	}

	if (t & 0x100)
		flags |= C;
	else
		flags &= ~C;

	acc = t;
	update_nz(acc);
}

void
sbc(uint32_t addr)
{
	uint32_t t, h;

	if (flags & C)
		t = (uint32_t) acc - mem[addr];
	else
		t = (uint32_t) acc - mem[addr] - 1;

	if ((t ^ acc) & (t ^ mem[addr] ^ 0x80) & 0x80)
		flags |= V;
	else
		flags &= ~V;

	if (flags & D) {
		if (flags & C)
			h = (acc & 0xf) - (mem[addr] & 0xf);
		else
			h = (acc & 0xf) - (mem[addr] & 0xf) - 1;
		if ((t & 0xf) > 9 || (h & 0x10))
			t += 6;
		if ((t & 0xf0) > 0x90 || (t & 0x100))
			t += 0x60;
	}

	if (t & 0x100)
		flags &= ~C;
	else
		flags |= C;

	acc = t;
	update_nz(acc);
}

void
and(uint32_t addr)
{
	acc &= mem[addr];
	update_nz(acc);
}

void
ora(uint32_t addr)
{
	acc |= mem[addr];
	update_nz(acc);
}

void
eor(uint32_t addr)
{
	acc ^= mem[addr];
	update_nz(acc);
}

void
lda(uint32_t addr)
{
	acc = mem[addr];
	update_nz(acc);
}

void
st(uint32_t addr, uint32_t val)
{
	mem[addr] = val;
}

void
cmp(uint32_t reg, uint32_t addr)
{
	uint32_t t;
	t = reg - mem[addr];
	if (t & 0x100)
		flags &= ~C;
	else
		flags |= C; // the carry flag is set when reg >= mem[addr]
	update_nz(t);
}

void
asl(uint32_t addr)
{
	uint32_t t;
	t = mem[addr];
	if (t & 0x80)
		flags |= C;
	else
		flags &= ~C;
	t <<= 1;
	st(addr, t);
	update_nz(t);
}

void
lsr(uint32_t addr)
{
	uint32_t t;
	t = mem[addr];
	if (t & 1)
		flags |= C;
	else
		flags &= ~C;
	t >>= 1;
	st(addr, t);
	update_nz(t);
}

void
rol(uint32_t addr)
{
	uint32_t t;
	t = mem[addr];
	t <<= 1;
	if (flags & C)
		t |= 1;
	if (t & 0x100)
		flags |= C;
	else
		flags &= ~C;
	st(addr, t);
	update_nz(t);
}

void
ror(uint32_t addr)
{
	uint32_t t;
	t = mem[addr];
	if (flags & C)
		t |= 0x100;
	if (t & 1)
		flags |= C;
	else
		flags &= ~C;
	t >>= 1;
	st(addr, t);
	update_nz(t);
}

void
inc(uint32_t addr)
{
	uint32_t t;
	t = mem[addr] + 1;
	st(addr, t);
	update_nz(t);
}

void
dec(uint32_t addr)
{
	uint32_t t;
	t = mem[addr] - 1;
	st(addr, t);
	update_nz(t);
}

void
br(uint32_t cond)
{
	uint16_t t;
	if (cond) {
		t = mem[pc];
		if (t & 0x80)
			t |= 0xff00; // extend sign
		pc += t + 1;
	} else
		pc++;
}

#define IMM pc
#define ZP mem[pc]
#define ZPX ((mem[pc] + x) & 0xff)
#define ZPY ((mem[pc] + y) & 0xff)
#define ZPIX (((mem[mem[pc]] | mem[(mem[pc] + 1) & 0xff] << 8) + x) & 0xffff) // (zp),x
#define ZPIY (((mem[mem[pc]] | mem[(mem[pc] + 1) & 0xff] << 8) + y) & 0xffff) // (zp),y
#define ZPXI (mem[(mem[pc] + x) & 0xff] | mem[(mem[pc] + x + 1) & 0xff] << 8) // (zp,x)
#define ZPYI (mem[(mem[pc] + y) & 0xff] | mem[(mem[pc] + y + 1) & 0xff] << 8) // (zp,y)
#define ABS (mem[pc] | mem[(pc + 1) & 0xffff] << 8)
#define ABSX (((mem[pc] | mem[(pc + 1) & 0xffff] << 8) + x) & 0xffff)
#define ABSY (((mem[pc] | mem[(pc + 1) & 0xffff] << 8) + y) & 0xffff)

void
func_adc_zpxi(void)
{
	adc(ZPXI);
	pc++;
}

void
func_adc_zp(void)
{
	adc(ZP);
	pc++;
}

void
func_adc_imm(void)
{
	adc(IMM);
	pc++;
}

void
func_adc_abs(void)
{
	adc(ABS);
	pc += 2;
}

void
func_adc_zpiy(void)
{
	adc(ZPIY);
	pc++;
}

void
func_adc_zpx(void)
{
	adc(ZPX);
	pc++;
}

void
func_adc_absy(void)
{
	adc(ABSY);
	pc += 2;
}

void
func_adc_absx(void)
{
	adc(ABSX);
	pc += 2;
}

void
func_sbc_zpxi(void)
{
	sbc(ZPXI);
	pc++;
}

void
func_sbc_zp(void)
{
	sbc(ZP);
	pc++;
}

void
func_sbc_imm(void)
{
	sbc(IMM);
	pc++;
}

void
func_sbc_abs(void)
{
	sbc(ABS);
	pc += 2;
}

void
func_sbc_zpiy(void)
{
	sbc(ZPIY);
	pc++;
}

void
func_sbc_zpx(void)
{
	sbc(ZPX);
	pc++;
}

void
func_sbc_absy(void)
{
	sbc(ABSY);
	pc += 2;
}

void
func_sbc_absx(void)
{
	sbc(ABSX);
	pc += 2;
}

void
func_and_zpxi(void)
{
	and(ZPXI);
	pc++;
}

void
func_and_zp(void)
{
	and(ZP);
	pc++;
}

void
func_and_imm(void)
{
	and(IMM);
	pc++;
}

void
func_and_abs(void)
{
	and(ABS);
	pc += 2;
}

void
func_and_zpiy(void)
{
	and(ZPIY);
	pc++;
}

void
func_and_zpx(void)
{
	and(ZPX);
	pc++;
}

void
func_and_absy(void)
{
	and(ABSY);
	pc += 2;
}

void
func_and_absx(void)
{
	and(ABSX);
	pc += 2;
}

void
func_ora_zpxi(void)
{
	ora(ZPXI);
	pc++;
}

void
func_ora_zp(void)
{
	ora(ZP);
	pc++;
}

void
func_ora_imm(void)
{
	ora(IMM);
	pc++;
}

void
func_ora_abs(void)
{
	ora(ABS);
	pc += 2;
}

void
func_ora_zpiy(void)
{
	ora(ZPIY);
	pc++;
}

void
func_ora_zpx(void)
{
	ora(ZPX);
	pc++;
}

void
func_ora_absy(void)
{
	ora(ABSY);
	pc += 2;
}

void
func_ora_absx(void)
{
	ora(ABSX);
	pc += 2;
}

void
func_eor_zpxi(void)
{
	eor(ZPXI);
	pc++;
}

void
func_eor_zp(void)
{
	eor(ZP);
	pc++;
}

void
func_eor_imm(void)
{
	eor(IMM);
	pc++;
}

void
func_eor_abs(void)
{
	eor(ABS);
	pc += 2;
}

void
func_eor_zpiy(void)
{
	eor(ZPIY);
	pc++;
}

void
func_eor_zpx(void)
{
	eor(ZPX);
	pc++;
}

void
func_eor_absy(void)
{
	eor(ABSY);
	pc += 2;
}

void
func_eor_absx(void)
{
	eor(ABSX);
	pc += 2;
}

void
func_lda_zpxi(void)
{
	lda(ZPXI);
	pc++;
}

void
func_lda_zp(void)
{
	lda(ZP);
	pc++;
}

void
func_lda_imm(void)
{
	lda(IMM);
	pc++;
}

void
func_lda_abs(void)
{
	lda(ABS);
	pc += 2;
}

void
func_lda_zpiy(void)
{
	lda(ZPIY);
	pc++;
}

void
func_lda_zpx(void)
{
	lda(ZPX);
	pc++;
}

void
func_lda_absy(void)
{
	lda(ABSY);
	pc += 2;
}

void
func_lda_absx(void)
{
	lda(ABSX);
	pc += 2;
}

void
func_sta_zpxi(void)
{
	st(ZPXI, acc);
	pc++;
}

void
func_sta_zp(void)
{
	st(ZP, acc);
	pc++;
}

void
func_sta_abs(void)
{
	st(ABS, acc);
	pc += 2;
}

void
func_sta_zpiy(void)
{
	st(ZPIY, acc);
	pc++;
}

void
func_sta_zpx(void)
{
	st(ZPX, acc);
	pc++;
}

void
func_sta_absy(void)
{
	st(ABSY, acc);
	pc += 2;
}

void
func_sta_absx(void)
{
	st(ABSX, acc);
	pc += 2;
}

void
func_cmp_zpxi(void)
{
	cmp(acc, ZPXI);
	pc++;
}

void
func_cmp_zp(void)
{
	cmp(acc, ZP);
	pc++;
}

void
func_cmp_imm(void)
{
	cmp(acc, IMM);
	pc++;
}

void
func_cmp_abs(void)
{
	cmp(acc, ABS);
	pc += 2;
}

void
func_cmp_zpiy(void)
{
	cmp(acc, ZPIY);
	pc++;
}

void
func_cmp_zpx(void)
{
	cmp(acc, ZPX);
	pc++;
}

void
func_cmp_absy(void)
{
	cmp(acc, ABSY);
	pc += 2;
}

void
func_cmp_absx(void)
{
	cmp(acc, ABSX);
	pc += 2;
}

void
func_lsr_zp(void)
{
	lsr(ZP);
	pc++;
}

void
func_lsr_acc(void)
{
	if (acc & 1)
		flags |= C;
	else
		flags &= ~C;
	acc >>= 1;
	update_nz(acc);
}

void
func_lsr_abs(void)
{
	lsr(ABS);
	pc += 2;
}

void
func_lsr_zpx(void)
{
	lsr(ZPX);
	pc++;
}

void
func_lsr_absx(void)
{
	lsr(ABSX);
	pc += 2;
}

void
func_asl_zp(void)
{
	asl(ZP);
	pc++;
}

void
func_asl_acc(void)
{
	if (acc & 0x80)
		flags |= C;
	else
		flags &= ~C;
	acc <<= 1;
	update_nz(acc);
}

void
func_asl_abs(void)
{
	asl(ABS);
	pc += 2;
}

void
func_asl_zpx(void)
{
	asl(ZPX);
	pc++;
}

void
func_asl_absx(void)
{
	asl(ABSX);
	pc += 2;
}

void
func_rol_zp(void)
{
	rol(ZP);
	pc++;
}

void
func_rol_acc(void)
{
	uint32_t t;
	t = (uint32_t) acc << 1;
	if (flags & C)
		t |= 1;
	if (t & 0x100)
		flags |= C;
	else
		flags &= ~C;
	acc = t;
	update_nz(acc);
}

void
func_rol_abs(void)
{
	rol(ABS);
	pc += 2;
}

void
func_rol_zpx(void)
{
	rol(ZPX);
	pc++;
}

void
func_rol_absx(void)
{
	rol(ABSX);
	pc += 2;
}

void
func_ror_zp(void)
{
	ror(ZP);
	pc++;
}

void
func_ror_acc(void)
{
	uint32_t t;
	t = acc;
	if (flags & C)
		t |= 0x100;
	if (t & 1)
		flags |= C;
	else
		flags &= ~C;
	acc = t >> 1;
	update_nz(acc);
}

void
func_ror_abs(void)
{
	ror(ABS);
	pc += 2;
}

void
func_ror_zpx(void)
{
	ror(ZPX);
	pc++;
}

void
func_ror_absx(void)
{
	ror(ABSX);
	pc += 2;
}

void
func_ldx_imm(void)
{
	x = mem[IMM];
	update_nz(x);
	pc++;
}

void
func_ldx_zp(void)
{
	x = mem[ZP];
	update_nz(x);
	pc++;
}

void
func_ldx_abs(void)
{
	x = mem[ABS];
	update_nz(x);
	pc += 2;
}

void
func_ldx_zpy(void)
{
	x = mem[ZPY];
	update_nz(x);
	pc++;
}

void
func_ldx_absy(void)
{
	x = mem[ABSY];
	update_nz(x);
	pc += 2;
}

void
func_stx_zp(void)
{
	st(ZP, x);
	pc++;
}

void
func_stx_abs(void)
{
	st(ABS, x);
	pc += 2;
}

void
func_stx_zpy(void)
{
	st(ZPY, x);
	pc++;
}

void
func_ldy_imm(void)
{
	y = mem[IMM];
	update_nz(y);
	pc++;
}

void
func_ldy_zp(void)
{
	y = mem[ZP];
	update_nz(y);
	pc++;
}

void
func_ldy_abs(void)
{
	y = mem[ABS];
	update_nz(y);
	pc += 2;
}

void
func_ldy_zpx(void)
{
	y = mem[ZPX];
	update_nz(y);
	pc++;
}

void
func_ldy_absx(void)
{
	y = mem[ABSX];
	update_nz(y);
	pc += 2;
}

void
func_sty_zp(void)
{
	st(ZP, y);
	pc++;
}

void
func_sty_abs(void)
{
	st(ABS, y);
	pc += 2;
}

void
func_sty_zpx(void)
{
	st(ZPX, y);
	pc++;
}

void
func_dec_zp(void)
{
	dec(ZP);
	pc++;
}

void
func_dec_abs(void)
{
	dec(ABS);
	pc += 2;
}

void
func_dec_zpx(void)
{
	dec(ZPX);
	pc++;
}

void
func_dec_absx(void)
{
	dec(ABSX);
	pc += 2;
}

void
func_inc_zp(void)
{
	inc(ZP);
	pc++;
}

void
func_inc_abs(void)
{
	inc(ABS);
	pc += 2;
}

void
func_inc_zpx(void)
{
	inc(ZPX);
	pc++;
}

void
func_inc_absx(void)
{
	inc(ABSX);
	pc += 2;
}

void
func_cpx_imm(void)
{
	cmp(x, IMM);
	pc++;
}

void
func_cpx_zp(void)
{
	cmp(x, ZP);
	pc++;
}

void
func_cpx_abs(void)
{
	cmp(x, ABS);
	pc += 2;
}

void
func_cpy_imm(void)
{
	cmp(y, IMM);
	pc++;
}

void
func_cpy_zp(void)
{
	cmp(y, ZP);
	pc++;
}

void
func_cpy_abs(void)
{
	cmp(y, ABS);
	pc += 2;
}

void
func_bit_zp(void)
{
	uint32_t t;
	t = mem[ZP];
	if (t & 0x80)
		flags |= N;
	else
		flags &= ~N;
	if (t & 0x40)
		flags |= V;
	else
		flags &= ~V;
	if ((acc & t) == 0)
		flags |= Z;
	else
		flags &= ~Z;
	pc++;
}

void
func_bit_abs(void)
{
	uint32_t t;
	t = mem[ABS];
	if (t & 0x80)
		flags |= N;
	else
		flags &= ~N;
	if (t & 0x40)
		flags |= V;
	else
		flags &= ~V;
	if ((acc & t) == 0)
		flags |= Z;
	else
		flags &= ~Z;
	pc += 2;
}

void
func_jmp(void)
{
	pc = ABS;
}

void
func_jmpi(void)
{
	uint16_t addr;
	addr = ABS;
	pc = mem[addr] | mem[(addr & 0xff00) | ((addr + 1) & 0xff)] << 8;
}

void
func_jsr(void)
{
	char *s;
	uint16_t t; // uint16_t so t++ increments modulo 65536

	t = pc; // t is address of jsr plus 1

	pc = mem[pc] | mem[(pc + 1) & 0xffff] << 8;

	if (pc < 0xfff0) {
		sp -= 2;
		mem[0x100 + sp] = t + 1;
		mem[0x100 + ((sp + 1) & 0xff)] = (t + 1) >> 8;
		return;
	}

	switch (pc) {

	// putc

	case 0xfff1:
		pc = t + 2;
		putchar(acc);
		break;

	// puts

	case 0xfff2:
		pc = t + 4;
		t = mem[(pc - 2) & 0xffff] | mem[(pc - 1) & 0xffff] << 8;
		while (mem[t])
			putchar(mem[t++]);
		break;

	// gets

	case 0xfff3:
		pc = t + 2;
		s = (char *) mem + 512;
		fgets(s, 240, stdin);
		while (*s && *s != '\n') {
			*s = toupper(*s);
			s++;
		}
		*s = 0;
		break;

	default:
		exit(1);
		break;
	}
}

void
func_rts(void)
{
	pc = (mem[0x100 + sp] | mem[0x100 + ((sp + 1) & 0xff)] << 8) + 1;
	sp += 2;
}

void
func_rti(void)
{
	flags = mem[0x100 + sp];
	pc = (mem[0x100 + ((sp + 1) & 0xff)] | mem[0x100 + ((sp + 2) & 0xff)] << 8) + 1;
	sp += 3;
}

void
func_inx(void)
{
	x++;
	update_nz(x);
}

void
func_dex(void)
{
	x--;
	update_nz(x);
}

void
func_iny(void)
{
	y++;
	update_nz(y);
}

void
func_dey(void)
{
	y--;
	update_nz(y);
}

void
func_clc(void)
{
	flags &= ~C;
}

void
func_sec(void)
{
	flags |= C;
}

void
func_cli(void)
{
	flags &= ~I;
}

void
func_sti(void)
{
	flags |= I;
}

void
func_cld(void)
{
	flags &= ~D;
}

void
func_std(void)
{
	flags |= D;
}

void
func_clv(void)
{
	flags &= ~V;
}

void
func_tax(void)
{
	x = acc;
	update_nz(x);
}

void
func_txa(void)
{
	acc = x;
	update_nz(acc);
}

void
func_tay(void)
{
	y = acc;
	update_nz(y);
}

void
func_tya(void)
{
	acc = y;
	update_nz(acc);
}

void
func_tsx(void)
{
	x = sp;
	update_nz(x);
}

void
func_txs(void)
{
	sp = x; // no flags are affected
}

void
func_bpl(void)
{
	br((flags & N) ^ N);
}

void
func_bmi(void)
{
	br(flags & N);
}

void
func_bvc(void)
{
	br((flags & V) ^ V);
}

void
func_bvs(void)
{
	br(flags & V);
}

void
func_bcc(void)
{
	br((flags & C) ^ C);
}

void
func_bcs(void)
{
	br(flags & C);
}

void
func_bne(void)
{
	br((flags & Z) ^ Z);
}

void
func_beq(void)
{
	br(flags & Z);
}

// BRK and PHP push B=1, IRQ and NMI push B=0

void
func_php(void)
{
	sp--;
	mem[0x100 + sp] = flags | E | B;
}

void
func_plp(void)
{
	flags = mem[0x100 + sp];
	sp++;
}

void
func_pha(void)
{
	sp--;
	mem[0x100 + sp] = acc;
}

void
func_pla(void)
{
	acc = mem[0x100 + sp];
	sp++;
	update_nz(acc);
}

// BRK and PHP push B=1, IRQ and NMI push B=0

void
func_brk(void)
{
	pc -= 1;
	sp -= 3;

	mem[0x100 + sp] = flags | E | B;
	mem[0x100 + ((sp + 1) & 0xff)] = pc;
	mem[0x100 + ((sp + 2) & 0xff)] = pc >> 8;

	pc = mem[0xfffe] | mem[0xffff] << 8;

	flags |= I;
}

void
func_nop(void)
{
}

void
func_undef(void)
{
	pc -= 1;
	printf("undef %04x:%02x\n", (int) pc, (int) mem[pc]);
	exit(1);
}

void
update_nz(uint32_t t)
{
	if (t & 0x80)
		flags |= N;
	else
		flags &= ~N;
	if ((t & 0xff) == 0)
		flags |= Z;
	else
		flags &= ~Z;
}
