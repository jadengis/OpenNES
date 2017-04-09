//===-- include/memory/MirroredRam.h - Mirrored Ram Class -------*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//  
//===----------------------------------------------------------------------===//
///
/// \file
/// This file defines the Memory::MirroredRam class.
///
//===----------------------------------------------------------------------===//
#ifndef MEMORY_MIRRORED_RAM_H
#define MEMORY_MIRRORED_RAM_H

#include "common/CommonTypes.h"
#include "memory/MemoryException.h"
#include "memory/Bank.h"
#include "memory/Ram.h"

namespace Memory {

/// \class MirroredRam
/// \brief This class act as a random access memory for an architecture with the
/// given wordsize, that is mirrored with some given regularity. It is required
/// that the number of mirrors divide the size of the Ram and that it be a
/// power of 2, for performance reasons.
/// \tparam Wordsize Size of a memory word for the memory object.
template<class Wordsize> 
class MirroredRam : public Ram<Wordsize> {
  public:
    /// Create a mirrored Ram of with the given number of words, at the given
    /// base address, with the given regularity. It is required that the regularity
    /// of the Ram be a power of 2, and divide the 
    /// \param size The number of words in the memory bank.
    /// \param vaddr The base address of the memory bank.
    /// \throws MirroringException If memory is built with incompatible parameters.
    MirroredRam(std::size_t size, std::size_t mirrors, Vaddr vaddr = {0x0}); 

    /// Nothing is needed to destory a MirroredRam
    virtual ~MirroredRam() {};

    /// Write the data to the random access memory at the given index and
    /// all mirrors of that index.
    /// \param index Memory location to write to.
    /// \param data Data to write at the given location and all mirrors.
    void write(std::size_t index, Wordsize data) override;

  private:
    /// The number of mirrors in the mirrored ram.
    std::size_t mirrors;
    /// The number of words in a mirror.
    std::size_t mirrorSize;
    /// True if mirroSize is a power of 2, used for optimization
    bool mirrorSizeIsPow2;
};

template<class Wordsize>
MirroredRam<Wordsize>::MirroredRam(
    std::size_t size,
    std::size_t mirrors,
    Vaddr vaddr) : Ram<Wordsize>(size, vaddr) {
  // Ensure that the number of mirrors is a power of 2 and divides size.  
  if(((mirrors & (mirrors - 1)) != 0) || ((size & (mirrors - 1)) != 0)) {
    // The ram violates conditions, so throw a mirorring error.
    throw Exception::MirroringException("Number of mirrors " + 
        std::to_string(mirrors) + " violates the mirroring constraints.");
  }
  // This number of mirrors is acceptable.
  this->mirrors = mirrors;
  this->mirrorSize = size / mirrors; // perhaps optimize
  this->mirrorSizeIsPow2 = !(mirrorSize & (mirrorSize - 1));
}

template<class Wordsize>
void MirroredRam<Wordsize>::write(std::size_t index, Wordsize data) {
  // Compute the base index of the input index.
  // If mirror size is a power of 2, use an optimizaed modulo operation.
  auto baseIndex = mirrorSizeIsPow2 ? index & (mirrorSize - 1) : index % mirrorSize;
  // write the data in all mirrors.
  for(std::size_t i = 0; i < mirrors; i++) {
    this->getDataBank()[i*mirrorSize + baseIndex] = data;
  }
}

} // namespace Memory

#endif // MEMORY_MIRRORED_RAM_H //:~
