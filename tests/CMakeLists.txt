# ===-- tests/CMakeLists.txt - Tests build configuration ------------------=== #
#
#                            The OpenNES Project
# 
#  This file is distributed under GPL v2. See LICENSE.md for details.
#
# ===----------------------------------------------------------------------=== #
# Create the test executable directory
file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/tests)

# Set the core libs
set(LIBS common cpu)

# Configure the Catch Framework Main
add_library(catch EXCLUDE_FROM_ALL ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp)
add_dependencies(unittests catch)

macro(add_test_suite TARGET SRCS)
  # Append the catch frameworks main program to the list of srcs dependencies
  # for our test executable, as it is required to build our tests
  add_executable(test_${TARGET} EXCLUDE_FROM_ALL ${SRCS})
  set_target_properties(test_${TARGET} PROPERTIES
    OUTPUT_NAME tests/${TARGET}
    FOLDER tests
  )
  target_link_libraries(test_${TARGET} ${LIBS} catch)
  add_dependencies(unittests test_${TARGET})
  add_test(NAME ${TARGET} COMMAND ${EXECUTABLE_OUTPUT_PATH}/tests/${TARGET})
endmacro()

add_subdirectory(common)
add_subdirectory(cpu)
add_subdirectory(memory)
