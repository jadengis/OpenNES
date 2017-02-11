
#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <string.h>
#include <iostream>
#include "Common.h"

namespace Exception {

// Base exception class for OsNES. This will grab the stack 
// TODO: Get the Exception class to grab a stack trace at throw time.
class Base {
  public:
    // Construction Methods
    Base() noexcept;
    Base(const Base&) noexcept;
    Base& operator= (const Base&) noexcept;

    // Destructor
    virtual ~Base();

    // Error Message
    virtual std::string message() const noexcept;
};

}

#endif // EXCEPTION_H //
