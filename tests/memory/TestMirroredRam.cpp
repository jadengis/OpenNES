//===-- tests/memory/TestMirroredRam.cpp - Mirroed Ram Test -----*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details. The Catch
// framework IS NOT distributed under LICENSE.md.
// The Catch framework is included in this project under the Boost License
// simply as a matter of convenience.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Test cases for the MirroredRam class
///
//===----------------------------------------------------------------------===//

#include "tests/catch.hpp"
#include "common/CommonTypes.h"
#include "memory/MirroredRam.h"
#include "memory/MemoryException.h"

using namespace Memory;

TEST_CASE("Mirrored Ram write and read functionality", "[Memory][MirroredRam]") {
  // Build a MirroredRam object
  std::size_t size = 0x2000;
  std::size_t mirrors = 0x4;
  MirroredRam<byte> ram(size, mirrors);
  REQUIRE(ram.getSize() == size);

  SECTION("Write to index and read back from all mirrors.") {
    std::size_t index = 5;
    byte data = 7;
    // write the data at the index
    ram.write(index, data);
    for(std::size_t i = 0; i < mirrors; i++) {
      INFO("Reading from index 0x"<< std::hex << (index + i*(size / mirrors)))
      CHECK(ram.read(index + i*(size / mirrors)) == data);
    }
  }
}

TEST_CASE("MirroredRam building fails if conditions are violated.",
    "[Memory][MirroredRam]") {
  SECTION("Building fails if mirrors does not divide size.") {
    std::size_t size = 0x101;
    std::size_t mirrors = 0x2;
    REQUIRE_THROWS_AS(MirroredRam<byte>(size, mirrors), 
        Exception::MirroringException) ;
  }

  SECTION("Building fails if mirrors is not a power of 2.") {
    std::size_t size = 0x300;
    std::size_t mirrors = 0x3;
    REQUIRE_THROWS_AS(MirroredRam<byte>(size, mirrors), 
        Exception::MirroringException) ;
  }
}
