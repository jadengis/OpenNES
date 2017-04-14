//===-- include/common/BaseException.h - Base Exception ---------*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the Base exception class.
///
//===----------------------------------------------------------------------===//
#ifndef BASE_EXCEPTION_H
#define BASE_EXCEPTION_H

#include <execinfo.h>
#include <string.h>
#include <iostream>
#include <sstream>

#include "common/CommonTypes.h"

namespace Exception {

/// \class BaseException
/// \brief Base exception class for OpenNES. This class provides the basic
/// functionality for exceptions used in the project. Inheritors should be
/// simples extensions of this class, providing only the convenience of a
/// more specific type (and perhaps an informative message).
class BaseException {
  public:
    // Construction Methods
    /// Default exception constructor. Bootstrap the exception.
    BaseException() noexcept;
    BaseException(std::string&& errorMessage,
        std::string&& className = "BaseException") noexcept;
    BaseException(const BaseException&) noexcept;
    virtual BaseException& operator= (const BaseException&) noexcept;

    // Destructor
    virtual ~BaseException() {}

    /// Return the name of the current exception class. Must be overwritten
    /// in inherited exception classes.
    /// \return Name of the current exception class.
    virtual const std::string printClassName() const;

    /// Return the error message from the event that caused this exception.
    /// \return The internal error message.
    virtual const std::string& printErrorMessage() const;

    /// Return the stack trace acquired when the exception was created.
    /// \return The stack trace from throw time.
    virtual const std::string& printStackTrace() const final;
    

  private:
    /// Method for acquiring a stack trace,and storing it in this object.
    /// \param skip Number of frames to skip during formatting. defaults to 1.
    void obtainStackTrace(uint64 skip = 1);

    /// Name of the exception class
    const std::string className;
    /// Error message from throw time
    std::string errorMessage;
    /// The stack trace at the time of calling
    std::string stackTrace;
};

}

#endif // BASE_EXCEPTION_H //
