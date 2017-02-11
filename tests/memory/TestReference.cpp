//===-- tests/memory/TestReference.cpp - Reference Test --------*- C++ -*-===//
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
/// Test cases for the Reference class
///
//===----------------------------------------------------------------------===//

#include "tests/catch.hpp"
#include "Common.h"
#include "memory/Ram.h"
#include "memory/Reference.h"

TEST_CASE("Reference read and write to Ram", "[Memory][Reference]") {
  // Build a Ram object
  std::size_t size = 100;
  std::shared_ptr<Memory::Ram<byte> > ram_p(new Memory::Ram<byte>(size));
  REQUIRE(ram_p->getSize() == size);

  // Build a reference to the memory object
  Memory::Reference<byte> ref(ram_p, 5);

  SECTION("Write data to memory with reference, and read back") {
    byte data = 7;
    // write the data at the referenced index
    ref.write(data);
    byte testData = ref.read();
    REQUIRE(testData == data);
  }
}
