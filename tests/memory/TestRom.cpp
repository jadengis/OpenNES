//===-- tests/memory/TestRom.cpp - Rom Test ---------------------*- C++ -*-===//
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
/// Test cases for the Rom class
///
//===----------------------------------------------------------------------===//

#include "tests/catch.hpp"
#include "common/CommonTypes.h"
#include "memory/Rom.h"
#include "memory/MemoryException.h"

using namespace Memory;

static void writeToBank(Bank<byte>& bank, std::size_t index, byte data) {
  bank.write(index, data);
}

TEST_CASE("Rom build, load and read functionality.", "[Memory][Rom]") {
  // make a simple vector of data
  Rom<byte> rom;
  REQUIRE(rom.getSize() == 0);
  REQUIRE(rom.getBaseAddress().val == 0);

  SECTION("Loading a Rom from a vector object works correctly.") {
    std::vector<byte> data = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    SECTION("Loading the entire vector is correct.") {
      rom.load(std::begin(data), std::end(data));
      REQUIRE(rom.getSize() == 11);

      for(std::size_t i = 0; i < rom.getSize(); i++) {
        CHECK(rom.read(i) == data.at(i));
      }
    }

    SECTION("Loading a subvector is correct.") {
      rom.load(std::begin(data) + 2, std::end(data) - 2);
      REQUIRE(rom.getSize() == 7);

      for(std::size_t i = 0; i < rom.getSize(); i++) {
        CHECK(rom.read(i) == data.at(i + 2));
      }
    }

    SECTION("Trying to load twice throws an error") {
      rom.load(std::begin(data), std::end(data));
      std::vector<byte> moreData = {0, 1, 2, 3, 4}; 

      REQUIRE_THROWS_AS(rom.load(std::begin(moreData), std::end(moreData)), 
          Exception::ReadOnlyMemoryException);
    }
  }
}

TEST_CASE("Attempting to write to a Rom throws an error.", "[Memory][Rom]") {
    // build and load a Rom.
    Rom<byte> rom;
    std::vector<byte> data = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    rom.load(std::begin(data), std::end(data));

    // Rom object accidentally gets passed to a function that writes
    REQUIRE_THROWS_AS(writeToBank(rom, 0x5, 0x10),
        Exception::ReadOnlyMemoryException);
}
