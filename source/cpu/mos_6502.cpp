// OsNES Project | source/cpu_6502.cpp
// Description:
// Functional specification for the MOS 6502 CPU.
// Any and all details related to the overall operation ofthe 6502 should
// be implemented here.
//
// Instruction implementation details are based on the descriptions here:
// http://e-tradition.net/bytes/6502/6502_instruction_set.html
//
// Authors: 
// John Dengis
//
#include "mem.h"
#include "mos_6502.h"

// Static Functions
static inline uint8  Check_Zero(uint8 x);
static inline uint8  Check_Not_Zero(uint8 x);
static inline uint8  Check_Nth_Bit(uint8 x, Bit_Position N);
static inline uint16 Compute_Branch(uint16 PC, uint8 M);

using namespace com;

// ----------------------------------------------------------------------------
// Load and Store Instructons
// ----------------------------------------------------------------------------

// Load Accumulator with Memory
void MOS_6502::LDA(const Mem::Ref M) {
  // Copy memory to accumulator
  reg.AC = *M;
  // set appropriate status register flags
  reg.SRF.Z = Check_Zero(reg.AC);
  reg.SRF.N = Check_Nth_Bit(reg.AC, Bit_Position::bit7);
  return;
}

// Load Index X with Memory
void MOS_6502::LDX(const Mem::Ref M) {
  // Copy memory to X register
  reg.X = *M;
  // set appropriate status register flags
  reg.SRF.Z = Check_Zero(reg.AC);
  reg.SRF.N = Check_Nth_Bit(reg.AC, Bit_Position::bit7);
  return;
}

// Load Index Y with Memory
void MOS_6502::LDY(const Mem::Ref M) {
  // Copy memory to Y register
  reg.Y = *M;
  // set appropriate status register flags
  reg.SRF.Z = Check_Zero(reg.AC);
  reg.SRF.N = Check_Nth_Bit(reg.AC, Bit_Position::bit7);
  return;
}

// Store Accumulator in Memory
void MOS_6502::STA(Mem::Ref M) {
  // Copy accumulator to memory location M
  *M = reg.AC;
  return;
}

// Store Index X in Memory
void MOS_6502::STX(Mem::Ref M) {
  // Copy X register to memory location M
  *M = reg.X;
  return;
}

// Store Index Y in Memory
void MOS_6502::STY(Mem::Ref M) {
  // Copy Y register to memory location M
  *M = reg.Y;
  return;
}


// ----------------------------------------------------------------------------
// Arithmetic Instructions
// ----------------------------------------------------------------------------

