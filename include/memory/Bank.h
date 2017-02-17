//===-- include/memory/Bank.h - Memory Bank Class -----------*- C++ -*-===//
//
//                           The OsNES Project
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

#include "common/CommonTypes.h"

namespace Memory {

template<class Wordsize> 
class Bank {
  public:
    // Constructors and Destructors
    inline Bank(std::size_t size);
    virtual ~Bank() {};

    /// Write word \p data at \p index
    /// \param index Index into the dataBank array
    /// \param data Word to store at \p index
    virtual void write(std::size_t index, Wordsize data) = 0;

    /// Read word from \p index
    /// \param index Index into the dataBank array
    /// \returns word at the given index
    virtual inline const Wordsize read(std::size_t index) const final;

    /// Get the size of the memory
    /// \returns the size of the memory
    inline std::size_t getSize() const;

  protected:
    /// Size of the underlying array 
    std::size_t size;

    /// The array of data comprising the memory bank
    std::unique_ptr<Wordsize[]> dataBank;
};

template<class Wordsize>
Bank<Wordsize>::Bank(std::size_t size) {
  // Store the memory bank size
  this->size = size;
  // Initialize the memory bank
  this->dataBank = std::make_unique<Wordsize[]>(size);
}

template<class Wordsize>
const Wordsize Bank<Wordsize>::read(std::size_t index) const {
  // read the data from the given index
  return dataBank[index];
}

template<class Wordsize>
std::size_t Bank<Wordsize>::getSize() const {
  return size;
}

} // namespace Memory

#endif // MEMORY_BANK_H //
