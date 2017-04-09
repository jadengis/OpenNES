# ===-- tests/memory/CMakeLists.txt - Memory Tests -------------------------=== #
#
#                            The OpenNES Project
# 
#  This file is distributed under GPL v2. See LICENSE.md for details.
#
# ===----------------------------------------------------------------------=== #
set(SRCS TestReference.cpp
         TestRam.cpp
         TestMirroredRam.cpp
         )
add_test_suite(MemoryTests "${SRCS}")