// Add Memory to Accumulator with Carry
void MOS_6502::ADC(const Mem::Ref M) {
  // Store the original value of the accumulator
  byte AC = reg.AC; 

  // ADD the memory M to Accumulator + carry if set
  reg.AC = AC + *M + reg.SRF.C;
  // Set the carry bit ( 1 if the add overflowed, 0 otherwise
  reg.SRF.C = (reg.AC < AC);
  // Set overflow flag
  reg.SRF.V = Check_Integer_Overflow(
  // Set zero flag
  reg.SRF.Z = Check_Zero(reg.AC);
  // TODO: Set the N, V.
  return;
}


// ----------------------------------------------------------------------------
// Increment and Decrement Instructions
// ----------------------------------------------------------------------------

// Increment Memory by One
void MOS_6502::INC(Mem::Ref M) {
  *M = *M + 1;
  // set appropriate status register flags
  reg.SRF.Z = Check_Zero(*M);
  reg.SRF.N = Check_Nth_Bit(*M, Bit_Position::bit7);
  return;
}

// Increment Index X by One
void MOS_6502::INX() {
  reg.X = reg.X + 1;
  // set appropriate status register flags
  reg.SRF.Z = Check_Zero(reg.X);
  reg.SRF.N = Check_Nth_Bit(reg.X, Bit_Position::bit7);
  return;
}

// Increment Memory by One
void MOS_6502::INY() {
  reg.Y = reg.Y + 1;
  // set appropriate status register flags
  reg.SRF.Z = Check_Zero(reg.Y);
  reg.SRF.N = Check_Nth_Bit(reg.Y, Bit_Position::bit7);
  return;
}

// Decrement Memory by One
void MOS_6502::DEC(Mem::Ref M) {
  *M = *M - 1;
  // set appropriate status register flags
  reg.SRF.Z = Check_Zero(*M);
  reg.SRF.N = Check_Nth_Bit(*M, Bit_Position::bit7);
  return;
}

// Decrement Index X by One
void MOS_6502::DEX() {
  reg.X = reg.X - 1;
  // set appropriate status register flags
  reg.SRF.Z = Check_Zero(reg.X);
  reg.SRF.N = Check_Nth_Bit(reg.X, Bit_Position::bit7);
  return;
}

// Decrement Memory by One
void MOS_6502::DEY() {
  reg.Y = reg.Y - 1;
  // set appropriate status register flags
  reg.SRF.Z = Check_Zero(reg.Y);
  reg.SRF.N = Check_Nth_Bit(reg.Y, Bit_Position::bit7);
  return;
}


// ----------------------------------------------------------------------------
// Logical Instructions
// ----------------------------------------------------------------------------

// AND Memory with Accumulator
void MOS_6502::AND(const Mem::Ref M) {
  // AND the memory M with the Accumulator
  reg.AC = reg.AC & *M;
  // Set the remaining status register flags
  reg.SRF.Z = Check_Zero(reg.AC);
  reg.SRF.N = Check_Nth_Bit(reg.AC, Bit_Position::bit7);
  return;
}

// EOR Exclusive-OR Memory with Accumulator
void MOS_6502::EOR(const Mem::Ref M) {
  // XOR the memory M with the Accumulator
  reg.AC = reg.AC ^ *M;
  // Set the remaining status register flags
  reg.SRF.Z = Check_Zero(reg.AC);
  reg.SRF.N = Check_Nth_Bit(reg.AC, Bit_Position::bit7);
  return;
}

// OR Memory with Accumulator
void MOS_6502::ORA(const Mem::Ref M) {
  // OR the memory M with the Accumulator
  reg.AC = reg.AC | *M;
  // Set the remaining status register flags
  reg.SRF.Z = Check_Zero(reg.AC);
  reg.SRF.N = Check_Nth_Bit(reg.AC, Bit_Position::bit7);
  return;
}


// ----------------------------------------------------------------------------
// Jump, Branch, Compare and Test Bits Instructions
// ----------------------------------------------------------------------------

// Jump to New Location
void MOS_6502::JMP(const Mem::Ref M) {
  // Grab the new PC bytes from memory location M.
  // (PC+1) -> PCL
  // (PC+2) -> PCH
  // Note that after the opcode has been fetched PC is incremented, so by
  // convention, we have PC+1 = M, PC+2 = M+1.
  reg.PCL = *M;
  reg.PCH = *(M+1);
  return;
}

// Branch on Carry Clear
void MOS_6502::BCC(const Mem::Ref M) {
  if(reg.SRF.C == 0) {
    // Condition true, branch to PC + offset
    reg.PC = Compute_Branch(reg.PC,*M);
  }
  return;
}

// Branch of Carry Set
void MOS_6502::BCS(const Mem::Ref M) {
  if(reg.SRF.C == 1) {
    // Condition true, branch to PC + offset
    reg.PC = Compute_Branch(reg.PC,*M);
  }
  return;
}

// Branch on Result Zero
void MOS_6502::BEQ(const Mem::Ref M) {
  if(reg.SRF.Z == 1) {
    // Condition true, branch to PC + offset
    reg.PC = Compute_Branch(reg.PC,*M);
  }
  return;
}

// Branch on Result Minus
void MOS_6502::BMI(const Mem::Ref M) {
  if(reg.SRF.N == 1) {
    // Condition true, branch to PC + offset
    reg.PC = Compute_Branch(reg.PC,*M);
  }
  return;
}

// Branch on Result not Zero
void MOS_6502::BNE(const Mem::Ref M) {
  if(reg.SRF.Z == 0) {
    // Condition true, branch to PC + offset
    reg.PC = Compute_Branch(reg.PC,*M);
  }
  return;
}

// Branch on Result Plus
void MOS_6502::BPL(const Mem::Ref M) {
  if(reg.SRF.N == 0) {
    // Condition true, branch to PC + offset
    reg.PC = Compute_Branch(reg.PC,*M);
  }
  return;
}

// Branch on Overflow Clear
void MOS_6502::BVC(const Mem::Ref M) {
  if(reg.SRF.V == 0) {
    // Condition true, branch to PC + offset
    reg.PC = Compute_Branch(reg.PC,*M);
  }
  return;
}

// Branch on Overflow Set
void MOS_6502::BVS(const Mem::Ref M) {
  if(reg.SRF.V == 1) {
    // Condition true, branch to PC + offset
    reg.PC = Compute_Branch(reg.PC,*M);
  }
  return;
}

// Compare Memory with Accumulator
void MOS_6502::CMP(const Mem::Ref M) {
  // set appropriate bit flags
  reg.SRF.N = reg.AC <  *M; 
  reg.SRF.Z = reg.AC == *M; 
  reg.SRF.C = reg.AC >= *M; 
  return;
}

// Compare Memory and Index X
void MOS_6502::CPX(const Mem::Ref M) {
  // set appropriate bit flags
  reg.SRF.N = reg.X <  *M; 
  reg.SRF.Z = reg.X == *M; 
  reg.SRF.C = reg.X >= *M; 
  return;
}

// Compare Memory and Index Y
void MOS_6502::CPY(const Mem::Ref M) {
  // set appropriate bit flags
  reg.SRF.N = reg.Y <  *M; 
  reg.SRF.Z = reg.Y == *M; 
  reg.SRF.C = reg.Y >= *M; 
  return;
}

// Test Bits in Memory with Accumulator
void MOS_6502::BIT(const Mem::Ref M) {
  // zero flag is set to result of A AND M
  reg.SRF.Z = Check_Not_Zero(reg.AC & *M);
  // M7 -> N, M6 -> V
  reg.SRF.N = Check_Nth_Bit(*M, Bit_Position::bit7);
  reg.SRF.V = Check_Nth_Bit(*M, Bit_Position::bit6);
  return;
}


// ----------------------------------------------------------------------------
// Shift and Rotate Instructions
// ----------------------------------------------------------------------------

// Shift Left One Bit (Memory or Accumulator)
void MOS_6502::ASL(Mem::Ref M) {
  // Set the carry bit.
  reg.SRF.C = Check_Nth_Bit(*M, Bit_Position::bit7);
  // Shift memory (or accumulator) left 1
  *M = *M << 1;
  // Set the remaining SR flags
  reg.SRF.Z = Check_Zero(*M);
  reg.SRF.N = Check_Nth_Bit(*M, Bit_Position::bit7);
  return;
}


// ----------------------------------------------------------------------------
// Transfer Instructions
// ----------------------------------------------------------------------------

// Transfer Accumulator to Index X
void MOS_6502::TAX() {
  // Copy accumulator to X register
  reg.X = reg.AC;
  // set appropriate status register flags
  reg.SRF.Z = Check_Zero(reg.X);
  reg.SRF.N = Check_Nth_Bit(reg.X, Bit_Position::bit7);
  return;
}

// Transfer Accumulator to Index Y
void MOS_6502::TAY() {
  // Copy accumulator to Y register
  reg.Y = reg.AC;
  // set appropriate status register flags
  reg.SRF.Z = Check_Zero(reg.Y);
  reg.SRF.N = Check_Nth_Bit(reg.Y, Bit_Position::bit7);
  return;
}

// Transfer Index X to Accumulator
void MOS_6502::TXA() {
  // Copy X register to accumulator
  reg.AC = reg.X;
  // set appropriate status register flags
  reg.SRF.Z = Check_Zero(reg.AC);
  reg.SRF.N = Check_Nth_Bit(reg.AC, Bit_Position::bit7);
  return;
}

// Transfer Index Y to Accumulator
void MOS_6502::TAY() {
  // Copy Y register to accumulator
  reg.AC = reg.Y;
  // set appropriate status register flags
  reg.SRF.Z = Check_Zero(reg.AC);
  reg.SRF.N = Check_Nth_Bit(reg.AC, Bit_Position::bit7);
  return;
}


// ----------------------------------------------------------------------------
// Stack Instructions
// ----------------------------------------------------------------------------

// Transfer Stack Pointer to Index X
void MOS_6502::TSX() {
  // Copy Stack Pointer to X register
  reg.X = reg.SP;
  // set appropriate status register flags
  reg.SRF.Z = Check_Zero(reg.X);
  reg.SRF.N = Check_Nth_Bit(reg.X, Bit_Position::bit7);
  return;
}

// Transfer Index X to Stack Pointer
void MOS_6502::TXS() {
  // Copy X register to stack pointer
  reg.SP = reg.X;
  // set appropriate status register flags
  reg.SRF.Z = Check_Zero(reg.SP);
  reg.SRF.N = Check_Nth_Bit(reg.SP, Bit_Position::bit7);
  return;
}

// Push Accumulator on the Stack
void MOS_6502::PHA() {
  stack.push(reg.AC);
  return;
}

// Push Processor Status on the Stack
void MOS_6502::PHP() {
  stack.push(reg.SR);
  return;
}

// Pull Accumulator from Stack
void MOS_6502::PLA() {
  reg.AC = stack.pull();
  // set appropriate status register flags
  reg.SRF.Z = Check_Zero(reg.SP);
  reg.SRF.N = Check_Nth_Bit(reg.SP, Bit_Position::bit7);
  return;
}

// Pull Processor Status from Stack
void MOS_6502::PLP() {
  reg.SR = stack.pull();
  return;
}
  

// ----------------------------------------------------------------------------
// Subroutine Instructions
// ----------------------------------------------------------------------------

// Jump to New Location Saving Return Address
void MOS_6502::JSR(const Mem::Ref M) {
  // Push the value PC+2 onto the stack then grab the new PC bytes from memory
  // location M.
  // (PC+1) -> PCL
  // (PC+2) -> PCH
  // Note that after the opcode has been fetched PC is incremented, so by
  // convention, we have PC+1 = M, PC+2 = M+1.
  reg.PC = reg.PC + 2;
  stack.push(reg.PCH);
  stack.push(reg.PCL);
  reg.PCL = *M;
  reg.PCH = *(M+1);
  return;
}

void MOS_6502::RTI() {
  // pull status register from stack, followed by program counter
  // BRK implementation pushes PCH then PCL then SR so must pull in reverse order
  reg.SR  = stack.pull()
  reg.PCL = stack.pull()
  reg.PCH = stack.pull()
  return;
}

// Return from Subroutine
void MOS_6502::RTS() {
  // pull program counter from the stack and increment to land on new instruction
  // JSR implementation pushes PCH then PCL so must pull PCL then PCH
  reg.PCL = stack.pull();
  reg.PCH = stack.pull();
  reg.PC  = reg.PC + 1;
  return;
}


// ----------------------------------------------------------------------------
// Set and Reset (Clear) Instructions
// ----------------------------------------------------------------------------

// Clear Carry Flag
void MOS_6502::CLC() {
  reg.SRF.C = 0;
  return;
}

// Clear Decimal Mode
void MOS_6502::CLD() {
  reg.SRF.D = 0;
  return;
}

// Clear Interrupt Disable Bit
void MOS_6502::CLI() {
  reg.SRF.I = 0;
  return;
}

// Clear Overflow Flag
void MOS_6502::CLV() {
  reg.SRF.V = 0;
  return;
}

// Set Carry Flag
void MOS_6502::SEC() {
  reg.SRF.C = 1;
  return;
}

// Set Decimal Flag
void MOS_6502::SED() {
  reg.SRF.D = 1;
  return;
}

// Set Interrupt Disable Status
void MOS_6502::SEI() {
  reg.SRF.I = 1;
  return;
}


// ----------------------------------------------------------------------------
// Other Instructions
// ----------------------------------------------------------------------------

// No Operation
void MOS_6502::NOP() {
  return;
}

// Force Break
void MOS_6502::BRK() {
  // interrupt, push PC+2, push SR
  reg.SRF.I = 1; // Set interrupt flag
  stack.push(reg.PCH);
  stack.push(reg.PCL);
  stack.push(reg.SR);
  return;
}


// ----------------------------------------------------------------------------
// Static Function Definitions
// ----------------------------------------------------------------------------

static inline uint8 Check_Zero(uint8 x) {
  // Returns 1 if 0, 0 otherwise
  return x == 0;
}

static inline uint8 Check_Not_Zero(uint8 x) {
  // Returns 1 if not 0, 0 otherwise
  return x != 0;
}

static inline uint8 Check_Nth_Bit(uint8 x, Bit_Position N) {
  // Returns 1 if Nth bit 1, 0 otherwise. Bit indexing it 0 - 7.
  return (x >> static_cast<uint8>(N)) & ONE_BIT_MASK;
}

static inline uint16 Compute_Branch(uint16 PC, uint8 M) {
  // Cast the memory M to a signed int and then add to the program counter to
  // compute the branch.
  return PC + static_cast<int8>(M);
}
