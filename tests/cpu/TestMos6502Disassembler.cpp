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

  SECTION("BIT zeropage instruction disassembles correctly.") {
    loadRam(ramPtr, Op::BIT_ZPG, 0x0C); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::BIT_ZPG);
    CHECK(inst.name == "BIT");
    CHECK(inst.addr == "zpg");
    CHECK(inst.operand.lo == 0x0C);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 3);
    
  }

  SECTION("BIT absolute instruction disassembles correctly.") {
    loadRam(ramPtr, Op::BIT_ABS, 0x0C, 0xC0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::BIT_ABS);
    CHECK(inst.name == "BIT");
    CHECK(inst.addr == "abs");
    CHECK(inst.operand.lo == 0x0C);
    CHECK(inst.operand.hi == 0xC0);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("BPL relative instruction disassembles correctly.") {
    loadRam(ramPtr, Op::BPL_REL, 0x0C); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::BPL_REL);
    CHECK(inst.name == "BPL");
    CHECK(inst.addr == "rel");
    CHECK(inst.operand.lo == 0x0C);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("BMI relative instruction disassembles correctly.") {
    loadRam(ramPtr, Op::BMI_REL, 0x0C); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::BMI_REL);
    CHECK(inst.name == "BMI");
    CHECK(inst.addr == "rel");
    CHECK(inst.operand.lo == 0x0C);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("BVC relative instruction disassembles correctly.") {
    loadRam(ramPtr, Op::BVC_REL, 0x0C); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::BVC_REL);
    CHECK(inst.name == "BVC");
    CHECK(inst.addr == "rel");
    CHECK(inst.operand.lo == 0x0C);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("BVS relative instruction disassembles correctly.") {
    loadRam(ramPtr, Op::BVS_REL, 0x0C); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::BVS_REL);
    CHECK(inst.name == "BVS");
    CHECK(inst.addr == "rel");
    CHECK(inst.operand.lo == 0x0C);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("BCC relative instruction disassembles correctly.") {
    loadRam(ramPtr, Op::BCC_REL, 0x0C); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::BCC_REL);
    CHECK(inst.name == "BCC");
    CHECK(inst.addr == "rel");
    CHECK(inst.operand.lo == 0x0C);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("BCS relative instruction disassembles correctly.") {
    loadRam(ramPtr, Op::BCS_REL, 0x0C); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::BCS_REL);
    CHECK(inst.name == "BCS");
    CHECK(inst.addr == "rel");
    CHECK(inst.operand.lo == 0x0C);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("BNE relative instruction disassembles correctly.") {
    loadRam(ramPtr, Op::BNE_REL, 0x0C); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::BNE_REL);
    CHECK(inst.name == "BNE");
    CHECK(inst.addr == "rel");
    CHECK(inst.operand.lo == 0x0C);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("BEQ relative instruction disassembles correctly.") {
    loadRam(ramPtr, Op::BEQ_REL, 0x0C); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::BEQ_REL);
    CHECK(inst.name == "BEQ");
    CHECK(inst.addr == "rel");
    CHECK(inst.operand.lo == 0x0C);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("BRK implied instruction disassembles correctly.") {
    loadRam(ramPtr, Op::BRK_IMPL); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::BRK_IMPL);
    CHECK(inst.name == "BRK");
    CHECK(inst.addr == "impl");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 7);
    
  }

  SECTION("CMP immediate instruction disassembles correctly.") {
    loadRam(ramPtr, Op::CMP_IMMED, 0x0B); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::CMP_IMMED);
    CHECK(inst.name == "CMP");
    CHECK(inst.addr == "#");
    CHECK(inst.operand.lo == 0x0B);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("CMP zeropage instruction disassembles correctly.") {
    loadRam(ramPtr, Op::CMP_ZPG, 0x0B); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::CMP_ZPG);
    CHECK(inst.name == "CMP");
    CHECK(inst.addr == "zpg");
    CHECK(inst.operand.lo == 0x0B);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 3);
    
  }

  SECTION("CMP zeropage X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::CMP_ZPG_X, 0x0B); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::CMP_ZPG_X);
    CHECK(inst.name == "CMP");
    CHECK(inst.addr == "zpg,X");
    CHECK(inst.operand.lo == 0x0B);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("CMP absolute instruction disassembles correctly.") {
    loadRam(ramPtr, Op::CMP_ABS, 0x0B, 0xB0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::CMP_ABS);
    CHECK(inst.name == "CMP");
    CHECK(inst.addr == "abs");
    CHECK(inst.operand.lo == 0x0B);
    CHECK(inst.operand.hi == 0xB0);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("CMP absolute X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::CMP_ABS_X, 0x0B, 0xB0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::CMP_ABS_X);
    CHECK(inst.name == "CMP");
    CHECK(inst.addr == "abs,X");
    CHECK(inst.operand.lo == 0x0B);
    CHECK(inst.operand.hi == 0xB0);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("CMP absolute Y-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::CMP_ABS_Y, 0x0B, 0xB0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::CMP_ABS_Y);
    CHECK(inst.name == "CMP");
    CHECK(inst.addr == "abs,Y");
    CHECK(inst.operand.lo == 0x0B);
    CHECK(inst.operand.hi == 0xB0);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("CMP X-indexed indirect instruction disassembles correctly.") {
    loadRam(ramPtr, Op::CMP_X_IND, 0x0B); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::CMP_X_IND);
    CHECK(inst.name == "CMP");
    CHECK(inst.addr == "X,ind");
    CHECK(inst.operand.lo == 0x0B);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 6);
    
  }

  SECTION("CMP indirect Y-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::CMP_IND_Y, 0x0B); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::CMP_IND_Y);
    CHECK(inst.name == "CMP");
    CHECK(inst.addr == "ind,Y");
    CHECK(inst.operand.lo == 0x0B);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 5);
    
  }

  SECTION("CPX immediate instruction disassembles correctly.") {
    loadRam(ramPtr, Op::CPX_IMMED, 0x0B); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::CPX_IMMED);
    CHECK(inst.name == "CPX");
    CHECK(inst.addr == "#");
    CHECK(inst.operand.lo == 0x0B);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("CPX zeropage instruction disassembles correctly.") {
    loadRam(ramPtr, Op::CPX_ZPG, 0x0B); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::CPX_ZPG);
    CHECK(inst.name == "CPX");
    CHECK(inst.addr == "zpg");
    CHECK(inst.operand.lo == 0x0B);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 3);
    
  }

  SECTION("CPX absolute instruction disassembles correctly.") {
    loadRam(ramPtr, Op::CPX_ABS, 0x0B, 0xB0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::CPX_ABS);
    CHECK(inst.name == "CPX");
    CHECK(inst.addr == "abs");
    CHECK(inst.operand.lo == 0x0B);
    CHECK(inst.operand.hi == 0xB0);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("CPY immediate instruction disassembles correctly.") {
    loadRam(ramPtr, Op::CPY_IMMED, 0x0B); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::CPY_IMMED);
    CHECK(inst.name == "CPY");
    CHECK(inst.addr == "#");
    CHECK(inst.operand.lo == 0x0B);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("CPY zeropage instruction disassembles correctly.") {
    loadRam(ramPtr, Op::CPY_ZPG, 0x0B); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::CPY_ZPG);
    CHECK(inst.name == "CPY");
    CHECK(inst.addr == "zpg");
    CHECK(inst.operand.lo == 0x0B);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 3);
    
  }

  SECTION("CPY absolute instruction disassembles correctly.") {
    loadRam(ramPtr, Op::CPY_ABS, 0x0B, 0xB0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::CPY_ABS);
    CHECK(inst.name == "CPY");
    CHECK(inst.addr == "abs");
    CHECK(inst.operand.lo == 0x0B);
    CHECK(inst.operand.hi == 0xB0);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("DEC zeropage instruction disassembles correctly.") {
    loadRam(ramPtr, Op::DEC_ZPG, 0x0A); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::DEC_ZPG);
    CHECK(inst.name == "DEC");
    CHECK(inst.addr == "zpg");
    CHECK(inst.operand.lo == 0x0A);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 5);
    
  }

  SECTION("DEC zeropage X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::DEC_ZPG_X, 0x0A); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::DEC_ZPG_X);
    CHECK(inst.name == "DEC");
    CHECK(inst.addr == "zpg,X");
    CHECK(inst.operand.lo == 0x0A);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 6);
    
  }

  SECTION("DEC absolute instruction disassembles correctly.") {
    loadRam(ramPtr, Op::DEC_ABS, 0x0A, 0xA0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::DEC_ABS);
    CHECK(inst.name == "DEC");
    CHECK(inst.addr == "abs");
    CHECK(inst.operand.lo == 0x0A);
    CHECK(inst.operand.hi == 0xA0);
    CHECK(inst.cycles == 6);
    
  }

  SECTION("DEC absolute X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::DEC_ABS_X, 0x0A, 0xA0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::DEC_ABS_X);
    CHECK(inst.name == "DEC");
    CHECK(inst.addr == "abs,X");
    CHECK(inst.operand.lo == 0x0A);
    CHECK(inst.operand.hi == 0xA0);
    CHECK(inst.cycles == 7);
    
  }

  SECTION("EOR immediate instruction disassembles correctly.") {
    loadRam(ramPtr, Op::EOR_IMMED, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::EOR_IMMED);
    CHECK(inst.name == "EOR");
    CHECK(inst.addr == "#");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("EOR zeropage instruction disassembles correctly.") {
    loadRam(ramPtr, Op::EOR_ZPG, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::EOR_ZPG);
    CHECK(inst.name == "EOR");
    CHECK(inst.addr == "zpg");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 3);
    
  }

  SECTION("EOR zeropage X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::EOR_ZPG_X, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::EOR_ZPG_X);
    CHECK(inst.name == "EOR");
    CHECK(inst.addr == "zpg,X");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("EOR absolute instruction disassembles correctly.") {
    loadRam(ramPtr, Op::EOR_ABS, 0x0E, 0xE0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::EOR_ABS);
    CHECK(inst.name == "EOR");
    CHECK(inst.addr == "abs");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0xE0);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("EOR absolute X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::EOR_ABS_X, 0x0E, 0xE0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::EOR_ABS_X);
    CHECK(inst.name == "EOR");
    CHECK(inst.addr == "abs,X");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0xE0);
    CHECK(inst.cycles == 4);
    
  }
 
  SECTION("EOR absolute Y-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::EOR_ABS_Y, 0x0E, 0xE0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::EOR_ABS_Y);
    CHECK(inst.name == "EOR");
    CHECK(inst.addr == "abs,Y");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0xE0);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("EOR X-indirect instruction disassembles correctly.") {
    loadRam(ramPtr, Op::EOR_X_IND, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::EOR_X_IND);
    CHECK(inst.name == "EOR");
    CHECK(inst.addr == "X,ind");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 6);
    
  }

  SECTION("EOR indirect-Y instruction disassembles correctly.") {
    loadRam(ramPtr, Op::EOR_IND_Y, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::EOR_IND_Y);
    CHECK(inst.name == "EOR");
    CHECK(inst.addr == "ind,Y");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 5);
    
  }

  SECTION("CLC implied instruction disassembles correctly.") {
    loadRam(ramPtr, Op::CLC_IMPL);
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::CLC_IMPL);
    CHECK(inst.name == "CLC");
    CHECK(inst.addr == "impl");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("SEC implied instruction disassembles correctly.") {
    loadRam(ramPtr, Op::SEC_IMPL);
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::SEC_IMPL);
    CHECK(inst.name == "SEC");
    CHECK(inst.addr == "impl");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("CLI implied instruction disassembles correctly.") {
    loadRam(ramPtr, Op::CLI_IMPL);
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::CLI_IMPL);
    CHECK(inst.name == "CLI");
    CHECK(inst.addr == "impl");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("SEI implied instruction disassembles correctly.") {
    loadRam(ramPtr, Op::SEI_IMPL);
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::SEI_IMPL);
    CHECK(inst.name == "SEI");
    CHECK(inst.addr == "impl");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("CLV implied instruction disassembles correctly.") {
    loadRam(ramPtr, Op::CLV_IMPL);
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::CLV_IMPL);
    CHECK(inst.name == "CLV");
    CHECK(inst.addr == "impl");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("CLD implied instruction disassembles correctly.") {
    loadRam(ramPtr, Op::CLD_IMPL);
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::CLD_IMPL);
    CHECK(inst.name == "CLD");
    CHECK(inst.addr == "impl");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("SED implied instruction disassembles correctly.") {
    loadRam(ramPtr, Op::SED_IMPL);
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::SED_IMPL);
    CHECK(inst.name == "SED");
    CHECK(inst.addr == "impl");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("INC zeropage instruction disassembles correctly.") {
    loadRam(ramPtr, Op::INC_ZPG, 0x0A); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::INC_ZPG);
    CHECK(inst.name == "INC");
    CHECK(inst.addr == "zpg");
    CHECK(inst.operand.lo == 0x0A);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 5);
    
  }

  SECTION("INC zeropage X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::INC_ZPG_X, 0x0A); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::INC_ZPG_X);
    CHECK(inst.name == "INC");
    CHECK(inst.addr == "zpg,X");
    CHECK(inst.operand.lo == 0x0A);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 6);
    
  }

  SECTION("INC absolute instruction disassembles correctly.") {
    loadRam(ramPtr, Op::INC_ABS, 0x0A, 0xA0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::INC_ABS);
    CHECK(inst.name == "INC");
    CHECK(inst.addr == "abs");
    CHECK(inst.operand.lo == 0x0A);
    CHECK(inst.operand.hi == 0xA0);
    CHECK(inst.cycles == 6);
    
  }

  SECTION("INC absolute X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::INC_ABS_X, 0x0A, 0xA0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::INC_ABS_X);
    CHECK(inst.name == "INC");
    CHECK(inst.addr == "abs,X");
    CHECK(inst.operand.lo == 0x0A);
    CHECK(inst.operand.hi == 0xA0);
    CHECK(inst.cycles == 7);
    
  }

  SECTION("JMP absolute instruction disassembles correctly.") {
    loadRam(ramPtr, Op::JMP_ABS, 0x0A, 0xA0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::JMP_ABS);
    CHECK(inst.name == "JMP");
    CHECK(inst.addr == "abs");
    CHECK(inst.operand.lo == 0x0A);
    CHECK(inst.operand.hi == 0xA0);
    CHECK(inst.cycles == 3);
    
  }

  SECTION("JMP indirect instruction disassembles correctly.") {
    loadRam(ramPtr, Op::JMP_IND, 0x0A, 0xA0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::JMP_IND);
    CHECK(inst.name == "JMP");
    CHECK(inst.addr == "ind");
    CHECK(inst.operand.lo == 0x0A);
    CHECK(inst.operand.hi == 0xA0);
    CHECK(inst.cycles == 5);
    
  }

  SECTION("JSR absolute instruction disassembles correctly.") {
    loadRam(ramPtr, Op::JSR_ABS, 0x0A, 0xA0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::JSR_ABS);
    CHECK(inst.name == "JSR");
    CHECK(inst.addr == "abs");
    CHECK(inst.operand.lo == 0x0A);
    CHECK(inst.operand.hi == 0xA0);
    CHECK(inst.cycles == 6);
    
  }

  SECTION("LDA immediate instruction disassembles correctly.") {
    loadRam(ramPtr, Op::LDA_IMMED, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::LDA_IMMED);
    CHECK(inst.name == "LDA");
    CHECK(inst.addr == "#");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("LDA zeropage instruction disassembles correctly.") {
    loadRam(ramPtr, Op::LDA_ZPG, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::LDA_ZPG);
    CHECK(inst.name == "LDA");
    CHECK(inst.addr == "zpg");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 3);
    
  }

  SECTION("LDA zeropage X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::LDA_ZPG_X, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::LDA_ZPG_X);
    CHECK(inst.name == "LDA");
    CHECK(inst.addr == "zpg,X");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("LDA absolute instruction disassembles correctly.") {
    loadRam(ramPtr, Op::LDA_ABS, 0x0E, 0xE0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::LDA_ABS);
    CHECK(inst.name == "LDA");
    CHECK(inst.addr == "abs");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0xE0);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("LDA absolute X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::LDA_ABS_X, 0x0E, 0xE0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::LDA_ABS_X);
    CHECK(inst.name == "LDA");
    CHECK(inst.addr == "abs,X");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0xE0);
    CHECK(inst.cycles == 4);
    
  }
 
  SECTION("LDA absolute Y-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::LDA_ABS_Y, 0x0E, 0xE0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::LDA_ABS_Y);
    CHECK(inst.name == "LDA");
    CHECK(inst.addr == "abs,Y");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0xE0);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("LDA X-indirect instruction disassembles correctly.") {
    loadRam(ramPtr, Op::LDA_X_IND, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::LDA_X_IND);
    CHECK(inst.name == "LDA");
    CHECK(inst.addr == "X,ind");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 6);
    
  }

  SECTION("LDA indirect-Y instruction disassembles correctly.") {
    loadRam(ramPtr, Op::LDA_IND_Y, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::LDA_IND_Y);
    CHECK(inst.name == "LDA");
    CHECK(inst.addr == "ind,Y");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 5);
    
  }

  SECTION("LDX immediate instruction disassembles correctly.") {
    loadRam(ramPtr, Op::LDX_IMMED, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::LDX_IMMED);
    CHECK(inst.name == "LDX");
    CHECK(inst.addr == "#");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("LDX zeropage instruction disassembles correctly.") {
    loadRam(ramPtr, Op::LDX_ZPG, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::LDX_ZPG);
    CHECK(inst.name == "LDX");
    CHECK(inst.addr == "zpg");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 3);
    
  }

  SECTION("LDX zeropage X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::LDX_ZPG_Y, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::LDX_ZPG_Y);
    CHECK(inst.name == "LDX");
    CHECK(inst.addr == "zpg,Y");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("LDX absolute instruction disassembles correctly.") {
    loadRam(ramPtr, Op::LDX_ABS, 0x0E, 0xE0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::LDX_ABS);
    CHECK(inst.name == "LDX");
    CHECK(inst.addr == "abs");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0xE0);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("LDX absolute X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::LDX_ABS_Y, 0x0E, 0xE0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::LDX_ABS_Y);
    CHECK(inst.name == "LDX");
    CHECK(inst.addr == "abs,Y");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0xE0);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("LDY immediate instruction disassembles correctly.") {
    loadRam(ramPtr, Op::LDY_IMMED, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::LDY_IMMED);
    CHECK(inst.name == "LDY");
    CHECK(inst.addr == "#");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("LDY zeropage instruction disassembles correctly.") {
    loadRam(ramPtr, Op::LDY_ZPG, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::LDY_ZPG);
    CHECK(inst.name == "LDY");
    CHECK(inst.addr == "zpg");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 3);
    
  }

  SECTION("LDY zeropage X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::LDY_ZPG_X, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::LDY_ZPG_X);
    CHECK(inst.name == "LDY");
    CHECK(inst.addr == "zpg,X");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("LDY absolute instruction disassembles correctly.") {
    loadRam(ramPtr, Op::LDY_ABS, 0x0E, 0xE0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::LDY_ABS);
    CHECK(inst.name == "LDY");
    CHECK(inst.addr == "abs");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0xE0);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("LDY absolute X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::LDY_ABS_X, 0x0E, 0xE0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::LDY_ABS_X);
    CHECK(inst.name == "LDY");
    CHECK(inst.addr == "abs,X");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0xE0);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("LSR accumulator instruction disassembles correctly.") {
    loadRam(ramPtr, Op::LSR_ACC); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::LSR_ACC);
    CHECK(inst.name == "LSR");
    CHECK(inst.addr == "A");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("LSR zeropage instruction disassembles correctly.") {
    loadRam(ramPtr, Op::LSR_ZPG, 0x0D); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::LSR_ZPG);
    CHECK(inst.name == "LSR");
    CHECK(inst.addr == "zpg");
    CHECK(inst.operand.lo == 0x0D);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 5);
    
  }

  SECTION("LSR zeropage X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::LSR_ZPG_X, 0x0D); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::LSR_ZPG_X);
    CHECK(inst.name == "LSR");
    CHECK(inst.addr == "zpg,X");
    CHECK(inst.operand.lo == 0x0D);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 6);
    
  }

  SECTION("LSR absolute instruction disassembles correctly.") {
    loadRam(ramPtr, Op::LSR_ABS, 0x0D, 0xD0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::LSR_ABS);
    CHECK(inst.name == "LSR");
    CHECK(inst.addr == "abs");
    CHECK(inst.operand.lo == 0x0D);
    CHECK(inst.operand.hi == 0xD0);
    CHECK(inst.cycles == 6);
    
  }

  SECTION("LSR absolute X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::LSR_ABS_X, 0x0D, 0xD0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::LSR_ABS_X);
    CHECK(inst.name == "LSR");
    CHECK(inst.addr == "abs,X");
    CHECK(inst.operand.lo == 0x0D);
    CHECK(inst.operand.hi == 0xD0);
    CHECK(inst.cycles == 7);
    
  }

  SECTION("NOP implied instruction disassembles correctly.") {
    loadRam(ramPtr, Op::NOP_IMPL); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::NOP_IMPL);
    CHECK(inst.name == "NOP");
    CHECK(inst.addr == "impl");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("ORA immediate instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ORA_IMMED, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ORA_IMMED);
    CHECK(inst.name == "ORA");
    CHECK(inst.addr == "#");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("ORA zeropage instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ORA_ZPG, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ORA_ZPG);
    CHECK(inst.name == "ORA");
    CHECK(inst.addr == "zpg");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 3);
    
  }

  SECTION("ORA zeropage X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ORA_ZPG_X, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ORA_ZPG_X);
    CHECK(inst.name == "ORA");
    CHECK(inst.addr == "zpg,X");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("ORA absolute instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ORA_ABS, 0x0E, 0xE0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ORA_ABS);
    CHECK(inst.name == "ORA");
    CHECK(inst.addr == "abs");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0xE0);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("ORA absolute X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ORA_ABS_X, 0x0E, 0xE0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ORA_ABS_X);
    CHECK(inst.name == "ORA");
    CHECK(inst.addr == "abs,X");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0xE0);
    CHECK(inst.cycles == 4);
    
  }
 
  SECTION("ORA absolute Y-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ORA_ABS_Y, 0x0E, 0xE0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ORA_ABS_Y);
    CHECK(inst.name == "ORA");
    CHECK(inst.addr == "abs,Y");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0xE0);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("ORA X-indirect instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ORA_X_IND, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ORA_X_IND);
    CHECK(inst.name == "ORA");
    CHECK(inst.addr == "X,ind");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 6);
    
  }

  SECTION("ORA X-indirect instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ORA_IND_Y, 0x0E); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ORA_IND_Y);
    CHECK(inst.name == "ORA");
    CHECK(inst.addr == "ind,Y");
    CHECK(inst.operand.lo == 0x0E);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 5);
    
  }

  SECTION("TAX implied instruction disassembles correctly.") {
    loadRam(ramPtr, Op::TAX_IMPL); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::TAX_IMPL);
    CHECK(inst.name == "TAX");
    CHECK(inst.addr == "impl");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }
  
  SECTION("TXA implied instruction disassembles correctly.") {
    loadRam(ramPtr, Op::TXA_IMPL); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::TXA_IMPL);
    CHECK(inst.name == "TXA");
    CHECK(inst.addr == "impl");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }
  
  SECTION("DEX implied instruction disassembles correctly.") {
    loadRam(ramPtr, Op::DEX_IMPL); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::DEX_IMPL);
    CHECK(inst.name == "DEX");
    CHECK(inst.addr == "impl");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }
  
  SECTION("INX implied instruction disassembles correctly.") {
    loadRam(ramPtr, Op::INX_IMPL); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::INX_IMPL);
    CHECK(inst.name == "INX");
    CHECK(inst.addr == "impl");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("TAY implied instruction disassembles correctly.") {
    loadRam(ramPtr, Op::TAY_IMPL); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::TAY_IMPL);
    CHECK(inst.name == "TAY");
    CHECK(inst.addr == "impl");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }
  
  SECTION("TYA implied instruction disassembles correctly.") {
    loadRam(ramPtr, Op::TYA_IMPL); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::TYA_IMPL);
    CHECK(inst.name == "TYA");
    CHECK(inst.addr == "impl");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }
  
  SECTION("DEY implied instruction disassembles correctly.") {
    loadRam(ramPtr, Op::DEY_IMPL); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::DEY_IMPL);
    CHECK(inst.name == "DEY");
    CHECK(inst.addr == "impl");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }
  
  SECTION("INY implied instruction disassembles correctly.") {
    loadRam(ramPtr, Op::INY_IMPL); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::INY_IMPL);
    CHECK(inst.name == "INY");
    CHECK(inst.addr == "impl");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("ROL accumulator instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ROL_ACC); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ROL_ACC);
    CHECK(inst.name == "ROL");
    CHECK(inst.addr == "A");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("ROL zeropage instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ROL_ZPG, 0x0D); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ROL_ZPG);
    CHECK(inst.name == "ROL");
    CHECK(inst.addr == "zpg");
    CHECK(inst.operand.lo == 0x0D);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 5);
    
  }

  SECTION("ROL zeropage X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ROL_ZPG_X, 0x0D); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ROL_ZPG_X);
    CHECK(inst.name == "ROL");
    CHECK(inst.addr == "zpg,X");
    CHECK(inst.operand.lo == 0x0D);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 6);
    
  }

  SECTION("ROL absolute instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ROL_ABS, 0x0D, 0xD0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ROL_ABS);
    CHECK(inst.name == "ROL");
    CHECK(inst.addr == "abs");
    CHECK(inst.operand.lo == 0x0D);
    CHECK(inst.operand.hi == 0xD0);
    CHECK(inst.cycles == 6);
    
  }

  SECTION("ROL absolute X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ROL_ABS_X, 0x0D, 0xD0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ROL_ABS_X);
    CHECK(inst.name == "ROL");
    CHECK(inst.addr == "abs,X");
    CHECK(inst.operand.lo == 0x0D);
    CHECK(inst.operand.hi == 0xD0);
    CHECK(inst.cycles == 7);
    
  }

  SECTION("ROR accumulator instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ROR_ACC); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ROR_ACC);
    CHECK(inst.name == "ROR");
    CHECK(inst.addr == "A");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("ROR zeropage instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ROR_ZPG, 0x0D); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ROR_ZPG);
    CHECK(inst.name == "ROR");
    CHECK(inst.addr == "zpg");
    CHECK(inst.operand.lo == 0x0D);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 5);
    
  }

  SECTION("ROR zeropage X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ROR_ZPG_X, 0x0D); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ROR_ZPG_X);
    CHECK(inst.name == "ROR");
    CHECK(inst.addr == "zpg,X");
    CHECK(inst.operand.lo == 0x0D);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 6);
    
  }

  SECTION("ROR absolute instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ROR_ABS, 0x0D, 0xD0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ROR_ABS);
    CHECK(inst.name == "ROR");
    CHECK(inst.addr == "abs");
    CHECK(inst.operand.lo == 0x0D);
    CHECK(inst.operand.hi == 0xD0);
    CHECK(inst.cycles == 6);
    
  }

  SECTION("ROR absolute X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::ROR_ABS_X, 0x0D, 0xD0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::ROR_ABS_X);
    CHECK(inst.name == "ROR");
    CHECK(inst.addr == "abs,X");
    CHECK(inst.operand.lo == 0x0D);
    CHECK(inst.operand.hi == 0xD0);
    CHECK(inst.cycles == 7);
    
  }
  
  SECTION("RTI implied instruction disassembles correctly.") {
    loadRam(ramPtr, Op::RTI_IMPL); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::RTI_IMPL);
    CHECK(inst.name == "RTI");
    CHECK(inst.addr == "impl");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 6);
    
  }
  
  SECTION("RTS implied instruction disassembles correctly.") {
    loadRam(ramPtr, Op::RTS_IMPL); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::RTS_IMPL);
    CHECK(inst.name == "RTS");
    CHECK(inst.addr == "impl");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 6);
    
  }

  SECTION("SBC immediate instruction disassembles correctly.") {
    loadRam(ramPtr, Op::SBC_IMMED, 0x0F); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::SBC_IMMED);
    CHECK(inst.name == "SBC");
    CHECK(inst.addr == "#");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }

  SECTION("SBC zeropage instruction disassembles correctly.") {
    loadRam(ramPtr, Op::SBC_ZPG, 0x0F); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::SBC_ZPG);
    CHECK(inst.name == "SBC");
    CHECK(inst.addr == "zpg");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 3);
    
  }

  SECTION("SBC zeropage X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::SBC_ZPG_X, 0x0F); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::SBC_ZPG_X);
    CHECK(inst.name == "SBC");
    CHECK(inst.addr == "zpg,X");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("SBC absolute instruction disassembles correctly.") {
    loadRam(ramPtr, Op::SBC_ABS, 0x0F, 0xF0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::SBC_ABS);
    CHECK(inst.name == "SBC");
    CHECK(inst.addr == "abs");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0xF0);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("SBC absolute X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::SBC_ABS_X, 0x0F, 0xF0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::SBC_ABS_X);
    CHECK(inst.name == "SBC");
    CHECK(inst.addr == "abs,X");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0xF0);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("SBC absolute Y-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::SBC_ABS_Y, 0x0F, 0xF0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::SBC_ABS_Y);
    CHECK(inst.name == "SBC");
    CHECK(inst.addr == "abs,Y");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0xF0);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("SBC X-indirect instruction disassembles correctly.") {
    loadRam(ramPtr, Op::SBC_X_IND, 0x0F); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::SBC_X_IND);
    CHECK(inst.name == "SBC");
    CHECK(inst.addr == "X,ind");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 6);
    
  }
  
  SECTION("SBC indirect-Y instruction disassembles correctly.") {
    loadRam(ramPtr, Op::SBC_IND_Y, 0x0F); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::SBC_IND_Y);
    CHECK(inst.name == "SBC");
    CHECK(inst.addr == "ind,Y");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 5);
    
  }

  SECTION("STA zeropage instruction disassembles correctly.") {
    loadRam(ramPtr, Op::STA_ZPG, 0x0F); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::STA_ZPG);
    CHECK(inst.name == "STA");
    CHECK(inst.addr == "zpg");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 3);
    
  }

  SECTION("STA zeropage X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::STA_ZPG_X, 0x0F); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::STA_ZPG_X);
    CHECK(inst.name == "STA");
    CHECK(inst.addr == "zpg,X");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("STA absolute instruction disassembles correctly.") {
    loadRam(ramPtr, Op::STA_ABS, 0x0F, 0xF0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::STA_ABS);
    CHECK(inst.name == "STA");
    CHECK(inst.addr == "abs");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0xF0);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("STA absolute X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::STA_ABS_X, 0x0F, 0xF0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::STA_ABS_X);
    CHECK(inst.name == "STA");
    CHECK(inst.addr == "abs,X");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0xF0);
    CHECK(inst.cycles == 5);
    
  }

  SECTION("STA absolute Y-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::STA_ABS_Y, 0x0F, 0xF0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::STA_ABS_Y);
    CHECK(inst.name == "STA");
    CHECK(inst.addr == "abs,Y");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0xF0);
    CHECK(inst.cycles == 5);
    
  }

  SECTION("STA X-indirect instruction disassembles correctly.") {
    loadRam(ramPtr, Op::STA_X_IND, 0x0F); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::STA_X_IND);
    CHECK(inst.name == "STA");
    CHECK(inst.addr == "X,ind");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 6);
    
  }
  
  SECTION("STA indirect-Y instruction disassembles correctly.") {
    loadRam(ramPtr, Op::STA_IND_Y, 0x0F); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::STA_IND_Y);
    CHECK(inst.name == "STA");
    CHECK(inst.addr == "ind,Y");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 6);
    
  }
  
  SECTION("TXS implied instruction disassembles correctly.") {
    loadRam(ramPtr, Op::TXS_IMPL); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::TXS_IMPL);
    CHECK(inst.name == "TXS");
    CHECK(inst.addr == "impl");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }
  
  SECTION("TSX implied instruction disassembles correctly.") {
    loadRam(ramPtr, Op::TSX_IMPL); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::TSX_IMPL);
    CHECK(inst.name == "TSX");
    CHECK(inst.addr == "impl");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 2);
    
  }
  
  SECTION("PHA implied instruction disassembles correctly.") {
    loadRam(ramPtr, Op::PHA_IMPL); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::PHA_IMPL);
    CHECK(inst.name == "PHA");
    CHECK(inst.addr == "impl");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 3);
    
  }

  SECTION("PLA implied instruction disassembles correctly.") {
    loadRam(ramPtr, Op::PLA_IMPL); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::PLA_IMPL);
    CHECK(inst.name == "PLA");
    CHECK(inst.addr == "impl");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 4);
    
  }
  
  SECTION("PHP implied instruction disassembles correctly.") {
    loadRam(ramPtr, Op::PHP_IMPL); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::PHP_IMPL);
    CHECK(inst.name == "PHP");
    CHECK(inst.addr == "impl");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 3);
    
  }

  SECTION("PLP implied instruction disassembles correctly.") {
    loadRam(ramPtr, Op::PLP_IMPL); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::PLP_IMPL);
    CHECK(inst.name == "PLP");
    CHECK(inst.addr == "impl");
    CHECK(inst.operand.lo == 0x00);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 4);
    
  }
  
  SECTION("STX zeropage instruction disassembles correctly.") {
    loadRam(ramPtr, Op::STX_ZPG, 0x0F); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::STX_ZPG);
    CHECK(inst.name == "STX");
    CHECK(inst.addr == "zpg");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 3);
    
  }

  SECTION("STX zeropage X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::STX_ZPG_Y, 0x0F); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::STX_ZPG_Y);
    CHECK(inst.name == "STX");
    CHECK(inst.addr == "zpg,Y");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("STX absolute instruction disassembles correctly.") {
    loadRam(ramPtr, Op::STX_ABS, 0x0F, 0xF0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::STX_ABS);
    CHECK(inst.name == "STX");
    CHECK(inst.addr == "abs");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0xF0);
    CHECK(inst.cycles == 4);
    
  }
  
  SECTION("STY zeropage instruction disassembles correctly.") {
    loadRam(ramPtr, Op::STY_ZPG, 0x0F); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::STY_ZPG);
    CHECK(inst.name == "STY");
    CHECK(inst.addr == "zpg");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 3);
    
  }

  SECTION("STY zeropage X-indexed instruction disassembles correctly.") {
    loadRam(ramPtr, Op::STY_ZPG_X, 0x0F); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::STY_ZPG_X);
    CHECK(inst.name == "STY");
    CHECK(inst.addr == "zpg,X");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0x00);
    CHECK(inst.cycles == 4);
    
  }

  SECTION("STY absolute instruction disassembles correctly.") {
    loadRam(ramPtr, Op::STY_ABS, 0x0F, 0xF0); 
    Reference<byte> ref(ramPtr, 0);
    // Disassemble
    Mos6502Instruction inst = dis.disassembleInstruction(ref);

    CHECK(inst.opcode == Op::STY_ABS);
    CHECK(inst.name == "STY");
    CHECK(inst.addr == "abs");
    CHECK(inst.operand.lo == 0x0F);
    CHECK(inst.operand.hi == 0xF0);
    CHECK(inst.cycles == 4);
    
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

