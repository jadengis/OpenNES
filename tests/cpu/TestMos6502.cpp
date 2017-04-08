//===-- tests/cpu/TestMos6502.cpp - Mos6502 Test -----------------*- C++ -*-===//
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
/// Test cases for the Mos6502 class
///
//===----------------------------------------------------------------------===//

#include <limits>

#include "tests/catch.hpp"
#include "common/CommonTypes.h"
#include "cpu/Mos6502.h"
#include "Mos6502_Inst.h"

#include "MockMapper.h"

static MockMapper memMap;

/// \class TestMos6502
/// \brief Class for testing Mos6502 methods.
class TestMos6502 : public Cpu::Mos6502 {
  public:
    TestMos6502() : Mos6502(::memMap) {}
    ~TestMos6502() {}
  protected:
    void fetchOpcodeImpl() override {}
    void decodeOpcodeImpl() override {}
    void executeOpcodeImpl() override {}
};

#define SET_OVERFLOW() \
  ADC(100);\
  ADC(100);

#define REQUIRE_GREATER() \
  CHECK((getRegSR() & Cpu::Mos6502::SR_N) == 0);\
  CHECK((getRegSR() & Cpu::Mos6502::SR_Z) == 0);\
  REQUIRE((getRegSR() & Cpu::Mos6502::SR_C) != 0);

#define REQUIRE_EQUAL() \
  CHECK((getRegSR() & Cpu::Mos6502::SR_N) == 0);\
  CHECK((getRegSR() & Cpu::Mos6502::SR_C) != 0);\
  REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) != 0);

#define REQUIRE_LESS() \
  CHECK((getRegSR() & Cpu::Mos6502::SR_Z) == 0);\
  CHECK((getRegSR() & Cpu::Mos6502::SR_C) == 0);\
  REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);

TEST_CASE_METHOD(TestMos6502, "Functionality testing for Mos6502 ADC", "[Mos6502][ADC]") {
  // initialized accumulator should be zero
  REQUIRE(getRegAC() == 0);

  SECTION("Adding unsigned integers together gives correct results") {
    byte data = 7;
    // add data to the accumulator
    ADC(data);
    REQUIRE(getRegAC() == 7);

    // add more data to accumulator
    data = 5;
    ADC(data);
    REQUIRE(getRegAC() == 12);
    // carry bit should not be set
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_C) == 0);

    // At this point the accumulator should hold 12, add the max byte should cause
    // and overflow in carry
    data = std::numeric_limits<byte>::max(); // 255
    ADC(data);

    // value will overflow to 11
    REQUIRE(getRegAC() == 11);
    // carry bit should be set
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_C) != 0);
  }

  SECTION("Adding signed integers together gives the correct results") {
    int8 data = -5;
    // add data to the accumulator
    ADC(static_cast<byte>(data));
    REQUIRE(static_cast<int8>(getRegAC()) == -5);
    // negative bit should be set
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);

    data = 5;
    // adding 5 again should null to zero
    ADC(static_cast<byte>(data));
    REQUIRE(static_cast<int8>(getRegAC()) == 0);
    // zero bit should be set
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
    // carry will also be set by this
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_C) != 0);
    // Clear the carry before continuing
    CLC();

    // accumulator is currently 0
    data = 100;
    // adding 100 twice should overflow.
    ADC(static_cast<byte>(data));
    REQUIRE(static_cast<int8>(getRegAC()) == 100);
    // negative bit should be unset
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) == 0);
    // overflow bit should be unset
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_V) == 0);
    // add again
    ADC(static_cast<byte>(data));
    REQUIRE(getRegAC() == 200);
    // overflow bit should be set
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_V) != 0);
  }

}

