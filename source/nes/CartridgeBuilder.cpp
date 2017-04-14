//===-- source/nes/CartridgeBuilder.cpp - Cartridge Builder -----*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of the CartridgeBuilder class.
///
//===----------------------------------------------------------------------===//

#include <iterator>
#include <fstream>

#include "common/CommonTypes.h"
#include "common/CommonException.h"
#include "nes/Cartridge.h"
#include "nes/CartridgeBuilder.h"

using namespace Nes;

std::unique_ptr<Cartridge> CartridgeBuilder::build() {
  // Open an input stream from the inputFile, and first, read in the file header.
  std::ifstream romStream(inputFile, std::ios::binary);
  std::istream_iterator<byte> romFileItr(romStream);
  std::array<byte, INES_HEADER_SIZE> header;

  for(std::size_t i = 0; i < INES_HEADER_SIZE; i++) {
    header.at(i) = *romFileItr; 
    romFileItr++;
  }

  // Parse the file header for the contained rom configuration
  parseiNesHeader(header);

  // File header is okay, so import the rest of the file, construct the 
  // Cartridge object and wrap it in a unique_ptr.
  std::vector<byte> romFile(romFileItr, std::istream_iterator<byte>());
  cartridgePtr = std::unique_ptr<Cartridge>(new Cartridge(options, romFile));

  // move the unique_ptr out of the builder p
  return std::move(cartridgePtr);
}


void CartridgeBuilder::parseiNesHeader(std::array<byte, INES_HEADER_SIZE> header) {
  // Check if the file is in the valid fomart by checking the first 4 bytes
  bool isInvalid = false;
  for(std::size_t i = 0; i < 4; i++) {
    isInvalid |= (header.at(i) != NES_TOKEN.at(i));
  }
  if(isInvalid) {
    throw Exception::InvalidFormatException("The input file " + inputFile + " is "
        + "in an invalid format.");
  }
  // At this point we know the we are in the correct format, so we will start
  // parsing out the bytes.
  // Byte 4 is number of 16kB Roms
  options.num16kRom = header.at(4);
  // Byte 5 is number of 8kB VRoms
  options.num8kVRom = header.at(5);
  // Byte 8 is number of 8kB Rams. If zero, we assume 1 for compatibility with
  // old version of the iNES standard.
  options.num8kVRom = (header.at(8) == 0) ? 1 : header.at(8);
  // iNES mapper index = byte6[4-7]|byte7[4-7]
  options.mapperIndex = (header.at(6) >> 4) | (header.at(7) & 0xF0);

  // Miscellaneous flags
  options.isVerticalMirroring = header.at(6) & 0x1;
  options.hasBatteryBackedRam = header.at(6) & 0x2;
  options.hasTrainer = header.at(6) & 0x4;
  options.fourScreenVram = header.at(6) & 0x8;
  options.isVSSystem = header.at(7) & 0x1;
  options.isPAL = header.at(9) & 0x1;

  // All other bits of header should be zeroed out at this time.
  
}

CartridgeBuilder& CartridgeBuilder::setInputFile(std::string inputFile) { 
  // Set the input file and return a reference for chaining.
  this->inputFile = inputFile;
  return *this;
}
