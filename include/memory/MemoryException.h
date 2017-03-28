//===-- include/memory/MemoryException.h - Memory Exceptions ----*- C++ -*-===//
//
//                           The OsNES Project
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

/// \class ReadOnlyMemoryException
/// \brief This is the exception to throw when attempting to write to a read only
/// memory.
class ReadOnlyMemoryException : public BaseException {
  public:
    // Construction Methods
    ReadOnlyMemoryException() : BaseException(
        "Attempted write to read only memory at runtime.",
        "ReadOnlyMemoryException") {}
    ReadOnlyMemoryException(const ReadOnlyMemoryException& originalException) noexcept :
        BaseException(originalException) {}

    // Destructors
    ~ReadOnlyMemoryException() {}

};

} // namespace Exception

#endif // MEMORY_EXCEPTION_H //