TEST_CASE_METHOD(TestMos6502, "Functionality testing for Mos6502 SBC", "[Mos6502][SBC]") {
  // initialized accumulator should be zero
  REQUIRE(getRegAC() == 0);

  SECTION("Subtracting unsigned integers gives correct results") {
    // Load accumulator with initial data and set carry flag
    LDA(10);
    SEC();
    byte data = 7;
    // subtract data from the accumulator
    SBC(data);
    REQUIRE(getRegAC() == 3);

    // subtract more data from accumulator
    data = 3;
    SBC(data);
    REQUIRE(getRegAC() == 0);
    // borrow bit should be set
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_C) != 0);

    // subtract more data from accumulator
    data = 5;
    SBC(data);
    REQUIRE(getRegAC() == static_cast<byte>(-5));
    // borrow bit should not be set
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) == 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_C) == 0);

  }

  SECTION("Subtracting signed integers gives the correct results") {
    // set carry initially
    SEC();
    int8 data = 5;
    // add data to the accumulator
    SBC(static_cast<byte>(data));
    REQUIRE(static_cast<int8>(getRegAC()) == static_cast<int8>(-5));
    // negative bit should be set
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);

    SEC();
    data = -5;
    // adding 5 again should null to zero
    SBC(static_cast<byte>(data));
    REQUIRE(static_cast<int8>(getRegAC()) == 0);
    // zero bit should be set
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
    // carry will also be set by this
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_C) != 0);
    // Set the carry before continuing
    SEC();

    // accumulator is currently 0
    data = 100;
    // subtract 100 twice should overflow.
    SBC(static_cast<byte>(data));
    REQUIRE(static_cast<int8>(getRegAC()) == -100);
    // negative bit should be unset
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);
    // overflow bit should be unset
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_V) == 0);
    // subtact again
    SBC(static_cast<byte>(data));
    // overflow bit should be set
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_V) != 0);
  }

}

TEST_CASE_METHOD(TestMos6502, "Functionality testing for Mos6502 AND", "[Mos6502][AND]") {
  // initialized accumulator should be zero
  REQUIRE(getRegAC() == 0);

  SECTION("ANDing bytes together gives the correct results") {
    // Load some initial data into the accumulator.
    byte data = 0x0E;
    LDA(data);
    REQUIRE(getRegAC() == 0x0E);

    // 0x0E & 0x07 == 0x6
    data = 0x07;
    AND(data);
    REQUIRE(getRegAC() == 0x06);
    
  }

  SECTION("ANDing bytes together sets the correct SR flags") {
    // AND with 0 is 0, should set zero flag
    byte data = 0xFF;
    AND(data);
    CHECK(getRegAC() == 0x0);
    // zero bit should be set
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
    // Now load the data and check the sign bit
    LDA(data);
    data = 0x80;
    AND(data);
    REQUIRE(getRegAC() == 0x80);
    // negative bit should be set
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);

  }

}

TEST_CASE_METHOD(TestMos6502, "Functionality testing for Mos6502 ORA", "[Mos6502][ORA]") {
  // initialized accumulator should be zero
  REQUIRE(getRegAC() == 0);

  SECTION("ORing bytes together gives the correct results") {
    // Load some initial data into the accumulator
    byte data = 0x0F;
    ORA(data);
    REQUIRE(getRegAC() == data);

    // 0xF0 ^ 0xF0 == 0xFF
    data = 0xF0;
    EOR(data);
    REQUIRE(getRegAC() == 0xFF);
  }

  SECTION("ORing bytes together sets the correct SR flags") {
    // OR with 0 is 0, should set 0 flag
    byte data = 0x0;
    ORA(data);
    CHECK(getRegAC() == 0);
    // zero bit should be set
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
    // Now OR 0 with 0x80
    data = 0x80;
    ORA(data);
    CHECK(getRegAC() == 0x80);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);
  }

}

