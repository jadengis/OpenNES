//===-- source/cpu/InterpretedMos6502.cpp - Interpreted Emulator *- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implemntation of the InterpretedMos6502 class, an 
/// interpreted implementation of a Mos6502 emulator.
///
//===----------------------------------------------------------------------===//
#include <functional>
#include <unordered_map>

#include "common/CommonTypes.h"
#include "cpu/interpreter/InterpretedMos6502.h"
#include "memory/Reference.h"

#include "Mos6502_Inst.h"

using namespace Cpu;
using namespace Memory;

InterpretedMos6502::InterpretedMos6502(Memory::Mapper<byte>& memMap) :
    Mos6502(memMap) {}
InterpretedMos6502::~InterpretedMos6502() {}

//===----------------------------------------------------------------------===//
// For all instruction emulation functions, we use the instruction information to
// build the virtual address (if needed), feed that into the MMU to get an
// appropriate memory refrence, and read an write to that memory as needed.
// 
// For immediate and relative addressing, we read the immediate value from the 
// lo byte of the input instruction.
//===----------------------------------------------------------------------===//

/// Helper function for computing the virtual address referenced by a
/// Mos6502Instruction.
/// \param inst The instruction whose operands build the address.
/// \returns The virtual address.
static inline Vaddr computeAddress(const Mos6502Instruction& inst) {
  Vaddr vaddr;
  vaddr.ll = inst.operand.lo;
  vaddr.hh = inst.operand.hi;
  return vaddr;
}

/// Helper function for computing the virtual address referenced by a
/// Memory::Reference.
/// \param ref The reference which points to the address.
/// \returns The virtual address.
static inline Vaddr computeAddress(const Reference<byte>& ref) {
  Vaddr vaddr;
  vaddr.ll = ref.read();
  vaddr.hh = ref.read(1);
  return vaddr;
}

// Add with carry
void InterpretedMos6502::adcImmediate(const Mos6502Instruction& inst) {
  ADC(inst.operand.lo);
}

void InterpretedMos6502::adcZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  ADC(ref.read());
}

void InterpretedMos6502::adcZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  ADC(ref.read());
}

void InterpretedMos6502::adcAbsolute(const Mos6502Instruction& inst) { 
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  ADC(ref.read());
}

void InterpretedMos6502::adcAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  ADC(ref.read());
}

void InterpretedMos6502::adcAbsoluteY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteYIndexed(computeAddress(inst));
  ADC(ref.read());
}

void InterpretedMos6502::adcXIndirect(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().xIndexedIndirect(computeAddress(inst));
  ADC(ref.read());
}

void InterpretedMos6502::adcIndirectY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().indirectYIndexed(computeAddress(inst));
  ADC(ref.read());
}

// AND with memory
void InterpretedMos6502::andImmediate(const Mos6502Instruction& inst) {
  AND(inst.operand.lo);
}

void InterpretedMos6502::andZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  AND(ref.read());
}

void InterpretedMos6502::andZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  AND(ref.read());
}

void InterpretedMos6502::andAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  AND(ref.read());
}

void InterpretedMos6502::andAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  AND(ref.read());
}

void InterpretedMos6502::andAbsoluteY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteYIndexed(computeAddress(inst));
  AND(ref.read());
}

void InterpretedMos6502::andXIndirect(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().xIndexedIndirect(computeAddress(inst));
  AND(ref.read());
}

void InterpretedMos6502::andIndirectY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().xIndexedIndirect(computeAddress(inst));
  AND(ref.read());
}

// Arithmetic shift left
void InterpretedMos6502::aslAccumulator(const Mos6502Instruction& inst) { 
  setRegAC(ASL(getRegAC()));
}

void InterpretedMos6502::aslZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  ref.write(ASL(ref.read()));
}

void InterpretedMos6502::aslZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  ref.write(ASL(ref.read()));
}

void InterpretedMos6502::aslAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  ref.write(ASL(ref.read()));
}

void InterpretedMos6502::aslAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  ref.write(ASL(ref.read()));
}

// Branching
void InterpretedMos6502::bccRelative(const Mos6502Instruction& inst) {
  BCC(inst.operand.lo);
}

void InterpretedMos6502::bcsRelative(const Mos6502Instruction& inst) {
  BCS(inst.operand.lo);
}

void InterpretedMos6502::beqRelative(const Mos6502Instruction& inst) {
  BEQ(inst.operand.lo);
}

