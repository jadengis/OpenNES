//===-- include/memory/Bank.h - Memory Bank Base Class -----------*- C++ -*-===//
//
//                           The OsNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//  
//===----------------------------------------------------------------------===//
///
/// \file
/// This is the base class for all memory bank objects, providing the common
/// interface that all memory banks must implement
///
//===----------------------------------------------------------------------===//
#ifndef MEMORY_BANK_H
#define MEMORY_BANK_H
#include "Common.h"
namespace Memory {
  template<class Wordsize> class Bank {
    public:
      Bank(std::size_t size) {
        // Store the memory bank size
        this->size = size;
        // Initialize the memory bank
        data_bank = std::make_unique<Wordsize[]>(size);
      };
      virtual ~Bank() {};
      virtual inline void Write(std::size_t index, Wordsize data) = 0;
      virtual inline Wordsize Read(std::size_t index) = 0;
    protected:
      std::size_t size;
      std::unique_ptr<Wordsize[]> data_bank;
  };
}

template<class Wordsize>
void Memory::Bank::Write(std::size_t index, Wordsize data) {
  // write the data at the given index
  data_bank[index] = data;
}

template<class Wordsize>
Wordsize Memory::Bank::Read(std::size_t index) {
  // read the data from the given index
  return data_bank[index];
}
#endif // MEMORY_BANK_H //:~
