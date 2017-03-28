//===-- include/cpu/CpuException.h - Cpu Exceptions ----------------*- C++ -*-===//
//
//                           The OsNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declarations of all the Cpu exception classes.
///
//===----------------------------------------------------------------------===//
#ifndef CPU_EXCEPTION_H
#define CPU_EXCEPTION_H

#include "common/BaseException.h"

namespace Exception {

/// \class InvalidOpcodeException
/// \brief The exception type to throw when encountering an undefined opcode.
class InvalidOpcodeException : public BaseException {
  public:
    // Construction Methods
    InvalidOpcodeException(byte opcode) noexcept : 
        BaseException(
          "The following invalid opcode was encountered at runtime: " +
          std::to_string(static_cast<uint64>(opcode)),
          "InvalidOpcodeException") {}
    InvalidOpcodeException(const InvalidOpcodeException& originalException) noexcept :
        BaseException(originalException) {}

    // Destructors
    ~InvalidOpcodeException() {}

};

} // namespace Exception

#endif // CPU_EXCEPTION_H //
