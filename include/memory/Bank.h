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
/// \tparam Wordsize Size of a memory word for the memory object.
template<class Wordsize> 
class Bank : public AbstractMemory<Wordsize> {
  public:
    /// Create a memory bank of with the given number of words, at the given
    /// base address.
    /// \param size The number of words in the memory bank.
    /// \param vaddr The base address of the memory bank.
    inline Bank(std::size_t size, Vaddr vaddr = {0x0});
    virtual ~Bank() {};

    /// Read word from \p index into the memory bank.
    /// \param index Index into the dataBank array.
    /// \returns Word at the given index.
    inline const Wordsize read(std::size_t index) const final;

    /// Get the size of this memory bank.
    /// \returns The size of this memory bank.
    inline std::size_t getSize() const;

    /// Resize the Memory::Bank object.
    /// \param size The new size of the memory bank.
    inline void resize(std::size_t size);

    /// Get the base address of this memory bank.
    /// \returns The base address of this memory bank.
    inline Vaddr getBaseAddress() const;

    /// Set the base address of this memory bank.
    /// \param vaddr The base address to give this memory bank.
    inline void setBaseAddress(const Vaddr vaddr);
  
  protected:
    /// Get a reference to the internal dataBank.
    /// \returns A reference to the internal dataBank
    inline std::vector<Wordsize>& getDataBank();

  private:
    /// The array of data comprising the memory bank
    std::vector<Wordsize> dataBank;

    /// The base virtual address of this memory bank
    Vaddr baseAddress;
};

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
void Bank<Wordsize>::resize(std::size_t size) {
  dataBank.resize(size);
}

template<class Wordsize>
Vaddr Bank<Wordsize>::getBaseAddress() const {
  return baseAddress;
}

template<class Wordsize>
void Bank<Wordsize>::setBaseAddress(const Vaddr vaddr) {
  this.baseAddress.val = vaddr.val;
}

template<class Wordsize>
std::vector<Wordsize>& Bank<Wordsize>::getDataBank() {
  return dataBank;
}

} // namespace Memory

#endif // MEMORY_BANK_H //
