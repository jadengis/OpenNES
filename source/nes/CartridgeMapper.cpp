//===-- source/nes/Cartridge.cpp - Cartridge --------------------*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of the Cartridge class.
///
//===----------------------------------------------------------------------===//

#include <iterator>

#include "common/CommonTypes.h"
#include "common/CommonException.h"
#include "nes/Cartridge.h"

using namespace Nes;
using namespace Memory;

Cartridge& Cartridge::operator=(Cartridge&& otherCartridge) {
  if(this != &otherCartridge) {
    mapperPtr = std::move(otherCartridge.mapperPtr);
    trainer = std::move(otherCartridge.trainer);
    prgRams = std::move(otherCartridge.prgRams);
    prgRoms = std::move(otherCartridge.prgRoms);
    chrRoms = std::move(otherCartridge.chrRoms);
  }
  return *this;
}

Cartridge::Cartridge(CartridgeOptions options, const std::vector<byte>& romFile) {
  // Iterate thourgh the list of options, building the cartridge internals. 
  // Acquire an iterator to the begining of the romFile.
  auto romFileItr = std::begin(romFile);
  // populate the 512 byte trainer if necessary.
  if(options.hasTrainer) {
    trainer = std::make_shared<Rom<byte>>();
    trainer->load(romFileItr, romFileItr + SIZE_512B);
    romFileItr += SIZE_512B;
  }

  // resize the number of RAMs, and resize each RAM to 8k.
  prgRams.resize(options.num8kRam);
  for(auto ram : prgRams) {
    ram->resize(SIZE_8KB);
  }

  // populate all 16k PRG ROMs
  prgRoms.reserve(options.num16kRom);
  for(std::size_t i = 0; i < options.num16kRom; i++) {
    prgRoms.emplace_back(std::make_shared<Rom<byte>>());
    prgRoms.back()->load(romFileItr, romFileItr + SIZE_16KB);
    romFileItr += SIZE_16KB;
  }

  // populate all 8k CHR ROMS
  chrRoms.reserve(options.num8kVRom);
  for(std::size_t i = 0; i < options.num8kVRom; i++) {
    chrRoms.emplace_back(std::make_shared<Rom<byte>>());
    chrRoms.back()->load(romFileItr, romFileItr + SIZE_8KB);
    romFileItr += SIZE_8KB;
  }

  // Check to make sure that the entire romFile was read
  if(romFileItr != std::end(romFile)) {
    throw Exception::InvalidFormatException("Input ROM file had an unexpected number of bytes.");
  }

  // determine the kind of memory mapper and build it.
  
}
