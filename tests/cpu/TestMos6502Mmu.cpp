//===-- tests/cpu/TestMos6502Mmu.cpp - Mos6502 MMU Test ---------*- C++ -*-===//
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
/// Test cases for the Mos6502 MMU class
///
//===----------------------------------------------------------------------===//
#include <array>
#include <memory>

#include "tests/catch.hpp"
#include "common/CommonTypes.h"
#include "memory/Mapper.h"
#include "memory/Bank.h"
#include "memory/Ram.h"
#include "cpu/Mos6502Mmu.h"

using namespace Memory;
using namespace Cpu;

#define NUM_BANKS 0x10
#define BANK_SIZE 0x1000

/// \class MockMapper
/// \brief A fake memory mapper for testing.
class MockMapper : public Mapper<byte> {
  public:
    MockMapper();
    ~MockMapper() {}
    std::shared_ptr<Bank<byte>> mapToHardware(Vaddr vaddr) const override;
  private:
    /// An array of ptrs to Ram banks that can be mapped to
    std::array<std::shared_ptr<Ram<byte>>, NUM_BANKS> dataBanks;
};

MockMapper::MockMapper() {
  Vaddr vaddr;
  // bootstrap the mock mapper.
  for(std::size_t i = 0; i < NUM_BANKS; i++) {
    vaddr.val = i * BANK_SIZE;
    dataBanks[i] = std::make_shared<Ram<byte>>(BANK_SIZE, vaddr);
  }
}

std::shared_ptr<Bank<byte>> MockMapper::mapToHardware(Vaddr vaddr) const {
  // mask out the high 4 bits and use as an index into the array
  std::size_t index = (vaddr.val >> 12) & 0xF;
  return dataBanks[index];
}

