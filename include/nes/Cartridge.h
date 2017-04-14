//===-- include/nes/Cartridge.h - Nes Cartridge Class -----------*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//  
//===----------------------------------------------------------------------===//
///
/// \file
/// This file defines the Nes::Cartridge class.
///
//===----------------------------------------------------------------------===//
#ifndef NES_CARTRIDGE_H
#define NES_CARTRIDGE_H

#include <vector>

#include "common/CommonTypes.h"
#include "memory/Mapper.h"
#include "memory/Ram.h"
#include "memory/Rom.h"


namespace Nes {
// Forward declarations
class CartridgeBuilder;

/// \struct CartridgeOptions
/// \brief Options required for building a Cartridge.
/// This is a plain-old data structure for storing information pulled from the
/// cartridge file header, to be used when building a new Cartridge.
struct CartridgeOptions {
  /// The number of 8kB Ram banks.
  byte num8kRam;
  /// The number of 16kB Rom banks.
  byte num16kRom;
  /// The number of 8kB Video Rom banks.
  byte num8kVRom;
  /// iNes mapper index.
  byte mapperIndex;

  // various flags
  /// True if use vertical mirroring, otherwise use horizontal mirroring.
  bool isVerticalMirroring;
  /// True if has battery backed ram at $6000 - $7FFF.
  bool hasBatteryBackedRam;
  /// True if has 512-byte trainer at $7000-$71FF. This is a rare option.
  bool hasTrainer;
  /// True if using four-screen VRAM layout.
  bool fourScreenVram;
  /// True if using VS-System cartridge. THis is a rare option.
  bool isVSSystem;
  /// True if PAL cartridge, otherwise NTSC.
  bool isPAL;
};

/// \class Cartridge
/// \brief This class represents an Nes cartridge. It contains all cartridge
/// specific information related to the game being emulated.
class Cartridge {
  /// CartridgeBuilder is a friend of the Cartridge. Cartridges can only be
  /// built by the cartridge builder.
  friend CartridgeBuilder;

  public:
    /// Cartridges cannot be copied.
    Cartridge(const Cartridge&) = delete;
    /// Cartridges cannot be copy assigned.
    Cartridge& operator=(const Cartridge&) = delete;

    /// Cartridges can only be move assigned.
    /// \param otherCartridge Cartridge to move from.
    /// \returns Reference to this Cartridge.
    Cartridge& operator=(Cartridge&& otherCartridge);

    /// Get the memory mapper for this cartridge.
    /// \returns Reference to the contained memory mapper.
    inline const Memory::Mapper<byte>& getMapper() const;

  private:
    /// Number of bytes in a 512 byte object
    static constexpr const std::size_t SIZE_512B = 0x200;
    /// Number of bytes in an 8kB memory object
    static constexpr const std::size_t SIZE_8KB = 0x2000;
    /// Number of bytes in a 16kB memory object
    static constexpr const std::size_t SIZE_16KB = 0x4000;

    /// Constructor for Cartridge is private. Cartridges can only be built
    /// by the CartridgeBuilder.
    explicit Cartridge(CartridgeOptions options, const std::vector<byte>& romFile);

    /// The memory mapper for this cartridge.
    std::unique_ptr<Memory::Mapper<byte>> mapperPtr;  

    /// The array of PRG RAMs for this cartridge.
    std::vector<Memory::Ram<byte>> prgRams;

    /// The array of PRG ROMs for this cartridge.
    std::vector<Memory::Rom<byte>> prgRoms;

    /// The array of CHR ROMs for this cartdige.
    std::vector<Memory::Rom<byte>> chrRoms;

    /// 512 byte trainer.
    Memory::Rom<byte> trainer;
};

const Memory::Mapper<byte>& Cartridge::getMapper() const {
  return *mapperPtr;
}

} // namespace Nes

#endif // NES_CARTRIDGE_H //
