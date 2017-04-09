//===-- include/memory/AbstactMemory.h - Abstact Memory ---------*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//  
//===----------------------------------------------------------------------===//
///
/// \file
/// This file defines the Memory::AbstractMemory abstract class, which serves 
/// as base class for all memory objects.
///
//===----------------------------------------------------------------------===//
#ifndef ABSTRACT_MEMORY_H
#define ABSTRACT_MEMORY_H

namespace Memory {

/// \class AbstractMemory
/// \brief This class represents an abstract piece of memory.
/// \tparam Wordsize Size of a memory word for the memory object.
template<class Wordsize>
class AbstractMemory {
  public:
    virtual ~AbstractMemory() {}

    /// Write data word to the index in memory.
    /// \param index Index into the memory array.
    /// \param data Word to store at the index.
    virtual void write(std::size_t index, Wordsize data) = 0;

    /// Read data word from the index into memory.
    /// \param index Index into the memory array.
    /// \returns Word at the given index.
    virtual const Wordsize read(std::size_t index) const = 0;

};

} // namespace Memory

#endif // ABSTRACT_MEMORY_H //
