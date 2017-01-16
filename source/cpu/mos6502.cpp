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
#include "exception.h"
#include "cpu/mem.h"
#include "cpu/mos6502.h"

void Mos6502::Execute(byte opcode) {
  // To execute a fetched opcode, first update the cycle count, use the indicated
  // addressing mode to compute the memory reference, if needed, and then call the
  // associated emulation function

  // Declare memory refence before looking up the opcode
  Mem::Ref ref;

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
      ORA(*ref);
      break;
    case Op::ORA_ZPG:
      cycle_count += 3;
      ref = ZPG();
      ORA(*ref);
      break;
    case Op::ASL_ZPG:
      cycle_count += 5;
      ref = ZPG();
      *ref = ASL(*ref);
      break;
    case Op::PHP_IMPL:
      cycle_count += 3;
      PHP();
      break;
    case Op::ORA_IMMED:
      cycle_count += 2;
      ref = IMMED();
      ORA(*ref);
      break;
    case Op::ASL_ACC:
      cycle_count += 2;
      reg.ac = ASL(reg.ac);
      break;
    case Op::ORA_ABS:
      cycle_count += 4;
      ref = ABS();
      ORA(*ref);
      break;
    case Op::ASL_ABS:
      cycle_count += 6;
      ref = ABS();
      *ref = ASL(*ref);
      break;

    // HI-NIBBLE == 0x10
    case Op::BPL_REL:
      cycle_count += 2;
      ref = REL();
      BPL(*ref);
      break;
    case Op::ORA_IND_Y:
      cycle_count += 5;
      ref = IND_Y();
      ORA(*ref);
      break;
    case Op::ORA_ZPG_X:
      cycle_count += 4;
      ref = ZPG_X();
      ORA(*ref);
      break;
    case Op::ASL_ZPG_X:
      cycle_count += 6;
      ref = ZPG_X();
      *ref = ASL(*ref);
      break;
    case Op::CLC_IMPL:
      cycle_count += 2;
      CLC();
      break;
    case Op::ORA_ABS_Y:
      cycle_count += 4;
      ref = ABS_Y();
      ORA(*ref);
      break;
    case Op::ORA_ABS_X:
      cycle_count += 4;
      ref = ABS_X();
      ORA(*ref);
      break;
    case Op::ASL_ABS_X:
      cycle_count += 4;
      ref = ABS_X();
      *ref = ASL(*ref);
      break;

    // HI-NIBBLE == 0x20
    case Op::JSR_ABS:
      cycle_count += 6;
      ref = ABS();
      JSR(*ref, *(ref + 1));
      break;
    case Op::AND_X_IND:
      cycle_count += 6;
      ref = X_IND();
      AND(*ref);
      break;
    case Op::BIT_ZPG:
      cycle_count += 3;
      ref = ZPG();
      BIT(*ref);
      break;
    case Op::AND_ZPG:
      cycle_count += 3;
      ref = ZPG();
      AND(*ref);
      break;
    case Op::ROL_ZPG:
      cycle_count += 5;
      ref = ZPG();
      *ref = ROL(*ref);
      break;
    case Op::PLP_IMPL:
      cycle_count += 4;
      PLP();
      break;
    case Op::AND_IMMED:
      cycle_count += 2;
      ref = IMMED();
      AND(*ref);
      break;
    case Op::ROL_ACC:
      cycle_count += 2;
      reg.ac = ROL(reg.ac);
      break;
    case Op::BIT_ABS:
      cycle_count += 4;
      ref = ABS();
      BIT(*ref);
      break;
    case Op::AND_ABS:
      cycle_count += 4;
      ref = ABS();
      AND(*ref);
      break;
    case Op::ROL_ABS:
      cycle_count += 6;
      ref = ABS();
      *ref = ROL(*ref);
      break;

    // HI-NIBBLE == 0x30
    case Op::BMI_REL:
      cycle_count += 2;
      ref = REL();
      BMI(*ref);
      break;
    case Op::AND_IND_Y:
      cycle_count += 5;
      ref = IND_Y();
      AND(*ref);
      break;
    case Op::AND_ZPG_X:
      cycle_count += 4;
      ref = ZPG_X();
      AND(*ref);
      break;
    case Op::ROL_ZPG_X:
      cycle_count += 6;
      ref = ZPG_X();
      *ref = ROL(*ref);
      break;
    case Op::SEC_IMPL:
      cycle_count += 2;
      SEC();
      break;
    case Op::AND_ABS_Y:
      cycle_count += 4;
      ref = ABS_Y();
      AND(*ref);
      break;
    case Op::AND_ABS_X:
      cycle_count += 4;
      ref = ABS_X();
      AND(*ref);
      break;
    case Op::ROL_ABS_X:
      cycle_count += 7;
      ref = ABS_X();
      *ref = ROL(*ref);
      break;

    // HI-NIBBLE == 0x40
    case Op::RTI_IMPL:
      cycle_count += 6;
      RTI();
      break;
    case Op::EOR_X_IND:
      cycle_count += 6;
      ref = X_IND();
      EOR(*ref);
      break;
    case Op::EOR_ZPG:
      cycle_count += 3;
      ref = ZPG();
      EOR(*ref);
      break;
    case Op::LSR_ZPG:
      cycle_count += 5;
      ref = ZPG();
      *ref = LSR(*ref);
      break;
    case Op::PHA_IMPL:
      cycle_count += 3;
      PHA();
      break;
    case Op::EOR_IMMED:
      cycle_count += 2;
      ref = IMMED();
      EOR(*ref);
      break;
    case Op::LSR_ACC:
      cycle_count += 2;
      reg.ac = LSR(reg.ac);
      break;
    case Op::JMP_ABS:
      cycle_count += 3;
      ref = ABS();
      JMP(*ref, *(ref+1));
      break;
    case Op::EOR_ABS:
      cycle_count += 4;
      ref = ABS();
      EOR(*ref);
      break;
    case Op::LSR_ABS:
      cycle_count += 6;
      ref = ABS();
      *ref = LSR(*ref);
      break;

    // HI-NIBBLE == 0x50
    case Op::BVC_REL:
      cycle_count += 2;
      ref = REL();
      BVC(*ref);
      break;
    case Op::EOR_IND_Y:
      cycle_count += 5;
      ref = IND_Y();
      EOR(*ref);
      break;
    case Op::EOR_ZPG_X:
      cycle_count += 4;
      ref = ZPG_X();
      EOR(*ref);
      break;
    case Op::LSR_ZPG_X:
      cycle_count += 6;
      ref = ZPG_X();
      *ref = LSR(*ref);
      break;
    case Op::CLI_IMPL:
      cycle_count += 2;
      CLI();
      break;
    case Op::EOR_ABS_Y:
      cycle_count += 4;
      ref = ABS_Y();
      EOR(*ref);
      break;
    case Op::EOR_ABS_X:
      cycle_count += 4;
      ref = ABS_X();
      EOR(*ref);
      break;
    case Op::LSR_ABS_X:
      cycle_count += 7;
      ref = ABS_X();
      *ref = LSR(*ref);
      break;

    // HI-NIBBLE == 0x60
    case Op::RTS_IMPL:
      cycle_count += 6;
      RTS();
      break;
    case Op::ADC_X_IND:
      cycle_count += 6;
      ref = X_IND();
      ADC(*ref);
      break;
    case Op::ADC_ZPG:
      cycle_count += 3;
      ref = ZPG();
      ADC(*ref);
      break;
    case Op::ROR_ZPG:
      cycle_count += 5;
      ref = ZPG();
      *ref = ROR(*ref);
      break;
    case Op::PLA_IMPL:
      cycle_count += 4;
      PLA();
      break;
    case Op::ADC_IMMED:
      cycle_count += 2;
      ref = IMMED();
      ADC(*ref);
      break;
    case Op::ROR_ACC:
      cycle_count += 2;
      reg.ac = ROR(reg.ac);
      break;
    case Op::JMP_IND:
      cycle_count += 5;
      ref = IND();
      JMP(*ref, *(ref+1));
      break;
    case Op::ADC_ABS:
      cycle_count += 4;
      ref = ABS();
      ADC(*ref);
      break;
    case Op::ROR_ABS:
      cycle_count += 6;
      ref = ABS();
      *ref = ROR(*ref);
      break;

    // HI-NIBBLE == 0x70
    case Op::BVS_REL:
      cycle_count += 2;
      ref = REL();
      BVS(*ref);
      break;
    case Op::ADC_IND_Y:
      cycle_count += 5;
      ref = IND_Y();
      ADC(*ref);
      break;
    case Op::ADC_ZPG_X:
      cycle_count += 4;
      ref = ZPG_X();
      ADC(*ref);
      break;
    case Op::ROR_ZPG_X:
      cycle_count += 6;
      ref = ZPG_X();
      *ref = ROR(*ref);
      break;
    case Op::SEI_IMPL:
      cycle_count += 2;
      SEI();
      break;
    case Op::ADC_ABS_Y:
      cycle_count += 5;
      ref = ABS_Y();
      ADC(*ref);
      break;
    case Op::ADC_ABS_X:
      cycle_count += 6;
      ref = ABS_X();
      ADC(*ref);
      break;
    case Op::ROR_ABS_X:
      cycle_count += 7;
      ref = ABS_X();
      *ref = ROR(*ref);
      break;

    // HI-NIBBLE == 0x80
    case Op::STA_X_IND:
      cycle_count += 6;
      ref = X_IND();
      *ref = STA();
      break;
    case Op::STY_ZPG:
      cycle_count += 3;
      ref = ZPG();
      *ref = STY();
      break;
    case Op::STA_ZPG:
      cycle_count += 3;
      ref = ZPG();
      *ref = STA();
      break;
    case Op::STX_ZPG:
      cycle_count += 3;
      ref = ZPG();
      *ref = STX();
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
      *ref = STY();
      break;
    case Op::STA_ABS:
      cycle_count += 4;
      ref = ABS();
      *ref = STA();
      break;
    case Op::STX_ABS:
      cycle_count += 4;
      ref = ABS();
      *ref = STX();
      break;

    // HI-NIBBLE == 0x90


    default:
      // opcode must be unrecognized, throw exception
      throw Exception::BadOpcode(opcode);
      break;
  }

}
