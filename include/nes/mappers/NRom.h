//===-- include/nes/mappers/NRom.h - NRom Mapper ------- --------*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//  
//===----------------------------------------------------------------------===//
///
/// \file
/// This file declares the Nes::Mappers::NRom class.
///
//===----------------------------------------------------------------------===//
#ifndef NES_NROM_MAPPER_H
#define NES_NROM_MAPPER_H

#include <memory>

#include "common/CommonTypes.h"
#include "memory/Mapper.h"
#include "memory/Bank.h"
#include "nes/CartridgeMapper.h"

namespace Nes {
namespace Mappers {

/// \class NRom
/// \brief This class represents the memory mapper from Nintendo NROM
/// Cartridges. 
class NRom : public CartridgeMapper {
  /// CartridgeMapperBuilder is a friend of the NRom. NRom mappers
  /// can only be built by the CartridgeMapperBuilder.
  friend CartridgeMapperBuilder;

  public:
    /// The index of this memory mapper, specified by the iNES format. 
    static constexpr const size_t& iNesIndex = 0x00;

    /// Destroy an NRom
    ~NRom() {}

    /// Map an address from the Cpu to a piece of hardware in the Cartridge.
    /// \param vaddr Virtual address from the Cpu.
    /// \returns shared_ptr to the hardware on the Cartridge.
    std::shared_ptr<Memory::Bank<byte>> mapToHardware(Vaddr vaddr) const override;

  private:
    /// Construct an NRom.
    /// \param prgRams The array of PRG RAMs from the containing cartridge.
    /// \param prgRoms The array of PRG ROMs from the containing cartridge.
    /// \param chrRoms The array of CHR ROMs from the containing cartridge.
    NRom(
        std::vector<std::shared_ptr<Memory::Ram<byte>>>& prgRams,
        std::vector<std::shared_ptr<Memory::Rom<byte>>>& prgRoms,
        std::vector<std::shared_ptr<Memory::Rom<byte>>>& chrRoms
        );

};

} // namespace Mappers
} // namespace Nes

#endif // NES_NROM_MAPPER_H //
