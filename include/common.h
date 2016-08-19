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

// Common constant definitions
static const uint64 MAX_SIZE_8BIT = 256;
static const uint8  NEG_BIT_8BIT  = 0x80;

// Common helper functions
static inline uint8 Check_Neg_Bit(uint8 x) {
  // Returns 1 if neg bit 1, 0 otherwise
  return (reg.AC & NEG_BIT_8BIT) >> 7;
}

#endif // COMMON_H //:~
