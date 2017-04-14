//===-- tests/common/TestCache.cpp - Cache Test ------------ ----*- C++ -*-===//
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
/// Test cases for the Cache class.
///
//===----------------------------------------------------------------------===//

#include <string>

#include "tests/catch.hpp"
#include "common/CommonTypes.h"
#include "common/structures/Cache.h"
#include "common/structures/StructureException.h"

using namespace Structure;

TEST_CASE("Adding and looking up members in the cache works correctly.", 
    "[Common][Cache]") {
  // Build a cache with default cacheSize
  Cache<addr, std::string> cache;
  REQUIRE(cache.empty() == true);
  
  SECTION("Add some element to the cache, then look them up.") {
    // add a few elements
    cache.add(0x00FF, "Hello!"); 
    cache.add(0x0F0F, "How are you?"); 

    REQUIRE(cache.hasKey(0x00FF));
    REQUIRE(cache.hasKey(0x0F0F));
    
    std::string testString = cache.lookup(0x00FF);
    CHECK(testString == "Hello!");

    testString = cache.lookup(0x0F0F);
    CHECK(testString == "How are you?");

  }

}

TEST_CASE("Size manipulation works correctly.", "[Common][Cache]") {
  // Build a Cache with a low maximum
  Cache<addr, std::string, 5> cache;
  REQUIRE(cache.empty() == true);
  REQUIRE(cache.maxSize() == 5);
  REQUIRE(cache.size() == 0);

  SECTION("Size methods always return the correct size.") {
    // add elements to the cache, and check that size updates correctly
    cache.add(1, "one");
    CHECK(cache.hasKey(1));
    CHECK(cache.lookup(1) == "one");
    REQUIRE(cache.size() == 1);
    cache.add(2, "two");
    CHECK(cache.hasKey(2));
    CHECK(cache.lookup(2) == "two");
    REQUIRE(cache.size() == 2);
    cache.add(3, "three");
    CHECK(cache.hasKey(3));
    CHECK(cache.lookup(3) == "three");
    REQUIRE(cache.size() == 3);

    cache.remove();
    CHECK_FALSE(cache.hasKey(1));
    REQUIRE(cache.size() == 2);
    cache.remove();
    CHECK_FALSE(cache.hasKey(2));
    REQUIRE(cache.size() == 1);
    cache.remove();
    CHECK_FALSE(cache.hasKey(3));
    REQUIRE(cache.size() == 0);
    REQUIRE(cache.empty());

  }

  SECTION("Cache doesn't store more than the max size") {
    for(uint64 i = 1; i <= 5; i++) {
      cache.add(i, "element " + std::to_string(i));
    }
    REQUIRE(cache.size() == cache.maxSize());
    // try to add another element
    cache.add(6, "new");
    // check that the first added element was dropped
    CHECK_FALSE(cache.hasKey(1));
    CHECK(cache.size() == cache.maxSize());

  }

  SECTION("Clearing the cache works correctly.") {
    for(uint64 i = 1; i <= 5; i++) {
      cache.add(i, "element " + std::to_string(i));
    }
    REQUIRE(cache.size() == cache.maxSize());
    cache.clear();
    REQUIRE(cache.empty());
    
  }

}

TEST_CASE("Attempting to use keys not in the cache throws exception.",
    "[Common][Cache]") {
  Cache<addr, std::string> cache;
  cache.add(1, "one");
  cache.add(2, "two");
  REQUIRE_THROWS_AS(cache.lookup(3), Exception::KeyErrorException);
    
}
