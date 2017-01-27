//===-- source/cpu/mos6502.cpp - Mos6502 Cpu Class Impl ---------*- C++ -*-===//
//
//                           The OsNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Functional specification for the MOS 6502 CPU.
/// Any and all details related to the overall operation ofthe 6502 should
/// be implemented here.
///
/// Instruction implementation details are based on the descriptions here:
/// http://e-tradition.net/bytes/6502/6502_instruction_set.html
///
//===----------------------------------------------------------------------===//
#ifndef MOS6502_INST_H
#define MOS6502_INST_H
#include "cpu/mem.h"
#include "cpu/Mos6502.h"

using namespace com;

// Static Functions
static inline byte   Check_Zero(byte x);
static inline byte   Check_Not_Zero(byte x);
static inline byte   Check_Nth_Bit(byte x, Bit_Position n);
static inline uint16 Compute_Branch(uint16 pc, byte m);

// ----------------------------------------------------------------------------
// Load and Store Instructons
// ----------------------------------------------------------------------------

// Load Accumulator with Memory
inline void Mos6502::LDA(const byte opd) {
  // Copy memory to accumulator
  reg.ac = opd;
  // set appropriate status register flags
  reg.srf.z = Check_Zero(reg.ac);
  reg.srf.n = Check_Nth_Bit(reg.ac, Bit_Position::bit7);
  return;
}

// Load Index X with Memory
inline void Mos6502::LDX(const byte opd) {
  // Copy memory to X register
  reg.x = opd;
  // set appropriate status register flags
  reg.srf.z = Check_Zero(reg.x);
  reg.srf.n = Check_Nth_Bit(reg.x, Bit_Position::bit7);
  return;
}

// Load Index Y with Memory
inline void Mos6502::LDY(const byte opd) {
  // Copy memory to Y register
  reg.y = opd;
  // set appropriate status register flags
  reg.srf.z = Check_Zero(reg.y);
  reg.srf.n = Check_Nth_Bit(reg.y, Bit_Position::bit7);
  return;
}

// Store Accumulator in Memory
inline byte Mos6502::STA() {
  // return accumulator value to be stored
  return reg.ac;
}

// Store Index X in Memory
inline byte Mos6502::STX() {
  // return X register value to be stored
  return reg.x;
}

// Store Index Y in Memory
inline byte Mos6502::STY() {
  // return Y register value to be stored
  return reg.y;
}


// ----------------------------------------------------------------------------
// Arithmetic Instructions
// ----------------------------------------------------------------------------

// Add Memory to Accumulator with Carry
inline void Mos6502::ADC(const byte opd) {
  // To add 2 bytes with carry, we will first widen to native width, perform
  // the add with carry, and mask out the relevant bits.
  // ADD the memory to Accumulator + carry if set
  uint_native sum = static_cast<uint_native>(reg.ac) + static_cast<uint_native>(opd) + 
                   static_cast<uint_native>(reg.srf.c);
  // Mask out the accumulator value
  reg.ac = static_cast<byte>(sum & BYTE_MASK);
  // Set the carry bit ( 1 if the add overflowed, 0 otherwise)
  // Mask out carry bit (bit 8)
  reg.srf.c = static_cast<byte>((sum >> 8) & ONE_BIT_MASK);
  // Set the Negative flag
  // Mask out sign bit (bit 7)
  reg.srf.n = static_cast<byte>((sum >> 7) & ONE_BIT_MASK);
  // Set overflow flag
  // Notice that a signed overflow will only have occured if the two addends have the
  // same sign, but the sum has a different sign (implying a rollover). Below is a clever
  // bit manipulation to check this fact.
  reg.srf.v = ((~(reg.ac ^ opd) & (reg.ac ^ sum)) >> 7) & ONE_BIT_MASK;
  // Set zero flag
  reg.srf.z = Check_Zero(reg.ac);
  return;
}

