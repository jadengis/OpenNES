# ===-- source/cpu/CMakeLists.txt - Cpu build configuration ----------------=== #
#
#                            The OpenNES Project
# 
#  This file is distributed under GPL v2. See LICENSE.md for details.
#
# ===----------------------------------------------------------------------=== #
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(SRCS Mos6502.cpp
         Mos6502Mmu.cpp
         Mos6502Disassembler.cpp
         interpreter/InterpretedMos6502.cpp
         )

add_library(cpu ${SRCS})
