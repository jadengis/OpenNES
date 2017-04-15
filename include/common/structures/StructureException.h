//===-- include/common/StructureException.h - Structure Exceptions-* C++ *-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains exceptions to be raised by custom data structures.
///
//===----------------------------------------------------------------------===//
#ifndef STRUCTURE_EXCEPTION_H
#define STRUCTURE_EXCEPTION_H

#include "common/BaseException.h"

namespace Exception {

/// \class StructureException
/// \brief This is the base exceptions class for all data structure exceptions.
class StructureException : public BaseException {
  public:
    StructureException() : BaseException(
        "A data structure error occured at runtime.") {}
    StructureException(
        std::string&& errorMessage) :
      BaseException(std::move(errorMessage)) {}
    StructureException(const StructureException& originalException) noexcept :
        BaseException(originalException) {}

    // Destructors
    ~StructureException() {}

    /// Print the name of this exception class.
    /// \returns The name of this exception class as a string.
    const std::string printClassName() const override {
      return "StructureException";
    }

};

/// \class KeyErrorException
/// \brief This is the type of exception to throw when an access key is missing.
class KeyErrorException : public StructureException {
  public:
    // Construction Methods
    KeyErrorException() noexcept : 
        StructureException(
          "An unknown key was used in a data structure.") {}
    KeyErrorException(
        std::string&& errorMessage) :
      StructureException(std::move(errorMessage)) {}
    KeyErrorException(const KeyErrorException& originalException) noexcept :
        StructureException(originalException) {}

    // Destructors
    ~KeyErrorException() {}

    /// Print the name of this exception class.
    /// \returns The name of this exception class as a string.
    const std::string printClassName() const override {
      return "KeyErrorException";
    }

};

}

#endif // STRUCTURE_EXCEPTION_H //
