
#ifndef CPU_EXCEPTION_H
#define CPU_EXCEPTION_H
#include "BaseException.h"

namespace Exception {

class BadOpcode : public Base {
  public:
    // Construction Methods
    BadOpcode(byte opcode) : badOpcode(opcode) {}
    BadOpcode(const BadOpcode&) noexcept;
    BadOpcode& operator= (const BadOpcode&) noexcept;

    // Destructors
    ~BadOpcode() {}

    //
    std::string message() const noexcept;
  private:
    const byte badOpcode;
};

} // namespace Exception

#endif // CPU_EXCEPTION_H //
