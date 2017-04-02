//===-- include/cpu/CpuException.h - Cpu Exceptions ----------------*- C++ -*-===//
//
//                           The OpenNES Project
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

/// \class CpuException
/// \brief This is the base exceptions class for all cpu exceptions.
class CpuException : public BaseException {
  public:
    CpuException() : BaseException(
        "A Cpu error occured at runtime.",
        "CpuException") {}
    CpuException(
        std::string&& errorMessage,
        std::string&& className = "CpuException") :
      BaseException(errorMessage, className) {}
    CpuException(const CpuException& originalException) noexcept :
        BaseException(originalException) {}

    // Destructors
    ~CpuException() {}

};

/// \class InvalidOpcodeException
/// \brief This is the type of exception to throw when encountering an undefined opcode.
class InvalidOpcodeException : public CpuException {
  public:
    // Construction Methods
    InvalidOpcodeException(byte opcode) noexcept : 
        CpuException(
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
