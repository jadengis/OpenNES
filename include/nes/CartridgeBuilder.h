//===-- include/nes/CartridgeBuilder.h - Cartridge Builder Class -----------*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//  
//===----------------------------------------------------------------------===//
///
/// \file
/// This file defines the Nes::CartridgeBuilder class.
///
//===----------------------------------------------------------------------===//
#ifndef NES_CARTRIDGE_BUILDER_H
#define NES_CARTRIDGE_H

#include <fstream>
#include <memory>
#include <array>
#include <vector>

#include "common/CommonTypes.h"
#include "common/patterns/Builder.h"
#include "memory/Mapper.h"
#include "memory/Rom.h"
#include "memory/Ram.h"
#include "nes/Cartridge.h"

namespace Nes {

/// \class Cartridge
/// \brief This class represents an Nes cartridge. It contains all cartridge
/// specific information related to the game being emulated.
class CartridgeBuilder : public Pattern::Builder<Cartridge>{
  public:
    /// Construct an empty CartridgeBuilder.
    CartridgeBuilder() {}

    /// Destroy a CartridgeBuilder.
    ~CartridgeBuilder() {}

    /// This method implement the abstract build() method from Pattern::Builder.
    /// \returns unique_ptr to the built Cartridge.
    std::unique_ptr<Cartridge> build() override;

    /// Set the path to the file to build this cartridge from.
    /// \param filepath Path to the .nes file containing cartridge information.
    /// \returns This builder for chaining.
    CartridgeBuilder& setInputFile(std::string inputFile);

  private:
    /// The number of bytes in the iNES file header.
    static constexpr const std::size_t& INES_HEADER_SIZE = 16;
    /// The array of bytes designating the .nes format: NES^Z
    static constexpr const std::array<byte, 4> NES_TOKEN 
      = {0x4E, 0x45, 0x53, 0x1A};
    
    /// Read the iNES file header of the input file and convert these
    /// input cartridge building options. This file parses the iNES header
    /// according to the specification here:
    /// http://fms.komkon.org/EMUL8/NES.html#LABM
    /// \param header The file header in a byte array.
    /// \throws Exception::InvalidFormatException if format is invalid. 
    void parseiNesHeader(std::array<byte, INES_HEADER_SIZE> header);

    /// System path to the .nes file containing cartridge information.
    std::string inputFile;
    /// Specifications for the hardware of the input cartridge.
    CartridgeOptions options;
    /// Temporary storage for a constructed cartridge pointer.
    std::unique_ptr<Cartridge> cartridgePtr;

};

} // namespace Nes

#endif // NES_CARTRIDGE_BUILDER_H //
