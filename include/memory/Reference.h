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

#include "Common.h"
#include "memory/Bank.h"

namespace Memory {

  /// Reference - This creates references to the underlying words in objects of
  /// the type Memory::Bank. These references should be use to access data in
  /// other subsystems.
  template<class Wordsize>
  class Reference {
    public:
      // Constructor and Destructor
      inline Reference(std::shared_ptr< Bank<Wordsize> > data_bank, std::size_t index);
      virtual ~Reference() {};

      /// Write to referenced location
      inline void Write(Wordsize data);

      /// Read from references location
      inline const Wordsize Read() const;

    private:
      /// Index into the underlying memory bank
      std::size_t index;

      /// The memory bank pointed to by the reference
      std::shared_ptr<Bank> data_bank;
  };

}

template <class Wordsize>
Memory::Reference::Reference(std::shared_ptr<Bank> data_bank, std::size_t index) {
  this->data_bank = data_bank;
  this->index = index;
}

template<class Wordsize>
void Memory::Reference::Write(Wordsize data) {
  data_bank->Write(index, data);
}

template<class Wordsize>
const Wordsize Memory::Reference::Read() const {
  return data_bank->Read(index);
}

#endif // MEMORY_REFERENCE_H //
