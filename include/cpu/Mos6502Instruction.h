//===-- include/cpu/Mos6502Intruction.h - Mos6502 Instruction ---*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Data structure representing and instruction for the Mos6502.
///
//===----------------------------------------------------------------------===//
#ifndef MOS_6502_INSTRUCTION_H
#define MOS_6502_INSTRUCTION_H

#include <string>

#include "common/CommonTypes.h"

namespace Cpu {

/// \class Mos6502Instruction
/// \brief This class represents a machine instruction for the Mos6502 architecture.
struct Mos6502Instruction {
  /// Default constructor for Mos6502Instructions. Bootstrap an instruction object.
  Mos6502Instruction() {
      this->opcode = 0;
      this->name = "";
      this->name = "";
      this->type = InstructionType::NO_OP;
      this->operand.lo = 0;
      this->operand.hi = 0;
      this->cycles = 0;
  }

  /// Move constructor for Mos6502Instruction objects.
  /// \param inst Mos6502Instruction to move to this new object.
  Mos6502Instruction(Mos6502Instruction&& inst) {
    *this = std::move(inst);
  }

  /// Move assignment operator for Mos6502Instruction objects.
  /// \param inst Mos6502Instruction to move to this new object.
  /// \returns Referenceto this object for chaining.
  Mos6502Instruction& operator=(Mos6502Instruction&& inst) {
    if(this != &inst) {
      // move all data members
      this->opcode = std::move(inst.opcode);
      this->name = std::move(inst.name);
      this->addr = std::move(inst.addr);
      this->type = std::move(inst.type);
      this->operand.lo = std::move(inst.operand.lo);
      this->operand.hi = std::move(inst.operand.hi);
      this->cycles = std::move(inst.cycles);

      // null out old instruction
      inst.opcode = 0;
      inst.type = InstructionType::NO_OP;
      inst.operand.lo = 0;
      inst.operand.hi = 0;
      inst.cycles = 0;
    }
    return *this;
  }
    
  enum class InstructionType {
    NO_OP = 0,
    ONE_OP = 1,
    TWO_OP = 2
  };
  /// Opcode for the given instruction.
  byte opcode;
  /// Name of the instruction.
  std::string name;
  /// Addressing mode for the given instruction.
  std::string addr;
  /// Instruction type
  InstructionType type;
  struct {
    /// Low byte operand for the given instuction, if it exists.
    byte lo;
    /// High byte operand for the given instuction, if it exists.
    byte hi;
  } operand;
  /// Cycles to execute for the given instruction.
  byte cycles;
};

} // namespace Cpu

#endif // MOS_6502_INSTRUCTION_H //
