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
#include "cpu.h"
#include "mem.h"

class MOS_6502 : public CPU<byte> {
  public:
    void  execute(byte opcode) override;
    byte fetch() override;
    
  private:
    // Register structure
    struct {
      union {
        uint16 PC; // Program Counter
        struct {
#ifdef __BIG_ENDIAN__
          byte PCH;
          byte PCL;
#else // Little Endian
          byte PCL;
          byte PCH;
#endif // __BIG_ENDIAN__
        };
      };
      byte  AC; // Accumulator
      byte  X;  // X Register
      byte  Y;  // Y Register
      union {
        byte SR; // Status Register [NV-BDIZC]
        struct {
#ifdef __BIG_ENDIAN__
          byte N       : 1; // Negative
          byte V       : 1; // Overflow
          byte ignored : 1; // Ignored
          byte B       : 1; // Break
          byte D       : 1; // Decimal (use BCD for arithmetic)
          byte I       : 1; // Interrupt (IRQ diable)
          byte Z       : 1; // Zero
          byte C       : 1; // Carry
#else // Little Endian
          byte C       : 1; // Carry
          byte Z       : 1; // Zero
          byte I       : 1; // Interrupt (IRQ diable)
          byte D       : 1; // Decimal (use BCD for arithmetic)
          byte B       : 1; // Break
          byte ignored : 1; // Ignored
          byte V       : 1; // Overflow
          byte N       : 1; // Negative
#endif // __BIG_ENDIAN__
        }      SRF; // Status Register Fields
      }
      byte  SP; // Stack Pointer
    } reg;

    // Interal stack interface object
    //    CPU_Array_Stack<byte> stack;

    // Address mode functions
    Mem::Ref accumulator();
    Mem::Ref absolute();
    Mem::Ref absolute_X();
    Mem::Ref absolute_Y();
    Mem::Ref immediate();
    Mem::Ref indirect();

    // CPU Instruction emulation functions
    void ADC(Mem::Ref);
    void AND(Mem::Ref);
    void ASL(Mem::Ref);
    void BCC(Mem::Ref);
    void BCS(Mem::Ref);
    void BCC(Mem::Ref);
    void BEQ(Mem::Ref);
    void BIT(Mem::Ref);
    void BMI(Mem::Ref);
    void BNE(Mem::Ref);
    void BPL(Mem::Ref);
    void BRK(Mem::Ref);
    void BVC(Mem::Ref);
    void BVS(Mem::Ref);
    void CLC(Mem::Ref);
    void CLD(Mem::Ref);
    void CLI(Mem::Ref);
    void CLV(Mem::Ref);
    void CMP(Mem::Ref);
    void CPX(Mem::Ref);
    void CPY(Mem::Ref);
    void DEC(Mem::Ref);
    void DEX(Mem::Ref);
    void EOR(Mem::Ref);
    void INC(Mem::Ref);
    void INX(Mem::Ref);
    void INY(Mem::Ref);
    void JMP(Mem::Ref);
    void JSR(Mem::Ref);
    void LDA(Mem::Ref);
    void LDX(Mem::Ref);
    void LDY(Mem::Ref);
    void LSR(Mem::Ref);
    void NOP(Mem::Ref);
    void ORA(Mem::Ref);
    void PHA(Mem::Ref);
    void PHP(Mem::Ref);
    void PLA(Mem::Ref);
    void PLP(Mem::Ref);
    void ROL(Mem::Ref);
    void ROR(Mem::Ref);
    void RTI(Mem::Ref);
    void RTS(Mem::Ref);
    void SBC(Mem::Ref);
    void SEC(Mem::Ref);
    void SED(Mem::Ref);
    void SEI(Mem::Ref);
    void STA(Mem::Ref);
    void STX(Mem::Ref);
    void STY(Mem::Ref);
    void TAX(Mem::Ref);
    void TAY(Mem::Ref);
    void TSX(Mem::Ref);
    void TXA(Mem::Ref);
    void TXS(Mem::Ref);
    void TYA(Mem::Ref);
};

// SR Flag Masks
static const byte SR_N = 0x80; // Negative
static const byte SR_V = 0x40; // Overflow
static const byte SR_B = 0x10; // Break
static const byte SR_D = 0x08; // Decimal (use BCD for arithmetics)
static const byte SR_I = 0x04; // Interrupt (IRQ disable)
static const byte SR_Z = 0x02; // Zero
static const byte SR_C = 0x01; // Carry