// Subtract Memory from Accumulator with Borrow
// Notice that SBC(x) == ADC(~x) since a - x - !c == a + ~x + 1 - !c == a + ~x + c
inline void Mos6502::SBC(const byte opd) {
  ADC(~opd);
  return;
}


// ----------------------------------------------------------------------------
// Increment and Decrement Instructions
// ----------------------------------------------------------------------------

// Increment Memory by One
inline byte Mos6502::INC(byte opd) {
  opd = opd + 1;
  // set appropriate status register flags
  reg.srf.z = Check_Zero(opd);
  reg.srf.n = Check_Nth_Bit(opd, Bit_Position::bit7);
  return opd;
}

// Increment Index X by One
inline void Mos6502::INX() {
  reg.x = reg.x + 1;
  // set appropriate status register flags
  reg.srf.z = Check_Zero(reg.x);
  reg.srf.n = Check_Nth_Bit(reg.x, Bit_Position::bit7);
  return;
}

// Increment Memory by One
inline void Mos6502::INY() {
  reg.y = reg.y + 1;
  // set appropriate status register flags
  reg.srf.z = Check_Zero(reg.y);
  reg.srf.n = Check_Nth_Bit(reg.y, Bit_Position::bit7);
  return;
}

// Decrement Memory by One
inline byte Mos6502::DEC(byte opd) {
  opd = opd - 1;
  // set appropriate status register flags
  reg.srf.z = Check_Zero(opd);
  reg.srf.n = Check_Nth_Bit(opd, Bit_Position::bit7);
  return opd;
}

// Decrement Index X by One
inline void Mos6502::DEX() {
  reg.x = reg.x - 1;
  // set appropriate status register flags
  reg.srf.z = Check_Zero(reg.x);
  reg.srf.n = Check_Nth_Bit(reg.x, Bit_Position::bit7);
  return;
}

// Decrement Memory by One
inline void Mos6502::DEY() {
  reg.y = reg.y - 1;
  // set appropriate status register flags
  reg.srf.z = Check_Zero(reg.y);
  reg.srf.n = Check_Nth_Bit(reg.y, Bit_Position::bit7);
  return;
}


// ----------------------------------------------------------------------------
// Logical Instructions
// ----------------------------------------------------------------------------

// AND Memory with Accumulator
inline void Mos6502::AND(const byte opd) {
  // AND the memory M with the Accumulator
  reg.ac = reg.ac & opd;
  // Set the remaining status register flags
  reg.srf.z = Check_Zero(reg.ac);
  reg.srf.n = Check_Nth_Bit(reg.ac, Bit_Position::bit7);
  return;
}

// EOR Exclusive-OR Memory with Accumulator
inline void Mos6502::EOR(const byte opd) {
  // XOR the memory M with the Accumulator
  reg.ac = reg.ac ^ opd;
  // Set the remaining status register flags
  reg.srf.z = Check_Zero(reg.ac);
  reg.srf.n = Check_Nth_Bit(reg.ac, Bit_Position::bit7);
  return;
}

// OR Memory with Accumulator
inline void Mos6502::ORA(const byte opd) {
  // OR the memory M with the Accumulator
  reg.ac = reg.ac | opd;
  // Set the remaining status register flags
  reg.srf.z = Check_Zero(reg.ac);
  reg.srf.n = Check_Nth_Bit(reg.ac, Bit_Position::bit7);
  return;
}


// ----------------------------------------------------------------------------
// Jump, Branch, Compare and Test Bits Instructions
// ----------------------------------------------------------------------------

// Jump to New Location
inline void Mos6502::JMP(const byte opd_lo, const byte opd_hi) {
  // opd_lo is the low byte of the new PC and opd_hi is the high byte of new PC
  // (PC+1 = opd_lo) -> PCL
  // (PC+2 = opd_hi) -> PCH
  reg.pcl = opd_lo;
  reg.pch = opd_hi;
  return;
}

