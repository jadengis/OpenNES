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

#include "Common.h"

namespace Memory {

  template<class Wordsize> 
  class Bank {
    public:
      // Constructors and Destructors
      inline Bank(std::size_t size);
      virtual ~Bank() {};

      /// Write word at index
      virtual inline void Write(std::size_t index, Wordsize data) = 0;

      /// Read word from index
      virtual inline const Wordsize Read(std::size_t index) const final;

    protected:
      /// Size of the underlying array 
      std::size_t size;
      /// The array of data comprising the memory bank
      std::unique_ptr<Wordsize[]> data_bank;
  };

}

template<class Wordsize>
Memory::Bank::Bank(std::size_t size) {
  // Store the memory bank size
  this->size = size;
  // Initialize the memory bank
  data_bank = std::make_unique<Wordsize[]>(size);
}

template<class Wordsize>
const Wordsize Memory::Bank::Read(std::size_t index) const {
  // read the data from the given index
  return data_bank[index];
}

#endif // MEMORY_BANK_H //