// Instruction Opcodes for the MOS 6502 CPU.
// This list is in increasing order, and the addressing mode is included
// in the opname.
// Note: immed is used instead of # to list immediate addressing.

namespace op {
  // HI-NIBBLE == 0x00
  static const byte BRK_impl  = 0x00;
  static const byte ORA_X_ind = 0x01;
  static const byte ORA_zpg   = 0x05;
  static const byte ASL_zpg   = 0x06;
  static const byte PHP_impl  = 0x08;
  static const byte ORA_immed = 0x09;
  static const byte ASL_A     = 0x0A;
  static const byte ORA_abs   = 0x0D;
  static const byte ASL_abs   = 0x0E;

  // HI-NIBBLE == 0x10
  static const byte BPL_rel   = 0x10;
  static const byte ORA_ind_Y = 0x11;
  static const byte ORA_zpg_X = 0x15;
  static const byte ASL_zpg_X = 0x16;
  static const byte CLC_impl  = 0x18;
  static const byte ORA_abs_Y = 0x19;
  static const byte ORA_abs_X = 0x1D;
  static const byte ASL_abs_X = 0x1E;

  // HI-NIBBLE == 0x20
  static const byte JSR_abs   = 0x20;
  static const byte AND_X_ind = 0x21;
  static const byte BIT_zpg   = 0x24;
  static const byte AND_zpg   = 0x25;
  static const byte ROL_zpg   = 0x26;
  static const byte PLP_impl  = 0x28;
  static const byte AND_immed = 0x29;
  static const byte ROL_A     = 0x2A;
  static const byte BIT_abs   = 0x2C;
  static const byte AND_abs   = 0x2D;
  static const byte ROL_abs   = 0x2E;

  // HI-NIBBLE == 0x30
  static const byte BMI_rel   = 0x30;
  static const byte AND_ind_Y = 0x31;
  static const byte AND_zpg_X = 0x35;
  static const byte ROL_zpg_X = 0x36;
  static const byte SEC_impl  = 0x38;
  static const byte AND_abs_Y = 0x39;
  static const byte AND_abs_X = 0x3D;
  static const byte ROL_abs_X = 0x3E;

  // HI-NIBBLE == 0x40
  static const byte RTI_impl  = 0x40;
  static const byte EOR_X_ind = 0x41;
  static const byte EOR_zpg   = 0x45;
  static const byte LSR_zpg   = 0x46;
  static const byte PHA_impl  = 0x48;
  static const byte EOR_immed = 0x49;
  static const byte LSR_A     = 0x4A;
  static const byte JMP_abs   = 0x4C;
  static const byte EOR_abs   = 0x4D;
  static const byte LSR_abs   = 0x4E;

  // HI-NIBBLE == 0x50
  static const byte BVC_rel   = 0x50;
  static const byte EOR_ind_Y = 0x51;
  static const byte EOR_zpg_X = 0x55;
  static const byte LSR_zpg_X = 0x56;
  static const byte CLI_impl  = 0x58;
  static const byte EOR_abs_Y = 0x59;
  static const byte EOR_abs_X = 0x5D;
  static const byte LSR_abs_X = 0x5E;

  // HI-NIBBLE == 0x60
  static const byte RTS_impl  = 0x60;
  static const byte ADC_X_ind = 0x61;
  static const byte ADC_zpg   = 0x65;
  static const byte ROR_zpg   = 0x66;
  static const byte PLA_impl  = 0x68;
  static const byte ADC_immed = 0x69;
  static const byte ROR_A     = 0x6A;
  static const byte JMP_ind   = 0x6C;
  static const byte ADC_abs   = 0x6D;
  static const byte ROR_abs   = 0x6E;

  // HI-NIBBLE == 0x70
  static const byte BVS_rel   = 0x70;
  static const byte ADC_ind_Y = 0x71;
  static const byte ADC_zpg_X = 0x75;
  static const byte ROR_zpg_X = 0x76;
  static const byte SEI_impl  = 0x78;
  static const byte ADC_abs_Y = 0x79;
  static const byte ADC_abs_X = 0x7D;
  static const byte ROR_abs_X = 0x7E;

