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
      BaseException(std::move(errorMessage), std::move(className)) {}
    MemoryException(const MemoryException& originalException) noexcept :
        BaseException(originalException) {}

    // Destructors
    ~MemoryException() {}

};

/// \class ReadOnlyMemoryException
/// \brief This is the exception to throw when attempting to write to a read only
/// memory.
class ReadOnlyMemoryException : public MemoryException {
  public:
    // Construction Methods
    ReadOnlyMemoryException() : MemoryException(
        "Attempted write to read only memory at runtime.",
        "ReadOnlyMemoryException") {}
    ReadOnlyMemoryException(
        std::string&& errorMessage,
        std::string&& className = "ReadOnlyMemoryException") :
      MemoryException(std::move(errorMessage), std::move(className)) {}
    ReadOnlyMemoryException(const ReadOnlyMemoryException& originalException) noexcept :
        MemoryException(originalException) {}

    // Destructors
    ~ReadOnlyMemoryException() {}

};

/// \class MirroringException
/// \brief This is the exception to throw when there is an error building a mirrored
/// memory.
class MirroringException : public MemoryException {
  public:
    // Construction Methods
    MirroringException() : MemoryException(
        "There was an error building a mirrored memory.",
        "MirroringException") {}
    MirroringException(
        std::string&& errorMessage,
        std::string&& className = "MirroringException") :
      MemoryException(std::move(errorMessage), std::move(className)) {}
    MirroringException(const MirroringException& originalException) noexcept :
        MemoryException(originalException) {}

    // Destructors
    ~MirroringException() {}

};


} // namespace Exception

#endif // MEMORY_EXCEPTION_H //
