//===-- include/cpu/Mos6502Disassembler.h - Mos6502 Disassembler *- C++ -*-===//
//
//                           The OsNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration if the Mos6502 Disassambler.
///
//===----------------------------------------------------------------------===//
#ifndef MOS_6502_DISASSEMBLER_H
#define MOS_6502_DISASSEMBLER_H

#include "common/CommonTypes.h"
#include "cpu/Mos6502Instruction.h"
#include "memory/Reference.h"

namespace Cpu {

/// \class Mos6502Disassembler
/// \brief This class is a disassembler for the Mos6502 architecture
struct Mos6502Disassembler {
  public:
    /// Look into the given opcode and return a formatted Mos6502Instruction.
    /// This function reads from the currently stored readPosition.
    /// \return Disassembled instruction.
    Mos6502Instruction&& disassembleInstruction();

    /// Look into the given opcode and return a formatted Mos6502Instruction.
    /// This function sets the read position before executing.
    /// \param readPosition Memory location to read from.
    /// \return Disassembled instruction.
    inline Mos6502Instruction&& disassembleInstruction(Memory::Reference readPosition);

    /// Set the read position of te disassembler.
    /// \param readPosition Value of read position to set. 
    inline void setReadPosition(Memory::Reference readPosition);
  private:
    /// Memory location to start reading bytes from.
    Memory::Reference readPosition;
};

// Inlinable definitions
Mos6502Instruction&& disassembleInstruction(Memory::Reference readPosition) {
  setReadPosition(readPosition);
  return disassembleInstruction();
}

void setReadPosition(Memory::Reference readPosition) {
  this->readPosition = readPosition;
}

} // namespace Cpu

#endif // MOS_6502_DISASSEMBLER_H //:~