TEST_CASE_METHOD(TestMos6502, "Functionality testing for Mos6502 EOR", "[Mos6502][EOR]") {
  // initialized accumulator should be zero
  REQUIRE(getRegAC() == 0);

  SECTION("EORing bytes together gives the correct results") {
    // Load some initial data into the accumulator
    byte data = 0xFF;
    LDA(data);
    REQUIRE(getRegAC() == data);

    // 0xFF ^ 0xF0 == 0x0F
    data = 0xF0;
    EOR(data);
    REQUIRE(getRegAC() == 0x0F);
    // 0x0F ^ 0x06 == 0x09
    data = 0x06;
    EOR(data);
    REQUIRE(getRegAC() == 0x09);
  }

  SECTION("EORing bytes together sets the correct SR flags") {
    // EOR with 0 is 0, should set 0 flag
    byte data = 0x0;
    EOR(data);
    CHECK(getRegAC() == 0);
    // zero bit should be set
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
    // Now EOR 0 with 0x80
    data = 0x80;
    EOR(data);
    CHECK(getRegAC() == 0x80);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);
  }

}

TEST_CASE_METHOD(TestMos6502, "Functionality testing for Mos6502 BIT instruction",
    "[Mos6502],[BIT]") {
  SECTION("Test bits instructions has the correct behaviour") {
    // Load accumulator with some value
    LDA(0x0F);
    BIT(0xF0);
    CHECK((getRegSR() & Cpu::Mos6502::SR_V) != 0);
    CHECK((getRegSR() & Cpu::Mos6502::SR_N) != 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) != 0);

    // Load a different value
    LDA(0xFF);
    BIT(0x80);
    CHECK((getRegSR() & Cpu::Mos6502::SR_V) == 0);
    CHECK((getRegSR() & Cpu::Mos6502::SR_N) != 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) == 0);
  }
}

TEST_CASE_METHOD(TestMos6502, "Functionality testing for Mos6502 shift instructions",
    "[Mos6502][Shift]") {
  SECTION("Shifting left by one bit gives the correct result") {
    // Take one bit in the far right position and check that it shifts the
    // whole way.
    byte data = 0x01;
    byte test = 0x0;
    for(long i = 0; i < 6; i++) {
      test = ASL(data);
      data <<= 1;
      REQUIRE(test == data);
      REQUIRE(getRegSR() == 0);
    }
    test = ASL(data);
    data <<= 1;
    REQUIRE(test == data);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);
    test = ASL(data);
    CHECK(test == 0);
    CHECK((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_C) != 0);
  }

  SECTION("Shifting right by one bit gives the correct result") {
    // Take one bit in the far left position and check that it shifts the
    // whole way
    byte data = 0x80;
    byte test = 0x0;
    for(long i = 0; i < 7; i++) {
      test = LSR(data);
      data >>= 1;
      REQUIRE(test == data);
      REQUIRE(getRegSR() == 0);
    }
    test = LSR(data);
    data >>= 1;
    CHECK(test == 0);
    CHECK((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_C) != 0);
  }

}

TEST_CASE_METHOD(TestMos6502, "Functionality testing for Mos6502 rotate instructions",
    "[Mos6502],[Rotate]") {
  SECTION("Rotating left by one bit gives the correct result") {
    // Take one bit in the far right position and check that it shifts the
    // whole way.
    byte data = 0x01;
    byte test = 0x0;
    for(long i = 0; i < 6; i++) {
      test = ROL(data);
      data <<= 1;
      REQUIRE(test == data);
      REQUIRE(getRegSR() == 0);
    }
    test = ROL(data);
    data <<= 1;
    REQUIRE(test == data);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);
    test = ROL(data);
    CHECK(test == 0);
    CHECK((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_C) != 0);
    // One more rotation should bring us full circle
    data = test;
    test = ROL(data);
    CHECK(test == 0x01);
    CHECK((getRegSR() & Cpu::Mos6502::SR_Z) == 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_C) == 0);
  }

  SECTION("Rotating right by one bit gives the correct result") {
    // Take one bit in the far left position and check that it shifts the
    // whole way.
    byte data = 0x80;
    byte test = 0x0;
    for(long i = 0; i < 7; i++) {
      test = ROR(data);
      data >>= 1;
      REQUIRE(test == data);
      REQUIRE(getRegSR() == 0);
    }
    test = ROR(data);
    CHECK(test == 0);
    CHECK((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_C) != 0);
    // One more rotation should bring us full circle
    data = test;
    test = ROR(data);
    CHECK(test == 0x80);
    CHECK((getRegSR() & Cpu::Mos6502::SR_Z) == 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_C) == 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);
  }

}