  // HI-NIBBLE == 0x80
  static const byte STA_X_ind = 0x81;
  static const byte STY_zpg   = 0x84;
  static const byte STA_zpg   = 0x85;
  static const byte STX_zpg   = 0x86;
  static const byte DEY_impl  = 0x88;
  static const byte TXA_impl  = 0x8A;
  static const byte STY_abs   = 0x8C;
  static const byte STA_abs   = 0x8D;
  static const byte STX_abs   = 0x8E;

  // HI-NIBBLE == 0x90
  static const byte BCC_rel   = 0x90;
  static const byte STA_ind_Y = 0x91;
  static const byte STY_zpg_X = 0x94;
  static const byte STA_zpg_x = 0x95;
  static const byte STX_zpg_Y = 0x96;
  static const byte TYA_impl  = 0x98;
  static const byte STA_abs_Y = 0x99;
  static const byte TXS_impl  = 0x9A;
  static const byte STA_abs_X = 0x9D;

  // HI-NIBBLE == 0xA0
  static const byte LDY_immed = 0xA0;
  static const byte LDA_X_ind = 0xA1;
  static const byte OP_LDX_immed = 0xA2;
  static const byte LDY_zpg   = 0xA4;
  static const byte LDA_zpg   = 0xA5;
  static const byte LDX_zpg   = 0xA6;
  static const byte TAY_impl  = 0xA8;
  static const byte LDA_immed = 0xA9;
  static const byte TAX_impl  = 0xAA;
  static const byte LDY_abs   = 0xAC;
  static const byte LDA_abs   = 0xAD;
  static const byte LDX_abs   = 0xAE;

  // HI-NIBBLE == 0xB0
  static const byte BCS_rel   = 0xB0;
  static const byte LDA_ind_Y = 0xB1;
  static const byte LDY_zpg_X = 0xB4;
  static const byte LDA_zpg_x = 0xB5;
  static const byte LDX_zpg_Y = 0xB6;
  static const byte CLV_impl  = 0xB8;
  static const byte LDA_abs_Y = 0xB9;
  static const byte TSX_impl  = 0xBA;
  static const byte LDY_abs_X = 0xBC;
  static const byte LDA_abs_X = 0xBD;
  static const byte LDX_abs_Y = 0xBE;

  // HI-NIBBLE == 0xC0
  static const byte CPY_immed = 0xC0;
  static const byte CMP_X_ind = 0xC1;
  static const byte CPY_zpg   = 0xC4;
  static const byte CMP_zpg   = 0xC5;
  static const byte DEC_zpg   = 0xC6;
  static const byte INY_impl  = 0xC8;
  static const byte CMP_immed = 0xC9;
  static const byte DEX_impl  = 0xCA;
  static const byte CPY_abs   = 0xCC;
  static const byte CMP_abs   = 0xCD;
  static const byte DEC_abs   = 0xCE;

  // HI-NIBBLE == 0xD0
  static const byte BNE_rel   = 0xD0;
  static const byte CMP_ind_Y = 0xD1;
  static const byte CMP_zpg_X = 0xD5;
  static const byte DEC_zpg_X = 0xD6;
  static const byte CLD_impl  = 0xD8;
  static const byte CMP_abs_Y = 0xD9;
  static const byte CMP_abs_X = 0xDD;
  static const byte DEC_abs_X = 0xDE;

  // HI-NIBBLE == 0xE0
  static const byte CPX_immed = 0xE0;
  static const byte SBC_X_ind = 0xE1;
  static const byte CPX_zpg   = 0xE4;
  static const byte SBC_zpg   = 0xE5;
  static const byte INC_zpg   = 0xE6;
  static const byte INX_impl  = 0xE8;
  static const byte SBC_immed = 0xE9;
  static const byte NOP_impl  = 0xEA;
  static const byte CPX_abs   = 0xEC;
  static const byte SBC_abs   = 0xED;
  static const byte INC_abs   = 0xEE;

  // HI-NIBBLE == 0xF0
  static const byte BEQ_rel   = 0xF0;
  static const byte SBC_ind_Y = 0xF1;
  static const byte SBC_zpg_X = 0xF5;
  static const byte INC_zpg_X = 0xF6;
  static const byte SED_impl  = 0xF8;
  static const byte SBC_abs_Y = 0xF9;
  static const byte SBC_abs_X = 0xFD;
  static const byte INC_abs_X = 0xFE;
}
#endif // MOS_6502_H //:~
