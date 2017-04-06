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
        "A data structure error occured at runtime.",
        "StructureException") {}
    StructureException(
        std::string&& errorMessage,
        std::string&& className = "StructureException") :
      BaseException(std::move(errorMessage), std::move(className)) {}
    StructureException(const StructureException& originalException) noexcept :
        BaseException(originalException) {}

    // Destructors
    ~StructureException() {}

};

/// \class KeyErrorException
/// \brief This is the type of exception to throw when an access key is missing.
class KeyErrorException : public StructureException {
  public:
    // Construction Methods
    KeyErrorException() noexcept : 
        StructureException(
          "An unknown key was used in a data structure.",
          "KeyErrorException") {}
    KeyErrorException(
        std::string&& errorMessage) :
      StructureException(std::move(errorMessage), "KeyErrorException") {}
    KeyErrorException(const KeyErrorException& originalException) noexcept :
        StructureException(originalException) {}

    // Destructors
    ~KeyErrorException() {}

};


}

#endif // STRUCTURE_EXCEPTION_H //