// Branch on Carry Clear
inline void Mos6502::BCC(const byte opd) {
  if(reg.srf.c == 0) {
    // Condition true, branch to PC + offset
    reg.pc = Compute_Branch(reg.pc, opd);
  }
  return;
}

// Branch of Carry Set
inline void Mos6502::BCS(const byte opd) {
  if(reg.srf.c == 1) {
    // Condition true, branch to PC + offset
    reg.pc = Compute_Branch(reg.pc, opd);
  }
  return;
}

// Branch on Result Zero
inline void Mos6502::BEQ(const byte opd) {
  if(reg.srf.z == 1) {
    // Condition true, branch to PC + offset
    reg.pc = Compute_Branch(reg.pc,opd);
  }
  return;
}

// Branch on Result Minus
inline void Mos6502::BMI(const byte opd) {
  if(reg.srf.n == 1) {
    // Condition true, branch to PC + offset
    reg.pc = Compute_Branch(reg.pc,opd);
  }
  return;
}

// Branch on Result not Zero
inline void Mos6502::BNE(const byte opd) {
  if(reg.srf.z == 0) {
    // Condition true, branch to PC + offset
    reg.pc = Compute_Branch(reg.pc,opd);
  }
  return;
}

// Branch on Result Plus
inline void Mos6502::BPL(const byte opd) {
  if(reg.srf.n == 0) {
    // Condition true, branch to PC + offset
    reg.pc = Compute_Branch(reg.pc,opd);
  }
  return;
}

// Branch on Overflow Clear
inline void Mos6502::BVC(const byte opd) {
  if(reg.srf.v == 0) {
    // Condition true, branch to PC + offset
    reg.pc = Compute_Branch(reg.pc,opd);
  }
  return;
}

// Branch on Overflow Set
inline void Mos6502::BVS(const byte opd) {
  if(reg.srf.v == 1) {
    // Condition true, branch to PC + offset
    reg.pc = Compute_Branch(reg.pc,opd);
  }
  return;
}

// Compare Memory with Accumulator
inline void Mos6502::CMP(const byte opd) {
  // set appropriate bit flags
  reg.srf.n = reg.ac < opd; 
  reg.srf.z = reg.ac == opd; 
  reg.srf.c = reg.ac >= opd; 
  return;
}

// Compare Memory and Index X
inline void Mos6502::CPX(const byte opd) {
  // set appropriate bit flags
  reg.srf.n = reg.x < opd; 
  reg.srf.z = reg.x == opd; 
  reg.srf.c = reg.x >= opd; 
  return;
}

// Compare Memory and Index Y
inline void Mos6502::CPY(const byte opd) {
  // set appropriate bit flags
  reg.srf.n = reg.y < opd; 
  reg.srf.z = reg.y == opd; 
  reg.srf.c = reg.y >= opd; 
  return;
}

// Test Bits in Memory with Accumulator
inline void Mos6502::BIT(const byte opd) {
  // zero flag is set to result of A AND M
  reg.srf.z = Check_Not_Zero(reg.ac & opd);
  // M7 -> N, M6 -> V
  reg.srf.n = Check_Nth_Bit(opd, Bit_Position::bit7);
  reg.srf.v = Check_Nth_Bit(opd, Bit_Position::bit6);
  return;
}


// ----------------------------------------------------------------------------
// Shift and Rotate Instructions
// ----------------------------------------------------------------------------

// Shift Left One Bit (Memory or Accumulator)
inline byte Mos6502::ASL(byte opd) {
  // Set the carry bit.
  reg.srf.c = Check_Nth_Bit(opd, Bit_Position::bit7);
  // Shift memory (or accumulator) left 1
  opd = opd << 1;
  // Set the remaining SR flags
  reg.srf.z = Check_Zero(opd);
  reg.srf.n = Check_Nth_Bit(opd, Bit_Position::bit7);
  return opd;
}

