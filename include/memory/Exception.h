
#ifndef MEMORY_EXCEPTION_H
#define MEMORY_EXCEPTION_H
#include <string.h>
#include <iostream>
#include "Common.h"
#include "BaseException.h"

namespace Exception {

class ReadOnlyMemory : public Base {
  public:
    // Construction Methods
    ReadOnlyMemory() {}
    ReadOnlyMemory(const ReadOnlyMemory&) noexcept;
    ReadOnlyMemory& operator= (const ReadOnlyMemory&) noexcept;

    // Destructors
    ~ReadOnlyMemory() {}

    //
    std::string message() const noexcept;
};

} // namespace Exception
#endif // MEMORY_EXCEPTION_H //
