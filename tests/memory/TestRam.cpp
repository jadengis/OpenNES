//===-- tests/memory/TestRam.cpp - Ram Test ---------------------*- C++ -*-===//
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
/// Test cases for the Ram class
///
//===----------------------------------------------------------------------===//

#include "tests/catch.hpp"
#include "common/CommonTypes.h"
#include "memory/Ram.h"

using namespace Memory;

TEST_CASE("Ram write and read functionality", "[Memory][Ram]") {
  // Build a Ram object
  std::size_t size = 100;
  Ram<byte> ram(size);
  REQUIRE(ram.getSize() == size);

  SECTION("Write to index and read back") {
    std::size_t index = 5;
    byte data = 7;
    // write the data at the index
    ram.write(index, data);
    REQUIRE(ram.read(index) == data);
  }
}

TEST_CASE("Getting and Setting base address works correcty.", "[Memory][Ram]") {
  // Build a Ram object
  std::size_t size = 100;
  Vaddr vaddr = {0x200};
  Ram<byte> ram(size, vaddr);
  REQUIRE(ram.getSize() == size);
  REQUIRE(ram.getBaseAddress().val == 0x200);

  // set the base address to something else
  vaddr.val = 0x1111;
  ram.setBaseAddress(vaddr);
  REQUIRE(ram.getBaseAddress().val == 0x1111);
}

TEST_CASE("Rams are correctly resizable.", "[Memory][Ram]") {
  // Build a default Ram object
  Ram<byte> ram;
  REQUIRE(ram.getSize() == 0);
  ram.resize(0x200);
  REQUIRE(ram.getSize() == 0x200);
  
}
