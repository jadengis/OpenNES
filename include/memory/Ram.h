//===-- include/memory/Ram.h - Ram Class ------------------------*- C++ -*-===//
//
//                           The OsNES Project
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

#include "Common.h"
#include "Exception.h"
#include "memory/Bank.h"

namespace Memory {

  template<class Wordsize> 
  class Ram : public Bank<Wordsize> {
    public:
      Ram(std::size_t size) : Bank(size) {};
      virtual ~Ram() {};
      inline void Write(std::size_t index, Wordsize data) override;
  };
}

template<class Wordsize>
void Memory::Ram::Write(std::size_t index, Wordsize data) {
  // write the data at the given index
  data_bank[index] = data;
}

#endif // MEMORY_RAM_H //:~
