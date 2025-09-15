void (*ftab[256])(void) = {

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
