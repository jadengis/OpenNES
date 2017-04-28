//===-- source/nes/CartridgeMapperBuilder.cpp - Mapper Builder --*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of the CartridgeMapperBuilder class.
///
//===----------------------------------------------------------------------===//

#include "common/CommonTypes.h"
#include "common/CommonException.h"
#include "nes/CartridgeMapper.h"
#include "nes/CartridgeMapperBuilder.h"

#include "nes/mappers/NRom.h"

using namespace Nes;
using namespace Nes::Mappers;

std::unique_ptr<CartridgeMapper> CartridgeMapperBuilder::build() {
  // Look up the mapper index and build the corresponding mapper.
  // throw UnsupportedException if the mapper id is unsupported.
  switch(iNesIndex) {
    case NRom::iNesIndex:
      mapperPtr = std::unique_ptr<CartridgeMapper>(new NRom(prgRams, prgRoms, chrRoms));
    default:
      // mapper is unsupported.
      throw Exception::UnsupportedFeatureException("iNES mapper index "
          + std::to_string(iNesIndex) + " is not currently supported.");
  }

  // return the uniquePtr to the constructed cartridge mapper.
  return std::move(mapperPtr);

}

CartridgeMapperBuilder& CartridgeMapperBuilder::setiNESIndex(std::size_t iNesIndex) {
  // Set the iNES mapper index and return a reference for chaining.
  this->iNesIndex = iNesIndex;
  return *this;
}

CartridgeMapperBuilder& CartridgeMapperBuilder::setPrgRams(
    std::vector<std::shared_ptr<Memory::Ram<byte>>>& prgRams) { 
  // Set the prgRams and return a reference for chaining.
  this->prgRams = prgRams;
  return *this;
}

CartridgeMapperBuilder& CartridgeMapperBuilder::setPrgRoms(
    std::vector<std::shared_ptr<Memory::Rom<byte>>>& prgRoms) { 
  // Set the prgRams and return a reference for chaining.
  this->prgRoms = prgRoms;
  return *this;
}

CartridgeMapperBuilder& CartridgeMapperBuilder::setChrRoms(
    std::vector<std::shared_ptr<Memory::Rom<byte>>>& chrRoms) { 
  // Set the prgRams and return a reference for chaining.
  this->chrRoms = chrRoms;
  return *this;
}
