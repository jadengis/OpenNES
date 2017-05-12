# ===-- tests/nes/CMakeLists.txt - Nes Tests -------------------------------=== #
#
#                            The OpenNES Project
# 
#  This file is distributed under GPL v2. See LICENSE.md for details.
#
# ===----------------------------------------------------------------------=== #
set(SRCS TestCartridgeBuilder.cpp
         )
include_directories(${CMAKE_SOURCE_DIR}/source/nes)
add_test_suite(NesTests "${SRCS}")
