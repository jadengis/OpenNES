
#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <exception>
#include <string.h>
#include <iostream>
#include "Common.h"

// Base exception class for OsNES. This will grab the stack 
// TODO: Get the Exception class to grab a stack trace at throw time.
namespace Exception {
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

  class BadOpcode : public Base {
    public:
      // Construction Methods
      BadOpcode(byte opcode) : bad_opcode(opcode) {}
      BadOpcode(const BadOpcode&) noexcept;
      BadOpcode& operator= (const BadOpcode&) noexcept;

      // Destructors
      ~BadOpcode() {}

      //
      std::string message() const noexcept;
    private:
      const byte bad_opcode;
  };
}
#endif // EXCEPTION_H //:~
