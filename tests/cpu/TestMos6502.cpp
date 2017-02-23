//===-- tests/cpu/TestMos6502.cpp - Mos6502 Test -----------------*- C++ -*-===//
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
/// Test cases for the Mos6502 class
///
//===----------------------------------------------------------------------===//

#include "tests/catch.hpp"
#include "common/CommonTypes.h"
#include "tests/cpu/Mos6502.h"

TEST_CASE("Functionality testing for Mos6502 ADC", "[Mos6502][ADC]") {
  // Build a Mos6502 test object
  Test::Mos6502 cpu;
  // initialized accumulator should be zero
  REQUIRE(cpu.getRegAC() == 0);

  SECTION("Adding numbers together gives correst results") {
    byte data = 7;
    // add data to the accumulator
    cpu.testADC(data);
    REQUIRE(cpu.getRegAC() == 7);

    // add more data to accumulator
    data = 5;
    cpu.testADC(data);
    REQUIRE(cpu.getRegAC() == 12);
  }
}
