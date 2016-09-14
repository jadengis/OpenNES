// OsNES Project | include/mem.h
// Description:
// All NES memory objects are declared here.
//
// Authors: 
// John Dengis
//
#ifndef MEM_H
#define MEM_H
#include "common.h"

namespace Mem {
  class Bank {
    public:
      class Page {
        // A memory Page for the NES consists of a 256 byte array of memory
        // as well as an identifier.
        public:
          // Page Constructor / Deconstructor
          Page(uint8 nam = 0);
          virtual ~Page();

          // field access functions
          void set_name(uint8 nam);

          // Page Element Access
          byte& operator[](const uint8 index);

        private:
          uint8 name;    // integer from 0 - 255
          byte * byte_p; // pointer to byte array
      };
      // Bank Constructor / Deconstructor
      Bank(uint8 nam = 0);
      virtual ~Bank();

      // field access functions
      void set_name(uint8 nam);

      // Page Pointer Access
      Page& operator[](const uint8 index);

    private:
      uint8 name;    // integer from 0 - 255
      Page * page_p; // pointer to page array
  };
}
#endif // MEM_H //:~
