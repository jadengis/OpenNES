//===-- include/nes/CartridgeMapper.h - Cartridge Mapper --------*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//  
//===----------------------------------------------------------------------===//
///
/// \file
/// This file declares the Nes::CartridgeMapper class.
///
//===----------------------------------------------------------------------===//
#ifndef NES_CARTRIDGE_MAPPER_H
#define NES_CARTRIDGE_MAPPER_H

#include <memory>

#include "common/CommonTypes.h"
#include "memory/Mapper.h"
#include "memory/Ram.h"
#include "memory/Rom.h"

namespace Nes {
// Forward Declarations
class CartridgeMapperBuilder;

/// \class CartridgeMapper
/// \brief This class represents a memory mapper from an Nes Cartridge. This
/// base class contains the common elements between the more specific 
class CartridgeMapper : public Memory::Mapper<byte> {
  /// CartridgeMapperBuilder is a friend of the CartridgeMapper. CartridgeMappers
  /// can only be built by the CartridgeMapperBuilder.
  friend CartridgeMapperBuilder;

  public:
    /// Destroy a CartridgeMapper
    ~CartridgeMapper() {}

  protected:
    /// Build a CartridgeMapper.
    /// \param prgRams The array of PRG RAMs from the containing cartridge.
    /// \param prgRoms The array of PRG ROMs from the containing cartridge.
    /// \param chrRoms The array of CHR ROMs from the containing cartridge.
    CartridgeMapper(
        std::vector<std::shared_ptr<Memory::Ram<byte>>>& prgRams,
        std::vector<std::shared_ptr<Memory::Rom<byte>>>& prgRoms,
        std::vector<std::shared_ptr<Memory::Rom<byte>>>& chrRoms
        );

    /// Get the currently loaded PRG RAM.
    /// \returns The loaded PRG RAM.
    std::weak_ptr<Memory::Ram<byte>> getPrgRam() const;

    /// Set the currently loaded PRG RAM.
    /// \param index Index into the RAM array.
    void setPrgRam(std::size_t index);
    
    /// Get the currently loaded lower PRG ROM.
    /// \returns The loaded lower PRG ROM.
    std::weak_ptr<Memory::Rom<byte>> getLowerPrgRom() const;

    /// Set the currently loaded lower PRG ROM.
    /// \param index Index into the ROM array.
    void setLowerPrgRom(std::size_t index);
    
    /// Get the currently loaded upper PRG ROM.
    /// \returns The loaded upper PRG ROM.
    std::weak_ptr<Memory::Rom<byte>> getUpperPrgRom() const;

    /// Set the currently loaded upper PRG ROM.
    /// \param index Index into the ROM array.
    void setUpperPrgRom(std::size_t index);
    
    /// Get the internal reference to the PRG RAM array.
    /// \returns The internal reference to the PRG RAM array.
    std::vector<std::shared_ptr<Memory::Ram<byte>>>& getPrgRams();

    /// Get the internal reference to the PRG ROM array.
    /// \returns The internal reference to the PRG ROM array.
    std::vector<std::shared_ptr<Memory::Rom<byte>>>& getPrgRoms();

    /// Get the internal reference to the CHR ROM array.
    /// \returns The internal reference to the CHR ROM array.
    std::vector<std::shared_ptr<Memory::Rom<byte>>>& getChrRoms();

  private:
    /// The base address reserved for PRG RAM.
    static constexpr const Vaddr& PRG_RAM_ADDR = {0x6000};

    /// The base address reserved for Lower PRG ROM.
    static constexpr const Vaddr& LOWER_PRG_ROM_ADDR = {0x8000};

    /// The base address reserved for Upper PRG ROM.
    static constexpr const Vaddr& UPPER_PRG_ROM_ADDR = {0xC000};

    /// The PRG RAM currently at base address 0x6000.
    std::weak_ptr<Memory::Ram<byte>> prgRam;

    /// The PRG ROM currently as base address 0x8000.
    std::weak_ptr<Memory::Rom<byte>> lowerPrgRom;

    /// The CHR ROM currently as base address 0xC000.
    std::weak_ptr<Memory::Rom<byte>> upperPrgRom;

    /// A reference to the PRG RAMs for this mappers Cartridge.
    std::vector<std::shared_ptr<Memory::Ram<byte>>>& prgRams;

    /// A reference to the PRG ROMs for this mappers Cartridge.
    std::vector<std::shared_ptr<Memory::Rom<byte>>>& prgRoms;

    /// A reference to the CHR ROMs for this mappers Cartridge.
    std::vector<std::shared_ptr<Memory::Rom<byte>>>& chrRoms;

};

} // namespace Nes

#endif // NES_CARTRIDGE_MAPPER_H //
