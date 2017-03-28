//===-- include/memory/Bank.h - Memory Bank Class -----------*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//  
//===----------------------------------------------------------------------===//
///
/// \file
/// This file defines the Memory::Bank class, which serves as base class for all
/// memory bank objects.
///
//===----------------------------------------------------------------------===//
#ifndef MEMORY_BANK_H
#define MEMORY_BANK_H

#include <vector>

#include "common/CommonTypes.h"
#include "memory/AbstractMemory.h"

namespace Memory {

/// \class Bank
/// \brief This class serves as the abstract base class for linear memory banks.
/// This class provides some common implementation details, but leaves the write
/// method unimplemented, as this tends to be implementation specific.
template<class Wordsize> 
class Bank : public AbstractMemory<Wordsize> {
  public:
    // Constructors and Destructors
    inline Bank(std::size_t size);
    inline Bank(std::size_t size, Vaddr vaddr);
    virtual ~Bank() {};

    /// Read word from \p index into the memory bank.
    /// \param index Index into the dataBank array.
    /// \returns Word at the given index.
    inline const Wordsize read(std::size_t index) const final;

    /// Get the size of this memory bank.
    /// \returns The size of this memory bank.
    inline std::size_t getSize() const;

    /// Get the base address of this memory bank.
    /// \returns The base address of this memory bank.
    inline Vaddr getBaseAddress() const;

  protected:
    /// The array of data comprising the memory bank
    std::vector<Wordsize> dataBank;

    /// The base virtual address of this memory bank
    Vaddr baseAddress;
};

template<class Wordsize>
Bank<Wordsize>::Bank(std::size_t size) {
  // Initialize the memory bank
  this->dataBank.resize(size);
  this->baseAddress.val = 0;
}

template<class Wordsize>
Bank<Wordsize>::Bank(std::size_t size, Vaddr vaddr) {
  // Initialize the memory bank
  this->dataBank.resize(size);
  this->baseAddress.val = vaddr.val;
}

template<class Wordsize>
const Wordsize Bank<Wordsize>::read(std::size_t index) const {
  // read the data from the given index
  return dataBank[index];
}

template<class Wordsize>
std::size_t Bank<Wordsize>::getSize() const {
  return dataBank.size();
}

template<class Wordsize>
Vaddr Bank<Wordsize>::getBaseAddress() const {
  return baseAddress;
}

} // namespace Memory

#endif // MEMORY_BANK_H //