TEST_CASE_METHOD(TestMos6502, "Functionality testing for Mos6502 branch instructions",
    "[Mos6502][Branch]") {
  // initialized accumulator should be zero
  REQUIRE(getRegPC() == 0);

  SECTION("Branching on carry clear makes the correct change to the PC") {
    // We must have the carry cleared here
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_C) == 0);
    // Branch forward by some number of bytes
    int8 data = 64;
    BCC(static_cast<byte>(data));
    REQUIRE(getRegPC() == 64);
    // try and branch back
    data = -32;
    BCC(static_cast<byte>(data));
    REQUIRE(getRegPC() == 32);

    // now set the carry and check the branch does not work
    SEC();
    BCC(static_cast<byte>(data));
    REQUIRE(getRegPC() == 32);

  }

  SECTION("Branching on carry set makes the correct change to the PC") {
    // We must have the carry set here
    SEC();
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_C) != 0);
    // Branch forward by some number of bytes
    int8 data = 64;
    BCS(static_cast<byte>(data));
    REQUIRE(getRegPC() == 64);
    // try and branch back
    data = -32;
    BCS(static_cast<byte>(data));
    REQUIRE(getRegPC() == 32);

    // now clear the carry and check the branch does not work
    CLC();
    BCS(static_cast<byte>(data));
    REQUIRE(getRegPC() == 32);

  }

  SECTION("Branching on zero set makes the correct change to the PC") {
    // check that accumulator is 0, then add 0 to 0 to set SR_Z == 1
    REQUIRE(getRegAC() == 0);
    ADC(0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
    // Branch forward by some number of bytes
    int8 data = 64;
    BEQ(static_cast<byte>(data));
    REQUIRE(getRegPC() == 64);
    // try and branch back
    data = -32;
    BEQ(static_cast<byte>(data));
    REQUIRE(getRegPC() == 32);

    // now clear the zero flag and check the branch does not work
    ADC(5);
    BEQ(static_cast<byte>(data));
    REQUIRE(getRegPC() == 32);

  }

  SECTION("Branching on minus set makes the correct change to the PC") {
    // check that accumulator is 0, then add -1 to 0 to set SR_N == 1
    REQUIRE(getRegAC() == 0);
    ADC(static_cast<byte>(-1));
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);
    // Branch forward by some number of bytes
    int8 data = 64;
    BMI(static_cast<byte>(data));
    REQUIRE(getRegPC() == 64);
    // try and branch back
    data = -32;
    BMI(static_cast<byte>(data));
    REQUIRE(getRegPC() == 32);

    // now clear the negative flag and check the branch does not work
    ADC(5);
    BMI(static_cast<byte>(data));
    REQUIRE(getRegPC() == 32);

  }

  SECTION("Branching on zero clear makes the correct change to the PC") {
    // zero flag should default to zero
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) == 0);
    // Branch forward by some number of bytes
    int8 data = 64;
    BNE(static_cast<byte>(data));
    REQUIRE(getRegPC() == 64);
    // try and branch back
    data = -32;
    BNE(static_cast<byte>(data));
    REQUIRE(getRegPC() == 32);

    // now set the zero flag and check the branch does not work
    ADC(0);
    BNE(static_cast<byte>(data));
    REQUIRE(getRegPC() == 32);

  }

  SECTION("Branching on minus clear makes the correct change to the PC") {
    // minus flag should be unset by default
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) == 0);
    // Branch forward by some number of bytes
    int8 data = 64;
    BPL(static_cast<byte>(data));
    REQUIRE(getRegPC() == 64);
    // try and branch back
    data = -32;
    BPL(static_cast<byte>(data));
    REQUIRE(getRegPC() == 32);

    // now set the negative flag and check the branch does not work
    ADC(static_cast<byte>(-1));
    BPL(static_cast<byte>(data));
    REQUIRE(getRegPC() == 32);

  }
  
  SECTION("Branching on overflow clear makes the correct change to the PC") {
    // overflow flag should be unset by default
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_V) == 0);
    // Branch forward by some number of bytes
    int8 data = 64;
    BVC(static_cast<byte>(data));
    REQUIRE(getRegPC() == 64);
    // try and branch back
    data = -32;
    BVC(static_cast<byte>(data));
    REQUIRE(getRegPC() == 32);

    // now set the overflow flag and check the branch does not work
    SET_OVERFLOW()
    BVC(static_cast<byte>(data));
    REQUIRE(getRegPC() == 32);

  }

  SECTION("Branching on overflow set makes the correct change to the PC") {
    // set the overflow flag
    SET_OVERFLOW();
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_V) != 0);
    // Branch forward by some number of bytes
    int8 data = 64;
    BVS(static_cast<byte>(data));
    REQUIRE(getRegPC() == 64);
    // try and branch back
    data = -32;
    BVS(static_cast<byte>(data));
    REQUIRE(getRegPC() == 32);

    // now clear the overflow flag and check the branch does not work
    CLV();
    BVS(static_cast<byte>(data));
    REQUIRE(getRegPC() == 32);

  }

}

