// OsNES Project | source/cpu_6502.cpp
// Description:
// Functional specification for the MOS 6502 CPU.
// Any and all details related to the overall operation ofthe 6502 should
// be implemented here.
//
// Authors: 
// John Dengis
//
#include "cpu_6502.h"

// ----------------------------------------------------------------------------
// Instruction emulation functions
// ----------------------------------------------------------------------------
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

void MOS_6502::AND(const uint8 *M_p) {
  // AND the memory M with the Accumulator
  reg.AC = reg.AC & *M_p;
  // Set the remaining SR flags
  reg.SR.Z = Check_Zero(reg.AC);
  reg.SR.N = Check_Neg_Bit(reg.AC);
  return;
}

void MOS_6502::ASL(uint8* M_p) {
  // Set the carry bit.
  reg.SR.C = Check_Neg_Bit(*M_p);
  // Shift memory (or accumulator) left 1
  *M_p = *M_p << 1;
  // Set the remaining SR flags
  reg.SR.Z = (*M_p == 0);
  reg.SR.N = Check_Neg_Bit(*M_p);
  return;
}

void MOS_6502::BCC(uint8* M_p) {
  if(reg.SR.C == 0) {
    // Condition true, branch to PC + offset
    reg.PC = reg.PC + static_cast<int8>(*M_p);
  }
  return;
}

void MOS_6502::BCS(uint8* M_p) {
  if(reg.SR.C == 1) {
    // Condition true, branch to PC + offset
    reg.PC = reg.PC + static_cast<int8>(*M_p);
  }
  return;
