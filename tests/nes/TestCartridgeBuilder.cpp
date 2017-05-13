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
#include "common/BaseException.h"
#include "nes/Cartridge.h"
#include "nes/CartridgeBuilder.h"

using namespace Nes;

TEST_CASE("Building Cartridges from Rom files works correctly.",
    "[Nes][Cartridge]") {
  // Create a cartridge builder
  CartridgeBuilder builder;
  SECTION("Build a cartridge from dummy romFile, and check properties") {
    // Build a cartridge from testRom.nes and assert it has the right mapper.
    builder.setInputFile(GET_RESOURCE_PATH("testRom.nes"));
    auto cartridgePtr = builder.build();
    auto& mapper = cartridgePtr->getMapper();
    std::string name = mapper.getName();
    REQUIRE(name == "NRom");
    
    // This address should be a Ram of size 0x2000, base address == 0x8000
    Vaddr vaddr = {0x7000};
    auto bankPtr = mapper.mapToHardware(vaddr);
    CHECK((bankPtr->getSize()) == 0x2000);
    CHECK((bankPtr->getBaseAddress().val) == 0x6000);

    // This address should be a Rom of size 0x4000, base address == 0x8000
    vaddr.val = 0x9000;
    bankPtr = mapper.mapToHardware(vaddr);
    CHECK((bankPtr->getSize()) == 0x4000);
    CHECK((bankPtr->getBaseAddress().val) == 0x8000);

    // This address should be a Rom of size 0x4000, base address == 0xC000
    vaddr.val = 0xD000;
    bankPtr = mapper.mapToHardware(vaddr);
    CHECK((bankPtr->getSize()) == 0x4000);
    CHECK((bankPtr->getBaseAddress().val) == 0xC000);

  } 
}
