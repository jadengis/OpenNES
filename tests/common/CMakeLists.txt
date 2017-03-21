# ===-- tests/common/CMakeLists.txt - Common Tests -------------------------=== #
#
#                            The OsNES Project
# 
#  This file is distributed under GPL v2. See LICENSE.md for details.
#
# ===----------------------------------------------------------------------=== #
set(SRCS TestException.cpp)
add_test_suite(CommonTests ${SRCS})
