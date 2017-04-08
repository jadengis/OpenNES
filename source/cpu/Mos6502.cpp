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
  // call the implementation of fetchOpcode
  fetchOpcodeImpl();
}

void Mos6502::decodeOpcode() {
  // call the implementation of decodeOpcode
  decodeOpcodeImpl();
}

void Mos6502::executeOpcode() {
  // call the implementation of executeOpcode
  executeOpcodeImpl();
}
