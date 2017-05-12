//===-- include/nes/CartridgeMapperBuilder.h --------------------*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//  
//===----------------------------------------------------------------------===//
///
/// \file
/// This file defines the Nes::CartridgeMapperBuilder class.
///
//===----------------------------------------------------------------------===//
#ifndef NES_CARTRIDGE_MAPPER_BUILDER_H
#define NES_CARTRIDGE_MAPPER_BUILDER_H

#include <memory>
#include <vector>

#include "common/CommonTypes.h"
#include "common/patterns/Builder.h"
#include "memory/Mapper.h"
#include "memory/Rom.h"
#include "memory/Ram.h"
#include "nes/CartridgeMapper.h"

namespace Nes {

/// \class CartridgeMapperBuilder
/// \brief This class is the builder class for a CartridgeMapper. This class will
/// determine the correct iNES mapper to build.
class CartridgeMapperBuilder : public Pattern::Builder<CartridgeMapper>{
  public:
    /// Construct an empty CartridgeMapperBuilder.
    CartridgeMapperBuilder() {}

    /// Destroy a CartridgeMapperBuilder.
    ~CartridgeMapperBuilder() {}

    /// This method implement the abstract build() method from Pattern::Builder.
    /// \returns unique_ptr to the built CartridgeMapper.
    std::unique_ptr<CartridgeMapper> build() override;

    /// Set the iNES index to build the mapper with.
    /// \param The iNES mapper index.
    /// \returns This builder for chaining.
    CartridgeMapperBuilder& setiNESIndex(std::size_t iNesIndex);

    /// Set the vector of PRG RAMS to build the mapper with.
    /// \param Reference to the vector of Ram to use.
    /// \returns This builder for chaining.
    CartridgeMapperBuilder& setPrgRams(
        std::vector<std::shared_ptr<Memory::Ram<byte>>>* prgRamsPtr);

    /// Set the vector of PRG ROMS to build the mapper with.
    /// \param Reference to the vector of Rom to use.
    /// \returns This builder for chaining.
    CartridgeMapperBuilder& setPrgRoms(
        std::vector<std::shared_ptr<Memory::Rom<byte>>>* prgRomsPtr);

    /// Set the vector of CHR ROMS to build the mapper with.
    /// \param Reference to the vector of Rom to use.
    /// \returns This builder for chaining.
    CartridgeMapperBuilder& setChrRoms(
        std::vector<std::shared_ptr<Memory::Rom<byte>>>* chrRomsPtr);

  private:
    /// Temporary storage for a constructed cartridge pointer.
    std::unique_ptr<CartridgeMapper> mapperPtr;

    /// The iNes format mapper index.
    std::size_t iNesIndex;

    /// A reference to the PRG RAMs for this mappers Cartridge.
    std::vector<std::shared_ptr<Memory::Ram<byte>>>* prgRamsPtr;

    /// A reference to the PRG ROMs for this mappers Cartridge.
    std::vector<std::shared_ptr<Memory::Rom<byte>>>* prgRomsPtr;

    /// A reference to the CHR ROMs for this mappers Cartridge.
    std::vector<std::shared_ptr<Memory::Rom<byte>>>* chrRomsPtr;

};

} // namespace Nes

#endif // NES_CARTRIDGE_MAPPER_BUILDER_H //
