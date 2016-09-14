// OsNES Project | include/mos_6502.h
// Description:
// Functional specification for the MOS 6502 CPU.
// Any and all details related to the overall operation ofthe 6502 should
// be declared here.
//
// Authors: 
// John Dengis
//
#ifndef MOS_6502_H
#define MOS_6502_H
#include "common.h"
#include "cpu_array_stack.h"

class MOS_6502 : public CPU<uint8> {
  public:
    void  execute(uint8 opcode) override;
    uint8 fetch() override;

    // CPU Instruction emulation inline functions
    void ADC(uint8*);
    void AND(uint8*);
    void ASL(uint8*);
    void BCC(uint8*);
    void BCS(uint8*);

  private:
    // Register structure
    struct {
      union {
        uint16 PC; // Program Counter
        struct {
#ifdef __BIG_ENDIAN__
          uint8 PCH;
          uint8 PCL;
#else // Little Endian
          uint8 PCL;
          uint8 PCH;
#endif // __BIG_ENDIAN__
        };
      };
      uint8  AC; // Accumulator
      uint8  X;  // X Register
      uint8  Y;  // Y Register
      struct {
        uint8 N; // Negative
        uint8 V; // Overflow
        uint8 B; // Break
        uint8 D; // Decimal (use BCD for arithmetic)
        uint8 I; // Interrupt (IRQ diable)
        uint8 Z; // Zero
        uint8 C; // Carry
      }      SR; // Status Register [NV-BDIZC]
      uint8  SP; // Stack Pointer
    } reg;

    // Interal stack interface object
    CPU_Array_Stack<uint8> stack;
};

// SR Flag Masks
static const SR_N = 0x80; // Negative
static const SR_V = 0x40; // Overflow
static const SR_B = 0x10; // Break
static const SR_D = 0x08; // Decimal (use BCD for arithmetics)
static const SR_I = 0x04; // Interrupt (IRQ disable)
static const SR_Z = 0x02; // Zero
static const SR_C = 0x01; // Carry

// Instruction Opcodes for the MOS 6502 CPU.
// This list is in increasing order, and the addressing mode is included
// in the opname.
// Note: immed is used instead of # to list immediate addressing.

namespace op {
  // HI-NIBBLE == 0x00
  static const uint8 BRK_impl  = 0x00;
  static const uint8 ORA_X_ind = 0x01;
  static const uint8 ORA_zpg   = 0x05;
  static const uint8 ASL_zpg   = 0x06;
  static const uint8 PHP_impl  = 0x08;
  static const uint8 ORA_immed = 0x09;
  static const uint8 ASL_A     = 0x0A;
  static const uint8 ORA_abs   = 0x0D;
  static const uint8 ASL_abs   = 0x0E;

  // HI-NIBBLE == 0x10
  static const uint8 BPL_rel   = 0x10;
  static const uint8 ORA_ind_Y = 0x11;
  static const uint8 ORA_zpg_X = 0x15;
  static const uint8 ASL_zpg_X = 0x16;
  static const uint8 CLC_impl  = 0x18;
  static const uint8 ORA_abs_Y = 0x19;
  static const uint8 ORA_abs_X = 0x1D;
  static const uint8 ASL_abs_X = 0x1E;

  // HI-NIBBLE == 0x20
  static const uint8 JSR_abs   = 0x20;
  static const uint8 AND_X_ind = 0x21;
  static const uint8 BIT_zpg   = 0x24;
  static const uint8 AND_zpg   = 0x25;
  static const uint8 ROL_zpg   = 0x26;
  static const uint8 PLP_impl  = 0x28;
  static const uint8 AND_immed = 0x29;
  static const uint8 ROL_A     = 0x2A;
  static const uint8 BIT_abs   = 0x2C;
  static const uint8 AND_abs   = 0x2D;
  static const uint8 ROL_abs   = 0x2E;

  // HI-NIBBLE == 0x30
  static const uint8 BMI_rel   = 0x30;
  static const uint8 AND_ind_Y = 0x31;
  static const uint8 AND_zpg_X = 0x35;
  static const uint8 ROL_zpg_X = 0x36;
  static const uint8 SEC_impl  = 0x38;
  static const uint8 AND_abs_Y = 0x39;
  static const uint8 AND_abs_X = 0x3D;
  static const uint8 ROL_abs_X = 0x3E;

  // HI-NIBBLE == 0x40
  static const uint8 RTI_impl  = 0x40;
  static const uint8 EOR_X_ind = 0x41;
  static const uint8 EOR_zpg   = 0x45;
  static const uint8 LSR_zpg   = 0x46;
  static const uint8 PHA_impl  = 0x48;
  static const uint8 EOR_immed = 0x49;
  static const uint8 LSR_A     = 0x4A;
  static const uint8 JMP_abs   = 0x4C;
  static const uint8 EOR_abs   = 0x4D;
  static const uint8 LSR_abs   = 0x4E;

  // HI-NIBBLE == 0x50
  static const uint8 BVC_rel   = 0x50;
  static const uint8 EOR_ind_Y = 0x51;
  static const uint8 EOR_zpg_X = 0x55;
  static const uint8 LSR_zpg_X = 0x56;
  static const uint8 CLI_impl  = 0x58;
  static const uint8 EOR_abs_Y = 0x59;
  static const uint8 EOR_abs_X = 0x5D;
  static const uint8 LSR_abs_X = 0x5E;

