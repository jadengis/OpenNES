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
      ref = X_Indirect();
      ORA(*ref);
      break;
    case Op::ORA_ZPG:
      cycle_count += 3;
      ref = Zeropage();
      ORA(*ref);
      break;
    case Op::ASL_ZPG:
      cycle_count += 5;
      ref = Zeropage();
      *ref = ASL(*ref);
      break;
    case Op::PHP_IMPL:
      cycle_count += 3;
      PHP();
      break;
    case Op::ORA_IMMED:
      cycle_count += 2;
      ref = Immediate();
      ORA(*ref);
      break;
    case Op::ASL_A:
      cycle_count += 2;
      reg.ac = ASL(reg.ac);
      break;
    case Op::ORA_ABS:
      cycle_count += 4;
      ref = Absolute();
      ORA(*ref);
      break;
    case Op::ASL_ABS:
      cycle_count += 6;
      ref = Absolute();
      *ref = ASL(*ref);
      break;

    // HI-NIBBLE == 0x10
    case Op::BPL_REL:
      cycle_count += 2;
      ref = Relative();
      BPL(*ref);
      break;
    case Op::ORA_IND_Y:
      cycle_count += 5;
      ref = Indirect_Y();
      ORA(*ref);
      break;
    case Op::ORA_ZPG_X:
      cycle_count += 4;
      ref = Zeropage_X();
      ORA(*ref);
      break;

    default:
      // opcode must be unrecognized, throw exception
      throw Exception::BadOpcode(opcode);
      break;
  }

}
