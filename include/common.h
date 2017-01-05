#ifndef COMMON_H
#define COMMON_H
// Common includes
#include <memory>

// Integer aliases to give the native C types more convenient names
using int8   = signed char;
using int16  = signed short;
using int32  = signed int;
using int64  = signed long long;
using uint8  = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

// use the native 'arch_native' to represent the native architecture
// of the emulating machine. Default to 64 bit architecture.
#if ARCH == 32
using arch_native = uint32
#else
using arch_native = uint64
#endif

// use the type 'byte' when referring to arbitary bytes of data, i.e
// data that is not necessarily signed int or unsigned int; the only
// important thing is that it is 8 bits.
using byte = unsigned char;

// com - The common namespace for all common helper functions and
//       constant values used throughout the source.
namespace com {
  // Common enum type for referencing bit positions
  enum class Bit_Position {
    bit0 = 0,
    bit1 = 1,
    bit2 = 2,
    bit3 = 3,
    bit4 = 4,
    bit5 = 5,
    bit6 = 6,
    bit7 = 7
  };

  // Common constant definitions
  static const uint64 MAX_SIZE_BYTE = 256;
  static const int64  MAX_INT8      = 127;
  static const int64  MIN_INT8      = -128;

  // Useful masks
  static const arch_native BYTE_MASK     = 0xFF;
  static const byte       ONE_BIT_MASK  = 0x01;
}
#endif // COMMON_H //:~