void InterpretedMos6502::bmiRelative(const Mos6502Instruction& inst) {
  BMI(inst.operand.lo);
}

void InterpretedMos6502::bneRelative(const Mos6502Instruction& inst) {
  BNE(inst.operand.lo);
}

void InterpretedMos6502::bplRelative(const Mos6502Instruction& inst) {
  BPL(inst.operand.lo);
}

void InterpretedMos6502::bvcRelative(const Mos6502Instruction& inst) {
  BVC(inst.operand.lo);
}

void InterpretedMos6502::bvsRelative(const Mos6502Instruction& inst) {
  BVS(inst.operand.lo);
}

// Test bits
void InterpretedMos6502::bitZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  BIT(ref.read());
}

void InterpretedMos6502::bitAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  BIT(ref.read());
}

// Force break
void InterpretedMos6502::brkImplied(const Mos6502Instruction& inst) {
  BRK();
}

// Clear flags
void InterpretedMos6502::clcImplied(const Mos6502Instruction& inst) {
  CLC();
}

void InterpretedMos6502::cldImplied(const Mos6502Instruction& inst) {
  CLD();
}

void InterpretedMos6502::cliImplied(const Mos6502Instruction& inst) {
  CLI();
}

void InterpretedMos6502::clvImplied(const Mos6502Instruction& inst) {
  CLV();
}

// Compare with memory
void InterpretedMos6502::cmpImmediate(const Mos6502Instruction& inst) {
  CMP(inst.operand.lo);
}

void InterpretedMos6502::cmpZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  CMP(ref.read());
}

void InterpretedMos6502::cmpZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  CMP(ref.read());
}

void InterpretedMos6502::cmpAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  CMP(ref.read());
}

void InterpretedMos6502::cmpAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  CMP(ref.read());
}

void InterpretedMos6502::cmpAbsoluteY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteYIndexed(computeAddress(inst));
  CMP(ref.read());
}

void InterpretedMos6502::cmpXIndirect(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().xIndexedIndirect(computeAddress(inst));
  CMP(ref.read());
}

void InterpretedMos6502::cmpIndirectY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().indirectYIndexed(computeAddress(inst));
  CMP(ref.read());
}

void InterpretedMos6502::cpxImmediate(const Mos6502Instruction& inst) {
  CPX(inst.operand.lo);
}

void InterpretedMos6502::cpxZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  CPX(ref.read());
}

void InterpretedMos6502::cpxAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  CPX(ref.read());
}

void InterpretedMos6502::cpyImmediate(const Mos6502Instruction& inst) {
  CPY(inst.operand.lo);
}

void InterpretedMos6502::cpyZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  CPY(ref.read());
}

void InterpretedMos6502::cpyAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  CPY(ref.read());
}

// Decrement memory
void InterpretedMos6502::decZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  ref.write(DEC(ref.read()));
}

void InterpretedMos6502::decZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  ref.write(DEC(ref.read()));
}

void InterpretedMos6502::decAbsolute(const Mos6502Instruction& inst) { 
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  ref.write(DEC(ref.read()));
}

void InterpretedMos6502::decAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  ref.write(DEC(ref.read()));
}

void InterpretedMos6502::dexImplied(const Mos6502Instruction& inst) {
  DEX();
}

void InterpretedMos6502::deyImplied(const Mos6502Instruction& inst) {
  DEY();
}

// Exclusive OR with memory
void InterpretedMos6502::eorImmediate(const Mos6502Instruction& inst) {
  EOR(inst.operand.lo);
}

void InterpretedMos6502::eorZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  EOR(ref.read());
}

void InterpretedMos6502::eorZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  EOR(ref.read());
}

void InterpretedMos6502::eorAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  EOR(ref.read());
}

void InterpretedMos6502::eorAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  EOR(ref.read());
}

void InterpretedMos6502::eorAbsoluteY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteYIndexed(computeAddress(inst));
  EOR(ref.read());
}

void InterpretedMos6502::eorXIndirect(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().xIndexedIndirect(computeAddress(inst));
  EOR(ref.read());
}

void InterpretedMos6502::eorIndirectY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().indirectYIndexed(computeAddress(inst));
  EOR(ref.read());
}

// Increment memory
void InterpretedMos6502::incZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  ref.write(INC(ref.read()));
}

void InterpretedMos6502::incZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  ref.write(INC(ref.read()));
}

