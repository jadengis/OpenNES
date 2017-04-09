//===-- include/memory/Rom.h - Rom Class ------------------------*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//  
//===----------------------------------------------------------------------===//
///
/// \file
/// This file defines the Memory::Rom class.
///
//===----------------------------------------------------------------------===//
#ifndef MEMORY_ROM_H
#define MEMORY_ROM_H

#include "common/CommonTypes.h"
#include "memory/MemoryException.h"
#include "memory/Bank.h"

namespace Memory {

/// \class Rom
/// \brief This class acts as a read only memory for an architecture of the given
/// wordsize.
/// \tparam Wordsize Size of a memory word for the memory object.
template<class Wordsize> 
class Rom : public Bank<Wordsize> {
  public:
    /// Create a Rom of with the given number of words, at the given
    /// base address.
    /// \param size The number of words in the memory bank.
    /// \param vaddr The base address of the memory bank.
    Rom(std::size_t size, Vaddr vaddr = {0x0}) : Bank<Wordsize>(size, vaddr) {};

    // Destructor
    virtual ~Rom() {};

    /// Throw an error when trying to write to a ROM.
    /// We cannot write to a Rom, so throw a ReadOnlyMemoryException when
    /// this method is called.
    /// \throws ReadOnlyMemoryException This is guaranteed.
    inline void write(std::size_t index, Wordsize data) override;
    virtual void load() = delete;
};

template <class Wordsize>
void Rom<Wordsize>::write(std::size_t index, Wordsize data) {
  // Cannot write to a Rom, so throw a ReadOnlyMemory exception
  throw Exception::ReadOnlyMemoryException();
}

} // namespace Memory

#endif // MEMORY_ROM_H //:~
