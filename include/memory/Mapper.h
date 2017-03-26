//===-- include/memory/Mapper.h - Abstact Memory Mapper ----------*- C++ -*-===//
//
//                           The OsNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//  
//===----------------------------------------------------------------------===//
///
/// \file
/// This file declares the abstract Memory::Mapper class.
///
//===----------------------------------------------------------------------===//
#ifndef MEMORY_MAPPER_H
#define MEMORY_MAPPER_H

#include <memory>

#include "common/CommonTypes.h"
#include "memory/Bank.h"

namespace Memory {

/// \class Mapper
/// \brief This class represents an abstract memory mapper, mapping addresses in
/// the virtual address space to real hardware units. This abstract class serves
/// as a contract for any class mapping addresses to hardware.
template<class Wordsize>
class Mapper {
  public:
    virtual ~Mapper() {}

    /// This function maps a virtual address to its associated hardware unit.
    /// \param address Address to find the hardware for.
    /// \returns A shared pointer to the hardware resource.
    virtual std::shared_ptr<Bank<Wordsize>> mapToHardware(Vaddr address) const = 0;

};

} // namespace Memory

#endif // MEMORY_MAPPER_H //
