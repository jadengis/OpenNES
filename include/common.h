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

// use the type 'byte' when referring to arbitary bytes of data, i.e
// data that is not necessarily signed int or unsigned int; the only
// important thing is that it is 8 bits.
using byte   = unsigned char;

// com - The common namespace for all common helper functions and
//       constant values used throughout the source.
namespace com {
  // Common enum type for referencing bit positions
  enum bits {
    BIT0 = 0,
    BIT1,
    BIT2,
    BIT3,
    BIT4,
    BIT5,
    BIT6,
    BIT7
  };

  // Common constant definitions
  static const uint64 MAX_SIZE_BYTE = 256;
  static const uint8  ONE_BIT_MASK  = 0x01;

  // Common helper functions
  static inline uint8 Check_Zero(uint8 x) {
    // Returns 1 if 0, 0 otherwise
    return x == 0;
  }

  static inline uint8 Check_Not_Zero(uint8 x) {
    // Returns 1 if not 0, 0 otherwise
    return x != 0;
  }

  static inline uint8 Check_Nth_Bit(uint8 x, uint8 N) {
    // Returns 1 if Nth bit 1, 0 otherwise. Bit indexing it 0 - 7.
    return (x >> N) & ONE_BIT_MASK;
  }
}
#endif // COMMON_H //:~