void InterpretedMos6502::incAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  ref.write(INC(ref.read()));
}

void InterpretedMos6502::incAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  ref.write(INC(ref.read()));
}

void InterpretedMos6502::inxImplied(const Mos6502Instruction& inst) {
  INX();
}

void InterpretedMos6502::inyImplied(const Mos6502Instruction& inst) {
  INY();
}

// Jumps
void InterpretedMos6502::jmpAbsolute(const Mos6502Instruction& inst) {
  JMP(computeAddress(inst));
}

void InterpretedMos6502::jmpIndirect(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  JMP(computeAddress(ref));
}

void InterpretedMos6502::jsrAbsolute(const Mos6502Instruction& inst) {
  JMP(computeAddress(inst));
}

// Loads
void InterpretedMos6502::ldaImmediate(const Mos6502Instruction& inst) {
  LDA(inst.operand.lo);
}

void InterpretedMos6502::ldaZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  LDA(ref.read());
}

void InterpretedMos6502::ldaZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  LDA(ref.read());
}

void InterpretedMos6502::ldaAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  LDA(ref.read());
}

void InterpretedMos6502::ldaAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  LDA(ref.read());
}

void InterpretedMos6502::ldaAbsoluteY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteYIndexed(computeAddress(inst));
  LDA(ref.read());
}

void InterpretedMos6502::ldaXIndirect(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().xIndexedIndirect(computeAddress(inst));
  LDA(ref.read());
}

void InterpretedMos6502::ldaIndirectY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().indirectYIndexed(computeAddress(inst));
  LDA(ref.read());
}

void InterpretedMos6502::ldxImmediate(const Mos6502Instruction& inst) {
  LDX(inst.operand.lo);
}

void InterpretedMos6502::ldxZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  LDX(ref.read());
}

void InterpretedMos6502::ldxZeropageY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageYIndexed(computeAddress(inst));
  LDX(ref.read());
}

void InterpretedMos6502::ldxAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  LDX(ref.read());
}

void InterpretedMos6502::ldxAbsoluteY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteYIndexed(computeAddress(inst));
  LDX(ref.read());
}

void InterpretedMos6502::ldyImmediate(const Mos6502Instruction& inst) {
  LDY(inst.operand.lo);
}

void InterpretedMos6502::ldyZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  LDY(ref.read());
}

void InterpretedMos6502::ldyZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  LDY(ref.read());
}

void InterpretedMos6502::ldyAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  LDY(ref.read());
}

void InterpretedMos6502::ldyAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  LDY(ref.read());
}

// Logical shift right
void InterpretedMos6502::lsrAccumulator(const Mos6502Instruction& inst) {
  setRegAC(LSR(getRegAC()));
}

void InterpretedMos6502::lsrZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  ref.write(LSR(ref.read()));
}

void InterpretedMos6502::lsrZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  ref.write(LSR(ref.read()));
}

void InterpretedMos6502::lsrAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  ref.write(LSR(ref.read()));
}

void InterpretedMos6502::lsrAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  ref.write(LSR(ref.read()));
}

/// No operation
void InterpretedMos6502::nopImplied(const Mos6502Instruction& inst) {
  NOP();
}

//  OR with memory
void InterpretedMos6502::oraImmediate(const Mos6502Instruction& inst) {
  ORA(inst.operand.lo);
}

void InterpretedMos6502::oraZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  ORA(ref.read());
}

void InterpretedMos6502::oraZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  ORA(ref.read());
}

void InterpretedMos6502::oraAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  ORA(ref.read());
}

void InterpretedMos6502::oraAbsoluteX(const Mos6502Instruction& inst) { 
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  ORA(ref.read());
}

void InterpretedMos6502::oraAbsoluteY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteYIndexed(computeAddress(inst));
  ORA(ref.read());
}

void InterpretedMos6502::oraXIndirect(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().xIndexedIndirect(computeAddress(inst));
  ORA(ref.read());
}

void InterpretedMos6502::oraIndirectY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().xIndexedIndirect(computeAddress(inst));
  ORA(ref.read());
}

// Stack operations
void InterpretedMos6502::phaImplied(const Mos6502Instruction& inst) {
  PHA();
}

void InterpretedMos6502::phpImplied(const Mos6502Instruction& inst) {
  PHP();
}

void InterpretedMos6502::plaImplied(const Mos6502Instruction& inst) {
  PLA();
}

