#ifndef CPU_6502_H
#define CPU_6502_H
#include "common.h"

// Instruction Opcodes for the MOS 6502 CPU.
// This list is in increasing order, and the addressing mode is included
// in the opname.
// Note: imm is used instead of # to list immediate addressing.

// HI-NIBBLE == 0x00
static const uint8 op_BRK_impl  = 0x00;
static const uint8 op_ORA_X_ind = 0x01;
static const uint8 op_ORA_zpg   = 0x05;
static const uint8 op_ASL_zpg   = 0x06;
static const uint8 op_PHP_impl  = 0x08;
static const uint8 op_ORA_immed = 0x09;
static const uint8 op_ASL_A     = 0x0A;
static const uint8 op_ORA_abs   = 0x0D;
static const uint8 op_ASL_abs   = 0x0E;

// HI-NIBBLE == 0x10
static const uint8 op_BPL_rel   = 0x10;
static const uint8 op_ORA_ind_Y = 0x11;
static const uint8 op_ORA_zpg_X = 0x15;
static const uint8 op_ASL_zpg_X = 0x16;
static const uint8 op_CLC_impl  = 0x18;
static const uint8 op_ORA_abs_Y = 0x19;
static const uint8 op_ORA_abs_X = 0x1D;
static const uint8 op_ASL_abs_X = 0x1E;

// HI-NIBBLE == 0x20
static const uint8 op_JSR_abs   = 0x20;
static const uint8 op_AND_X_ind = 0x21;
static const uint8 op_BIT_zpg   = 0x24;
static const uint8 op_AND_zpg   = 0x25;
static const uint8 op_ROL_zpg   = 0x26;
static const uint8 op_PLP_impl  = 0x28;
static const uint8 op_AND_immed = 0x29;
static const uint8 op_ROL_A     = 0x2A;
static const uint8 op_BIT_abs   = 0x2C;
static const uint8 op_AND_abs   = 0x2D;
static const uint8 op_ROL_abs   = 0x2E;

// HI-NIBBLE == 0x30
static const uint8 op_BMI_rel   = 0x30;
static const uint8 op_AND_ind_Y = 0x31;
static const uint8 op_AND_zpg_X = 0x35;
static const uint8 op_ROL_zpg_X = 0x36;
static const uint8 op_SEC_impl  = 0x38;
static const uint8 op_AND_abs_Y = 0x39;
static const uint8 op_AND_abs_X = 0x3D;
static const uint8 op_ROL_abs_X = 0x3E;

// HI-NIBBLE == 0x40
static const uint8 op_RTI_impl  = 0x40;
static const uint8 op_EOR_X_ind = 0x41;
static const uint8 op_EOR_zpg   = 0x45;
static const uint8 op_LSR_zpg   = 0x46;
static const uint8 op_PHA_impl  = 0x48;
static const uint8 op_EOR_immed = 0x49;
static const uint8 op_LSR_A     = 0x4A;
static const uint8 op_JMP_abs   = 0x4C;
static const uint8 op_EOR_abs   = 0x4D;
static const uint8 op_LSR_abs   = 0x4E;

// HI-NIBBLE == 0x50
static const uint8 op_BVC_rel   = 0x50;
static const uint8 op_EOR_ind_Y = 0x51;
static const uint8 op_EOR_zpg_X = 0x55;
static const uint8 op_LSR_zpg_X = 0x56;
static const uint8 op_CLI_impl  = 0x58;
static const uint8 op_EOR_abs_Y = 0x59;
static const uint8 op_EOR_abs_X = 0x5D;
static const uint8 op_LSR_abs_X = 0x5E;

// HI-NIBBLE == 0x60
static const uint8 op_RTS_impl  = 0x60;
static const uint8 op_ADC_X_ind = 0x61;
static const uint8 op_ADC_zpg   = 0x65;
static const uint8 op_ROR_zpg   = 0x66;
static const uint8 op_PLA_impl  = 0x68;
static const uint8 op_ADC_immed = 0x69;
static const uint8 op_ROR_A     = 0x6A;
static const uint8 op_JMP_ind   = 0x6C;
static const uint8 op_ADC_abs   = 0x6D;
static const uint8 op_ROR_abs   = 0x6E;

// HI-NIBBLE == 0x70
static const uint8 op_BVS_rel   = 0x70;
static const uint8 op_ADC_ind_Y = 0x71;
static const uint8 op_ADC_zpg_X = 0x75;
static const uint8 op_ROR_zpg_X = 0x76;
static const uint8 op_SEI_impl  = 0x78;
static const uint8 op_ADC_abs_Y = 0x79;
static const uint8 op_ADC_abs_X = 0x7D;
static const uint8 op_ROR_abs_X = 0x7E;