TEST_CASE_METHOD(TestMos6502, "Functionality testing for Mos6502 clear and set instructions",
    "[Mos6502][Clear][Set]") {
  // Status register should be initialized to zero.
  REQUIRE(getRegSR() == 0);
  SECTION("Setting and clearing the decimal bit works correctly") {
    // set the carry bit
    SEC();
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_C) != 0);
    // clear the carry bit
    CLC();
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_C) == 0);
  }

  SECTION("Setting and clearing the decimal flag works correctly") {
    // set the decimal bit
    SED();
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_D) != 0);
    // clear the decimal bit
    CLD();
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_D) == 0);
  }

  SECTION("Setting and clearing the interrupt flag works correctly") {
    // set the interrupt bit
    SEI();
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_I) != 0);
    // clear the interrupt bit
    CLI();
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_I) == 0);
  }

  SECTION("Clearing the overflow flag works correctly") {
    SET_OVERFLOW();
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_V) != 0);
    // clear overflow flag
    CLV();
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_V) == 0);

  }

}

TEST_CASE_METHOD(TestMos6502, "Functionality testing for Mos6502 compare instructions",
    "[Mos6502],[Compare]") {
  // accumulator should initially be set to 0
  REQUIRE(getRegAC() == 0);
  SECTION("Compare with accumulator sets the correct flags") {
    // load accumulator with a value and compare with a greater value
    byte data = 5;
    LDA(data);
    CMP(data + 5);
    REQUIRE_LESS();
    // compare with the same value
    CMP(data);
    REQUIRE_EQUAL();
    // compare with a lesser value
    CMP(data - 3);
    REQUIRE_GREATER();
  }

  SECTION("Compare with X index sets the correct flags") {
    // load y-index with a value and compare with a greater value
    byte data = 5;
    LDX(data);
    CPX(data + 5);
    REQUIRE_LESS();
    // compare with the same value
    CPX(data);
    REQUIRE_EQUAL();
    // compare with a lesser value
    CPX(data - 3);
    REQUIRE_GREATER();
  }

  SECTION("Compare with X index sets the correct flags") {
    // load y-index with a value and compare with a greater value
    byte data = 5;
    LDY(data);
    CPY(data + 5);
    REQUIRE_LESS();
    // compare with the same value
    CPY(data);
    REQUIRE_EQUAL();
    // compare with a lesser value
    CPY(data - 3);
    REQUIRE_GREATER();
  }

}

