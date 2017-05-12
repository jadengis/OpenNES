//===-- source/nes/mappers/NRom.cpp - NRom Mapper ---------------*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of the CartridgeMapper class.
///
//===----------------------------------------------------------------------===//

#include "common/CommonTypes.h"
#include "memory/Ram.h"
#include "memory/Rom.h"
#include "nes/CartridgeMapper.h"
#include "nes/mappers/NRom.h"

using namespace Nes;
using namespace Memory;
using namespace Nes::Mappers;

NRom::NRom(
    std::vector<std::shared_ptr<Ram<byte>>>& prgRams,
    std::vector<std::shared_ptr<Rom<byte>>>& prgRoms,
    std::vector<std::shared_ptr<Rom<byte>>>& chrRoms) :
  CartridgeMapper(prgRams, prgRoms, chrRoms) {
  // Set the prgRam, lower and upper prgRoms
  setPrgRam(0);
  setLowerPrgRom(0);
  setUpperPrgRom(1);
}

std::shared_ptr<Bank<byte>> NRom::mapToHardware(Vaddr vaddr) const {
  addr address = vaddr.val;
  if(address < 0x6000) {
    return nullptr;
  }
  if(0x6000 <= address && address < 0x8000) {
    return getPrgRam().lock();
  }
  if(0x8000 <= address && address < 0xC000) {
    return getLowerPrgRom().lock();
  }
  if(0xC000 <= address && address <= 0xFFFF) {
    return getUpperPrgRom().lock();
  }
  return nullptr;
}
