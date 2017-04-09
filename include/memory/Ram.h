//===-- include/memory/Ram.h - Ram Class ------------------------*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//  
//===----------------------------------------------------------------------===//
///
/// \file
/// This file defines the Memory::Ram class.
///
//===----------------------------------------------------------------------===//
#ifndef MEMORY_RAM_H
#define MEMORY_RAM_H

#include "common/CommonTypes.h"
#include "memory/MemoryException.h"
#include "memory/Bank.h"

namespace Memory {

/// \class Ram
/// \brief This class act as a random access memory for an architecture with the
/// given wordsize.
/// \tparam Wordsize Size of a memory word for the memory object.
template<class Wordsize> 
class Ram : public Bank<Wordsize> {
  public:
    /// Create a Ram of with the given number of words, at the given
    /// base address.
    /// \param size The number of words in the memory bank.
    /// \param vaddr The base address of the memory bank.
    Ram(std::size_t size, Vaddr vaddr = {0x0}) : Bank<Wordsize>(size, vaddr) {};

    // Destructor
    virtual ~Ram() {};

    /// Write the data to the random access memory at the given index
    /// \param index Memory location to write to
    /// \param data Data to write at the given location
    inline void write(std::size_t index, Wordsize data) override;
};

template<class Wordsize>
void Ram<Wordsize>::write(std::size_t index, Wordsize data) {
  // write the data at the given index
  this->getDataBank()[index] = data;
}

} // namespace Memory

#endif // MEMORY_RAM_H //:~
