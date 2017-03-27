# ===-- source/cpu/CMakeLists.txt - Cpu build configuration ----------------=== #
#
#                            The OsNES Project
# 
#  This file is distributed under GPL v2. See LICENSE.md for details.
#
# ===----------------------------------------------------------------------=== #
set(SRCS Mos6502.cpp
         Mos6502Mmu.cpp
         Mos6502Disassembler.cpp)

add_library(cpu ${SRCS})
