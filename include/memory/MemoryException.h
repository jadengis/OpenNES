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
        "A Memory error occured at runtime.",
        "MemoryException") {}
    MemoryException(
        std::string&& errorMessage,
        std::string&& className = "MemoryException") :
      BaseException(errorMessage, className) {}
    MemoryException(const MemoryException& originalException) noexcept :
        BaseException(originalException) {}

    // Destructors
    ~MemoryException() {}

};

/// \class ReadOnlyMemoryException
/// \brief This is the exception to throw when attempting to write to a read only
/// memory.
class ReadOnlyMemoryException : public BaseException {
  public:
    // Construction Methods
    ReadOnlyMemoryException() : MemoryException(
        "Attempted write to read only memory at runtime.",
        "ReadOnlyMemoryException") {}
    ReadOnlyMemoryException(
        std::string&& errorMessage,
        std::string&& className = "ReadOnlyMemoryException") :
      MemoryException(errorMessage, className) {}
    ReadOnlyMemoryException(const ReadOnlyMemoryException& originalException) noexcept :
        MemoryException(originalException) {}

    // Destructors
    ~ReadOnlyMemoryException() {}

};

} // namespace Exception

#endif // MEMORY_EXCEPTION_H //
