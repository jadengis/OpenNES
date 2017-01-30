//===-- include/memory/Rom.h - Rom Class ------------------------*- C++ -*-===//
//
//                           The OsNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//  
//===----------------------------------------------------------------------===//
///
/// \file
/// This is the read-only memory class. This class of memory bank cannot be
/// written to, and must be loaded.
///
//===----------------------------------------------------------------------===//
#ifndef MEMORY_ROM_H
#define MEMORY_ROM_H
#include "Common.h"
#include "Exception.h"
#include "memory/Bank.h"
namespace Memory {
  template<class wordsize> class Rom : public Bank<wordsize> {
    public:
      Rom(std::size_t size) : Bank(size) {};
      virtual ~Rom() {};
      virtual inline void Write(std::size_t index, wordsize data) override;
      virtual inline wordsize Read(std::size_t index) override;
      virtual void Load() delete;
  };
}

void Memory::Rom::Write(std::size_t index, wordsize data) {
  // Cannot write to a Rom, so throw a ReadOnlyMemory exception
  throw Exception::ReadOnlyMemory();
}
#endif // MEMORY_ROM_H //:~
