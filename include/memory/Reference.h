//===-- include/memory/Reference.h - Reference Class ------------*- C++ -*-===//
//
//                           The OsNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//  
//===----------------------------------------------------------------------===//
///
/// \file
/// This file defines the Memory::Reference class.
///
//===----------------------------------------------------------------------===//
#ifndef MEMORY_REFERENCE_H
#define MEMORY_REFERENCE_H

#include "common/CommonTypes.h"
#include "memory/Bank.h"

namespace Memory {

/// Reference - This creates references to the underlying words in objects of
/// the type Memory::Bank. These references should be use to access data in
/// other subsystems.
template<class Wordsize>
class Reference {
  public:
    // Constructors and Destructor
    inline Reference();
    inline Reference(std::shared_ptr<Bank<Wordsize>> dataBank, std::size_t index);
    inline Reference(const Reference<Wordsize>& reference);
    virtual ~Reference() {};

    /// Write to referenced location
    inline void write(Wordsize data);

    /// Read from references location
    inline const Wordsize read() const;

    /// Increment the reference index before return.
    /// \return Reference to this for chaining.
    inline const Reference& operator++();

    /// Decrement the reference index before return.
    /// \return Reference to this for chaining.
    inline const Reference& operator--();

  private:
    /// Index into the underlying memory bank
    std::size_t index;

    /// The memory bank pointed to by the reference
    std::shared_ptr<Bank<Wordsize>> dataBank;
};

// default constructor
template <class Wordsize>
Reference<Wordsize>::Reference() {
  this->dataBank = nullptr;
  this->index = 0;
}

// normal constructor
template <class Wordsize>
Reference<Wordsize>::Reference(
    std::shared_ptr<Memory::Bank<Wordsize>> dataBank,
    std::size_t index) {
  this->dataBank = dataBank;
  this->index = index;
}

// copy constructor
template <class Wordsize>
Reference<Wordsize>::Reference(const Reference<Wordsize>& reference) {
  this->dataBank = reference.dataBank;
  this->index = reference.index;
}

template<class Wordsize>
void Reference<Wordsize>::write(Wordsize data) {
  // write data to dataBank at index
  dataBank->write(index, data);
}

template<class Wordsize>
const Wordsize Reference<Wordsize>::read() const {
  // read the word from dataBank at index
  return dataBank->read(index);
}

template<class Wordsize>
const Reference<Wordsize>& Reference<Wordsize>::operator++() {
  // increment the index, and return the this object
  this->index += 1;
  return *this;
}

template<class Wordsize>
const Reference<Wordsize>& Reference<Wordsize>::operator--() {
  // decrement the index, and return the this object
  this->index -= 1;
  return *this;
}

} // namespace Memory

#endif // MEMORY_REFERENCE_H //
