//===-- include/common/CommonException.h - Common Exceptions ------* C++ *-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains common exceptions that may be raised.
///
//===----------------------------------------------------------------------===//
#ifndef COMMON_EXCEPTION_H
#define COMMON_EXCEPTION_H

#include "common/BaseException.h"

namespace Exception {

/// \class InvalidFormatException
/// \brief This is the exception to throw when encountering a file with an 
/// unexpected or invalid format.
class InvalidFormatException : public BaseException {
  public:
    InvalidFormatException() : BaseException(
        "An input file had an invalid format.") {}
    InvalidFormatException(
        std::string&& errorMessage) :
      BaseException(std::move(errorMessage)) {}
    InvalidFormatException(const InvalidFormatException& originalException) noexcept :
        BaseException(originalException) {}

    // Destructors
    ~InvalidFormatException() {}

    /// Print the name of this exception class.
    /// \returns The name of this exception class as a string.
    const std::string printClassName() const override {
      return "InvalidFormatException";
    }

};

/// \class RuntimeException
/// \brief This is the type of exception to throw for general runtime exceptions.
class RuntimeException : public BaseException {
  public:
    // Construction Methods
    RuntimeException() noexcept : 
        BaseException(
          "A runtime error occured.") {}
    RuntimeException(
        std::string&& errorMessage) :
      BaseException(std::move(errorMessage)) {}
    RuntimeException(const RuntimeException& originalException) noexcept :
        BaseException(originalException) {}

    // Destructors
    ~RuntimeException() {}

    /// Print the name of this exception class.
    /// \returns The name of this exception class as a string.
    const std::string printClassName() const override {
      return "RuntimeException";
    }

};

}

#endif // COMMON_EXCEPTION_H //
