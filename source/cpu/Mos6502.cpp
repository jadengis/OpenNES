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
#include "Exception.h"
#include "memory/Reference.h"
#include "cpu/Mos6502.h"

void Mos6502::Execute(byte opcode) {
  // To execute a fetched opcode, first update the cycle count, use the indicated
  // addressing mode to compute the memory reference, if needed, and then call the
  // associated emulation function

  // Declare memory refence before looking up the opcode
  Memory::Reference ref;

  // Lookup the fetched opcode
  switch(opcode) {
    // HI-NIBBLE == 0x00
    case Op::BRK_IMPL:
      cycle_count += 7;
      BRK();
      break;
    case Op::ORA_X_IND:
      cycle_count += 6;
      ref = X_IND();
      ORA(ref.Read());
      break;
    case Op::ORA_ZPG:
      cycle_count += 3;
      ref = ZPG();
      ORA(ref.Read());
      break;
    case Op::ASL_ZPG:
      cycle_count += 5;
      ref = ZPG();
      ref.Write(ASL(ref.Read()));
      break;
    case Op::PHP_IMPL:
      cycle_count += 3;
      PHP();
      break;
    case Op::ORA_IMMED:
      cycle_count += 2;
      ref = IMMED();
      ORA(ref.Read());
      break;
    case Op::ASL_ACC:
      cycle_count += 2;
      reg.ac = ASL(reg.ac);
      break;
    case Op::ORA_ABS:
      cycle_count += 4;
      ref = ABS();
      ORA(ref.Read());
      break;
    case Op::ASL_ABS:
      cycle_count += 6;
      ref = ABS();
      ref.Write(ASL(ref.Read()));
      break;

    // HI-NIBBLE == 0x10
    case Op::BPL_REL:
      cycle_count += 2;
      ref = REL();
      BPL(ref.Read());
      break;
    case Op::ORA_IND_Y:
      cycle_count += 5;
      ref = IND_Y();
      ORA(ref.Read());
      break;
    case Op::ORA_ZPG_X:
      cycle_count += 4;
      ref = ZPG_X();
      ORA(ref.Read());
      break;
    case Op::ASL_ZPG_X:
      cycle_count += 6;
      ref = ZPG_X();
      ref.Write(ASL(ref.Read()));
      break;
    case Op::CLC_IMPL:
      cycle_count += 2;
      CLC();
      break;
    case Op::ORA_ABS_Y:
      cycle_count += 4;
      ref = ABS_Y();
      ORA(ref.Read());
      break;
    case Op::ORA_ABS_X:
      cycle_count += 4;
      ref = ABS_X();
      ORA(ref.Read());
      break;
    case Op::ASL_ABS_X:
      cycle_count += 4;
      ref = ABS_X();
      ref.Write(ASL(ref.Read()));
      break;

    // HI-NIBBLE == 0x20
    case Op::JSR_ABS:
      cycle_count += 6;
      ref = ABS();
      JSR(ref.Read(), (++ref).Read());
      break;
    case Op::AND_X_IND:
      cycle_count += 6;
      ref = X_IND();
      AND(ref.Read());
      break;
    case Op::BIT_ZPG:
      cycle_count += 3;
      ref = ZPG();
      BIT(ref.Read());
      break;
    case Op::AND_ZPG:
      cycle_count += 3;
      ref = ZPG();
      AND(ref.Read());
      break;
    case Op::ROL_ZPG:
      cycle_count += 5;
      ref = ZPG();
      ref.Write(ROL(ref.Read()));
      break;
    case Op::PLP_IMPL:
      cycle_count += 4;
      PLP();
      break;
    case Op::AND_IMMED:
      cycle_count += 2;
      ref = IMMED();
      AND(ref.Read());
      break;
    case Op::ROL_ACC:
      cycle_count += 2;
      reg.ac = ROL(reg.ac);
      break;
    case Op::BIT_ABS:
      cycle_count += 4;
      ref = ABS();
      BIT(ref.Read());
      break;
    case Op::AND_ABS:
      cycle_count += 4;
      ref = ABS();
      AND(ref.Read());
      break;
    case Op::ROL_ABS:
      cycle_count += 6;
      ref = ABS();
      ref.Wite(ROL(ref.Read()));
      break;

    // HI-NIBBLE == 0x30
    case Op::BMI_REL:
      cycle_count += 2;
      ref = REL();
      BMI(ref.Read());
      break;
    case Op::AND_IND_Y:
      cycle_count += 5;
      ref = IND_Y();
      AND(ref.Read());
      break;
    case Op::AND_ZPG_X:
      cycle_count += 4;
      ref = ZPG_X();
      AND(ref.Read());
      break;
    case Op::ROL_ZPG_X:
      cycle_count += 6;
      ref = ZPG_X();
      ref.Write(ROL(ref.Read()));
      break;
    case Op::SEC_IMPL:
      cycle_count += 2;
      SEC();
      break;
    case Op::AND_ABS_Y:
      cycle_count += 4;
      ref = ABS_Y();
      AND(ref.Read());
      break;
    case Op::AND_ABS_X:
      cycle_count += 4;
      ref = ABS_X();
      AND(ref.Read());
      break;
    case Op::ROL_ABS_X:
      cycle_count += 7;
      ref = ABS_X();
      ref.Write(ROL(ref.Read()));
      break;

    // HI-NIBBLE == 0x40
    case Op::RTI_IMPL:
      cycle_count += 6;
      RTI();
      break;
    case Op::EOR_X_IND:
      cycle_count += 6;
      ref = X_IND();
      EOR(ref.Read());
      break;
    case Op::EOR_ZPG:
      cycle_count += 3;
      ref = ZPG();
      EOR(ref.Read());
      break;
    case Op::LSR_ZPG:
      cycle_count += 5;
      ref = ZPG();
      ref.Write(LSR(ref.Read()));
      break;
    case Op::PHA_IMPL:
      cycle_count += 3;
      PHA();
      break;
    case Op::EOR_IMMED:
      cycle_count += 2;
      ref = IMMED();
      EOR(ref.Read());
      break;
    case Op::LSR_ACC:
      cycle_count += 2;
      reg.ac = LSR(reg.ac);
      break;
    case Op::JMP_ABS:
      cycle_count += 3;
      ref = ABS();
      JMP(ref.Read(), (++ref).Read());
      break;
    case Op::EOR_ABS:
      cycle_count += 4;
      ref = ABS();
      EOR(ref.Read());
      break;
    case Op::LSR_ABS:
      cycle_count += 6;
      ref = ABS();
      ref.Write(LSR(ref.Read()));
      break;

    // HI-NIBBLE == 0x50
    case Op::BVC_REL:
      cycle_count += 2;
      ref = REL();
      BVC(ref.Read());
      break;
    case Op::EOR_IND_Y:
      cycle_count += 5;
      ref = IND_Y();
      EOR(ref.Read());
      break;
    case Op::EOR_ZPG_X:
      cycle_count += 4;
      ref = ZPG_X();
      EOR(ref.Read());
      break;
    case Op::LSR_ZPG_X:
      cycle_count += 6;
      ref = ZPG_X();
      ref.Write(LSR(ref.Read()));
      break;
    case Op::CLI_IMPL:
      cycle_count += 2;
      CLI();
      break;
    case Op::EOR_ABS_Y:
      cycle_count += 4;
      ref = ABS_Y();
      EOR(ref.Read());
      break;
    case Op::EOR_ABS_X:
      cycle_count += 4;
      ref = ABS_X();
      EOR(ref.Read());
      break;
    case Op::LSR_ABS_X:
      cycle_count += 7;
      ref = ABS_X();
      ref.Write(LSR(ref.Read()));
      break;

    // HI-NIBBLE == 0x60
    case Op::RTS_IMPL:
      cycle_count += 6;
      RTS();
      break;
    case Op::ADC_X_IND:
      cycle_count += 6;
      ref = X_IND();
      ADC(ref.Read());
      break;
    case Op::ADC_ZPG:
      cycle_count += 3;
      ref = ZPG();
      ADC(ref.Read());
      break;
    case Op::ROR_ZPG:
      cycle_count += 5;
      ref = ZPG();
      ref.Write(ROR(ref.Read()));
      break;
    case Op::PLA_IMPL:
      cycle_count += 4;
      PLA();
      break;
    case Op::ADC_IMMED:
      cycle_count += 2;
      ref = IMMED();
      ADC(ref.Read());
      break;
    case Op::ROR_ACC:
      cycle_count += 2;
      reg.ac = ROR(reg.ac);
      break;
    case Op::JMP_IND:
      cycle_count += 5;
      ref = IND();
      JMP(ref.Read(), (++ref).Read());
      break;
    case Op::ADC_ABS:
      cycle_count += 4;
      ref = ABS();
      ADC(ref.Read());
      break;
    case Op::ROR_ABS:
      cycle_count += 6;
      ref = ABS();
      ref.Write(ROR(ref.Read()));
      break;

    // HI-NIBBLE == 0x70
    case Op::BVS_REL:
      cycle_count += 2;
      ref = REL();
      BVS(ref.Read());
      break;
    case Op::ADC_IND_Y:
      cycle_count += 5;
      ref = IND_Y();
      ADC(ref.Read());
      break;
    case Op::ADC_ZPG_X:
      cycle_count += 4;
      ref = ZPG_X();
      ADC(ref.Read());
      break;
    case Op::ROR_ZPG_X:
      cycle_count += 6;
      ref = ZPG_X();
      ref.Write(ROR(ref.Read()));
      break;
    case Op::SEI_IMPL:
      cycle_count += 2;
      SEI();
      break;
    case Op::ADC_ABS_Y:
      cycle_count += 5;
      ref = ABS_Y();
      ADC(ref.Read());
      break;
    case Op::ADC_ABS_X:
      cycle_count += 6;
      ref = ABS_X();
      ADC(ref.Read());
      break;
    case Op::ROR_ABS_X:
      cycle_count += 7;
      ref = ABS_X();
      ref.Write(ROR(ref.Read()));
      break;

    // HI-NIBBLE == 0x80
    case Op::STA_X_IND:
      cycle_count += 6;
      ref = X_IND();
      ref.Write(STA());
      break;
    case Op::STY_ZPG:
      cycle_count += 3;
      ref = ZPG();
      ref.Write(STY());
      break;
    case Op::STA_ZPG:
      cycle_count += 3;
      ref = ZPG();
      ref.Write(STA());
      break;
    case Op::STX_ZPG:
      cycle_count += 3;
      ref = ZPG();
      ref.Write(STX());
      break;
    case Op::DEY_IMPL:
      cycle_count += 2;
      DEY();
      break;
    case Op::TXA_IMPL:
      cycle_count += 2;
      TXA();
      break;
    case Op::STY_ABS:
      cycle_count += 4;
      ref = ABS();
      ref.Write(STY());
      break;
    case Op::STA_ABS:
      cycle_count += 4;
      ref = ABS();
      ref.Write(STA());
      break;
    case Op::STX_ABS:
      cycle_count += 4;
      ref = ABS();
      ref.Write(STX());
      break;

    // HI-NIBBLE == 0x90
    case Op::BCC_REL:
      cycle_count += 2;
      ref = REL();
      BCC(ref.Read());
      break;
    case Op::STA_IND_Y:
      cycle_count += 6;
      ref = IND_Y();
      ref.Write(STA());
      break;
    case Op::STY_ZPG_X:
      cycle_count += 4;
      ref = ZPG_X();
      ref.Write(STY());
      break;
    case Op::STA_ZPG_X:
      cycle_count += 4;
      ref = ZPG_X();
      ref.Write(STA());
      break;
    case Op::STX_ZPG_Y:
      cycle_count += 4;
      ref = ZPG_Y();
      ref.Write(STX());
      break;
    case Op::TYA_IMPL:
      cycle_count += 2;
      TYA();
      break;
    case Op::STA_ABS_Y:
      cycle_count += 4;
      ref = ABS_Y();
      ref.Write(STA());
      break;
    case Op::TXS_IMPL:
      cycle_count += 2;
      TXS();
      break;
    case Op::STA_ABS_X:
      cycle_count += 4;
      ref = ABS_X();
      ref.Write(STA());
      break;

    // HI-NIBBLE == 0xA0
    case Op::LDY_IMMED:
      cycle_count += 2;
      ref = IMMED();
      LDY(ref.Read());
      break;
    case Op::LDA_X_IND:
      cycle_count += 6;
      ref = X_IND();
      LDA(ref.Read());
      break;
    case Op::LDX_IMMED:
      cycle_count += 2;
      ref = IMMED();
      LDX(ref.Read());
      break;
    case Op::LDY_ZPG:
      cycle_count += 3;
      ref = ZPG();
      LDY(ref.Read());
      break;
    case Op::LDA_ZPG:
      cycle_count += 3;
      ref = ZPG();
      LDA(ref.Read());
      break;
    case Op::LDX_ZPG:
      cycle_count += 3;
      ref = ZPG();
      LDX(ref.Read());
      break;
    case Op::TAY_IMPL:
      cycle_count += 2;
      TAY();
      break;
    case Op::LDA_IMMED:
      cycle_count += 2;
      ref = IMMED();
      LDA(ref.Read());
      break;
    case Op::TAX_IMPL:
      cycle_count += 2;
      TAX();
      break;
    case Op::LDY_ABS:
      cycle_count += 4;
      ref = ABS();
      LDY(ref.Read());
      break;
    case Op::LDA_ABS:
      cycle_count += 4;
      ref = ABS();
      LDA(ref.Read());
      break;
    case Op::LDX_ABS:
      cycle_count += 4;
      ref = ABS();
      LDX(ref.Read());
      break;

    // HI-NIBBLE == 0xB0
    case Op::BCS_REL:
      cycle_count += 2;
      ref = REL();
      BCS(ref.Read());
      break;
    case Op::LDA_IND_Y:
      cycle_count += 5;
      ref = IND_Y();
      LDA(ref.Read());
      break;
    case Op::LDY_ZPG_X:
      cycle_count += 4;
      ref = ZPG_X();
      LDY(ref.Read());
      break;
    case Op::LDA_ZPG_X:
      cycle_count += 4;
      ref = ZPG_X();
      LDA(ref.Read());
      break;
    case Op::LDX_ZPG_Y:
      cycle_count += 4;
      ref = ZPG_Y();
      LDX(ref.Read());
      break;
    case Op::CLV_IMPL:
      cycle_count += 2;
      CLV();
      break;
    case Op::LDA_ABS_Y:
      cycle_count += 4;
      ref = ABS_Y();
      LDA(ref.Read());
      break;
    case Op::TSX_IMPL:
      cycle_count += 2;
      TSX();
      break;
    case Op::LDY_ABS_X:
      cycle_count += 4;
      ref = ABS_X();
      LDY(ref.Read());
      break;
    case Op::LDA_ABS_X:
      cycle_count += 4;
      ref = ABS_X();
      LDA(ref.Read());
      break;
    case Op::LDX_ABS_Y:
      cycle_count += 4;
      ref = ABS_Y();
      LDX(ref.Read());
      break;

    // HI-NIBBLE == 0xC0
    case Op::CPY_IMMED:
      cycle_count += 2;
      ref = IMMED();
      CPY(ref.Read());
      break;
    case Op::CMP_X_IND:
      cycle_count += 6;
      ref = X_IND();
      CMP(ref.Read());
      break;
    case Op::CPY_ZPG:
      cycle_count += 3;
      ref = ZPG();
      CPY(ref.Read());
      break;
    case Op::CMP_ZPG:
      cycle_count += 3;
      ref = ZPG();
      CMP(ref.Read());
      break;
    case Op::DEC_ZPG:
      cycle_count += 5;
      ref = ZPG();
      DEC(ref.Read());
      break;
    case Op::INY_IMPL:
      cycle_count += 2;
      INY();
      break;
    case Op::CMP_IMMED:
      cycle_count += 2;
      ref = IMMED();
      CMP(ref.Read());
      break;
    case Op::DEX_IMPL:
      cycle_count += 2;
      DEX();
      break;
    case Op::CPY_ABS:
      cycle_count += 4;
      ref = ABS();
      CPY(ref.Read());
      break;
    case Op::CMP_ABS:
      cycle_count += 4;
      ref = ABS();
      CMP(ref.Read());
      break;
    case Op::DEC_ABS:
      cycle_count += 6;
      ref = ABS();
      DEC(ref.Read());
      break;

    // HI-NIBBLE == 0xD0
    case Op::BNE_REL:
      cycle_count += 2;
      ref = REL();
      BNE(ref.Read());
      break;
    case Op::CMP_IND_Y:
      cycle_count += 5;
      ref = IND_Y();
      CPY(ref.Read());
      break;
    case Op::CMP_ZPG_X:
      cycle_count += 4;
      ref = ZPG_X();
      CMP(ref.Read());
      break;
    case Op::DEC_ZPG_X:
      cycle_count += 6;
      ref = ZPG_X();
      DEC(ref.Read());
      break;
    case Op::CLD_IMPL:
      cycle_count += 2;
      CLD();
      break;
    case Op::CMP_ABS_Y:
      cycle_count += 4;
      ref = ABS_Y();
      CPY(ref.Read());
      break;
    case Op::CMP_ABS_X:
      cycle_count += 4;
      ref = ABS_X();
      CMP(ref.Read());
      break;
    case Op::DEC_ABS_X:
      cycle_count += 7;
      ref = ABS_X();
      DEC(ref.Read());
      break;

    // HI-NIBBLE == 0xE0
    case Op::CPX_IMMED:
      cycle_count += 2;
      ref = IMMED();
      CPX(ref.Read());
      break;
    case Op::SBC_X_IND:
      cycle_count += 6;
      ref = X_IND();
      SBC(ref.Read());
      break;
    case Op::CPX_ZPG:
      cycle_count += 3;
      ref = ZPG();
      CPX(ref.Read());
      break;
    case Op::SBC_ZPG:
      cycle_count += 3;
      ref = ZPG();
      SBC(ref.Read());
      break;
    case Op::INC_ZPG:
      cycle_count += 5;
      ref = ZPG();
      INC(ref.Read());
      break;
    case Op::INX_IMPL:
      cycle_count += 2;
      INX();
      break;
    case Op::SBC_IMMED:
      cycle_count += 2;
      ref = IMMED();
      SBC(ref.Read());
      break;
    case Op::NOP_IMPL:
      cycle_count += 2;
      NOP();
      break;
    case Op::CPX_ABS:
      cycle_count += 4;
      ref = ABS();
      CPX(ref.Read());
      break;
    case Op::SBC_ABS:
      cycle_count += 4;
      ref = ABS();
      SBC(ref.Read());
      break;
    case Op::INC_ABS:
      cycle_count += 6;
      ref = ABS();
      INC(ref.Read());
      break;

    // HI-NIBBLE == 0xF0
    case Op::BEQ_REL:
      cycle_count += 2;
      ref = REL();
      BEQ(ref.Read());
      break;
    case Op::SBC_IND_Y:
      cycle_count += 5;
      ref = IND_Y();
      SBC(ref.Read());
      break;
    case Op::SBC_ZPG_X:
      cycle_count += 4;
      ref = ZPG_X();
      SBC(ref.Read());
      break;
    case Op::INC_ZPG_X:
      cycle_count += 6;
      ref = ZPG_X();
      INC(ref.Read());
      break;
    case Op::SED_IMPL:
      cycle_count += 2;
      SED();
      break;
    case Op::SBC_ABS_Y:
      cycle_count += 4;
      ref = ABS_Y();
      SBC(ref.Read());
      break;
    case Op::SBC_ABS_X:
      cycle_count += 4;
      ref = ABS_X();
      SBC(ref.Read());
      break;
    case Op::INC_ABS_X:
      cycle_count += 7;
      ref = ABS_X();
      INC(ref.Read());
      break;
    default:
      // opcode must be unrecognized, throw exception
      throw Exception::BadOpcode(opcode);
      break;
  }

}
