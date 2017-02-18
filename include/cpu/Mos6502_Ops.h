// Instruction Opcodes for the MOS 6502 CPU.
// This list is in increasing order, and the addressing mode is included
// in the opname.
// Note: immed is used instead of # to list immediate addressing.

namespace Op {
  // HI-NIBBLE == 0x00
  static const byte BRK_IMPL  = 0x00;
  static const byte ORA_X_IND = 0x01;
  static const byte ORA_ZPG   = 0x05;
  static const byte ASL_ZPG   = 0x06;
  static const byte PHP_IMPL  = 0x08;
  static const byte ORA_IMMED = 0x09;
  static const byte ASL_ACC   = 0x0A;
  static const byte ORA_ABS   = 0x0D;
  static const byte ASL_ABS   = 0x0E;

  // HI-NIBBLE == 0x10
  static const byte BPL_REL   = 0x10;
  static const byte ORA_IND_Y = 0x11;
  static const byte ORA_ZPG_X = 0x15;
  static const byte ASL_ZPG_X = 0x16;
  static const byte CLC_IMPL  = 0x18;
  static const byte ORA_ABS_Y = 0x19;
  static const byte ORA_ABS_X = 0x1D;
  static const byte ASL_ABS_X = 0x1E;

  // HI-NIBBLE == 0x20
  static const byte JSR_ABS   = 0x20;
  static const byte AND_X_IND = 0x21;
  static const byte BIT_ZPG   = 0x24;
  static const byte AND_ZPG   = 0x25;
  static const byte ROL_ZPG   = 0x26;
  static const byte PLP_IMPL  = 0x28;
  static const byte AND_IMMED = 0x29;
  static const byte ROL_ACC   = 0x2A;
  static const byte BIT_ABS   = 0x2C;
  static const byte AND_ABS   = 0x2D;
  static const byte ROL_ABS   = 0x2E;

  // HI-NIBBLE == 0x30
  static const byte BMI_REL   = 0x30;
  static const byte AND_IND_Y = 0x31;
  static const byte AND_ZPG_X = 0x35;
  static const byte ROL_ZPG_X = 0x36;
  static const byte SEC_IMPL  = 0x38;
  static const byte AND_ABS_Y = 0x39;
  static const byte AND_ABS_X = 0x3D;
  static const byte ROL_ABS_X = 0x3E;

  // HI-NIBBLE == 0x40
  static const byte RTI_IMPL  = 0x40;
  static const byte EOR_X_IND = 0x41;
  static const byte EOR_ZPG   = 0x45;
  static const byte LSR_ZPG   = 0x46;
  static const byte PHA_IMPL  = 0x48;
  static const byte EOR_IMMED = 0x49;
  static const byte LSR_ACC   = 0x4A;
  static const byte JMP_ABS   = 0x4C;
  static const byte EOR_ABS   = 0x4D;
  static const byte LSR_ABS   = 0x4E;

  // HI-NIBBLE == 0x50
  static const byte BVC_REL   = 0x50;
  static const byte EOR_IND_Y = 0x51;
  static const byte EOR_ZPG_X = 0x55;
  static const byte LSR_ZPG_X = 0x56;
  static const byte CLI_IMPL  = 0x58;
  static const byte EOR_ABS_Y = 0x59;
  static const byte EOR_ABS_X = 0x5D;
  static const byte LSR_ABS_X = 0x5E;

  // HI-NIBBLE == 0x60
  static const byte RTS_IMPL  = 0x60;
  static const byte ADC_X_IND = 0x61;
  static const byte ADC_ZPG   = 0x65;
  static const byte ROR_ZPG   = 0x66;
  static const byte PLA_IMPL  = 0x68;
  static const byte ADC_IMMED = 0x69;
  static const byte ROR_ACC   = 0x6A;
  static const byte JMP_IND   = 0x6C;
  static const byte ADC_ABS   = 0x6D;
  static const byte ROR_ABS   = 0x6E;

  // HI-NIBBLE == 0x70
  static const byte BVS_REL   = 0x70;
  static const byte ADC_IND_Y = 0x71;
  static const byte ADC_ZPG_X = 0x75;
  static const byte ROR_ZPG_X = 0x76;
  static const byte SEI_IMPL  = 0x78;
  static const byte ADC_ABS_Y = 0x79;
  static const byte ADC_ABS_X = 0x7D;
  static const byte ROR_ABS_X = 0x7E;

