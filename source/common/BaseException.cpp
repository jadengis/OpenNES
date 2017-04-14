//===-- source/common/BaseException.cpp - Base Exception - -------*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of the BaseException class.
///
//===----------------------------------------------------------------------===//

#include "common/BaseException.h"

using namespace Exception;

#define CLASS_NAME "BaseException"
#define MAX_NUM_FRAMES 128
#define MAX_BUF_LENGTH 512

// default constructor
BaseException::BaseException() noexcept : className(CLASS_NAME) {
  // Populate this exception with some default values.
  this->errorMessage = printClassName() + ": " +
    "An uncaught exception was thrown during runtime.\n";
  obtainStackTrace();
}

// main constructor, use this constructor with inherited classes to
// populate class properties.
BaseException::BaseException(
    std::string&& errorMessage, 
    std::string&& newClassName) noexcept : className(newClassName) {
  // Populate this exception with some default values.
  this->errorMessage = printClassName() + ": " + errorMessage + "\n";
  obtainStackTrace();
}

// copy constructor
BaseException::BaseException(const BaseException& originalException) noexcept :
    className(originalException.className) {
  this->errorMessage = originalException.errorMessage;
  this->stackTrace = originalException.stackTrace;
}

// assignment operator
BaseException& BaseException::operator=(const BaseException& originalException) noexcept {
  // Since className is a const field, it can't be overwritten
  this->errorMessage = originalException.errorMessage;
  this->stackTrace = originalException.stackTrace;
  return *this;
} 

// Public methods
const std::string BaseException::printClassName() const {
  return this->className;
}

const std::string& BaseException::printErrorMessage() const {
  return this->errorMessage;
}

const std::string& BaseException::printStackTrace() const {
  return this->stackTrace;
}

// Private methods
void BaseException::obtainStackTrace(uint64 skip) {
  // This implementation for this function is inspired by a Gist found 
  // here: https://gist.github.com/fmela/591333/c64f4eb86037bb237862a8283df70cdfc25f01d3
  std::size_t callStackSize = 0;
  void* callStack[MAX_NUM_FRAMES];
  std::size_t maxStackSize = sizeof(callStack)/sizeof(*callStack);
  char** callStackFrames;

  // Here, we will use execinfo.h api to grab the stack trace
  callStackSize = backtrace(callStack, maxStackSize);
  callStackFrames = backtrace_symbols(callStack, callStackSize);

  // process the stack frame strings
  std::ostringstream traceBuffer;
  // use a character array as a string buffer
  char stringBuffer[MAX_BUF_LENGTH];
  for(std::size_t i = skip; i < callStackSize; i++) {
    // TODO: demangle the strings before writing
    // write a formatted string to the string buffer
    snprintf(stringBuffer, sizeof(stringBuffer), "%s\n", callStackFrames[i]);
    traceBuffer << stringBuffer;
  }
  // free the memory allocated by backtrace_symbols for the frame strings
  free(callStackFrames);
  if(callStackSize == maxStackSize) {
    traceBuffer << "[truncated]\n";
  }
  // Store the trace in this object.
  this->stackTrace = traceBuffer.str();
}
