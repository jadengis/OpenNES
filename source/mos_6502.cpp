// OsNES Project | source/cpu_6502.cpp
// Description:
// Functional specification for the MOS 6502 CPU.
// Any and all details related to the overall operation ofthe 6502 should
// be implemented here.
//
// Authors: 
// John Dengis
//
#include "mos_6502.h"

// Local Functions
static inline uint16 Compute_Branch(uint16 PC, uint8 M);

using namespace com;

// ----------------------------------------------------------------------------
// Instruction emulation functions
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Arithmetic Instructions
// ----------------------------------------------------------------------------

// Add Memory to Accumulator with Carry
void MOS_6502::ADC(const uint8 *M_p) {
  // Store the original value of the accumulator
  uint8 AC = reg.AC; 

  // ADD the memory M to Accumulator + carry if set
  reg.AC = AC + *M_p + reg.SR.C;
  // Set the carry bit ( 1 if the add overflowed, 0 otherwise
  reg.SR.C = (reg.AC < AC);
  // Set zero flag
  reg.SR.Z = Check_Zero(reg.AC);
  // TODO: Set the N, V.
  return;
}

// ----------------------------------------------------------------------------
// Increment and Decrement Instructions
// ----------------------------------------------------------------------------

// Increment Memory by One
void MOS_6502:INC(uint8* M_p) {
  *M_p = *M_p + 1;
  // set appropriate status register flags
  reg.SR.Z = Check_Zero(*M_p);
  reg.SR.N = Check_Nth_Bit(*M_p, BIT7);
  return;
}

// Increment Index X by One
void MOS_6502:INX() {
  *reg.X = reg.x + 1;
  // set appropriate status register flags
  reg.SR.Z = Check_Zero(reg.X);
  reg.SR.N = Check_Nth_Bit(reg.X, BIT7);
  return;
}

// Increment Memory by One
void MOS_6502:INY() {
  reg.Y = reg.Y + 1;
  // set appropriate status register flags
  reg.SR.Z = Check_Zero(reg.Y);
  reg.SR.N = Check_Nth_Bit(reg.Y, BIT7);
  return;
}

// Decrement Memory by One
void MOS_6502:DEC(uint8* M_p) {
  *M_p = *M_p - 1;
  // set appropriate status register flags
  reg.SR.Z = Check_Zero(*M_p);
  reg.SR.N = Check_Nth_Bit(*M_p, BIT7);
  return;
}

// Decrement Index X by One
void MOS_6502:DEX() {
  *reg.X = reg.x - 1;
  // set appropriate status register flags
  reg.SR.Z = Check_Zero(reg.X);
  reg.SR.N = Check_Nth_Bit(reg.X, BIT7);
  return;
}

// Decrement Memory by One
void MOS_6502:DEY() {
  reg.Y = reg.Y - 1;
  // set appropriate status register flags
  reg.SR.Z = Check_Zero(reg.Y);
  reg.SR.N = Check_Nth_Bit(reg.Y, BIT7);
  return;
}

// ----------------------------------------------------------------------------
// Logical Instructions
// ----------------------------------------------------------------------------

// AND Memory with Accumulator
void MOS_6502::AND(const uint8* M_p) {
  // AND the memory M with the Accumulator
  reg.AC = reg.AC & *M_p;
  // Set the remaining SR flags
  reg.SR.Z = Check_Zero(reg.AC);
  reg.SR.N = Check_Nth_Bit(reg.AC, BIT7);
  return;
}

// EOR Exclusive-OR Memory with Accumulator
void MOS_6502::EOR(const uint8* M_p) {
  // XOR the memory M with the Accumulator
  reg.AC = reg.AC ^ *M_p;
  // Set the remaining SR flags
  reg.SR.Z = Check_Zero(reg.AC);
  reg.SR.N = Check_Nth_Bit(reg.AC, BIT7);
  return;
}


// ----------------------------------------------------------------------------
// Shift Left One Bit (Memory or Accumulator)
// ----------------------------------------------------------------------------
void MOS_6502::ASL(uint8* M_p) {
  // Set the carry bit.
  reg.SR.C = Check_Nth_Bit(*M_p, BIT7);
  // Shift memory (or accumulator) left 1
  *M_p = *M_p << 1;
  // Set the remaining SR flags
  reg.SR.Z = (*M_p == 0);
  reg.SR.N = Check_Nth_Bit(*M_p, BIT7);
  return;
}

// ----------------------------------------------------------------------------
// Jump, Branch, Compare and Test Bits
// ----------------------------------------------------------------------------