TEST_CASE_METHOD(TestMos6502, "Functionality testing for Mos6502 decrement instructions",
    "[Mos6502],[Decrement]") {
  SECTION("Memory to memory decrement has the correct behaviour") {
    byte data = 5;
    byte test = DEC(data);
    REQUIRE(test == data - 1);
  }

  SECTION("Memory to memory decrement sets the correct flags") {
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) == 0);
    byte data = 1;
    byte test = DEC(data);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) == 0);
    data = test;
    test = DEC(data);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);
  }

  SECTION("X-index decrement has the correct behaviour") {
    // Load X, decrement then check
    byte data = 5;
    LDX(data);
    DEX();
    REQUIRE(getRegX() == data - 1);
  }

  SECTION("X-index decrement sets the correct flags") {
    LDX(1);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) == 0);
    // 1 - 1 = 0
    DEX();
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) == 0);
    // 0 - 1 = -1
    DEX();
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);
  }

  SECTION("Y-index decrement has the correct behaviour") {
    // Load Y, decrement then check
    byte data = 5;
    LDY(data);
    DEY();
    REQUIRE(getRegY() == data - 1);
  }

  SECTION("Y-index decrement sets the correct flags") {
    LDY(1);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) == 0);
    // 1 - 1 = 0
    DEY();
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) == 0);
    // 0 - 1 = -1
    DEY();
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);
  }

}

TEST_CASE_METHOD(TestMos6502, "Functionality testing for Mos6502 increment instructions",
    "[Mos6502],[Increment]") {
  SECTION("Memory to memory increment has the correct behaviour") {
    byte data = 5;
    byte test = INC(data);
    REQUIRE(test == data + 1);
  }

SECTION("Memory to memory increment sets the correct flags") {
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) == 0);
    byte data = -2;
    byte test = INC(data);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) == 0);
    data = test;
    test = INC(data);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
  }

  SECTION("X-index increment has the correct behaviour") {
    // Load X, increment then check
    byte data = 5;
    LDX(data);
    INX();
    REQUIRE(getRegX() == data + 1);
  }

  SECTION("X-index increment sets the correct flags") {
    LDX(-2);
    // -2 + 1 = -1
    INX();
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) == 0);
    // -1 + 1 = 0
    INX();
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
  }

  SECTION("Y-index increment has the correct behaviour") {
    // Load Y, increment then check
    byte data = 5;
    LDY(data);
    INY();
    REQUIRE(getRegY() == data + 1);
  }

  SECTION("Y-index increment sets the correct flags") {
    LDY(-2);
    // -2 + 1 = -1
    INY();
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) == 0);
    // -1 + 1 = 0
    INY();
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
  }

}

TEST_CASE_METHOD(TestMos6502, "Functionality testing for Mos6502 load instructions",
    "[Mos6502],[Load]") {
  SECTION("Loading the accumulator puts the correct value in register") {
    // Load value and then check correctness
    for(byte i = 1; i <= 10; i++) {
      LDA(i);
      REQUIRE(getRegAC() == i);
    }
  }

  SECTION("Loading the accumulator sets the correct flags") {
    // Load 0 and check flags
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) == 0);
    LDA(0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
    // Load -1 and check flags
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) == 0);
    LDA(-1);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);
  }

  SECTION("Loading the X-index puts the correct value in register") {
    // Load value and then check correctness
    for(byte i = 1; i <= 10; i++) {
      LDX(i);
      REQUIRE(getRegX() == i);
    }
  }

  SECTION("Loading the X-index sets the correct flags") {
    // Load 0 and check flags
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) == 0);
    LDX(0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
    // Load -1 and check flags
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) == 0);
    LDX(-1);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);
  }

  SECTION("Loading the Y-index puts the correct value in register") {
    // Load value and then check correctness
    for(byte i = 1; i <= 10; i++) {
      LDY(i);
      REQUIRE(getRegY() == i);
    }
  }

  SECTION("Loading the Y-index sets the correct flags") {
    // Load 0 and check flags
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) == 0);
    LDY(0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
    // Load -1 and check flags
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) == 0);
    LDY(-1);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);
  }

}