  // HI-NIBBLE == 0x80
  static const byte STA_X_IND = 0x81;
  static const byte STY_ZPG   = 0x84;
  static const byte STA_ZPG   = 0x85;
  static const byte STX_ZPG   = 0x86;
  static const byte DEY_IMPL  = 0x88;
  static const byte TXA_IMPL  = 0x8A;
  static const byte STY_ABS   = 0x8C;
  static const byte STA_ABS   = 0x8D;
  static const byte STX_ABS   = 0x8E;

  // HI-NIBBLE == 0x90
  static const byte BCC_REL   = 0x90;
  static const byte STA_IND_Y = 0x91;
  static const byte STY_ZPG_X = 0x94;
  static const byte STA_ZPG_X = 0x95;
  static const byte STX_ZPG_Y = 0x96;
  static const byte TYA_IMPL  = 0x98;
  static const byte STA_ABS_Y = 0x99;
  static const byte TXS_IMPL  = 0x9A;
  static const byte STA_ABS_X = 0x9D;

  // HI-NIBBLE == 0xA0
  static const byte LDY_IMMED = 0xA0;
  static const byte LDA_X_IND = 0xA1;
  static const byte LDX_IMMED = 0xA2;
  static const byte LDY_ZPG   = 0xA4;
  static const byte LDA_ZPG   = 0xA5;
  static const byte LDX_ZPG   = 0xA6;
  static const byte TAY_IMPL  = 0xA8;
  static const byte LDA_IMMED = 0xA9;
  static const byte TAX_IMPL  = 0xAA;
  static const byte LDY_ABS   = 0xAC;
  static const byte LDA_ABS   = 0xAD;
  static const byte LDX_ABS   = 0xAE;

  // HI-NIBBLE == 0xB0
  static const byte BCS_REL   = 0xB0;
  static const byte LDA_IND_Y = 0xB1;
  static const byte LDY_ZPG_X = 0xB4;
  static const byte LDA_ZPG_X = 0xB5;
  static const byte LDX_ZPG_Y = 0xB6;
  static const byte CLV_IMPL  = 0xB8;
  static const byte LDA_ABS_Y = 0xB9;
  static const byte TSX_IMPL  = 0xBA;
  static const byte LDY_ABS_X = 0xBC;
  static const byte LDA_ABS_X = 0xBD;
  static const byte LDX_ABS_Y = 0xBE;

  // HI-NIBBLE == 0xC0
  static const byte CPY_IMMED = 0xC0;
  static const byte CMP_X_IND = 0xC1;
  static const byte CPY_ZPG   = 0xC4;
  static const byte CMP_ZPG   = 0xC5;
  static const byte DEC_ZPG   = 0xC6;
  static const byte INY_IMPL  = 0xC8;
  static const byte CMP_IMMED = 0xC9;
  static const byte DEX_IMPL  = 0xCA;
  static const byte CPY_ABS   = 0xCC;
  static const byte CMP_ABS   = 0xCD;
  static const byte DEC_ABS   = 0xCE;

  // HI-NIBBLE == 0xD0
  static const byte BNE_REL   = 0xD0;
  static const byte CMP_IND_Y = 0xD1;
  static const byte CMP_ZPG_X = 0xD5;
  static const byte DEC_ZPG_X = 0xD6;
  static const byte CLD_IMPL  = 0xD8;
  static const byte CMP_ABS_Y = 0xD9;
  static const byte CMP_ABS_X = 0xDD;
  static const byte DEC_ABS_X = 0xDE;

  // HI-NIBBLE == 0xE0
  static const byte CPX_IMMED = 0xE0;
  static const byte SBC_X_IND = 0xE1;
  static const byte CPX_ZPG   = 0xE4;
  static const byte SBC_ZPG   = 0xE5;
  static const byte INC_ZPG   = 0xE6;
  static const byte INX_IMPL  = 0xE8;
  static const byte SBC_IMMED = 0xE9;
  static const byte NOP_IMPL  = 0xEA;
  static const byte CPX_ABS   = 0xEC;
  static const byte SBC_ABS   = 0xED;
  static const byte INC_ABS   = 0xEE;

  // HI-NIBBLE == 0xF0
  static const byte BEQ_REL   = 0xF0;
  static const byte SBC_IND_Y = 0xF1;
  static const byte SBC_ZPG_X = 0xF5;
  static const byte INC_ZPG_X = 0xF6;
  static const byte SED_IMPL  = 0xF8;
  static const byte SBC_ABS_Y = 0xF9;
  static const byte SBC_ABS_X = 0xFD;
  static const byte INC_ABS_X = 0xFE;
}
