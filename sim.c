/* Tiny 6502 simulator

BSD 2-Clause License

Copyright (c) 2025, George Weigt
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint8_t acc, x, y, sp, *mem;
uint8_t nf, of, df, id, zf, cf;
uint16_t pc;

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
	if (addr == 0xfff0)
		putchar(val);
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
	t = mem[addr]++;
	zf = t ? 0 : 1;
	nf = (t & 0x80) ? 1 : 0;
	st(addr, t);
}

void
dec(uint32_t addr)
{
	uint8_t t;
	t = mem[addr]--;
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
func_adc_zpxi(void) // (zp,x)
{
	adc(ZPXI);
	pc++;
}

void
func_adc_zp(void) // zp
{
	adc(ZP);
	pc++;
}

void
func_adc_imm(void) // imm
{
	adc(IMM);
	pc++;
}

void
func_adc_abs(void) // abs
{
	adc(ABS);
	pc += 2;
}

void
func_adc_zpiy(void) // (zp),y
{
	adc(ZPIY);
	pc++;
}

void
func_adc_zpx(void) // zp,x
{
	adc(ZPX);
	pc++;
}

void
func_adc_absy(void) // abs,y
{
	adc(ABSY);
	pc += 2;
}

void
func_adc_absx(void) // abs,x
{
	adc(ABSX);
	pc += 2;
}

void
func_sbc_zpxi(void) // (zp,x)
{
	sbc(ZPXI);
	pc++;
}

void
func_sbc_zp(void) // zp
{
	sbc(ZP);
	pc++;
}

void
func_sbc_imm(void) // imm
{
	sbc(IMM);
	pc++;
}

void
func_sbc_abs(void) // abs
{
	sbc(ABS);
	pc += 2;
}

void
func_sbc_zpiy(void) // (zp),y
{
	sbc(ZPIY);
	pc++;
}

void
func_sbc_zpx(void) // zp,x
{
	sbc(ZPX);
	pc++;
}

void
func_sbc_absy(void) // abs,y
{
	sbc(ABSY);
	pc += 2;
}

void
func_sbc_absx(void) // abs,x
{
	sbc(ABSX);
	pc += 2;
}

void
func_and_zpxi(void) // (zp,x)
{
	and(ZPXI);
	pc++;
}

void
func_and_zp(void) // zp
{
	and(ZP);
	pc++;
}

void
func_and_imm(void) // imm
{
	and(IMM);
	pc++;
}

void
func_and_abs(void) // abs
{
	and(ABS);
	pc += 2;
}

void
func_and_zpiy(void) // (zp),y
{
	and(ZPIY);
	pc++;
}

void
func_and_zpx(void) // zp,x
{
	and(ZPX);
	pc++;
}

void
func_and_absy(void) // abs,y
{
	and(ABSY);
	pc += 2;
}

void
func_and_absx(void) // abs,x
{
	and(ABSX);
	pc += 2;
}

void
func_ora_zpxi(void) // (zp,x)
{
	ora(ZPXI);
	pc++;
}

void
func_ora_zp(void) // zp
{
	ora(ZP);
	pc++;
}

void
func_ora_imm(void) // imm
{
	ora(IMM);
	pc++;
}

void
func_ora_abs(void) // abs
{
	ora(ABS);
	pc += 2;
}

void
func_ora_zpiy(void) // (zp),y
{
	ora(ZPIY);
	pc++;
}

void
func_ora_zpx(void) // zp,x
{
	ora(ZPX);
	pc++;
}

void
func_ora_absy(void) // abs,y
{
	ora(ABSY);
	pc += 2;
}

void
func_ora_absx(void) // abs,x
{
	ora(ABSX);
	pc += 2;
}

void
func_eor_zpxi(void) // (zp,x)
{
	eor(ZPXI);
	pc++;
}

void
func_eor_zp(void) // zp
{
	eor(ZP);
	pc++;
}

void
func_eor_imm(void) // imm
{
	eor(IMM);
	pc++;
}

void
func_eor_abs(void) // abs
{
	eor(ABS);
	pc += 2;
}

void
func_eor_zpiy(void) // (zp),y
{
	eor(ZPIY);
	pc++;
}

void
func_eor_zpx(void) // zp,x
{
	eor(ZPX);
	pc++;
}

void
func_eor_absy(void) // abs,y
{
	eor(ABSY);
	pc += 2;
}

void
func_eor_absx(void) // abs,x
{
	eor(ABSX);
	pc += 2;
}

void
func_lda_zpxi(void) // (zp,x)
{
	lda(ZPXI);
	pc++;
}

void
func_lda_zp(void) // zp
{
	lda(ZP);
	pc++;
}

void
func_lda_imm(void) // imm
{
	lda(IMM);
	pc++;
}

void
func_lda_abs(void) // abs
{
	lda(ABS);
	pc += 2;
}

void
func_lda_zpiy(void) // (zp),y
{
	lda(ZPIY);
	pc++;
}

void
func_lda_zpx(void) // zp,x
{
	lda(ZPX);
	pc++;
}

void
func_lda_absy(void) // abs,y
{
	lda(ABSY);
	pc += 2;
}

void
func_lda_absx(void) // abs,x
{
	lda(ABSX);
	pc += 2;
}

void
func_sta_zpxi(void) // (zp,x)
{
	st(ZPXI, acc);
	pc++;
}

void
func_sta_zp(void) // zp
{
	st(ZP, acc);
	pc++;
}

void
func_sta_abs(void) // abs
{
	st(ABS, acc);
	pc += 2;
}

void
func_sta_zpiy(void) // (zp),y
{
	st(ZPIY, acc);
	pc++;
}

void
func_sta_zpx(void) // zp,x
{
	st(ZPX, acc);
	pc++;
}

void
func_sta_absy(void) // abs,y
{
	st(ABSY, acc);
	pc += 2;
}

void
func_sta_absx(void) // abs,x
{
	st(ABSX, acc);
	pc += 2;
}

void
func_cmp_zpxi(void) // (zp,x)
{
	cmp(acc, ZPXI);
	pc++;
}

void
func_cmp_zp(void) // zp
{
	cmp(acc, ZP);
	pc++;
}

void
func_cmp_imm(void) // imm
{
	cmp(acc, IMM);
	pc++;
}

void
func_cmp_abs(void) // abs
{
	cmp(acc, ABS);
	pc += 2;
}

void
func_cmp_zpiy(void) // (zp),y
{
	cmp(acc, ZPIY);
	pc++;
}

void
func_cmp_zpx(void) // zp,x
{
	cmp(acc, ZPX);
	pc++;
}

void
func_cmp_absy(void) // abs,y
{
	cmp(acc, ABSY);
	pc += 2;
}

void
func_cmp_absx(void) // abs,x
{
	cmp(acc, ABSX);
	pc += 2;
}

void
func_lsr_zp(void) // zp
{
	lsr(ZP);
	pc++;
}

void
func_lsr_acc(void) // acc
{
	cf = acc & 1;
	acc >>= 1;
	zf = acc ? 0 : 1;
	nf = 0;
}

void
func_lsr_abs(void) // abs
{
	lsr(ABS);
	pc += 2;
}

void
func_lsr_zpx(void) // zp,x
{
	lsr(ZPX);
	pc++;
}

void
func_lsr_absx(void) // abs,x
{
	lsr(ABSX);
	pc += 2;
}

void
func_asl_zp(void) // zp
{
	asl(ZP);
	pc++;
}

void
func_asl_acc(void) // acc
{
	cf = (acc & 0x80) ? 1 : 0;
	acc <<= 1;
	zf = acc ? 0 : 1;
	nf = (acc & 0x80) ? 1 : 0;
}

void
func_asl_abs(void) // abs
{
	asl(ABS);
	pc += 2;
}

void
func_asl_zpx(void) // zp,x
{
	asl(ZPX);
	pc++;
}

void
func_asl_absx(void) // abs,x
{
	asl(ABSX);
	pc += 2;
}

void
func_rol_zp(void) // zp
{
	rol(ZP);
	pc++;
}

void
func_rol_acc(void) // acc
{
	uint8_t t;
	t = acc;
	acc = acc << 1 | cf;
	zf = acc ? 0 : 1;
	nf = (acc & 0x80) ? 1 : 0;
	cf = (t & 0x80) ? 1 : 0;
}

void
func_rol_abs(void) // abs
{
	rol(ABS);
	pc += 2;
}

void
func_rol_zpx(void) // zp,x
{
	rol(ZPX);
	pc++;
}

void
func_rol_absx(void) // abs,x
{
	rol(ABSX);
	pc += 2;
}

void
func_ror_zp(void) // zp
{
	ror(ZP);
	pc++;
}

void
func_ror_acc(void) // acc
{
	uint8_t t;
	t = acc;
	acc = (acc >> 1) | (cf << 7);
	zf = acc ? 0 : 1;
	nf = (acc & 0x80) ? 1 : 0;
	cf = t & 1;
}

void
func_ror_abs(void) // abs
{
	ror(ABS);
	pc += 2;
}

void
func_ror_zpx(void) // zp,x
{
	ror(ZPX);
	pc++;
}

void
func_ror_absx(void) // abs,x
{
	ror(ABSX);
	pc += 2;
}

void
func_ldx_imm(void) // imm
{
	x = mem[IMM];
	zf = x ? 0 : 1;
	nf = (x & 0x80) ? 1 : 0;
	pc++;
}

void
func_ldx_zp(void) // zp
{
	x = mem[ZP];
	zf = x ? 0 : 1;
	nf = (x & 0x80) ? 1 : 0;
	pc++;
}

void
func_ldx_abs(void) // abs
{
	x = mem[ABS];
	zf = x ? 0 : 1;
	nf = (x & 0x80) ? 1 : 0;
	pc += 2;
}

void
func_ldx_zpy(void) // zp,y
{
	x = mem[ZPY];
	zf = x ? 0 : 1;
	nf = (x & 0x80) ? 1 : 0;
	pc++;
}

void
func_ldx_absy(void) // abs,y
{
	x = mem[ABSY];
	zf = x ? 0 : 1;
	nf = (x & 0x80) ? 1 : 0;
	pc += 2;
}

void
func_stx_zp(void) // zp
{
	st(ZP, x);
	pc++;
}

void
func_stx_abs(void) // abs
{
	st(ABS, x);
	pc += 2;
}

void
func_stx_zpy(void) // zp,y
{
	st(ZPY, x);
	pc++;
}

void
func_ldy_imm(void) // imm
{
	y = mem[IMM];
	zf = y ? 0 : 1;
	nf = (y & 0x80) ? 1 : 0;
	pc++;
}

void
func_ldy_zp(void) // zp
{
	y = mem[ZP];
	zf = y ? 0 : 1;
	nf = (y & 0x80) ? 1 : 0;
	pc++;
}

void
func_ldy_abs(void) // abs
{
	y = mem[ABS];
	zf = y ? 0 : 1;
	nf = (y & 0x80) ? 1 : 0;
	pc += 2;
}

void
func_ldy_zpx(void) // zp,x
{
	y = mem[ZPX];
	zf = y ? 0 : 1;
	nf = (y & 0x80) ? 1 : 0;
	pc++;
}

void
func_ldy_absx(void) // abs,x
{
	y = mem[ABSX];
	zf = y ? 0 : 1;
	nf = (y & 0x80) ? 1 : 0;
	pc += 2;
}

void
func_sty_zp(void) // zp
{
	st(ZP, y);
	pc++;
}

void
func_sty_abs(void) // abs
{
	st(ABS, y);
	pc += 2;
}

void
func_sty_zpx(void) // zp,x
{
	st(ZPX, y);
	pc++;
}

void
func_dec_zp(void) // zp
{
	dec(ZP);
	pc++;
}

void
func_dec_abs(void) // abs
{
	dec(ABS);
	pc += 2;
}

void
func_dec_zpx(void) // zp,x
{
	dec(ZPX);
	pc++;
}

void
func_dec_absx(void) // abs,x
{
	dec(ABSX);
	pc += 2;
}

void
func_inc_zp(void) // zp
{
	inc(ZP);
	pc++;
}

void
func_inc_abs(void) // abs
{
	inc(ABS);
	pc += 2;
}

void
func_inc_zpx(void) // zp,x
{
	inc(ZPX);
	pc++;
}

void
func_inc_absx(void) // abs,x
{
	inc(ABSX);
	pc += 2;
}

void
func_cpx_imm(void) // imm
{
	cmp(x, IMM);
	pc++;
}

void
func_cpx_zp(void) // zp
{
	cmp(x, ZP);
	pc++;
}

void
func_cpx_abs(void) // abs
{
	cmp(x, ABS);
	pc += 2;
}

void
func_cpy_imm(void) // imm
{
	cmp(y, IMM);
	pc++;
}

void
func_cpy_zp(void) // zp
{
	cmp(y, ZP);
	pc++;
}

void
func_cpy_abs(void) // abs
{
	cmp(y, ABS);
	pc += 2;
}

void
func_bit_zp(void) // zp
{
	uint8_t t;
	t = mem[ZP];
	nf = (t & 0x80) ? 1 : 0;
	of = (t & 0x40) ? 1 : 0;
	zf = (acc & t) ? 0 : 1;
	pc++;
}

void
func_bit_abs(void) // abs
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
	t = pc + 1;
	pc = mem[pc] | mem[t] << 8;
	mem[0x100 + --sp] = t >> 8;
	mem[0x100 + --sp] = t;
}

void
func_rts(void)
{
	pc = mem[0x100 + sp++];
	pc |= mem[0x100 + sp++] << 8;
	pc++;
}

void
func_rti(void)
{
	uint8_t t;
	t = mem[0x100 + sp++];
	nf = (t & 0x80) ? 1 : 0;
	of = (t & 0x40) ? 1 : 0;
	df = (t & 0x08) ? 1 : 0;
	id = (t & 0x04) ? 1 : 0;
	zf = (t & 0x02) ? 1 : 0;
	cf = (t & 0x01) ? 1 : 0;
	pc = mem[0x100 + sp++];
	pc |= mem[0x100 + sp++] << 8;
	pc++;
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
	nf = (x & 0x80) ? 0 : 1;
}

void
func_txs(void)
{
	sp = x;
	// no flags are affected
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

void
func_php(void)
{
	mem[0x100 + --sp] = nf << 7 | of << 6 | 1 << 5 | 1 << 4 | df << 3 | id << 2 | zf << 1 | cf;
}

void
func_plp(void)
{
	uint8_t t;
	t = mem[0x100 + sp++];
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
	mem[0x100 + --sp] = acc;
}

void
func_pla(void)
{
	acc = mem[0x100 + sp++];
	zf = acc ? 0 : 1;
	nf = (acc & 0x80) ? 1 : 0;
}

void
func_brk(void)
{
	pc++;
	mem[0x100 + --sp] = pc >> 8;
	mem[0x100 + --sp] = pc;
	mem[0x100 + --sp] = nf << 7 | of << 6 | 1 << 5 | 1 << 4 | df << 3 | id << 2 | zf << 1 | cf;
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
	if (mem[pc] != 0x80)
		printf("undef %04x:%02x\n", (uint32_t) pc, (uint32_t) mem[pc]);
	exit(1);
}

struct {
	void (*func)(void);
} ftab[256] = {

	func_brk,	// 00
	func_ora_zpxi,	// 01
	func_undef,	// 02
	func_undef,	// 03

	func_undef,	// 04
	func_ora_zp,	// 05
	func_asl_zp,	// 06
	func_undef,	// 07

	func_php,	// 08
	func_ora_imm,	// 09
	func_asl_acc,	// 0a
	func_undef,	// 0b

	func_undef,	// 0c
	func_ora_abs,	// 0d
	func_asl_abs,	// 0e
	func_undef,	// 0f

	func_bpl,	// 10
	func_ora_zpiy,	// 11
	func_undef,	// 12
	func_undef,	// 13

	func_undef,	// 14
	func_ora_zpx,	// 15
	func_asl_zpx,	// 16
	func_undef,	// 17

	func_clc,	// 18
	func_ora_absy,	// 19
	func_undef,	// 1a
	func_undef,	// 1b

	func_undef,	// 1c
	func_ora_absx,	// 1d
	func_asl_absx,	// 1e
	func_undef,	// 1f

	func_jsr,	// 20
	func_and_zpxi,	// 21
	func_undef,	// 22
	func_undef,	// 23

	func_bit_zp,	// 24
	func_and_zp,	// 25
	func_rol_zp,	// 26
	func_undef,	// 27

	func_plp,	// 28
	func_and_imm,	// 29
	func_rol_acc,	// 2a
	func_undef,	// 2b

	func_bit_abs,	// 2c
	func_and_abs,	// 2d
	func_rol_abs,	// 2e
	func_undef,	// 2f

	func_bmi,	// 30
	func_and_zpiy,	// 31
	func_undef,	// 32
	func_undef,	// 33

	func_undef,	// 34
	func_and_zpx,	// 35
	func_rol_zpx,	// 36
	func_undef,	// 37

	func_sec,	// 38
	func_and_absy,	// 39
	func_undef,	// 3a
	func_undef,	// 3b

	func_undef,	// 3c
	func_and_absx,	// 3d
	func_rol_absx,	// 3e
	func_undef,	// 3f

	func_rti,	// 40
	func_eor_zpxi,	// 41
	func_undef,	// 42
	func_undef,	// 43

	func_undef,	// 44
	func_eor_zp,	// 45
	func_lsr_zp,	// 46
	func_undef,	// 47

	func_pha,	// 48
	func_eor_imm,	// 49
	func_lsr_acc,	// 4a
	func_undef,	// 4b

	func_jmp,	// 4c
	func_eor_abs,	// 4d
	func_lsr_abs,	// 4e
	func_undef,	// 4f

	func_bvc,	// 50
	func_eor_zpiy,	// 51
	func_undef,	// 52
	func_undef,	// 53

	func_undef,	// 54
	func_eor_zpx,	// 55
	func_lsr_zpx,	// 56
	func_undef,	// 57

	func_cli,	// 58
	func_eor_absy,	// 59
	func_undef,	// 5a
	func_undef,	// 5b

	func_undef,	// 5c
	func_eor_absx,	// 5d
	func_lsr_absx,	// 5e
	func_undef,	// 5f

	func_rts,	// 60
	func_adc_zpxi,	// 61
	func_undef,	// 62
	func_undef,	// 63

	func_undef,	// 64
	func_adc_zp,	// 65
	func_ror_zp,	// 66
	func_undef,	// 67

	func_pla,	// 68
	func_adc_imm,	// 69
	func_ror_acc,	// 6a
	func_undef,	// 6b

	func_jmpi,	// 6c
	func_adc_abs,	// 6d
	func_ror_abs,	// 6e
	func_undef,	// 6f

	func_bvs,	// 70
	func_adc_zpiy,	// 71
	func_undef,	// 72
	func_undef,	// 73

	func_undef,	// 74
	func_adc_zpx,	// 75
	func_ror_zpx,	// 76
	func_undef,	// 77

	func_sti,	// 78
	func_adc_absy,	// 79
	func_undef,	// 7a
	func_undef,	// 7b

	func_undef,	// 7c
	func_adc_absx,	// 7d
	func_ror_absx,	// 7e
	func_undef,	// 7f

	func_undef,	// 80
	func_sta_zpxi,	// 81
	func_undef,	// 82
	func_undef,	// 83

	func_sty_zp,	// 84
	func_sta_zp,	// 85
	func_stx_zp,	// 86
	func_undef,	// 87

	func_dey,	// 88
	func_undef,	// 89
	func_txa,	// 8a
	func_undef,	// 8b

	func_sty_abs,	// 8c
	func_sta_abs,	// 8d
	func_stx_abs,	// 8e
	func_undef,	// 8f

	func_bcc,	// 90
	func_sta_zpiy,	// 91
	func_undef,	// 92
	func_undef,	// 93

	func_sty_zpx,	// 94
	func_sta_zpx,	// 95
	func_stx_zpy,	// 96
	func_undef,	// 97

	func_tya,	// 98
	func_sta_absy,	// 99
	func_txs,	// 9a
	func_undef,	// 9b

	func_undef,	// 9c
	func_sta_absx,	// 9d
	func_undef,	// 9e
	func_undef,	// 9f

	func_ldy_imm,	// a0
	func_lda_zpxi,	// a1
	func_ldx_imm,	// a2
	func_undef,	// a3

	func_ldy_zp,	// a4
	func_lda_zp,	// a5
	func_ldx_zp,	// a6
	func_undef,	// a7

	func_tay,	// a8
	func_lda_imm,	// a9
	func_tax,	// aa
	func_undef,	// ab

	func_ldy_abs,	// ac
	func_lda_abs,	// ad
	func_ldx_abs,	// ae
	func_undef,	// af

	func_bcs,	// b0
	func_lda_zpiy,	// b1
	func_undef,	// b2
	func_undef,	// b3

	func_ldy_zpx,	// b4
	func_lda_zpx,	// b5
	func_ldx_zpy,	// b6
	func_undef,	// b7

	func_clv,	// b8
	func_lda_absy,	// b9
	func_tsx,	// ba
	func_undef,	// bb

	func_ldy_absx,	// bc
	func_lda_absx,	// bd
	func_ldx_absy,	// be
	func_undef,	// bf

	func_cpy_imm,	// c0
	func_cmp_zpxi,	// c1
	func_undef,	// c2
	func_undef,	// c3

	func_cpy_zp,	// c4
	func_cmp_zp,	// c5
	func_dec_zp,	// c6
	func_undef,	// c7

	func_iny,	// c8
	func_cmp_imm,	// c9
	func_dex,	// ca
	func_undef,	// cb

	func_cpy_abs,	// cc
	func_cmp_abs,	// cd
	func_dec_abs,	// ce
	func_undef,	// cf

	func_bne,	// d0
	func_cmp_zpiy,	// d1
	func_undef,	// d2
	func_undef,	// d3

	func_undef,	// d4
	func_cmp_zpx,	// d5
	func_dec_zpx,	// d6
	func_undef,	// d7

	func_cld,	// d8
	func_cmp_absy,	// d9
	func_undef,	// da
	func_undef,	// db

	func_undef,	// dc
	func_cmp_absx,	// dd
	func_dec_absx,	// de
	func_undef,	// df

	func_cpx_imm,	// e0
	func_sbc_zpxi,	// e1
	func_undef,	// e2
	func_undef,	// e3

	func_cpx_zp,	// e4
	func_sbc_zp,	// e5
	func_inc_zp,	// e6
	func_undef,	// e7

	func_inx,	// e8
	func_sbc_imm,	// e9
	func_nop,	// ea
	func_undef,	// eb

	func_cpx_abs,	// ec
	func_sbc_abs,	// ed
	func_inc_abs,	// ee
	func_undef,	// ef

	func_beq,	// f0
	func_sbc_zpiy,	// f1
	func_undef,	// f2
	func_undef,	// f3

	func_undef,	// f4
	func_sbc_zpx,	// f5
	func_inc_zpx,	// f6
	func_undef,	// f7

	func_std,	// f8
	func_sbc_absy,	// f9
	func_undef,	// fa
	func_undef,	// fb

	func_undef,	// fc
	func_sbc_absx,	// fd
	func_inc_absx,	// fe
	func_undef,	// ff
};

uint8_t hello[22] = {
0xa2,0x00,
0xbd,0x0f,0x02,
0xf0,0x07,
0x8d,0xf0,0xff,
0xe8,
0x4c,0x02,0x02,
0x80,
0x68,0x65,0x6c,0x6c,0x6f,0x0a,0x00,
};

int
main()
{
	void (*func)(void);
	mem = malloc(65536);
	memcpy(mem + 0x200, hello, 22);
	pc = 0x200;
	for (;;) {
		func = ftab[mem[pc++]].func;
		func();
	}
}
