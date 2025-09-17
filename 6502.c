void
adc(uint32_t addr)
{
	uint32_t t, h;
	t = (uint32_t) acc + mem[addr] + cf;
	of = ((t ^ acc) & (t ^ mem[addr]) & 0x80) ? 1 : 0;
	if (df) {
		h = (acc & 0xf) + (mem[addr] & 0xf) + cf; // half add
		if ((t & 0xf) > 9 || (h & 0x10))
			t += 6;
		if ((t & 0xf0) > 0x90 || (t & 0x100))
			t += 0x60;
	}
	acc = t;
	zf = acc ? 0 : 1;
	cf = (t & 0x100) ? 1 : 0;
	nf = (t & 0x80) ? 1 : 0;
}

void
sbc(uint32_t addr)
{
	uint32_t t, h;
	t = (uint32_t) acc - mem[addr] - (cf ^ 1);
	of = ((t ^ acc) & (t ^ mem[addr] ^ 0x80) & 0x80) ? 1 : 0;
	if (df) {
		h = (acc & 0xf) - (mem[addr] & 0xf) - (cf ^ 1); // half subtract
		if ((t & 0xf) > 9 || (h & 0x10))
			t += 6;
		if ((t & 0xf0) > 0x90 || (t & 0x100))
			t += 0x60;
	}
	acc = t;
	zf = acc ? 0 : 1;
	cf = (t & 0x100) ? 0 : 1;
	nf = (t & 0x80) ? 1 : 0;
}

void
and(uint32_t addr)
{
	acc &= mem[addr];
	zf = acc ? 0 : 1;
	nf = (acc & 0x80) ? 1 : 0;
}

void
ora(uint32_t addr)
{
	acc |= mem[addr];
	zf = acc ? 0 : 1;
	nf = (acc & 0x80) ? 1 : 0;
}

void
eor(uint32_t addr)
{
	acc ^= mem[addr];
	zf = acc ? 0 : 1;
	nf = (acc & 0x80) ? 1 : 0;
}

void
lda(uint32_t addr)
{
	acc = mem[addr];
	zf = acc ? 0 : 1;
	nf = (acc & 0x80) ? 1 : 0;
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
	zf = (t & 0xff) ? 0 : 1;
	cf = (t & 0x100) ? 0 : 1;
	nf = (t & 0x80) ? 1 : 0;
}

void
asl(uint32_t addr)
{
	uint8_t t;
	t = mem[addr];
	cf = (t & 0x80) ? 1 : 0;
	t <<= 1;
	zf = t ? 0 : 1;
	nf = (t & 0x80) ? 1 : 0;
	st(addr, t);
}

void
lsr(uint32_t addr)
{
	uint8_t t;
	t = mem[addr];
	cf = t & 1;
	t >>= 1;
	zf = t ? 0 : 1;
	nf = 0;
	st(addr, t);
}

void
rol(uint32_t addr)
{
	uint8_t t, u;
	t = mem[addr];
	u = t;
	t = (t << 1) | cf;
	zf = t ? 0 : 1;
	nf = (t & 0x80) ? 1 : 0;
	cf = (u & 0x80) ? 1 : 0;
	st(addr, t);
}

void
ror(uint32_t addr)
{
	uint8_t t, u;
	t = mem[addr];
	u = t;
	t = (t >> 1) | (cf << 7);
	zf = t ? 0 : 1;
	nf = (t & 0x80) ? 1 : 0;
	cf = (u & 0x01) ? 1 : 0;
	st(addr, t);
}

void
inc(uint32_t addr)
{
	uint8_t t;
	t = mem[addr] + 1;
	zf = t ? 0 : 1;
	nf = (t & 0x80) ? 1 : 0;
	st(addr, t);
}

void
dec(uint32_t addr)
{
	uint8_t t;
	t = mem[addr] - 1;
	zf = t ? 0 : 1;
	nf = (t & 0x80) ? 1 : 0;
	st(addr, t);
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
	cf = acc & 1;
	acc >>= 1;
	zf = acc ? 0 : 1;
	nf = 0;
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
	cf = (acc & 0x80) ? 1 : 0;
	acc <<= 1;
	zf = acc ? 0 : 1;
	nf = (acc & 0x80) ? 1 : 0;
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
	uint8_t t;
	t = acc;
	acc = acc << 1 | cf;
	zf = acc ? 0 : 1;
	nf = (acc & 0x80) ? 1 : 0;
	cf = (t & 0x80) ? 1 : 0;
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
	uint8_t t;
	t = acc;
	acc = (acc >> 1) | (cf << 7);
	zf = acc ? 0 : 1;
	nf = (acc & 0x80) ? 1 : 0;
	cf = t & 1;
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
	zf = x ? 0 : 1;
	nf = (x & 0x80) ? 1 : 0;
	pc++;
}

void
func_ldx_zp(void)
{
	x = mem[ZP];
	zf = x ? 0 : 1;
	nf = (x & 0x80) ? 1 : 0;
	pc++;
}

void
func_ldx_abs(void)
{
	x = mem[ABS];
	zf = x ? 0 : 1;
	nf = (x & 0x80) ? 1 : 0;
	pc += 2;
}

void
func_ldx_zpy(void)
{
	x = mem[ZPY];
	zf = x ? 0 : 1;
	nf = (x & 0x80) ? 1 : 0;
	pc++;
}

void
func_ldx_absy(void)
{
	x = mem[ABSY];
	zf = x ? 0 : 1;
	nf = (x & 0x80) ? 1 : 0;
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
	zf = y ? 0 : 1;
	nf = (y & 0x80) ? 1 : 0;
	pc++;
}

