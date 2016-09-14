// OsNES Project | source/mem.cpp
// Description:
// Memory class implementation details here.
//
// Authors: 
// John Dengis
//
#include "mem.h"
using namespace com;

// ----------------------------------------------------------------------------
// Mem::Bank::Page Implementations
// ----------------------------------------------------------------------------
Mem::Bank::Page::Page(uint8 nam) : name{nam} {
  // A memory page consists of a 256 byte array of memory
  // so we will allocate that here.
  byte_p = new byte[MAX_SIZE_BYTE];
}

Mem::Bank::Page::~Page() {
  // a 256 byte array was allocated when this page was created so 
  // now that memory must be released.
  delete [] byte_p;
}

void Mem::Bank::Page::set_name(uint8 nam) {
  name = nam;
}

inline byte& Mem::Bank::Page::operator[](const uint8 index) {
  // fall back on the pointer index operator. Not array
  // out of bounds is not possible due to type limit on index.
  return byte_p[index];
}

// ----------------------------------------------------------------------------
// Mem::Bank Implementations
// ----------------------------------------------------------------------------
Mem::Bank::Bank(uint8 nam) : name{nam} {
  // A memory bank consists of 256 Pages containing 256 bytes
  // allocate this memory and set appropriate names
  page_p = new Page[MAX_SIZE_BYTE];
  for(long i = 0; i < MAX_SIZE_BYTE; i++) {
    page_p[i].set_name(i);
  }
}

Mem::Bank::~Bank() {
  // release array of allocated pages
  delete [] page_p;
}

void Mem::Bank::set_name(uint8 nam) {
  name = nam;
}

Mem::Bank::Page& Mem::Bank::operator[](const uint8 index) {
  // fall back on the pointer index operator. Not array
  // out of bounds is not possible due to type limit on index.
  return page_p[index];
}