// Shift One Bit Right (Memory or Accumulator)
inline byte Mos6502::LSR(byte opd) {
  // Set the carry bit
  reg.srf.c = Check_Nth_Bit(opd, Bit_Position::bit0);
  // Shift memory (or accumulator) left 1
  opd = opd >> 1;
  // Set the remaining SR flags
  reg.srf.z = Check_Zero(opd);
  return opd;
}

// Rotate One Bit Left (Memory or Accumulator)
inline byte Mos6502::ROL(byte opd) {
  // Store old carry
  byte old_c = reg.srf.c;
  // Set the carry bit
  reg.srf.c = Check_Nth_Bit(opd, Bit_Position::bit7);
  // Shift left by 1 and OR in old carry
  opd = (opd << 1) & old_c;
  // Set the remaining SR flags
  reg.srf.z = Check_Zero(opd);
  reg.srf.n = Check_Nth_Bit(opd, Bit_Position::bit7);
  return opd;
}

// Rotate One Bit Right (Memory or Accumulator)
inline byte Mos6502::ROR(byte opd) {
  // Store old carry
  byte old_c = reg.srf.c;
  // Set the carry bit
  reg.srf.c = Check_Nth_Bit(opd, Bit_Position::bit0);
  // Shift right by 1 and OR in old carry
  opd = (opd >> 1) & (old_c << 7);
  // Set the remaining SR flags
  reg.srf.z = Check_Zero(opd);
  reg.srf.n = Check_Nth_Bit(opd, Bit_Position::bit7);
  return opd;
}


// ----------------------------------------------------------------------------
// Transfer Instructions
// ----------------------------------------------------------------------------

// Transfer Accumulator to Index X
inline void Mos6502::TAX() {
  // Copy accumulator to X register
  reg.x = reg.ac;
  // set appropriate status register flags
  reg.srf.z = Check_Zero(reg.x);
  reg.srf.n = Check_Nth_Bit(reg.x, Bit_Position::bit7);
  return;
}

// Transfer Accumulator to Index Y
inline void Mos6502::TAY() {
  // Copy accumulator to Y register
  reg.y = reg.ac;
  // set appropriate status register flags
  reg.srf.z = Check_Zero(reg.y);
  reg.srf.n = Check_Nth_Bit(reg.y, Bit_Position::bit7);
  return;
}

// Transfer Index X to Accumulator
inline void Mos6502::TXA() {
  // Copy X register to accumulator
  reg.ac = reg.x;
  // set appropriate status register flags
  reg.srf.z = Check_Zero(reg.ac);
  reg.srf.n = Check_Nth_Bit(reg.ac, Bit_Position::bit7);
  return;
}

// Transfer Index Y to Accumulator
inline void Mos6502::TYA() {
  // Copy Y register to accumulator
  reg.ac = reg.y;
  // set appropriate status register flags
  reg.srf.z = Check_Zero(reg.ac);
  reg.srf.n = Check_Nth_Bit(reg.ac, Bit_Position::bit7);
  return;
}


// ----------------------------------------------------------------------------
// Stack Instructions
// ----------------------------------------------------------------------------

// Transfer Stack Pointer to Index X
inline void Mos6502::TSX() {
  // Copy Stack Pointer to X register
  reg.x = reg.sp;
  // set appropriate status register flags
  reg.srf.z = Check_Zero(reg.x);
  reg.srf.n = Check_Nth_Bit(reg.x, Bit_Position::bit7);
  return;
}

// Transfer Index X to Stack Pointer
inline void Mos6502::TXS() {
  // Copy X register to stack pointer
  reg.sp = reg.x;
  // set appropriate status register flags
  reg.srf.z = Check_Zero(reg.sp);
  reg.srf.n = Check_Nth_Bit(reg.sp, Bit_Position::bit7);
  return;
}

// Push Accumulator on the Stack
inline void Mos6502::PHA() {
  stack.Push(reg.ac);
  return;
}

// Push Processor Status on the Stack
inline void Mos6502::PHP() {
  stack.Push(reg.sr);
  return;
}

