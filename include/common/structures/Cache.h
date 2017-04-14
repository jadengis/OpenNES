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
template <class Key, class T, std::size_t cacheSize = 20>
class Cache {
  public:
    /// Initialize and empty cache.
    inline Cache();

    /// Cache destructor.
    ~Cache();

    /// Gets the current number of elements in the cache.
    /// \returns The size of the cache.
    inline std::size_t size();

    /// Gets the maximum number of elements the cache can hold.
    /// \returns The maximum size of the cache.
    inline std::size_t maxSize();

    /// Add the keyed data to the cache.
    /// \param key Lookup key.
    /// \param data Data to cache.
    inline void add(Key key, T data);

    /// Remove oldest element from the cache.
    inline void remove();

    /// Clears the entire cache.
    inline void clear();

    /// Checks whether the cache is empty.
    /// \returns True is cache is empty.
    inline bool empty();

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

template <class Key, class T, std::size_t cacheSize>
Cache<Key, T, cacheSize>::Cache() : keyQueue(), cache() {}

template <class Key, class T, std::size_t cacheSize>
Cache<Key, T, cacheSize>::~Cache() {}

template <class Key, class T, std::size_t cacheSize>
std::size_t Cache<Key, T, cacheSize>::size() {
  return keyQueue.size();
}

template <class Key, class T, std::size_t cacheSize>
std::size_t Cache<Key, T, cacheSize>::maxSize() {
  return cacheSize;;
}

template <class Key, class T, std::size_t cacheSize>
void Cache<Key, T, cacheSize>::add(Key key, T data) {
  // push the key into the queue and add the data to the map
  keyQueue.push_back(key);
  cache[key] = data;
  if(keyQueue.size() > cacheSize) {
    remove();
  }
}

template <class Key, class T, std::size_t cacheSize>
void Cache<Key, T, cacheSize>::remove() {
    // pop the front element, and delete from the map.
    cache.erase(keyQueue.front());
    keyQueue.pop_front();
}

template <class Key, class T, std::size_t cacheSize>
void Cache<Key, T, cacheSize>::clear() {
  // clear the queue and map
  keyQueue.clear();
  cache.clear();
}

template <class Key, class T, std::size_t cacheSize>
bool Cache<Key, T, cacheSize>::empty() {
  return keyQueue.empty();
}

template <class Key, class T, std::size_t cacheSize>
bool Cache<Key, T, cacheSize>::hasKey(const Key& key) const {
  // check to see that the map count for key is greater
  // than zero
  return cache.count(key) > 0;
}

template <class Key, class T, std::size_t cacheSize>
const T& Cache<Key, T, cacheSize>::lookup(const Key& key) const {
  if(!hasKey(key)) {
    throw Exception::KeyErrorException();
  }
  return const_cast<const decltype(cache)&>(cache).at(key);
}

} // namespace Structure

#endif // CACHE_H //
