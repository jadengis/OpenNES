//===-- include/common/Cache.h - Cache ------------ -------------*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the Cache class.
///
//===----------------------------------------------------------------------===//
#ifndef CACHE_H
#define CACHE_H

#include <deque>
#include <unordered_map>

#include "common/StructureException.h"

namespace Structure {

/// \class Cache
/// \brief This class serves as a keyed Cache. 
/// Template parameter Key will serve as a lookup key into the cache, and when
/// the cache limit is reached, the oldest element will be deleted.
/// \tparam Key The type to use for lookup keys.
/// \tparam T The type to store.
/// \tparam cacheSize The size of the cache.
template <class Key, class T, unsigned long cacheSize = 20>
class Cache {
  public:
    /// Initialize and empty cache.
    inline Cache();

    /// Cache destructor.
    ~Cache();

    /// Add the keyed data to the cache.
    /// \param key Lookup key.
    /// \param data Data to cache.
    inline void add(Key key, T data);

    /// Remove oldest element from the cache.
    inline void remove();

    /// Clears the entire cache.
    inline void clear();

    /// Check to see if the input key is in the cache.
    /// \param key The key to lookup.
    /// \returns True is key is in the cache, false otherwise.
    inline bool hasKey(const Key& key) const;
    
    /// Lookup key in the cache and return its value. 
    /// \param key The key to lookup.
    /// \returns A reference to the keyed item.
    inline const T& lookup(const Key& key) const;

  private:
    /// Input order of the keys in the cache.
    std::deque<Key> keyQueue;
    /// Key to data mapping.
    std::unordered_map<Key, T> cache;
};

template <class Key, class T, unsigned long cacheSize>
Cache::Cache() : keyQueue(), cache() {}

template <class Key, class T, unsigned long cacheSize>
Cache::~Cache() {}

template <class Key, class T, unsigned long cacheSize>
void Cache::add(Key key, T data) {
  // push the key into the queue and add the data to the map
  keyQueue.push_back(key);
  cache[key] = data;
  if(keyQueue.size() > cacheSize) {
    removeOldest();
  }
}

template <class Key, class T, unsigned long cacheSize>
void Cache::remove() {
    // pop the front element, and delete from the map.
    cache.erase(keyQueue.pop_front());
}

template <class Key, class T, unsigned long cacheSize>
void Cache::clear() {
  // clear the queue and map
  keyQueue.clear();
  cache.clear();
}

template <class Key, class T, unsigned long cacheSize>
bool hasKey(const Key& key) const {
  // check to see that the map count for key is greater
  // than zero
  return map.count(key) > 0;
}

template <class Key, class T, unsigned long cacheSize>
const T& lookup(const Key& key) const {
  if(!hasKey()) {
    throw KeyErrorException();
  }
  return cache[key];
}

} // namespace Structure

#endif // CACHE_H //
