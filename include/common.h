#ifndef COMMON_H
#define COMMON_H
// Integer typedefs to give the native C types more convenient names
typedef signed char        int8;
typedef signed short       int16;
typedef signed int         int32;
typedef signed long long   int64;
typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned long long uint64;

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
  static const uint64 MAX_SIZE_8BIT = 256;
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
