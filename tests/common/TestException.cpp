//===-- tests/common/TestException.cpp - Base Exception Test ----*- C++ -*-===//
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
/// Test cases for the BaseException class
///
//===----------------------------------------------------------------------===//

#include <iostream>

#include "tests/catch.hpp"
#include "common/CommonTypes.h"
#include "common/BaseException.h"

#define ERROR_MESSAGE "This is an error message"

// define some functions for testing the stack traces
void level_three() {
  // throw at level 3
  throw Exception::BaseException(ERROR_MESSAGE);
}

void level_two() {
  level_three();
}

void level_one() {
  level_two();
}

// This test case may fail for Release builds, because the optimizer
// will mess with the expected stack frames. This isn't mission critical
// as we shouldn't be throwing exceptions in Release builds anyway.
TEST_CASE("Throwing and catching BaseExceptions works correctly", 
    "[Common][Exception][!mayfail]") {
  // try and catch the exception
  try {
    level_one();
  }
  catch (Exception::BaseException& e) {
    // print out the error message and stack trace
    std::cout << e.printErrorMessage() << e.printStackTrace();
    std::string name = e.printClassName();
    std::string message = e.printErrorMessage();
    std::string trace = e.printStackTrace();

    // Perform various checks on this output data
    // name checks
    CHECK(name == "BaseException");
    // message checks
    CHECK((message.find(name)) != (std::string::npos));
    CHECK((message.find(ERROR_MESSAGE)) != (std::string::npos));
    // trace checks
    CHECK((trace.find("level_one")) != (std::string::npos));
    CHECK((trace.find("level_two")) != (std::string::npos));
    CHECK((trace.find("level_three")) != (std::string::npos));
  }

}

TEST_CASE("BaseExceptions can be caught as stl std::exception.",
    "[Common][Exception]") {
  REQUIRE_THROWS_AS(level_one(), std::exception);
  REQUIRE_THROWS_WITH(level_one(), Catch::Contains("BaseException"));
}
