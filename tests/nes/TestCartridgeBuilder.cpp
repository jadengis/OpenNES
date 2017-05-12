//===-- tests/nes/TestCartridgeBuilder.cpp - Rom Test -----------*- C++ -*-===//
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

#include<string.h>

#include "tests/catch.hpp"
#include "tests/TestResource.h"
#include "common/CommonTypes.h"
#include "nes/Cartridge.h"
#include "nes/CartridgeBuilder.h"

using namespace Nes;

TEST_CASE("Building Cartridges from Rom files works correctly",
    "[Nes][Cartridge]") {
  // Create a cartridge builder
  CartridgeBuilder builder;
  SECTION("Build a cartridge from dummy romFile") {
    builder.setInputFile(GET_RESOURCE_PATH("testRom.nes"));
    auto cartridgePtr = builder.build();
    auto& mapper = cartridgePtr->getMapper();
    std::string name = mapper.getName();
    REQUIRE(name == "NRom");

  } 
}
