//===-- source/cpu/Mos6502.cpp - Mos6502 Cpu Class Impl ---------*- C++ -*-===//
//
//                           The OsNES Project
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

void Mos6502::trace() {
}

void Mos6502::shutdown() {
}

// Run-time Emulation functions
byte Mos6502::fetchOpcode() {
}

Mos6502Instruction Mos6502::decodeOpcode(byte opcode) {
}

void Mos6502::executeOpcode(Mos6502Instruction inst) {
}

// Cpu state inspection methods.
int64 Mos6502::getCycleCount() {
  return cycleCount;
}

addr Mos6502::getRegPC() {
  return reg.pc;
}

byte Mos6502::getRegAC() {
  return reg.ac;
}

byte Mos6502::getRegX() {
  return reg.x;
}

byte Mos6502::getRegY() {
  return reg.y;
}

byte Mos6502::getRegSR() {
  return reg.sr;
}

byte Mos6502::getRegSP() {
  return reg.sp;
}