// Branch on Carry Clear
void MOS_6502::BCC(const uint8* M_p) {
  if(reg.SR.C == 0) {
    // Condition true, branch to PC + offset
    reg.PC = Compute_Branch(reg.PC,*M_p);
  }
  return;
}

// Branch of Carry Set
void MOS_6502::BCS(const uint8* M_p) {
  if(reg.SR.C == 1) {
    // Condition true, branch to PC + offset
    reg.PC = Compute_Branch(reg.PC,*M_p);
  }
  return;
}

// Branch on Result Zero
void MOS_6502::BEQ(const uint8* M_p) {
  if(reg.SR.Z == 1) {
    // Condition true, branch to PC + offset
    reg.PC = Compute_Branch(reg.PC,*M_p);
  }
  return;
}

// Branch on Result Minus
void MOS_6502::BMI(const uint8* M_p) {
  if(reg.SR.N == 1) {
    // Condition true, branch to PC + offset
    reg.PC = Compute_Branch(reg.PC,*M_p);
  }
  return;
}

// Branch on Result not Zero
void MOS_6502::BNE(const uint8* M_p) {
  if(reg.SR.Z == 0) {
    // Condition true, branch to PC + offset
    reg.PC = Compute_Branch(reg.PC,*M_p);
  }
  return;
}

// Branch on Result Plus
void MOS_6502::BPL(const uint8* M_p) {
  if(reg.SR.N == 0) {
    // Condition true, branch to PC + offset
    reg.PC = Compute_Branch(reg.PC,*M_p);
  }
  return;
}

// Branch on Overflow Clear
void MOS_6502::BVC(const uint8* M_p) {
  if(reg.SR.V == 0) {
    // Condition true, branch to PC + offset
    reg.PC = Compute_Branch(reg.PC,*M_p);
  }
  return;
}

// Branch on Overflow Set
void MOS_6502::BVS(const uint8* M_p) {
  if(reg.SR.V == 1) {
    // Condition true, branch to PC + offset
    reg.PC = Compute_Branch(reg.PC,*M_p);
  }
  return;
}

// Compare Memory with Accumulator
void MOS_6502::CMP(const uint8* M_p) {
  // set appropriate bit flags
  reg.SR.N = reg.AC <  *M_p; 
  reg.SR.Z = reg.AC == *M_p; 
  reg.SR.C = reg.AC >= *M_p; 
  return;
}

// Compare Memory and Index X
void MOS_6502::CPX(const uint8* M_p) {
  // set appropriate bit flags
  reg.SR.N = reg.X <  *M_p; 
  reg.SR.Z = reg.X == *M_p; 
  reg.SR.C = reg.X >= *M_p; 
  return;
}

// Compare Memory and Index Y
void MOS_6502::CPY(const uint8* M_p) {
  // set appropriate bit flags
  reg.SR.N = reg.Y <  *M_p; 
  reg.SR.Z = reg.Y == *M_p; 
  reg.SR.C = reg.Y >= *M_p; 
  return;
}

// Test Bits in Memory with Accumulator
void MOS_6502::BIT(const uint8* M_p) {
  // zero flag is set to result of A AND M
  reg.SR.Z = Check_Not_Zero(reg.AC & *M_p);
  // M7 -> N, M6 -> V
  reg.SR.N = Check_Nth_Bit(*M_p, BIT7);
  reg.SR.V = Check_Nth_Bit(*M_p, BIT6);
  return;
}

// ----------------------------------------------------------------------------
// Set and Clear Flag Instructions
// ----------------------------------------------------------------------------

// Clear Carry Flag
void MOS_6502::CLC() {
  reg.SR.C = 0;
  return;
}

// Clear Decimal Mode
void MOS_6502::CLD() {
  reg.SR.D = 0;
  return;
}

// Clear Interrupt Disable Bit
void MOS_6502::CLI() {
  reg.SR.I = 0;
  return;
}

// Clear Overflow Flag
void MOS_6502::CLV() {
  reg.SR.V = 0;
  return;
}

// ----------------------------------------------------------------------------
// Other Instructions
// ----------------------------------------------------------------------------

// Force Break
void MOS_6502::BRK() {
  // interrupt, push PC+2, push SR
  reg.SR.I = 1; // Set interrupt flag
  // TODO: Pushes
}


// ----------------------------------------------------------------------------
// Local Function Definitions
// ----------------------------------------------------------------------------
static inline uint16 Compute_Branch(uint16 PC, uint8 M) {
  // Cast the memory M to a signed int and then add to the program counter to
  // compute the branch.
  return PC + static_cast<int8>(M);
}
