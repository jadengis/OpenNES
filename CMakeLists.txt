# ===-- CMakeLists.txt - OpenNES CMake build configuration ----------------=== #
#
#                            The OsNES Project
# 
#  This file is distributed under GPL v2. See LICENSE.md for details.
#
# ===----------------------------------------------------------------------=== #
project (OpenNES)
cmake_minimum_required (VERSION 3.2.2)


# Ensure that we do not perform in-source builds, as this makes cleanup
# challenging.
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "In-source builds are not allowed for this project.
    Please use a build directory.")
endif()

# Set Executable and library output paths
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# Set current version if not set
if (NOT DEFINED OPENNES_VERSION_MAJOR)
  set (OPENNES_VERSION_MAJOR 0)
endif()
if (NOT DEFINED OPENNES_VERSION_MINOR)
  set (OPENNES_VERSION_MINOR 1)
endif()
if (NOT DEFINED OPENNES_VERSION_PATCH)
  set (OPENNES_VERSION_MINOR 0)
endif()

# Check if a build configuration was selected
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type selected, default to Debug")
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type (default Debug)" FORCE)
endif()


# Determine properties of the current build machine
message(STATUS "Detected Architecture: ${CMAKE_SYSTEM_PROCESSOR}")

# Detect 64bit or 32bit
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(__ARCH_64__ 1)
  add_definitions(-D__ARCH_64__=1)
else()
  set(__ARCH_32__ 1)
  add_definitions(-D__ARCH_32__=1)
endif()

# Determine platform specific configurations
if(__ARCH_64__ AND CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|amd64|AMD64")
  set(__X86__ 1)
  set(__X86_64__ 1)
  set(__LITTLE_ENDIAN__ 1)
  add_definitions(-D__X86__=1)
  add_definitions(-D__X86_64__=1)
  add_definitions(-D__LITTLE_ENDIAN__=1)
endif()


# Select build compiler specific configurations
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 6.0)
  message(FATAL_ERROR "OpenNES requires GCC 6.0 or greater (found ${CMAKE_CXX_COMPILER_VERSION})")
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.8)
  message(FATAL_ERROR "OpenNES requires Clang 3.8 or greater (found ${CMAKE_CXX_COMPILER_VERSION})")
endif()

# Set C++ language standard for the whole project
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set project level compiler options for all build types
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g --coverage")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

# Set project level executable link flags
# We are using execinfo.h for backtraces, so we require -rdynamic
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -rdynamic --coverage")


# project include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Enable testing congifuration
enable_testing()
add_custom_target(unittests)
add_custom_command(TARGET unittests POST_BUILD COMMAND ${CMAKE_CTEST_COMMAND})

# add the source directories
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/source)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)