  // HI-NIBBLE == 0x60
  static const uint8 RTS_impl  = 0x60;
  static const uint8 ADC_X_ind = 0x61;
  static const uint8 ADC_zpg   = 0x65;
  static const uint8 ROR_zpg   = 0x66;
  static const uint8 PLA_impl  = 0x68;
  static const uint8 ADC_immed = 0x69;
  static const uint8 ROR_A     = 0x6A;
  static const uint8 JMP_ind   = 0x6C;
  static const uint8 ADC_abs   = 0x6D;
  static const uint8 ROR_abs   = 0x6E;

  // HI-NIBBLE == 0x70
  static const uint8 BVS_rel   = 0x70;
  static const uint8 ADC_ind_Y = 0x71;
  static const uint8 ADC_zpg_X = 0x75;
  static const uint8 ROR_zpg_X = 0x76;
  static const uint8 SEI_impl  = 0x78;
  static const uint8 ADC_abs_Y = 0x79;
  static const uint8 ADC_abs_X = 0x7D;
  static const uint8 ROR_abs_X = 0x7E;

  // HI-NIBBLE == 0x80
  static const uint8 STA_X_ind = 0x81;
  static const uint8 STY_zpg   = 0x84;
  static const uint8 STA_zpg   = 0x85;
  static const uint8 STX_zpg   = 0x86;
  static const uint8 DEY_impl  = 0x88;
  static const uint8 TXA_impl  = 0x8A;
  static const uint8 STY_abs   = 0x8C;
  static const uint8 STA_abs   = 0x8D;
  static const uint8 STX_abs   = 0x8E;

  // HI-NIBBLE == 0x90
  static const uint8 BCC_rel   = 0x90;
  static const uint8 STA_ind_Y = 0x91;
  static const uint8 STY_zpg_X = 0x94;
  static const uint8 STA_zpg_x = 0x95;
  static const uint8 STX_zpg_Y = 0x96;
  static const uint8 TYA_impl  = 0x98;
  static const uint8 STA_abs_Y = 0x99;
  static const uint8 TXS_impl  = 0x9A;
  static const uint8 STA_abs_X = 0x9D;

  // HI-NIBBLE == 0xA0
  static const uint8 LDY_immed = 0xA0;
  static const uint8 LDA_X_ind = 0xA1;
  static const uint8 OP_LDX_immed = 0xA2;
  static const uint8 LDY_zpg   = 0xA4;
  static const uint8 LDA_zpg   = 0xA5;
  static const uint8 LDX_zpg   = 0xA6;
  static const uint8 TAY_impl  = 0xA8;
  static const uint8 LDA_immed = 0xA9;
  static const uint8 TAX_impl  = 0xAA;
  static const uint8 LDY_abs   = 0xAC;
  static const uint8 LDA_abs   = 0xAD;
  static const uint8 LDX_abs   = 0xAE;

  // HI-NIBBLE == 0xB0
  static const uint8 BCS_rel   = 0xB0;
  static const uint8 LDA_ind_Y = 0xB1;
  static const uint8 LDY_zpg_X = 0xB4;
  static const uint8 LDA_zpg_x = 0xB5;
  static const uint8 LDX_zpg_Y = 0xB6;
  static const uint8 CLV_impl  = 0xB8;
  static const uint8 LDA_abs_Y = 0xB9;
  static const uint8 TSX_impl  = 0xBA;
  static const uint8 LDY_abs_X = 0xBC;
  static const uint8 LDA_abs_X = 0xBD;
  static const uint8 LDX_abs_Y = 0xBE;

  // HI-NIBBLE == 0xC0
  static const uint8 CPY_immed = 0xC0;
  static const uint8 CMP_X_ind = 0xC1;
  static const uint8 CPY_zpg   = 0xC4;
  static const uint8 CMP_zpg   = 0xC5;
  static const uint8 DEC_zpg   = 0xC6;
  static const uint8 INY_impl  = 0xC8;
  static const uint8 CMP_immed = 0xC9;
  static const uint8 DEX_impl  = 0xCA;
  static const uint8 CPY_abs   = 0xCC;
  static const uint8 CMP_abs   = 0xCD;
  static const uint8 DEC_abs   = 0xCE;

  // HI-NIBBLE == 0xD0
  static const uint8 BNE_rel   = 0xD0;
  static const uint8 CMP_ind_Y = 0xD1;
  static const uint8 CMP_zpg_X = 0xD5;
  static const uint8 DEC_zpg_X = 0xD6;
  static const uint8 CLD_impl  = 0xD8;
  static const uint8 CMP_abs_Y = 0xD9;
  static const uint8 CMP_abs_X = 0xDD;
  static const uint8 DEC_abs_X = 0xDE;

  // HI-NIBBLE == 0xE0
  static const uint8 CPX_immed = 0xE0;
  static const uint8 SBC_X_ind = 0xE1;
  static const uint8 CPX_zpg   = 0xE4;
  static const uint8 SBC_zpg   = 0xE5;
  static const uint8 INC_zpg   = 0xE6;
  static const uint8 INX_impl  = 0xE8;
  static const uint8 SBC_immed = 0xE9;
  static const uint8 NOP_impl  = 0xEA;
  static const uint8 CPX_abs   = 0xEC;
  static const uint8 SBC_abs   = 0xED;
  static const uint8 INC_abs   = 0xEE;

  // HI-NIBBLE == 0xF0
  static const uint8 BEQ_rel   = 0xF0;
  static const uint8 SBC_ind_Y = 0xF1;
  static const uint8 SBC_zpg_X = 0xF5;
  static const uint8 INC_zpg_X = 0xF6;
  static const uint8 SED_impl  = 0xF8;
  static const uint8 SBC_abs_Y = 0xF9;
  static const uint8 SBC_abs_X = 0xFD;
  static const uint8 INC_abs_X = 0xFE;
}
#endif // MOS_6502_H //:~