void InterpretedMos6502::plpImplied(const Mos6502Instruction& inst) {
  PLP();
}

// Rotate left
void InterpretedMos6502::rolAccumulator(const Mos6502Instruction& inst) {
  setRegAC(ROL(getRegAC()));
}

void InterpretedMos6502::rolZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  ref.write(ROL(ref.read()));
}

void InterpretedMos6502::rolZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  ref.write(ROL(ref.read()));
}

void InterpretedMos6502::rolAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  ref.write(ROL(ref.read()));
}

void InterpretedMos6502::rolAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  ref.write(ROL(ref.read()));
}

// Rotate right
void InterpretedMos6502::rorAccumulator(const Mos6502Instruction& inst) {
  setRegAC(ROR(getRegAC()));
}

void InterpretedMos6502::rorZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  ref.write(ROR(ref.read()));
}

void InterpretedMos6502::rorZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  ref.write(ROR(ref.read()));
}

void InterpretedMos6502::rorAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  ref.write(ROR(ref.read()));
}

void InterpretedMos6502::rorAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  ref.write(ROR(ref.read()));
}

// Returns
void InterpretedMos6502::rtiImplied(const Mos6502Instruction& inst) {
  RTI();
}

void InterpretedMos6502::rtsImplied(const Mos6502Instruction& inst) {
  RTS();
}

// Subtract with borrow
void InterpretedMos6502::sbcImmediate(const Mos6502Instruction& inst) {
  SBC(inst.operand.lo);
}

void InterpretedMos6502::sbcZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  SBC(ref.read());
}

void InterpretedMos6502::sbcZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  SBC(ref.read());
}

void InterpretedMos6502::sbcAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  SBC(ref.read());
}

void InterpretedMos6502::sbcAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  SBC(ref.read());
}

void InterpretedMos6502::sbcAbsoluteY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteYIndexed(computeAddress(inst));
  SBC(ref.read());
}

void InterpretedMos6502::sbcXIndirect(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().xIndexedIndirect(computeAddress(inst));
  SBC(ref.read());
}

void InterpretedMos6502::sbcIndirectY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().indirectYIndexed(computeAddress(inst));
  SBC(ref.read());
}

// Set flags
void InterpretedMos6502::secImplied(const Mos6502Instruction& inst) {
  SEC();
}

void InterpretedMos6502::sedImplied(const Mos6502Instruction& inst) {
  SED();
}

void InterpretedMos6502::seiImplied(const Mos6502Instruction& inst) {
  SEI();
}

// Store accumulator
void InterpretedMos6502::staZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  ref.write(STA());
}

void InterpretedMos6502::staZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  ref.write(STA());
}

void InterpretedMos6502::staAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  ref.write(STA());
}

void InterpretedMos6502::staAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  ref.write(STA());
}

void InterpretedMos6502::staAbsoluteY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteYIndexed(computeAddress(inst));
  ref.write(STA());
}

void InterpretedMos6502::staXIndirect(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().xIndexedIndirect(computeAddress(inst));
  ref.write(STA());
}

void InterpretedMos6502::staIndirectY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().indirectYIndexed(computeAddress(inst));
  ref.write(STA());
}

// Store X-index register
void InterpretedMos6502::stxZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  ref.write(STX());
}

void InterpretedMos6502::stxZeropageY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageYIndexed(computeAddress(inst));
  ref.write(STX());
}

void InterpretedMos6502::stxAbsolute(const Mos6502Instruction& inst) { 
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  ref.write(STX());
}

// Store Y-index register
void InterpretedMos6502::styZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  ref.write(STY());
}

void InterpretedMos6502::styZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  ref.write(STY());
}

void InterpretedMos6502::styAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  ref.write(STY());
}

// Transfers
void InterpretedMos6502::taxImplied(const Mos6502Instruction& inst) {
  TAX();
}

void InterpretedMos6502::tayImplied(const Mos6502Instruction& inst) {
  TAY();
}

void InterpretedMos6502::tsxImplied(const Mos6502Instruction& inst) {
  TSX();
}

void InterpretedMos6502::txaImplied(const Mos6502Instruction& inst) {
  TXA();
}

void InterpretedMos6502::txsImplied(const Mos6502Instruction& inst) {
  TXS();
}

void InterpretedMos6502::tyaImplied(const Mos6502Instruction& inst) {
  TYA();
}
