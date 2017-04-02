//===-- tests/cpu/TestMos6502Disassembler.cpp - Disassembler Test *- C++ -*===//
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
#include "tests/catch.hpp"
#include "common/CommonTypes.h"
#include "memory/Mapper.h"
#include "memory/Bank.h"
#include "memory/Ram.h"
#include "cpu/CpuException.h"
#include "cpu/Mos6502_Ops.h"
#include "cpu/Mos6502Disassembler.h"

using namespace Memory;
using namespace Cpu;

/// This function will load the first 3 bytes of a ram with the values x, y and
/// z.
/// \param x First byte.
/// \param y Second byte.
/// \param z Third byte.
static inline void loadRam(
    std::shared_ptr<Ram<byte>> ramPtr, 
    byte x, 
    byte y = -1, 
    byte z = -1) {
  ramPtr->write(0, x);
  ramPtr->write(1, y);
  ramPtr->write(2, z);
}

TEST_CASE("The Mos6502 disassembler has the correct functionality.",
    "[Mos6502],[Disassembler]") {
  // Build a Ram object
  std::size_t size = 100;
  std::shared_ptr<Ram<byte>> ramPtr(new Ram<byte>(size));
  REQUIRE(ramPtr->getSize() == size);

  // build a disassembler
  Mos6502Disassembler dis;

  SECTION("ADC immediate instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ADC_IMMED, 0x0F); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ADC_IMMED);
    CHECK(inst.name == "ADC");
    CHECK(inst.addr == "#");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("ADC zeropage instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ADC_ZPG, 0x0F); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ADC_ZPG);
    CHECK(inst.name == "ADC");
    CHECK(inst.addr == "zpg");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 3);
    
  }

  SECTION("ADC zeropage X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ADC_ZPG_X, 0x0F); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ADC_ZPG_X);
    CHECK(inst.name == "ADC");
    CHECK(inst.addr == "zpg,X");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("ADC absolute instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ADC_ABS, 0x0F, 0xF0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ADC_ABS);
    CHECK(inst.name == "ADC");
    CHECK(inst.addr == "abs");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0xF0);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("ADC absolute X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ADC_ABS_X, 0x0F, 0xF0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ADC_ABS_X);
    CHECK(inst.name == "ADC");
    CHECK(inst.addr == "abs,X");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0xF0);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("ADC absolute Y-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ADC_ABS_Y, 0x0F, 0xF0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ADC_ABS_Y);
    CHECK(inst.name == "ADC");
    CHECK(inst.addr == "abs,Y");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0xF0);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("ADC X-indirect instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ADC_X_IND, 0x0F); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ADC_X_IND);
    CHECK(inst.name == "ADC");
    CHECK(inst.addr == "X,ind");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 6);
    
  }
  
  SECTION("ADC indirect-Y instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ADC_IND_Y, 0x0F); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ADC_IND_Y);
    CHECK(inst.name == "ADC");
    CHECK(inst.addr == "ind,Y");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 5);
    
  }

  SECTION("AND immediate instruction disassembles correctly.") {
    loadRam(ramPtr, Op::AND_IMMED, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::AND_IMMED);
    CHECK(inst.name == "AND");
    CHECK(inst.addr == "#");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("AND zeropage instruction disassembles correctly.") {
    loadRam(ramPtr, Op::AND_ZPG, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::AND_ZPG);
    CHECK(inst.name == "AND");
    CHECK(inst.addr == "zpg");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 3);
    
  }

  SECTION("AND zeropage X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::AND_ZPG_X, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::AND_ZPG_X);
    CHECK(inst.name == "AND");
    CHECK(inst.addr == "zpg,X");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("AND absolute instruction disassembles correctly.") {
    loadRam(ramPtr, Op::AND_ABS, 0x0E, 0xE0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::AND_ABS);
    CHECK(inst.name == "AND");
    CHECK(inst.addr == "abs");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0xE0);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("AND absolute X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::AND_ABS_X, 0x0E, 0xE0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::AND_ABS_X);
    CHECK(inst.name == "AND");
    CHECK(inst.addr == "abs,X");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0xE0);
    CHECK(inst.cycles == 4);
    
  }
 
  SECTION("AND absolute Y-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::AND_ABS_Y, 0x0E, 0xE0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::AND_ABS_Y);
    CHECK(inst.name == "AND");
    CHECK(inst.addr == "abs,Y");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0xE0);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("AND X-indirect instruction disassembles correctly.") {
    loadRam(ramPtr, Op::AND_X_IND, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::AND_X_IND);
    CHECK(inst.name == "AND");
    CHECK(inst.addr == "X,ind");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 6);
    
  }

  SECTION("AND indirect-Y instruction disassembles correctly.") {
    loadRam(ramPtr, Op::AND_IND_Y, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::AND_IND_Y);
    CHECK(inst.name == "AND");
    CHECK(inst.addr == "ind,Y");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 5);
    
  }

  SECTION("ASL accumulator instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ASL_ACC); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ASL_ACC);
    CHECK(inst.name == "ASL");
    CHECK(inst.addr == "A");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("ASL zeropage instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ASL_ZPG, 0x0D); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ASL_ZPG);
    CHECK(inst.name == "ASL");
    CHECK(inst.addr == "zpg");
    CHECK(inst.operand.lo == 0x0D);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 5);
    
  }

  SECTION("ASL zeropage X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ASL_ZPG_X, 0x0D); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ASL_ZPG_X);
    CHECK(inst.name == "ASL");
    CHECK(inst.addr == "zpg,X");
    CHECK(inst.operand.lo == 0x0D);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 6);
    
  }

  SECTION("ASL absolute instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ASL_ABS, 0x0D, 0xD0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ASL_ABS);
    CHECK(inst.name == "ASL");
    CHECK(inst.addr == "abs");
    CHECK(inst.operand.lo == 0x0D);
    CHECK(inst.operand.hi == 0xD0);
    CHECK(inst.cycles == 6);
    
  }

  SECTION("ASL absolute X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ASL_ABS_X, 0x0D, 0xD0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ASL_ABS_X);
    CHECK(inst.name == "ASL");
    CHECK(inst.addr == "abs,X");
    CHECK(inst.operand.lo == 0x0D);
    CHECK(inst.operand.hi == 0xD0);
    CHECK(inst.cycles == 7);
    
  }

}

TEST_CASE("Invalid opcode will throw the correct exception.",
    "[Mos6502],[Disassembler]") {
  // Build a Ram object
  std::size_t size = 100;
  std::shared_ptr<Ram<byte>> ramPtr(new Ram<byte>(size));
  REQUIRE(ramPtr->getSize() == size);

  // build a disassembler
  Mos6502Disassembler dis;

  loadRam(
      ramPtr, 
      0x02, // invalid opcode
      0x32,
      0x00);
  Reference<byte> ref(ramPtr, 0);

  REQUIRE_THROWS_AS(dis.disassembleInstruction(ref), 
      Exception::InvalidOpcodeException);

}    

