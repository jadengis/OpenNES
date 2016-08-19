
#ifndef EXCEPT_H
#define EXCEPT_H
#include <exception.h>
#include <string.h>
#include <iostreams.h>

// Base exception class for OsNES. This will grab the stack 
// TODO: Get the Exception class to grab a stack trace at throw time.
namespace Exception {
  class Base {
    public:
      // Construction Methods
      Exception() noexcept;
      Exception(const Exception&) noexcept;
      Exception& operator= (const Exception&) noexcept;

      // Destructor
      virtual ~Exception();

      // Error Message
      virtual string message() const noexcept;
  };

  class Bad_Opcode : public Base {
    public:
      // Construction Methods
      Exception_Bad_Opcode(uint8 opcode) : bad_opcode(opcode) {}
      Exception_Bad_Opcode(const Exception_Bad_Opcode&) noexcept;
      Exception_Bad_Opcode& operator= (const Exception_Bad_Opcode&) noexcept;

      // Destructors
      ~Exception_Bad_Opcode() {}

      //
      string message() const noexcept;
    private:
      const uint8 bad_opcode;
  };
}
#endif // EXCEPT_H //:~