TEST_CASE_METHOD(TestMos6502, "Functionality testing for Mos6502 jump instructions",
    "[Mos6502],[Jump]") {
  // Declare an address object
  Vaddr vaddr;
  // PC should be 0 on initialization
  REQUIRE(getRegPC() == 0);

  SECTION("Jumping to a new pc value has the correct behavior") {
    vaddr.ll = 0x12;
    vaddr.hh = 0x34;
    JMP(vaddr);
    REQUIRE(getRegPC() == 0x3412);
  }

  SECTION("Jumping with return has the correct behaviour") {
    // Set the value of PC to something initially
    vaddr.ll = 0x34;
    vaddr.hh = 0x12;
    JMP(vaddr);
    REQUIRE(getRegPC() == 0x1234);

    // Jump with return to a new address
    vaddr.ll = 0x12;
    vaddr.hh = 0x34;
    JSR(vaddr);
    REQUIRE(getRegPC() == 0x3412);

    // When you return from subroutine, add 3 to original pc
    RTS();
    REQUIRE(getRegPC() == 0x1234);
  }

}

TEST_CASE_METHOD(TestMos6502, "Functionality testing for Mos6502 interrupts",
    "[Mos6502],[Interrupt]") {
  // Setup the processor in some state
  SEC();
  SED();
  CHECK((getRegSR() & Cpu::Mos6502::SR_C) != 0);
  REQUIRE((getRegSR() & Cpu::Mos6502::SR_D) != 0);
  byte oldSR = getRegSR();
  // Jump to some non-trivial location
  Vaddr vaddr = {0x3412};
  JMP(vaddr);
  REQUIRE(getRegPC() == 0x3412);
  addr oldPC = getRegPC();
  SECTION("Breaking and then returning from the interrupt behaves correctly") {
    // Break immediately
    BRK();
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_I) != 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_B) != 0);
    RTI();
    CHECK((getRegSR() & Cpu::Mos6502::SR_I) == 0);
    CHECK(getRegSR() == oldSR);
    REQUIRE(getRegPC() == oldPC + 1);
  }

}

TEST_CASE_METHOD(TestMos6502, "Functionality testing for Mos6502 no op",
    "[Mos6502],[Noop]") {
  // put the Cpu into some non-trivial state
  Vaddr vaddr = {0x3412};
  JMP(vaddr);
  addr oldPC = getRegPC();
  LDA(4);
  byte oldAC = getRegAC();
  LDX(5);
  byte oldX = getRegX();
  LDY(6);
  byte oldY = getRegY();
  SEC();
  SED();
  byte oldSR = getRegSR();
  SECTION("Noop does nothing") {
    NOP();
    CHECK(getRegSR() == oldSR);
    CHECK(getRegY() == oldY);
    CHECK(getRegX() == oldX);
    CHECK(getRegAC() == oldAC);
    REQUIRE(getRegPC() == oldPC);
  }

}

TEST_CASE_METHOD(TestMos6502, "Functionality testing for Mos6502 stack operations",
    "[Mos6502],[Stack]") {
  SECTION("Pushing and pulling the accumulator works correctly") {
    // Loop a few values, pushing onto the stack, pulling off, and then checking
    byte size = 20;
    for(byte i = 1; i <= size; i++) {
      LDA(i);
      PHA();
    }
    REQUIRE((0xFF - size) == getRegSP());
    for(byte i = size; i >= 1; i--) {
      PLA();
      REQUIRE(getRegAC() == i);
    }
    REQUIRE(0xFF == getRegSP());
  }

  SECTION("Pulling accumulator off the stack sets the correct flags") {
    // Load 0 and push onto stack
    LDA(0);
    PHA();
    // Load a different value
    LDA(5);
    PLA();
    CHECK(getRegAC() == 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
    // Load -1 and push onto stack
    LDA(-1);
    PHA();
    // Load a different value
    LDA(5);
    PLA();
    CHECK(getRegAC() == static_cast<byte>(-1));
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);
  }

  SECTION("Pushing and pulling the status register works correctly") {
    // build a non-trivial SR and push onto stack
    SEC();
    SED();
    CHECK((getRegSR() & Cpu::Mos6502::SR_C) != 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_D) != 0);
    byte oldSR = getRegSR();
    // Push to stack and clear SR flags
    PHP();
    CLC();
    CLD();
    REQUIRE(getRegSR() == 0);
    // Pull from stack and check correctness
    PLP();
    CHECK((getRegSR() & Cpu::Mos6502::SR_C) != 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_D) != 0);
  }

}

