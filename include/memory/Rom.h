//===-- include/memory/Rom.h - Rom Class ------------------------*- C++ -*-===//
//
//                           The OsNES Project
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

#include "Common.h"
#include "Exception.h"
#include "memory/Bank.h"

namespace Memory {

  template<class Wordsize> 
  class Rom : public Bank<Wordsize> {
    public:
      Rom(std::size_t size) : Bank(size) {};
      virtual ~Rom() {};
      inline void Write(std::size_t index, Wordsize data) override;
      virtual void Load() delete;
  };
}

void Memory::Rom::Write(std::size_t index, Wordsize data) {
  // Cannot write to a Rom, so throw a ReadOnlyMemory exception
  throw Exception::ReadOnlyMemory();
}

#endif // MEMORY_ROM_H //:~
