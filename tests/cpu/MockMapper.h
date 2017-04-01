//===-- tests/cpu/MockMapper.h - Mock Mapper ---------- ---------*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details. The Catch
// framework IS NOT distributed under LICENSE.md.
// The Catch framework is included in this project under the Boost License
// simply as a matter of convenience.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains a fake mapper to use for testing.
///
//===----------------------------------------------------------------------===//
#include <array>
#include <memory>

#include "common/CommonTypes.h"
#include "memory/Mapper.h"
#include "memory/Bank.h"
#include "memory/Ram.h"

#define NUM_BANKS 0x10
#define BANK_SIZE 0x1000

/// \class MockMapper
/// \brief A fake memory mapper for testing.
class MockMapper : public Memory::Mapper<byte> {
  public:
    inline MockMapper();
    inline ~MockMapper() {}
    inline std::shared_ptr<Memory::Bank<byte>> mapToHardware(Vaddr vaddr) const override;
  private:
    /// An array of ptrs to Ram banks that can be mapped to
    std::array<std::shared_ptr<Memory::Ram<byte>>, NUM_BANKS> dataBanks;
};

MockMapper::MockMapper() {
  Vaddr vaddr;
  // bootstrap the mock mapper.
  for(std::size_t i = 0; i < NUM_BANKS; i++) {
    vaddr.val = i * BANK_SIZE;
    dataBanks[i] = std::make_shared<Memory::Ram<byte>>(BANK_SIZE, vaddr);
  }
}

std::shared_ptr<Memory::Bank<byte>> MockMapper::mapToHardware(Vaddr vaddr) const {
  // mask out the high 4 bits and use as an index into the array
  std::size_t index = (vaddr.val >> 12) & 0xF;
  return dataBanks[index];
}
