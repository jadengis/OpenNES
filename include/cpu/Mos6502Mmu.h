//===-- include/cpu/Mos6502Mmu.h - Memory Management Unit -------*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the Mos6502Mmu class.
///
//===----------------------------------------------------------------------===//
#ifndef MOS6502_MMU_H
#define MOS6502_MMU_H

#include "common/CommonTypes.h"
#include "memory/Ram.h"
#include "memory/Rom.h"
#include "memory/Mapper.h"
#include "memory/Reference.h"

namespace Cpu {

/// \class Mos6502Mmu
/// \brief This class represents the memory management unit for the Mos6502.
/// This class is responsible for taking virtual addresses and converting
/// them into references to real hardware.
class Mos6502Mmu {
  public:
    // Constructors / Destructors
    /// Constructor for the Mos6502Mmu. This constructor requires references to both
    /// index registers of the Mos6502 and a Memory::Mapper as these are needed to
    /// provide sensible memory management for the Mos6502.
    /// \param regX A reference to a Mos6502 X-index register.
    /// \param regY A reference to a Mos6502 Y-index register.
    /// \param memMap Hardware memory map to use internally.
    Mos6502Mmu(const byte& regX, const byte& regY, const Memory::Mapper<byte>& memMap);
    ~Mos6502Mmu() {};

    // Addressing mode functions
    /// Absolute addressing mode, operand is at the address.
    /// \param vaddr The virtual address to provide a reference for.
    /// \returns Memory reference for the input address.
    Memory::Reference<byte> absolute(Vaddr vaddr);

    /// Absolute addressing X-indexed, operand is at the address incremented by X
    /// with carry.
    /// \param vaddr The virtual address to provide a reference for.
    /// \returns Memory reference for the input address.
    Memory::Reference<byte> absoluteXIndexed(Vaddr vaddr);

    /// Absolute addressing Y-indexed, operand is at the address incremented by Y
    /// with carry.
    /// \param vaddr The virtual address to provide a reference for.
    /// \returns Memory reference for the input address.
    Memory::Reference<byte> absoluteYIndexed(Vaddr vaddr);

    /// Indirect addressing, operand is at the effective address; effective address 
    /// is the value at the given address.
    /// \param vaddr The virtual address to provide a reference for.
    /// \returns Memory reference for the input address.
    Memory::Reference<byte> indirect(Vaddr vaddr);

    /// X-indexed indirect addressing, operand is effective zeropage address; 
    /// effective address is byte (BB) incremented by X without carry.
    /// \param vaddr The virtual address to provide a reference for.
    /// \returns Memory reference for the input address.
    Memory::Reference<byte> xIndexedIndirect(Vaddr vaddr);

    /// Indirect addressing Y-indexed, operand is effective address incremented by
    /// Y with carry; effective address is word at zeropage address.
    /// \param vaddr The virtual address to provide a reference for.
    /// \returns Memory reference for the input address.
    Memory::Reference<byte> indirectYIndexed(Vaddr vaddr);

    /// Zeropage addressing, operand is at address; address hibyte is 0.
    /// \param vaddr The virtual address to provide a reference for.
    /// \returns Memory reference for the input address.
    Memory::Reference<byte> zeropage(Vaddr vaddr);

    /// Zeropage addressing X-indexed, operand is address incremented by X;
    /// address hibyte = zero ($00xx); no page transition.
    /// \param vaddr The virtual address to provide a reference for.
    /// \returns Memory reference for the input address.
    Memory::Reference<byte> zeropageXIndexed(Vaddr vaddr);

    /// Zeropage addressing Y-indexed, operand is address incremented by Y;
    /// address hibyte = zero ($00xx); no page transition.
    /// \param vaddr The virtual address to provide a reference for.
    /// \returns Memory reference for the input address.
    Memory::Reference<byte> zeropageYIndexed(Vaddr vaddr);

  private:
    /// External register value to use as X-index
    const byte& indexRegX;

    /// External register value to use as Y-index
    const byte& indexRegY;

    /// Reference to the memory mapper to use.
    const Memory::Mapper<byte>& memoryMap;

    // Private implementation functions
    inline Memory::Reference<byte> absoluteImpl(Vaddr vaddr) const;
    inline Memory::Reference<byte> zeropageImpl(Vaddr vaddr) const;
    inline Vaddr indirectImpl(Vaddr vaddr) const;

};

} // namespace Cpu

#endif // MOS6502_MMU_H //
