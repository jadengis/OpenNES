//===-- source/nes/CartridgeMapper.cpp - Cartridge Mapper -------*- C++ -*-===//
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

using namespace Nes;
using namespace Memory;

CartridgeMapper::CartridgeMapper(
    std::vector<std::shared_ptr<Ram<byte>>>& prgRams,
    std::vector<std::shared_ptr<Rom<byte>>>& prgRoms,
    std::vector<std::shared_ptr<Rom<byte>>>& chrRoms) :
  prgRams(prgRams),
  prgRoms(prgRoms),
  chrRoms(chrRoms) { }

// Get and Set methods.
std::weak_ptr<Ram<byte>> CartridgeMapper::getPrgRam() const {
  return prgRam;
}

void CartridgeMapper::setPrgRam(std::size_t index) {
  prgRam = prgRams.at(index);
}

std::weak_ptr<Rom<byte>> CartridgeMapper::getLowerPrgRom() const {
  return lowerPrgRom;
}

void CartridgeMapper::setLowerPrgRom(std::size_t index) {
  lowerPrgRom = prgRoms.at(index);
}

std::weak_ptr<Rom<byte>> CartridgeMapper::getUpperPrgRom() const {
  return upperPrgRom;
}

void CartridgeMapper::setUpperPrgRom(std::size_t index) {
  upperPrgRom = prgRoms.at(index);
}

std::vector<std::shared_ptr<Ram<byte>>>& CartridgeMapper::getPrgRams() {
  return prgRams;
}

std::vector<std::shared_ptr<Rom<byte>>>& CartridgeMapper::getPrgRoms() {
  return prgRoms;
}

std::vector<std::shared_ptr<Rom<byte>>>& CartridgeMapper::getChrRoms() {
  return chrRoms;
}
