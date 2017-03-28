//===-- source/cpu/Mos6502Mmu.cpp - Mos6502 Cpu Class Impl ---------*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of the Cpu memory management unit.
///
//===----------------------------------------------------------------------===//
#include "cpu/CpuException.h"
#include "cpu/Mos6502Mmu.h"

using namespace Cpu;
using namespace Memory;

// Constructor
Mos6502Mmu::Mos6502Mmu(
    const byte& regX, 
    const byte& regY, 
    const Mapper<byte>& memMap) :
  indexRegX(regX),
  indexRegY(regY),
  memoryMap(memMap) {}

//===---------------------------------------------------------------------===//
// Private inlined implementation functions
//===---------------------------------------------------------------------===//
Reference<byte> Mos6502Mmu::absoluteImpl(Vaddr vaddr) const {
  // Map this virtual address to its corresponding hardware bank.
  std::shared_ptr<Bank<byte>> dataBank = memoryMap.mapToHardware(vaddr);
  // Compute the index into this dataBank by subtracting the base address
  std::size_t index = vaddr.val - dataBank->getBaseAddress().val;
  return Reference<byte>(dataBank, index);
}

Vaddr Mos6502Mmu::indirectImpl(Vaddr vaddr) const {
  // Compute the absolute address to use
  std::shared_ptr<Bank<byte>> dataBank = memoryMap.mapToHardware(vaddr);
  std::size_t index = vaddr.val - dataBank->getBaseAddress().val;
  // Now grab the real address
  Vaddr effectiveAddress;
  effectiveAddress.ll = dataBank->read(index);
  effectiveAddress.hh = dataBank->read(index + 1);
  return effectiveAddress;
}

Reference<byte> Mos6502Mmu::zeropageImpl(Vaddr vaddr) const {
  // find the zeropage memory bank. since we are on the zeropage, we do not
  // need to compute a new index. vaddr's low byte is sufficient
  std::shared_ptr<Bank<byte>> dataBank = memoryMap.mapToHardware(vaddr);
  return Reference<byte>(dataBank, vaddr.ll);
}

//===---------------------------------------------------------------------===//
// Mos6502Mmu member functions
//===---------------------------------------------------------------------===//
Reference<byte> Mos6502Mmu::absolute(Vaddr vaddr) {
  return absoluteImpl(vaddr);
}

Reference<byte> Mos6502Mmu::absoluteXIndexed(Vaddr vaddr) {
  // Add with carry the index X to the virtual address
  vaddr.val += indexRegX;
  return absoluteImpl(vaddr);
}

Reference<byte> Mos6502Mmu::absoluteYIndexed(Vaddr vaddr) {
  // Add with carry the index Y to the virtual address
  vaddr.val += indexRegY;
  return absoluteImpl(vaddr);
}

Reference<byte> Mos6502Mmu::indirect(Vaddr vaddr) {
  return absoluteImpl(indirectImpl(vaddr));
}

Reference<byte> Mos6502Mmu::xIndexedIndirect(Vaddr vaddr) {
  // Increment the low byte of our address without carry; ensure high byte is zero.
  vaddr.ll += indexRegX;
  vaddr.hh = 0;
  // do indirect addressing.
  return absoluteImpl(indirectImpl(vaddr));
}

Reference<byte> Mos6502Mmu::indirectYIndexed(Vaddr vaddr) {
  // Compute the effective address, increment by Y and read from that address.
  Vaddr effectiveAddress = indirectImpl(vaddr);
  effectiveAddress.val += indexRegY;
  return absoluteImpl(effectiveAddress);
}

Reference<byte> Mos6502Mmu::zeropage(Vaddr vaddr) {
  return zeropageImpl(vaddr);
}

Reference<byte> Mos6502Mmu::zeropageXIndexed(Vaddr vaddr) {
  vaddr.ll += indexRegX;
  return zeropageImpl(vaddr);
}

Reference<byte> Mos6502Mmu::zeropageYIndexed(Vaddr vaddr) {
  vaddr.ll += indexRegY;
  return zeropageImpl(vaddr);
}
