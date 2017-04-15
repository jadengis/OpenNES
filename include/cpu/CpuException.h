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
        "A Cpu error occured at runtime.") {}
    CpuException(std::string&& errorMessage) 
      : BaseException(std::move(errorMessage)) {}
    CpuException(const CpuException& originalException) noexcept :
        BaseException(originalException) {}

    // Destructors
    ~CpuException() {}

    /// Print the name of this exception class.
    /// \returns The name of this exception class as a string.
    const std::string printClassName() const override {
      return "CpuException";
    }

};

/// \class InvalidOpcodeException
/// \brief This is the type of exception to throw when encountering an undefined opcode.
class InvalidOpcodeException : public CpuException {
  public:
    // Construction Methods
    /// Build an InvalidOpcodeException.
    /// \param opcode The opcode that was determined invalid.
    InvalidOpcodeException(byte opcode) noexcept : 
        CpuException(
          "The following invalid opcode was encountered at runtime: " +
          std::to_string(static_cast<uint64>(opcode))) {}
    InvalidOpcodeException(const InvalidOpcodeException& originalException) noexcept :
        CpuException(originalException) {}

    // Destructors
    ~InvalidOpcodeException() {}

    /// Print the name of this exception class.
    /// \returns The name of this exception class as a string.
    const std::string printClassName() const override {
      return "InvalidOpcodeException";
    }

};

} // namespace Exception

#endif // CPU_EXCEPTION_H //