void
func_ldy_zp(void)
{
	y = mem[ZP];
	zf = y ? 0 : 1;
	nf = (y & 0x80) ? 1 : 0;
	pc++;
}

void
func_ldy_abs(void)
{
	y = mem[ABS];
	zf = y ? 0 : 1;
	nf = (y & 0x80) ? 1 : 0;
	pc += 2;
}

void
func_ldy_zpx(void)
{
	y = mem[ZPX];
	zf = y ? 0 : 1;
	nf = (y & 0x80) ? 1 : 0;
	pc++;
}

void
func_ldy_absx(void)
{
	y = mem[ABSX];
	zf = y ? 0 : 1;
	nf = (y & 0x80) ? 1 : 0;
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
	uint8_t t;
	t = mem[ZP];
	nf = (t & 0x80) ? 1 : 0;
	of = (t & 0x40) ? 1 : 0;
	zf = (acc & t) ? 0 : 1;
	pc++;
}

void
func_bit_abs(void)
{
	uint8_t t;
	t = mem[ABS];
	nf = (t & 0x80) ? 1 : 0;
	of = (t & 0x40) ? 1 : 0;
	zf = (acc & t) ? 0 : 1;
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
	uint16_t t;

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
	uint8_t t;
	t = mem[0x100 + sp];
	nf = (t & 0x80) ? 1 : 0;
	of = (t & 0x40) ? 1 : 0;
	df = (t & 0x08) ? 1 : 0;
	id = (t & 0x04) ? 1 : 0;
	zf = (t & 0x02) ? 1 : 0;
	cf = (t & 0x01) ? 1 : 0;
	pc = (mem[0x100 + ((sp + 1) & 0xff)] | mem[0x100 + ((sp + 2) & 0xff)] << 8) + 1;
	sp += 3;
}

void
func_inx(void)
{
	x++;
	zf = x ? 0 : 1;
	nf = (x & 0x80) ? 1 : 0;
}

void
func_dex(void)
{
	x--;
	zf = x ? 0 : 1;
	nf = (x & 0x80) ? 1 : 0;
}

void
func_iny(void)
{
	y++;
	zf = y ? 0 : 1;
	nf = (y & 0x80) ? 1 : 0;
}

void
func_dey(void)
{
	y--;
	zf = y ? 0 : 1;
	nf = (y & 0x80) ? 1 : 0;
}

void
func_clc(void)
{
	cf = 0;
}

void
func_sec(void)
{
	cf = 1;
}

void
func_cli(void)
{
	id = 0;
}

void
func_sti(void)
{
	id = 1;
}

void
func_cld(void)
{
	df = 0;
}

void
func_std(void)
{
	df = 1;
}

void
func_clv(void)
{
	of = 0;
}

void
func_tax(void)
{
	x = acc;
	zf = x ? 0 : 1;
	nf = (x & 0x80) ? 1 : 0;
}

void
func_txa(void)
{
	acc = x;
	zf = acc ? 0 : 1;
	nf = (acc & 0x80) ? 1 : 0;
}

void
func_tay(void)
{
	y = acc;
	zf = y ? 0 : 1;
	nf = (y & 0x80) ? 1 : 0;
}

void
func_tya(void)
{
	acc = y;
	zf = acc ? 0 : 1;
	nf = (acc & 0x80) ? 1 : 0;
}

void
func_tsx(void)
{
	x = sp;
	zf = x ? 0 : 1;
	nf = (x & 0x80) ? 1 : 0;
}

// no flags affected

void
func_txs(void)
{
	sp = x;
}

void
func_bpl(void)
{
	br(nf ^ 1);
}

void
func_bmi(void)
{
	br(nf);
}

void
func_bvc(void)
{
	br(of ^ 1);
}

void
func_bvs(void)
{
	br(of);
}

void
func_bcc(void)
{
	br(cf ^ 1);
}

void
func_bcs(void)
{
	br(cf);
}

void
func_bne(void)
{
	br(zf ^ 1);
}

void
func_beq(void)
{
	br(zf);
}

// BRK and PHP push B=1, IRQ and NMI push B=0

void
func_php(void)
{
	sp--;
	mem[0x100 + sp] = nf << 7 | of << 6 | 1 << 5 | 1 << 4 | df << 3 | id << 2 | zf << 1 | cf;
}

void
func_plp(void)
{
	uint8_t t;

	t = mem[0x100 + sp];
	sp++;

	nf = (t & 0x80) ? 1 : 0;
	of = (t & 0x40) ? 1 : 0;
	df = (t & 0x08) ? 1 : 0;
	id = (t & 0x04) ? 1 : 0;
	zf = (t & 0x02) ? 1 : 0;
	cf = (t & 0x01) ? 1 : 0;
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
	zf = acc ? 0 : 1;
	nf = (acc & 0x80) ? 1 : 0;
}

// BRK and PHP push B=1, IRQ and NMI push B=0

void
func_brk(void)
{
	pc -= 1;
	sp -= 3;

	// return address

	mem[0x100 + ((sp + 1) & 0xff)] = pc;
	mem[0x100 + ((sp + 2) & 0xff)] = pc >> 8;

	// flags

	mem[0x100 + sp] = nf << 7 | of << 6 | 1 << 5 | 1 << 4 | df << 3 | id << 2 | zf << 1 | cf;

	pc = mem[0xfffe] | mem[0xffff] << 8;

	id = 1;
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