TEST_CASE("Mos6502 Memory Management Unit functionality tests", "[Mos6502],[Mmu]") {
  // instantiate the base objects needed to use the MMU
  byte regX = 0;
  byte regY = 0;
  auto memMap = MockMapper();

  // build the MMU
  auto mmu = Mos6502Mmu(regX, regY, memMap);

  SECTION("Absolute addressing has the correct behaviour") {
    // Write some memory to the ram, and try reading it from the MMU
    byte data = 5;
    Vaddr vaddr = {0x1023};
    auto ramPtr = memMap.mapToHardware(vaddr);
    ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val, data);

    byte test;
    auto memRef = mmu.absolute(vaddr);
    test = memRef.read();
    CHECK(test == data);

    // Now write some data to the Ram using a reference from the MMU
    data = 7;
    vaddr.val = 0x1001;
    memRef = mmu.absolute(vaddr);
    memRef.write(data);

    ramPtr = memMap.mapToHardware(vaddr);
    test = ramPtr->read(vaddr.val - ramPtr->getBaseAddress().val);
    CHECK(test == data);

  }

  SECTION("Absolute addressing X-indexed has the correct behaviour") {
    // Write some memory to the ram, and try reading it from the MMU
    byte data = 5;
    Vaddr vaddr = {0x1023};
    auto ramPtr = memMap.mapToHardware(vaddr);
    for(byte i = 0; i < 10; i++) {
      ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + i, data + i);
    }

    byte test;
    for(byte i = 0; i < 10; i++) {
      regX = i;
      auto memRef = mmu.absoluteXIndexed(vaddr);
      test = memRef.read();
      CHECK(test == (data + i));
    }

    // Now write some data to the Ram using a reference from the MMU
    data = 7;
    vaddr.val = 0x1001;
    for(byte i = 0; i < 10; i++) {
      regX = i;
      auto memRef = mmu.absoluteXIndexed(vaddr);
      memRef.write(data + i);
    }

    ramPtr = memMap.mapToHardware(vaddr);
    for(byte i = 0; i < 10; i++) {
      test = ramPtr->read(vaddr.val - ramPtr->getBaseAddress().val + i);
      CHECK(test == (data + i));
    }

  }

  SECTION("Absolute addressing Y-indexed has the correct behaviour") {
    // Write some memory to the ram, and try reading it from the MMU
    byte data = 5;
    Vaddr vaddr = {0x1023};
    auto ramPtr = memMap.mapToHardware(vaddr);
    for(byte i = 0; i < 10; i++) {
      ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + i, data + i);
    }

    byte test;
    for(byte i = 0; i < 10; i++) {
      regY = i;
      auto memRef = mmu.absoluteYIndexed(vaddr);
      test = memRef.read();
      CHECK(test == (data + i));
    }

    // Now write some data to the Ram using a reference from the MMU
    data = 7;
    vaddr.val = 0x1001;
    for(byte i = 0; i < 10; i++) {
      regY = i;
      auto memRef = mmu.absoluteYIndexed(vaddr);
      memRef.write(data + i);
    }

    ramPtr = memMap.mapToHardware(vaddr);
    for(byte i = 0; i < 10; i++) {
      test = ramPtr->read(vaddr.val - ramPtr->getBaseAddress().val + i);
      CHECK(test == (data + i));
    }

  }

  SECTION("Indirect addressing has the correct behaviour") {
    // write an address to the memory that points to some other bank containing
    // data.
    byte data = 5;
    Vaddr vaddr = {0x1023};
    auto ramPtr = memMap.mapToHardware(vaddr);
    ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val, 0x23);
    ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + 1, 0x20);
    vaddr.val = 0x2023;
    ramPtr = memMap.mapToHardware(vaddr);
    ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val, data);

    byte test;
    vaddr.val = 0x1023;
    auto memRef = mmu.indirect(vaddr);
    test = memRef.read();
    CHECK(test == data);

    data = 16;
    vaddr = {0x3001};
    ramPtr = memMap.mapToHardware(vaddr);
    ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val, 0x23);
    ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + 1, 0x40);
    vaddr.val = 0x3001;
    memRef = mmu.indirect(vaddr);
    memRef.write(data);

    vaddr.val = 0x4023;
    ramPtr = memMap.mapToHardware(vaddr);
    test = ramPtr->read(vaddr.val - ramPtr->getBaseAddress().val);
    CHECK(test == data);

  }
  
  SECTION("X-indexed indirect addressing has the correct behaviour") {
    // write an address to the memory that points to some other bank containing
    // data.
    byte data = 3;
    Vaddr vaddr = {0x0025};
    auto ramPtr = memMap.mapToHardware(vaddr);
    ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val, 0x23);
    ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + 1, 0x20);
    vaddr.val = 0x2023;
    ramPtr = memMap.mapToHardware(vaddr);
    ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val, data);

    byte test;
    regX = 2;
    vaddr.val = 0x0023;
    auto memRef = mmu.xIndexedIndirect(vaddr);
    test = memRef.read();
    CHECK(test == data);

    data = 117;
    vaddr = {0x0005};
    ramPtr = memMap.mapToHardware(vaddr);
    ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val, 0x23);
    ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + 1, 0x40);
    regX = 4;
    vaddr.val = 0x0001;
    memRef = mmu.xIndexedIndirect(vaddr);
    memRef.write(data);

    vaddr.val = 0x4023;
    ramPtr = memMap.mapToHardware(vaddr);
    test = ramPtr->read(vaddr.val - ramPtr->getBaseAddress().val);
    CHECK(test == data);

  }

  SECTION("Indirect Y-indexed addressing has the correct behaviour") {
    // write an address to the memory that points to some other bank containing
    // data.
    byte data = 5;
    Vaddr vaddr = {0x1023};
    auto ramPtr = memMap.mapToHardware(vaddr);
    ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val, 0x23);
    ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + 1, 0x20);
    vaddr.val = 0x2025;
    ramPtr = memMap.mapToHardware(vaddr);
    ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val, data);

    byte test;
    regY = 2;
    vaddr.val = 0x1023;
    auto memRef = mmu.indirectYIndexed(vaddr);
    test = memRef.read();
    CHECK(test == data);

    data = 16;
    vaddr = {0x3001};
    ramPtr = memMap.mapToHardware(vaddr);
    ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val, 0x23);
    ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + 1, 0x40);
    regY = 4;
    vaddr.val = 0x3001;
    memRef = mmu.indirectYIndexed(vaddr);
    memRef.write(data);

    vaddr.val = 0x4027;
    ramPtr = memMap.mapToHardware(vaddr);
    test = ramPtr->read(vaddr.val - ramPtr->getBaseAddress().val);
    CHECK(test == data);

  }

  SECTION("Zeropage addressing has the correct behaviour") {
    // Write some memory to the ram, and try reading it from the MMU
    byte data = 25;
    Vaddr vaddr = {0x0023};
    auto ramPtr = memMap.mapToHardware(vaddr);
    ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val, data);

    byte test;
    auto memRef = mmu.zeropage(vaddr);
    test = memRef.read();
    CHECK(test == data);

    // Now write some data to the Ram using a reference from the MMU
    data = 7;
    vaddr.hh = 0x0;
    vaddr.ll = 0x01;
    memRef = mmu.zeropage(vaddr);
    memRef.write(data);

    ramPtr = memMap.mapToHardware(vaddr);
    test = ramPtr->read(vaddr.val - ramPtr->getBaseAddress().val);
    CHECK(test == data);

  }

  SECTION("Zeropage addressing X-indexed has the correct behaviour") {
    // Write some memory to the ram, and try reading it from the MMU
    byte data = 10;
    Vaddr vaddr = {0x0023};
    auto ramPtr = memMap.mapToHardware(vaddr);
    for(byte i = 0; i < 10; i++) {
      ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + i, data + i);
    }

    byte test;
    for(byte i = 0; i < 10; i++) {
      regX = i;
      auto memRef = mmu.zeropageXIndexed(vaddr);
      test = memRef.read();
      CHECK(test == (data + i));
    }

    // Now write some data to the Ram using a reference from the MMU
    data = 30;
    vaddr.val = 0x0001;
    for(byte i = 0; i < 10; i++) {
      regX = i;
      auto memRef = mmu.zeropageXIndexed(vaddr);
      memRef.write(data + i);
    }

    ramPtr = memMap.mapToHardware(vaddr);
    for(byte i = 0; i < 10; i++) {
      test = ramPtr->read(vaddr.val - ramPtr->getBaseAddress().val + i);
      CHECK(test == (data + i));
    }

  }

  SECTION("Zeropage addressing Y-indexed has the correct behaviour") {
    // Write some memory to the ram, and try reading it from the MMU
    byte data = 100;
    Vaddr vaddr = {0x0050};
    auto ramPtr = memMap.mapToHardware(vaddr);
    for(byte i = 0; i < 10; i++) {
      ramPtr->write(vaddr.val - ramPtr->getBaseAddress().val + i, data + i);
    }

    byte test;
    for(byte i = 0; i < 10; i++) {
      regY = i;
      auto memRef = mmu.zeropageYIndexed(vaddr);
      test = memRef.read();
      CHECK(test == (data + i));
    }

    // Now write some data to the Ram using a reference from the MMU
    data = 7;
    vaddr.val = 0x0001;
    for(byte i = 0; i < 10; i++) {
      regY = i;
      auto memRef = mmu.zeropageYIndexed(vaddr);
      memRef.write(data + i);
    }

    ramPtr = memMap.mapToHardware(vaddr);
    for(byte i = 0; i < 10; i++) {
      test = ramPtr->read(vaddr.val - ramPtr->getBaseAddress().val + i);
      CHECK(test == (data + i));
    }

  }

}
