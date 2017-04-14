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
    Rom(std::size_t size = 0, Vaddr vaddr = {0x0}) : Bank<Wordsize>(size, vaddr) {};

    /// Destroy a Rom
    virtual ~Rom() {};

    /// Throw an error when trying to write to a ROM.
    /// We cannot write to a Rom, so throw a ReadOnlyMemoryException when
    /// this method is called.
    /// \throws ReadOnlyMemoryException This is guaranteed.
    inline void write(std::size_t index, Wordsize data) override;

    /// Load data into this Rom object. This can only be done once.
    /// \tparam InputIterator Type of input iterator to use.
    /// \param start Data import start position.
    /// \param end Data import end position.
    /// \throws Exception::ReadOnlyMemoryException if Rom has been loaded already.
    template<class InputIterator>
    inline void load(InputIterator start, InputIterator end);

  private:
    /// Roms may only be loaded once. This value is true if this rom has been
    /// loaded.
    bool isLoaded = false;
};

template <class Wordsize>
void Rom<Wordsize>::write(std::size_t index, Wordsize data) {
  // Cannot write to a Rom, so throw a ReadOnlyMemory exception
  throw Exception::ReadOnlyMemoryException();
}

template<class Wordsize> 
template<class InputIterator>
void Rom<Wordsize>::load(InputIterator start, InputIterator end) {
  // If this Rom has been loaded, throw a ROM exception
  if(isLoaded) {
    throw Exception::ReadOnlyMemoryException("Loaded ROM is trying to be overwritten");
  }
  // replace the internal dataBank with a new one containing the loaded data.
  this->getDataBank() = std::vector<byte>(start, end);
  isLoaded = true;
}

} // namespace Memory

#endif // MEMORY_ROM_H //:~
