//===-- tests/memory/TestRam.cpp - Ram Test ---------------------*- C++ -*-===//
//
//                           The OsNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details. The Catch
// framework IS NOT distributed under LICENSE.md.
// The Catch framework is included in this project under the Boost License
// simply as a matter of convenience.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Test cases for the Ram class
///
//===----------------------------------------------------------------------===//

#include "tests/catch.hpp"
#include "common/CommonTypes.h"
#include "memory/Ram.h"

TEST_CASE("Ram write and read functionality", "[Memory][Ram]") {
  // Build a Ram object
  std::size_t size = 100;
  Memory::Ram<byte> ram(size);
  REQUIRE(ram.getSize() == size);

  SECTION("Write to index and read back") {
    std::size_t index = 5;
    byte data = 7;
    // write the data at the index
    ram.write(index, data);
    REQUIRE(ram.read(index) == data);
  }
}