// HI-NIBBLE == 0x80
static const uint8 op_STA_X_ind = 0x81;
static const uint8 op_STY_zpg   = 0x84;
static const uint8 op_STA_zpg   = 0x85;
static const uint8 op_STX_zpg   = 0x86;
static const uint8 op_DEY_impl  = 0x88;
static const uint8 op_TXA_impl  = 0x8A;
static const uint8 op_STY_abs   = 0x8C;
static const uint8 op_STA_abs   = 0x8D;
static const uint8 op_STX_abs   = 0x8E;

// HI-NIBBLE == 0x90
static const uint8 op_BCC_rel   = 0x90;
static const uint8 op_STA_ind_Y = 0x91;
static const uint8 op_STY_zpg_X = 0x94;
static const uint8 op_STA_zpg_x = 0x95;
static const uint8 op_STX_zpg_Y = 0x96;
static const uint8 op_TYA_impl  = 0x98;
static const uint8 op_STA_abs_Y = 0x99;
static const uint8 op_TXS_impl  = 0x9A;
static const uint8 op_STA_abs_X = 0x9D;

// HI-NIBBLE == 0xA0
static const uint8 op_LDY_immed = 0xA0;
static const uint8 op_LDA_X_ind = 0xA1;
static const uint8 OP_LDX_immed = 0xA2;
static const uint8 op_LDY_zpg   = 0xA4;
static const uint8 op_LDA_zpg   = 0xA5;
static const uint8 op_LDX_zpg   = 0xA6;
static const uint8 op_TAY_impl  = 0xA8;
static const uint8 op_LDA_immed = 0xA9;
static const uint8 op_TAX_impl  = 0xAA;
static const uint8 op_LDY_abs   = 0xAC;
static const uint8 op_LDA_abs   = 0xAD;
static const uint8 op_LDX_abs   = 0xAE;

// HI-NIBBLE == 0xB0
static const uint8 op_BCS_rel   = 0xB0;
static const uint8 op_LDA_ind_Y = 0xB1;
static const uint8 op_LDY_zpg_X = 0xB4;
static const uint8 op_LDA_zpg_x = 0xB5;
static const uint8 op_LDX_zpg_Y = 0xB6;
static const uint8 op_CLV_impl  = 0xB8;
static const uint8 op_LDA_abs_Y = 0xB9;
static const uint8 op_TSX_impl  = 0xBA;
static const uint8 op_LDY_abs_X = 0xBC;
static const uint8 op_LDA_abs_X = 0xBD;
static const uint8 op_LDX_abs_Y = 0xBE;

// HI-NIBBLE == 0xC0
static const uint8 op_CPY_immed = 0xC0;
static const uint8 op_CMP_X_ind = 0xC1;
static const uint8 op_CPY_zpg   = 0xC4;
static const uint8 op_CMP_zpg   = 0xC5;
static const uint8 op_DEC_zpg   = 0xC6;
static const uint8 op_INY_impl  = 0xC8;
static const uint8 op_CMP_immed = 0xC9;
static const uint8 op_DEX_impl  = 0xCA;
static const uint8 op_CPY_abs   = 0xCC;
static const uint8 op_CMP_abs   = 0xCD;
static const uint8 op_DEC_abs   = 0xCE;

// HI-NIBBLE == 0xD0
static const uint8 op_BNE_rel   = 0xD0;
static const uint8 op_CMP_ind_Y = 0xD1;
static const uint8 op_CMP_zpg_X = 0xD5;
static const uint8 op_DEC_zpg_X = 0xD6;
static const uint8 op_CLD_impl  = 0xD8;
static const uint8 op_CMP_abs_Y = 0xD9;
static const uint8 op_CMP_abs_X = 0xDD;
static const uint8 op_DEC_abs_X = 0xDE;

// HI-NIBBLE == 0xE0
static const uint8 op_CPX_immed = 0xE0;
static const uint8 op_SBC_X_ind = 0xE1;
static const uint8 op_CPX_zpg   = 0xE4;
static const uint8 op_SBC_zpg   = 0xE5;
static const uint8 op_INC_zpg   = 0xE6;
static const uint8 op_INX_impl  = 0xE8;
static const uint8 op_SBC_immed = 0xE9;
static const uint8 op_NOP_impl  = 0xEA;
static const uint8 op_CPX_abs   = 0xEC;
static const uint8 op_SBC_abs   = 0xED;
static const uint8 op_INC_abs   = 0xEE;

// HI-NIBBLE == 0xF0
static const uint8 op_BEQ_rel   = 0xF0;
static const uint8 op_SBC_ind_Y = 0xF1;
static const uint8 op_SBC_zpg_X = 0xF5;
static const uint8 op_INC_zpg_X = 0xF6;
static const uint8 op_SED_impl  = 0xF8;
static const uint8 op_SBC_abs_Y = 0xF9;
static const uint8 op_SBC_abs_X = 0xFD;
static const uint8 op_INC_abs_X = 0xFE;

#endif // CPU_6502_H //:~
