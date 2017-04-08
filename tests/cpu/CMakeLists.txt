# ===-- tests/cpu/CMakeLists.txt - Cpu Tests -------------------------------=== #
#
#                            The OpenNES Project
# 
#  This file is distributed under GPL v2. See LICENSE.md for details.
#
# ===----------------------------------------------------------------------=== #
set(SRCS TestMos6502.cpp
         TestMos6502Mmu.cpp
         TestMos6502Disassembler.cpp
         TestInterpretedMos6502.cpp
         )
include_directories(${CMAKE_SOURCE_DIR}/source/cpu)
add_test_suite(CpuTests "${SRCS}")
