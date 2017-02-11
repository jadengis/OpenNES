//===-- source/cpu/mos6502.cpp - Mos6502 Cpu Class Impl ---------*- C++ -*-===//
//
//                           The OsNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of the public interface for the
/// Mos6502 class.
///
//===----------------------------------------------------------------------===//
#include "memory/Reference.h"
#include "cpu/Exception.h"
#include "cpu/Mos6502.h"

void Mos6502::executeOpcode(byte opcode) {
  // To execute a fetched opcode, first update the cycle count, use the indicated
  // addressing mode to compute the memory reference, if needed, and then call the
  // associated emulation function

  // Declare memory refence before looking up the opcode
  Memory::Reference<byte> ref(nullptr, 0);

  // Lookup the fetched opcode
  switch(opcode) {
    // HI-NIBBLE == 0x00
    case Op::BRK_IMPL:
      cycleCount += 7;
      BRK();
      break;
    case Op::ORA_X_IND:
      cycleCount += 6;
      ref = X_IND();
      ORA(ref.read());
      break;
    case Op::ORA_ZPG:
      cycleCount += 3;
      ref = ZPG();
      ORA(ref.read());
      break;
    case Op::ASL_ZPG:
      cycleCount += 5;
      ref = ZPG();
      ref.write(ASL(ref.read()));
      break;
    case Op::PHP_IMPL:
      cycleCount += 3;
      PHP();
      break;
    case Op::ORA_IMMED:
      cycleCount += 2;
      ref = IMMED();
      ORA(ref.read());
      break;
    case Op::ASL_ACC:
      cycleCount += 2;
      reg.ac = ASL(reg.ac);
      break;
    case Op::ORA_ABS:
      cycleCount += 4;
      ref = ABS();
      ORA(ref.read());
      break;
    case Op::ASL_ABS:
      cycleCount += 6;
      ref = ABS();
      ref.write(ASL(ref.read()));
      break;

    // HI-NIBBLE == 0x10
    case Op::BPL_REL:
      cycleCount += 2;
      ref = REL();
      BPL(ref.read());
      break;
    case Op::ORA_IND_Y:
      cycleCount += 5;
      ref = IND_Y();
      ORA(ref.read());
      break;
    case Op::ORA_ZPG_X:
      cycleCount += 4;
      ref = ZPG_X();
      ORA(ref.read());
      break;
    case Op::ASL_ZPG_X:
      cycleCount += 6;
      ref = ZPG_X();
      ref.write(ASL(ref.read()));
      break;
    case Op::CLC_IMPL:
      cycleCount += 2;
      CLC();
      break;
    case Op::ORA_ABS_Y:
      cycleCount += 4;
      ref = ABS_Y();
      ORA(ref.read());
      break;
    case Op::ORA_ABS_X:
      cycleCount += 4;
      ref = ABS_X();
      ORA(ref.read());
      break;
    case Op::ASL_ABS_X:
      cycleCount += 4;
      ref = ABS_X();
      ref.write(ASL(ref.read()));
      break;

    // HI-NIBBLE == 0x20
    case Op::JSR_ABS:
      cycleCount += 6;
      ref = ABS();
      JSR(ref.read(), (++ref).read());
      break;
    case Op::AND_X_IND:
      cycleCount += 6;
      ref = X_IND();
      AND(ref.read());
      break;
    case Op::BIT_ZPG:
      cycleCount += 3;
      ref = ZPG();
      BIT(ref.read());
      break;
    case Op::AND_ZPG:
      cycleCount += 3;
      ref = ZPG();
      AND(ref.read());
      break;
    case Op::ROL_ZPG:
      cycleCount += 5;
      ref = ZPG();
      ref.write(ROL(ref.read()));
      break;
    case Op::PLP_IMPL:
      cycleCount += 4;
      PLP();
      break;
    case Op::AND_IMMED:
      cycleCount += 2;
      ref = IMMED();
      AND(ref.read());
      break;
    case Op::ROL_ACC:
      cycleCount += 2;
      reg.ac = ROL(reg.ac);
      break;
    case Op::BIT_ABS:
      cycleCount += 4;
      ref = ABS();
      BIT(ref.read());
      break;
    case Op::AND_ABS:
      cycleCount += 4;
      ref = ABS();
      AND(ref.read());
      break;
    case Op::ROL_ABS:
      cycleCount += 6;
      ref = ABS();
      ref.write(ROL(ref.read()));
      break;

    // HI-NIBBLE == 0x30
    case Op::BMI_REL:
      cycleCount += 2;
      ref = REL();
      BMI(ref.read());
      break;
    case Op::AND_IND_Y:
      cycleCount += 5;
      ref = IND_Y();
      AND(ref.read());
      break;
    case Op::AND_ZPG_X:
      cycleCount += 4;
      ref = ZPG_X();
      AND(ref.read());
      break;
    case Op::ROL_ZPG_X:
      cycleCount += 6;
      ref = ZPG_X();
      ref.write(ROL(ref.read()));
      break;
    case Op::SEC_IMPL:
      cycleCount += 2;
      SEC();
      break;
    case Op::AND_ABS_Y:
      cycleCount += 4;
      ref = ABS_Y();
      AND(ref.read());
      break;
    case Op::AND_ABS_X:
      cycleCount += 4;
      ref = ABS_X();
      AND(ref.read());
      break;
    case Op::ROL_ABS_X:
      cycleCount += 7;
      ref = ABS_X();
      ref.write(ROL(ref.read()));
      break;

    // HI-NIBBLE == 0x40
    case Op::RTI_IMPL:
      cycleCount += 6;
      RTI();
      break;
    case Op::EOR_X_IND:
      cycleCount += 6;
      ref = X_IND();
      EOR(ref.read());
      break;
    case Op::EOR_ZPG:
      cycleCount += 3;
      ref = ZPG();
      EOR(ref.read());
      break;
    case Op::LSR_ZPG:
      cycleCount += 5;
      ref = ZPG();
      ref.write(LSR(ref.read()));
      break;
    case Op::PHA_IMPL:
      cycleCount += 3;
      PHA();
      break;
    case Op::EOR_IMMED:
      cycleCount += 2;
      ref = IMMED();
      EOR(ref.read());
      break;
    case Op::LSR_ACC:
      cycleCount += 2;
      reg.ac = LSR(reg.ac);
      break;
    case Op::JMP_ABS:
      cycleCount += 3;
      ref = ABS();
      JMP(ref.read(), (++ref).read());
      break;
    case Op::EOR_ABS:
      cycleCount += 4;
      ref = ABS();
      EOR(ref.read());
      break;
    case Op::LSR_ABS:
      cycleCount += 6;
      ref = ABS();
      ref.write(LSR(ref.read()));
      break;

    // HI-NIBBLE == 0x50
    case Op::BVC_REL:
      cycleCount += 2;
      ref = REL();
      BVC(ref.read());
      break;
    case Op::EOR_IND_Y:
      cycleCount += 5;
      ref = IND_Y();
      EOR(ref.read());
      break;
    case Op::EOR_ZPG_X:
      cycleCount += 4;
      ref = ZPG_X();
      EOR(ref.read());
      break;
    case Op::LSR_ZPG_X:
      cycleCount += 6;
      ref = ZPG_X();
      ref.write(LSR(ref.read()));
      break;
    case Op::CLI_IMPL:
      cycleCount += 2;
      CLI();
      break;
    case Op::EOR_ABS_Y:
      cycleCount += 4;
      ref = ABS_Y();
      EOR(ref.read());
      break;
    case Op::EOR_ABS_X:
      cycleCount += 4;
      ref = ABS_X();
      EOR(ref.read());
      break;
    case Op::LSR_ABS_X:
      cycleCount += 7;
      ref = ABS_X();
      ref.write(LSR(ref.read()));
      break;

    // HI-NIBBLE == 0x60
    case Op::RTS_IMPL:
      cycleCount += 6;
      RTS();
      break;
    case Op::ADC_X_IND:
      cycleCount += 6;
      ref = X_IND();
      ADC(ref.read());
      break;
    case Op::ADC_ZPG:
      cycleCount += 3;
      ref = ZPG();
      ADC(ref.read());
      break;
    case Op::ROR_ZPG:
      cycleCount += 5;
      ref = ZPG();
      ref.write(ROR(ref.read()));
      break;
    case Op::PLA_IMPL:
      cycleCount += 4;
      PLA();
      break;
    case Op::ADC_IMMED:
      cycleCount += 2;
      ref = IMMED();
      ADC(ref.read());
      break;
    case Op::ROR_ACC:
      cycleCount += 2;
      reg.ac = ROR(reg.ac);
      break;
    case Op::JMP_IND:
      cycleCount += 5;
      ref = IND();
      JMP(ref.read(), (++ref).read());
      break;
    case Op::ADC_ABS:
      cycleCount += 4;
      ref = ABS();
      ADC(ref.read());
      break;
    case Op::ROR_ABS:
      cycleCount += 6;
      ref = ABS();
      ref.write(ROR(ref.read()));
      break;

    // HI-NIBBLE == 0x70
    case Op::BVS_REL:
      cycleCount += 2;
      ref = REL();
      BVS(ref.read());
      break;
    case Op::ADC_IND_Y:
      cycleCount += 5;
      ref = IND_Y();
      ADC(ref.read());
      break;
    case Op::ADC_ZPG_X:
      cycleCount += 4;
      ref = ZPG_X();
      ADC(ref.read());
      break;
    case Op::ROR_ZPG_X:
      cycleCount += 6;
      ref = ZPG_X();
      ref.write(ROR(ref.read()));
      break;
    case Op::SEI_IMPL:
      cycleCount += 2;
      SEI();
      break;
    case Op::ADC_ABS_Y:
      cycleCount += 5;
      ref = ABS_Y();
      ADC(ref.read());
      break;
    case Op::ADC_ABS_X:
      cycleCount += 6;
      ref = ABS_X();
      ADC(ref.read());
      break;
    case Op::ROR_ABS_X:
      cycleCount += 7;
      ref = ABS_X();
      ref.write(ROR(ref.read()));
      break;

    // HI-NIBBLE == 0x80
    case Op::STA_X_IND:
      cycleCount += 6;
      ref = X_IND();
      ref.write(STA());
      break;
    case Op::STY_ZPG:
      cycleCount += 3;
      ref = ZPG();
      ref.write(STY());
      break;
    case Op::STA_ZPG:
      cycleCount += 3;
      ref = ZPG();
      ref.write(STA());
      break;
    case Op::STX_ZPG:
      cycleCount += 3;
      ref = ZPG();
      ref.write(STX());
      break;
    case Op::DEY_IMPL:
      cycleCount += 2;
      DEY();
      break;
    case Op::TXA_IMPL:
      cycleCount += 2;
      TXA();
      break;
    case Op::STY_ABS:
      cycleCount += 4;
      ref = ABS();
      ref.write(STY());
      break;
    case Op::STA_ABS:
      cycleCount += 4;
      ref = ABS();
      ref.write(STA());
      break;
    case Op::STX_ABS:
      cycleCount += 4;
      ref = ABS();
      ref.write(STX());
      break;

    // HI-NIBBLE == 0x90
    case Op::BCC_REL:
      cycleCount += 2;
      ref = REL();
      BCC(ref.read());
      break;
    case Op::STA_IND_Y:
      cycleCount += 6;
      ref = IND_Y();
      ref.write(STA());
      break;
    case Op::STY_ZPG_X:
      cycleCount += 4;
      ref = ZPG_X();
      ref.write(STY());
      break;
    case Op::STA_ZPG_X:
      cycleCount += 4;
      ref = ZPG_X();
      ref.write(STA());
      break;
    case Op::STX_ZPG_Y:
      cycleCount += 4;
      ref = ZPG_Y();
      ref.write(STX());
      break;
    case Op::TYA_IMPL:
      cycleCount += 2;
      TYA();
      break;
    case Op::STA_ABS_Y:
      cycleCount += 4;
      ref = ABS_Y();
      ref.write(STA());
      break;
    case Op::TXS_IMPL:
      cycleCount += 2;
      TXS();
      break;
    case Op::STA_ABS_X:
      cycleCount += 4;
      ref = ABS_X();
      ref.write(STA());
      break;

    // HI-NIBBLE == 0xA0
    case Op::LDY_IMMED:
      cycleCount += 2;
      ref = IMMED();
      LDY(ref.read());
      break;
    case Op::LDA_X_IND:
      cycleCount += 6;
      ref = X_IND();
      LDA(ref.read());
      break;
    case Op::LDX_IMMED:
      cycleCount += 2;
      ref = IMMED();
      LDX(ref.read());
      break;
    case Op::LDY_ZPG:
      cycleCount += 3;
      ref = ZPG();
      LDY(ref.read());
      break;
    case Op::LDA_ZPG:
      cycleCount += 3;
      ref = ZPG();
      LDA(ref.read());
      break;
    case Op::LDX_ZPG:
      cycleCount += 3;
      ref = ZPG();
      LDX(ref.read());
      break;
    case Op::TAY_IMPL:
      cycleCount += 2;
      TAY();
      break;
    case Op::LDA_IMMED:
      cycleCount += 2;
      ref = IMMED();
      LDA(ref.read());
      break;
    case Op::TAX_IMPL:
      cycleCount += 2;
      TAX();
      break;
    case Op::LDY_ABS:
      cycleCount += 4;
      ref = ABS();
      LDY(ref.read());
      break;
    case Op::LDA_ABS:
      cycleCount += 4;
      ref = ABS();
      LDA(ref.read());
      break;
    case Op::LDX_ABS:
      cycleCount += 4;
      ref = ABS();
      LDX(ref.read());
      break;

    // HI-NIBBLE == 0xB0
    case Op::BCS_REL:
      cycleCount += 2;
      ref = REL();
      BCS(ref.read());
      break;
    case Op::LDA_IND_Y:
      cycleCount += 5;
      ref = IND_Y();
      LDA(ref.read());
      break;
    case Op::LDY_ZPG_X:
      cycleCount += 4;
      ref = ZPG_X();
      LDY(ref.read());
      break;
    case Op::LDA_ZPG_X:
      cycleCount += 4;
      ref = ZPG_X();
      LDA(ref.read());
      break;
    case Op::LDX_ZPG_Y:
      cycleCount += 4;
      ref = ZPG_Y();
      LDX(ref.read());
      break;
    case Op::CLV_IMPL:
      cycleCount += 2;
      CLV();
      break;
    case Op::LDA_ABS_Y:
      cycleCount += 4;
      ref = ABS_Y();
      LDA(ref.read());
      break;
    case Op::TSX_IMPL:
      cycleCount += 2;
      TSX();
      break;
    case Op::LDY_ABS_X:
      cycleCount += 4;
      ref = ABS_X();
      LDY(ref.read());
      break;
    case Op::LDA_ABS_X:
      cycleCount += 4;
      ref = ABS_X();
      LDA(ref.read());
      break;
    case Op::LDX_ABS_Y:
      cycleCount += 4;
      ref = ABS_Y();
      LDX(ref.read());
      break;

    // HI-NIBBLE == 0xC0
    case Op::CPY_IMMED:
      cycleCount += 2;
      ref = IMMED();
      CPY(ref.read());
      break;
    case Op::CMP_X_IND:
      cycleCount += 6;
      ref = X_IND();
      CMP(ref.read());
      break;
    case Op::CPY_ZPG:
      cycleCount += 3;
      ref = ZPG();
      CPY(ref.read());
      break;
    case Op::CMP_ZPG:
      cycleCount += 3;
      ref = ZPG();
      CMP(ref.read());
      break;
    case Op::DEC_ZPG:
      cycleCount += 5;
      ref = ZPG();
      DEC(ref.read());
      break;
    case Op::INY_IMPL:
      cycleCount += 2;
      INY();
      break;
    case Op::CMP_IMMED:
      cycleCount += 2;
      ref = IMMED();
      CMP(ref.read());
      break;
    case Op::DEX_IMPL:
      cycleCount += 2;
      DEX();
      break;
    case Op::CPY_ABS:
      cycleCount += 4;
      ref = ABS();
      CPY(ref.read());
      break;
    case Op::CMP_ABS:
      cycleCount += 4;
      ref = ABS();
      CMP(ref.read());
      break;
    case Op::DEC_ABS:
      cycleCount += 6;
      ref = ABS();
      DEC(ref.read());
      break;

    // HI-NIBBLE == 0xD0
    case Op::BNE_REL:
      cycleCount += 2;
      ref = REL();
      BNE(ref.read());
      break;
    case Op::CMP_IND_Y:
      cycleCount += 5;
      ref = IND_Y();
      CPY(ref.read());
      break;
    case Op::CMP_ZPG_X:
      cycleCount += 4;
      ref = ZPG_X();
      CMP(ref.read());
      break;
    case Op::DEC_ZPG_X:
      cycleCount += 6;
      ref = ZPG_X();
      DEC(ref.read());
      break;
    case Op::CLD_IMPL:
      cycleCount += 2;
      CLD();
      break;
    case Op::CMP_ABS_Y:
      cycleCount += 4;
      ref = ABS_Y();
      CPY(ref.read());
      break;
    case Op::CMP_ABS_X:
      cycleCount += 4;
      ref = ABS_X();
      CMP(ref.read());
      break;
    case Op::DEC_ABS_X:
      cycleCount += 7;
      ref = ABS_X();
      DEC(ref.read());
      break;

    // HI-NIBBLE == 0xE0
    case Op::CPX_IMMED:
      cycleCount += 2;
      ref = IMMED();
      CPX(ref.read());
      break;
    case Op::SBC_X_IND:
      cycleCount += 6;
      ref = X_IND();
      SBC(ref.read());
      break;
    case Op::CPX_ZPG:
      cycleCount += 3;
      ref = ZPG();
      CPX(ref.read());
      break;
    case Op::SBC_ZPG:
      cycleCount += 3;
      ref = ZPG();
      SBC(ref.read());
      break;
    case Op::INC_ZPG:
      cycleCount += 5;
      ref = ZPG();
      INC(ref.read());
      break;
    case Op::INX_IMPL:
      cycleCount += 2;
      INX();
      break;
    case Op::SBC_IMMED:
      cycleCount += 2;
      ref = IMMED();
      SBC(ref.read());
      break;
    case Op::NOP_IMPL:
      cycleCount += 2;
      NOP();
      break;
    case Op::CPX_ABS:
      cycleCount += 4;
      ref = ABS();
      CPX(ref.read());
      break;
    case Op::SBC_ABS:
      cycleCount += 4;
      ref = ABS();
      SBC(ref.read());
      break;
    case Op::INC_ABS:
      cycleCount += 6;
      ref = ABS();
      INC(ref.read());
      break;

    // HI-NIBBLE == 0xF0
    case Op::BEQ_REL:
      cycleCount += 2;
      ref = REL();
      BEQ(ref.read());
      break;
    case Op::SBC_IND_Y:
      cycleCount += 5;
      ref = IND_Y();
      SBC(ref.read());
      break;
    case Op::SBC_ZPG_X:
      cycleCount += 4;
      ref = ZPG_X();
      SBC(ref.read());
      break;
    case Op::INC_ZPG_X:
      cycleCount += 6;
      ref = ZPG_X();
      INC(ref.read());
      break;
    case Op::SED_IMPL:
      cycleCount += 2;
      SED();
      break;
    case Op::SBC_ABS_Y:
      cycleCount += 4;
      ref = ABS_Y();
      SBC(ref.read());
      break;
    case Op::SBC_ABS_X:
      cycleCount += 4;
      ref = ABS_X();
      SBC(ref.read());
      break;
    case Op::INC_ABS_X:
      cycleCount += 7;
      ref = ABS_X();
      INC(ref.read());
      break;
    default:
      // opcode must be unrecognized, throw exception
      throw Exception::BadOpcode(opcode);
      break;
  }

}
