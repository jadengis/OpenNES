//===-- include/common/CommonTypes.h - Common Types -------------*- C++ -*-===//
//
//                           The OsNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains definitions of common type names used through out the
/// code base (in particular preferred aliases).
///
//===----------------------------------------------------------------------===//
#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include <limits>
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

// use the type 'uint_native' for the  native register width of the emulating
// architecture
using uint_native = unsigned long;

// use the type 'byte' when referring to arbitary bytes of data, i.e
// data that is not necessarily signed int or unsigned int; the only
// important thing is that it is 8 bits.
using byte = unsigned char;

// use the type 'addr' when referring to 16 bit addresses
using addr = unsigned short;

#endif // COMMON_TYPES_H //:~
