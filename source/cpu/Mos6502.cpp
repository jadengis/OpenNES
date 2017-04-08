//===-- source/cpu/Mos6502.cpp - Mos6502 Cpu Class Impl ---------*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of the public interface for the
/// Mos6502 class.
///
//===----------------------------------------------------------------------===//
#include "common/CommonTypes.h"

#include "memory/Reference.h"
#include "cpu/CpuException.h"
#include "cpu/Mos6502.h"
#include "cpu/Mos6502Instruction.h"

using namespace Cpu;

// CpuBase class methods
void Mos6502::init() {
}

void Mos6502::run() {
}

void Mos6502::step() {
  if(getCycleCount() == 0) {
    fetchOpcode();
    decodeOpcode();
    executeOpcode();
  }
  decrementCycles();
}

void Mos6502::reset() {
  // load RESET vector from memory
  reg.pc = getMmu().loadVector(RESET_VECTOR);
}

void Mos6502::trace() {
}

void Mos6502::shutdown() {
}

void Mos6502::fetchOpcode() {
  // call the implement of fetchOpcode
  fetchOpcodeImpl();
}

void Mos6502::decodeOpcode() {
  // call the implement of fetchOpcode
  decodeOpcodeImpl();
}

void Mos6502::executeOpcode() {
  executeOpcodeImpl();
}

void Mos6502::incrementRegPC(const Mos6502Instruction& inst) {
  // Certain instruction like jumps and branchs should not have the PC
  // incremented upon completion of the instruction as the PC is already
  // set to what it should be.
  if(inst.adjustRegPC) {
    incrementRegPC(static_cast<byte>(inst.type) + 1);
  }
}