TEST_CASE_METHOD(TestMos6502, "Functionality testing for Mos6502 store operations",
    "[Mos6502],[Store]") {
  SECTION("Store accumulator works correctly") {
    byte data = 5;
    LDA(data);
    byte test = STA();
    REQUIRE(test == data);
  }

  SECTION("Store X-index works correctly") {
    byte data = 5;
    LDX(data);
    byte test = STX();
    REQUIRE(test == data);
  }

  SECTION("Store Y-index works correctly") {
    byte data = 5;
    LDA(data);
    byte test = STA();
    REQUIRE(test == data);
  }

}

TEST_CASE_METHOD(TestMos6502, "Functionality testing for Mos6502 transfer instructions",
    "[Mos6502],[Transfer]") {
  SECTION("Transfer from accumulator to X-index works correctly") {
    // Load, transfer then check
    LDA(5);
    TAX();
    REQUIRE(getRegX() == 5);
    LDA(0);
    TAX();
    REQUIRE(getRegX() == 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
    LDA(-1);
    TAX();
    REQUIRE(getRegX() == static_cast<byte>(-1));
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);
  }

  SECTION("Transfer from X-index to accumulator works correctly") {
    // Load, transfer then check
    LDX(5);
    TXA();
    REQUIRE(getRegAC() == 5);
    LDX(0);
    TXA();
    REQUIRE(getRegAC() == 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
    LDX(-1);
    TXA();
    REQUIRE(getRegAC() == static_cast<byte>(-1));
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);
  }

  SECTION("Transfer from accumulator to Y-index works correctly") {
    // Load, transfer then check
    LDA(5);
    TAY();
    REQUIRE(getRegY() == 5);
    LDA(0);
    TAY();
    CHECK(getRegY() == 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
    LDA(-1);
    TAY();
    CHECK(getRegY() == static_cast<byte>(-1));
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);
  }

  SECTION("Transfer from Y-index to accumulator works correctly") {
    // Load, transfer then check
    LDY(5);
    TYA();
    REQUIRE(getRegAC() == 5);
    LDY(0);
    TYA();
    REQUIRE(getRegAC() == 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
    LDY(-1);
    TYA();
    REQUIRE(getRegAC() == static_cast<byte>(-1));
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);
  }

  SECTION("Transfer from X-index to stack pointer works correctly") {
    // Load, transfer then check
    LDX(5);
    TXS();
    REQUIRE(getRegSP() == 5);
    LDX(0);
    TXS();
    REQUIRE(getRegSP() == 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
    LDX(-1);
    TXS();
    REQUIRE(getRegSP() == static_cast<byte>(-1));
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0);   
  }

  SECTION("Transfer from stack pointer to X-index works correctly") {
    // Load, transfer to SP, load new value, transfer back and check;
    LDX(5);
    TXS();
    LDX(10);
    TSX();
    REQUIRE(getRegX() == 5);
    LDX(0);
    TXS();
    LDX(10);
    TSX();
    REQUIRE(getRegX() == 0);
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_Z) != 0);
    LDX(-1);
    TXS();
    LDX(10);
    TSX();
    REQUIRE(getRegX() == static_cast<byte>(-1));
    REQUIRE((getRegSR() & Cpu::Mos6502::SR_N) != 0); 
  }

}
