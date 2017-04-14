# ===-- source/nes/CMakeLists.txt - Nes build configuration ----------------=== #
#
#                            The OpenNES Project
# 
#  This file is distributed under GPL v2. See LICENSE.md for details.
#
# ===----------------------------------------------------------------------=== #
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(SRCS Cartridge.cpp
         CartridgeBuilder.cpp
         )

add_library(nes ${SRCS})
