//===-- include/memory/MemoryException.h - Memory Exceptions ----*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declarations of all the Memory exception classes.
///
//===----------------------------------------------------------------------===//
#ifndef MEMORY_EXCEPTION_H
#define MEMORY_EXCEPTION_H

#include "common/BaseException.h"

namespace Exception {

/// \class MemoryException
/// \brief This the the base exception type for all memory related exceptions.
class MemoryException : public BaseException {
  public:
    MemoryException() : BaseException(
        "A Memory error occured at runtime.") {}
    MemoryException(
        std::string&& errorMessage) :
      BaseException(std::move(errorMessage)) {}
    MemoryException(const MemoryException& originalException) noexcept :
        BaseException(originalException) {}

    // Destructors
    ~MemoryException() {}

    /// Print the name of this exception class.
    /// \returns The name of this exception class as a string.
    const std::string printClassName() const override {
      return "MemoryException";
    }

};

/// \class ReadOnlyMemoryException
/// \brief This is the exception to throw when attempting to write to a read only
/// memory.
class ReadOnlyMemoryException : public MemoryException {
  public:
    // Construction Methods
    ReadOnlyMemoryException() : MemoryException(
        "Attempted write to read only memory at runtime.") {}
    ReadOnlyMemoryException(
        std::string&& errorMessage) :
      MemoryException(std::move(errorMessage)) {}
    ReadOnlyMemoryException(const ReadOnlyMemoryException& originalException) noexcept :
        MemoryException(originalException) {}

    // Destructors
    ~ReadOnlyMemoryException() {}

    /// Print the name of this exception class.
    /// \returns The name of this exception class as a string.
    const std::string printClassName() const override {
      return "ReadOnlyMemoryException";
    }

};

/// \class MirroringException
/// \brief This is the exception to throw when there is an error building a mirrored
/// memory.
class MirroringException : public MemoryException {
  public:
    // Construction Methods
    MirroringException() : MemoryException(
        "There was an error building a mirrored memory.") {}
    MirroringException(
        std::string&& errorMessage) :
      MemoryException(std::move(errorMessage)) {}
    MirroringException(const MirroringException& originalException) noexcept :
        MemoryException(originalException) {}

    // Destructors
    ~MirroringException() {}

    /// Print the name of this exception class.
    /// \returns The name of this exception class as a string.
    const std::string printClassName() const override {
      return "MirroringException";
    }

};

} // namespace Exception

#endif // MEMORY_EXCEPTION_H //
