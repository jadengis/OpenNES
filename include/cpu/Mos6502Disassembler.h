//===-- include/cpu/Mos6502Disassembler.h - Mos6502 Disassembler *- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the Mos6502 Disassambler.
///
//===----------------------------------------------------------------------===//
#ifndef MOS_6502_DISASSEMBLER_H
#define MOS_6502_DISASSEMBLER_H

#include "common/CommonTypes.h"
#include "cpu/Mos6502Instruction.h"
#include "memory/Reference.h"

namespace Cpu {

/// \class Mos6502Disassembler
/// \brief This class is a disassembler for the Mos6502 architecture.
struct Mos6502Disassembler {
  public:
    /// Look into the given opcode and return a formatted Mos6502Instruction.
    /// This function reads from the currently stored readPosition.
    /// \return Disassembled instruction.
    inline Mos6502Instruction disassembleInstruction();

    /// Look into the given opcode and return a formatted Mos6502Instruction.
    /// This function sets the read position before executing.
    /// \param readPosition Memory location to read from.
    /// \return Disassembled instruction.
    inline Mos6502Instruction disassembleInstruction(Memory::Reference<byte> readPosition);

    /// Look into the given opcode and return a formatted Mos6502Instruction.
    /// This instruction will pull data starting from the current read position
    /// \param opcode The opcode of the instruction to disassemble.
    Mos6502Instruction disassembleInstruction(byte opcode);

    /// Set the read position of te disassembler.
    /// \param readPosition Value of read position to set. 
    inline void setReadPosition(Memory::Reference<byte> readPosition);
  private:
    /// This function builds and forwards a Mos6502Instruction given a set of
    /// input data.
    /// \param opcode Opcode of the instruction to return.
    /// \param name Name of the instruction.
    /// \param addr Addressing mode of the given instruction.
    /// \param cycles Number of cycles taken to execute.
    /// \param type The InstructionType of the instruction.
    /// \return The formatted Mos6502 Instruction.
    Mos6502Instruction initInstruction(
        byte opcode,
        std::string&& name,
        std::string&& addr,
        byte cycles,
        Mos6502Instruction::InstructionType type);

    /// Memory location to start reading bytes from.
    Memory::Reference<byte> readPosition;
};

// Inlinable definitions
Mos6502Instruction Mos6502Disassembler::disassembleInstruction() {
  return disassembleInstruction(readPosition.read());
}

Mos6502Instruction Mos6502Disassembler::disassembleInstruction(
    Memory::Reference<byte> readPosition) {
  setReadPosition(readPosition);
  return disassembleInstruction(readPosition.read());
}

void Mos6502Disassembler::setReadPosition(Memory::Reference<byte> readPosition) {
  this->readPosition = readPosition;
}

} // namespace Cpu

#endif // MOS_6502_DISASSEMBLER_H //