// Pull Accumulator from Stack
inline void Mos6502::PLA() {
  reg.ac = stack.Pull();
  // set appropriate status register flags
  reg.srf.z = Check_Zero(reg.sp);
  reg.srf.n = Check_Nth_Bit(reg.sp, Bit_Position::bit7);
  return;
}

// Pull Processor Status from Stack
inline void Mos6502::PLP() {
  reg.sr = stack.Pull();
  return;
}
  

// ----------------------------------------------------------------------------
// Subroutine Instructions
// ----------------------------------------------------------------------------

// Jump to New Location Saving Return Address
inline void Mos6502::JSR(const byte opd_lo, const byte opd_hi) {
  // Push the value PC+2 onto the stack then assigned the new PC bytes from
  // opd_lo and opd_hi.
  // opd_lo -> PCL
  // opd_hi -> PCH
  reg.pc = reg.pc + 2;
  stack.Push(reg.pch);
  stack.Push(reg.pcl);
  reg.pcl = opd_lo;
  reg.pch = opd_hi;
  return;
}

inline void Mos6502::RTI() {
  // pull status register from stack, followed by program counter
  // BRK implementation pushes PCH then PCL then SR so must pull in reverse order
  reg.sr  = stack.Pull();
  reg.pcl = stack.Pull();
  reg.pch = stack.Pull();
  return;
}

// Return from Subroutine
inline void Mos6502::RTS() {
  // pull program counter from the stack and increment to land on new instruction
  // JSR implementation pushes PCH then PCL so must pull PCL then PCH
  reg.pcl = stack.Pull();
  reg.pch = stack.Pull();
  reg.pc  = reg.pc + 1;
  return;
}


// ----------------------------------------------------------------------------
// Set and Reset (Clear) Instructions
// ----------------------------------------------------------------------------

// Clear Carry Flag
inline void Mos6502::CLC() {
  reg.srf.c = 0;
  return;
}

// Clear Decimal Mode
inline void Mos6502::CLD() {
  reg.srf.d = 0;
  return;
}

// Clear Interrupt Disable Bit
inline void Mos6502::CLI() {
  reg.srf.i = 0;
  return;
}

// Clear Overflow Flag
inline void Mos6502::CLV() {
  reg.srf.v = 0;
  return;
}

// Set Carry Flag
inline void Mos6502::SEC() {
  reg.srf.c = 1;
  return;
}

// Set Decimal Flag
inline void Mos6502::SED() {
  reg.srf.d = 1;
  return;
}

// Set Interrupt Disable Status
inline void Mos6502::SEI() {
  reg.srf.i = 1;
  return;
}


// ----------------------------------------------------------------------------
// Other Instructions
// ----------------------------------------------------------------------------

// No Operation
inline void Mos6502::NOP() {
  return;
}

// Force Break
inline void Mos6502::BRK() {
  // interrupt, push PC+2, push SR
  reg.srf.i = 1; // Set interrupt flag
  stack.Push(reg.pch);
  stack.Push(reg.pcl);
  stack.Push(reg.sr);
  return;
}


// ----------------------------------------------------------------------------
// Static Function Definitions
// ----------------------------------------------------------------------------

static inline byte Check_Zero(byte x) {
  // Returns 1 if 0, 0 otherwise
  return x == 0;
}

static inline byte Check_Not_Zero(byte x) {
  // Returns 1 if not 0, 0 otherwise
  return x != 0;
}

static inline byte Check_Nth_Bit(byte x, Bit_Position n) {
  // Returns 1 if Nth bit 1, 0 otherwise. Bit indexing it 0 - 7.
  return (x >> static_cast<byte>(n)) & ONE_BIT_MASK;
}

static inline uint16 Compute_Branch(uint16 pc, byte m) {
  // Cast the memory M to a signed int and then add to the program counter to
  // compute the branch.
  return pc + static_cast<int8>(m);
}
#endif // MOS6502_INST_H //
