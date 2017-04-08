//===-- tests/cpu/TestInterpretedMos6502.cpp - Interpreter Test -*- C++ -*-===//
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
/// Test cases for the Mos6502 interpreter
///
//===----------------------------------------------------------------------===//

#include <limits>
#include <array>

#include "tests/catch.hpp"
#include "common/CommonTypes.h"
#include "cpu/Mos6502.h"
#include "cpu/interpreter/InterpretedMos6502.h"

#include "MockMapper.h"


using namespace Cpu;
using namespace Memory;

template <uint32 N>
using range = std::array<uint32, N>;

static void loadRamWithProgram1(
    std::shared_ptr<Bank<byte>>& ramPtr, 
    MockMapper& memMap) {
  Vaddr vaddr = {0xFFFC};
  ramPtr = memMap.mapToHardware(vaddr);
  // write the RESET_VECTOR
  ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val, 0x01);
  ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + 1, 0x40);
  // write the IRQ_VECTOR
  ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + 2, 0x01);
  ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + 3, 0x50);

  addr i = 0; // ticker
  vaddr.val = 0x4001;
  ramPtr = memMap.mapToHardware(vaddr);
  ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + (i++), Op::LDA_IMMED);
  ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + (i++), 0x05);
  ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + (i++), Op::STA_ABS);
  ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + (i++), 0x01);
  ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + (i++), 0x00);
  ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + (i++), Op::ADC_IMMED);
  ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + (i++), 0x0A);
  ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + (i++), Op::STA_ABS);
  ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + (i++), 0x02);
  ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + (i++), 0x00);
  ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + (i++), Op::BRK_IMPL);
  ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + (i++), 0x01); // skipped
  ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + (i++), Op::LDX_ABS);
  ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + (i++), 0x02);
  ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + (i++), 0x00);
  ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + (i++), Op::STX_ZPG);
  ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + (i++), 0x03);

  i = 0;
  vaddr.val = 0x5001;
  ramPtr = memMap.mapToHardware(vaddr);
  ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + (i++), Op::NOP_IMPL);
  ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + (i++), Op::NOP_IMPL);
  ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + (i++), Op::RTI_IMPL);

}

TEST_CASE("Functional test for Mos6502 interpreter.", "[Mos6502][Interpreter]") {
  // Add some data to the memory mapper in key locations
  Vaddr vaddr;
  MockMapper memMap;
  std::shared_ptr<Bank<byte>> ramPtr;
  loadRamWithProgram1(ramPtr, memMap);
  // build an interpreter
  InterpretedMos6502 cpu(memMap);
  
  SECTION("Run cpu with single steps to verify correctness.") {
    cpu.reset();
    // An LDA_IMMED + STA_ABS takes 6 cycles. 
    for(auto x : range<6>()) {
      cpu.step();
    }
    // Cycle count should be zero
    REQUIRE(cpu.getCycleCount() == 0);
    vaddr.val = 0x0001;
    ramPtr = memMap.mapToHardware(vaddr);
    byte test = ramPtr->read(vaddr.val - ramPtr->getBaseAddress().val);
    INFO("Read the value " << std::hex << "0x" << test << " @ 0x" << vaddr.val);
    REQUIRE(test == 0x05);

    // ADC_IMMED + STA_ABS takes 6 cycles
    for(auto x : range<6>()) {
      cpu.step();
    }
    REQUIRE(cpu.getCycleCount() == 0);
    vaddr.val = 0x0002;
    ramPtr = memMap.mapToHardware(vaddr);
    test = ramPtr->read(vaddr.val - ramPtr->getBaseAddress().val);
    INFO("Read the value " << std::hex << "0x" << test << " @ 0x" << vaddr.val);
    REQUIRE(test == 0x0F); // 5 + 10 = 15

    // Next instruction is BRK.
    for(auto x : range<7>()) {
      cpu.step();
    }
    // Cycle count should be zero
    REQUIRE(cpu.getCycleCount() == 0);

    // two NOPs is 4 cycles.
    for(auto x : range<4>()) {
      cpu.step();
    }
    REQUIRE(cpu.getCycleCount() == 0);
    
    // Now RTI is 6 cycles
    for(auto x : range<6>()) {
      cpu.step();
    }
    REQUIRE(cpu.getCycleCount() == 0);

    // Now load X from 0x0002 = 15, and store elsewhere
    // LDX_ABS + STX_ZPG = 7 cycles
    for(auto x : range<7>()) {
      cpu.step();
    }
    REQUIRE(cpu.getCycleCount() == 0);
    vaddr.val = 0x0003;
    ramPtr = memMap.mapToHardware(vaddr);
    test = ramPtr->read(vaddr.val - ramPtr->getBaseAddress().val);
    INFO("Read the value " << std::hex << "0x" << test << " @ 0x" << vaddr.val);
    REQUIRE(test == 0x0F);     
    
  }

}
