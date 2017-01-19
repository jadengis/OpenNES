// OsNES Project | include/mem.h
// Description:
// All NES memory objects are declared here.
//
// Authors: 
// John Dengis
//
#ifndef MEM_H
#define MEM_H
#include "Common.h"


namespace Mem {
  // Class Declarations
  class Ref;
  class Bank;

  // Definitions
  class Bank {
    // The MOS 6502 chip had support only for 16 bit addressing (2 bytes).
    // However, in practice this was not enough memory for developing games
    // so the hardware allowed for "bank switching" from on 16 bit address
    // space to another. Mem::Bank is a representation of those memory banks.
    public:
      class Page {
        // A memory Page for the NES consists of a 256 byte array of memory
        // as well as an identifier.
        public:
          // Page constructor / deconstructor
          Page(uint8 nam = 0);
          virtual ~Page();

          // field access functions
          void set_name(uint8 nam);

          // Page element access
          byte&       operator[](const uint8 index);
          const byte& operator[](const uint8 index) const;

        private:
          uint8 name;       // integer from 0 - 255
          byte * byte_p;    // pointer to byte array
          friend class Ref; // Ref constructor can access private data
      };
      // Bank constructor / deconstructor
      Bank(uint8 nam = 0);
      virtual ~Bank();

      // field access functions
      void set_name(uint8 nam);

      // Page pointer access
      Page&       operator[](const uint8 index);
      const Page& operator[](const uint8 index) const;

    private:
      uint8 name;    // integer from 0 - 255
      Page * page_p; // pointer to page array
  };

  class Ref {
    // Mem::Ref is a class of objects to be used to make references to specific
    // locations in the NES memory. Internally, the memory reference acts as a
    // base pointer, base, with integer displacement disp.
    // Refs will deference like pointers, which will compute the displaced memory
    // location and load from there.
    public:
      Ref(byte * bse = nullptr, uint8 index = 0);
      Ref(Mem::Bank::Page page, uint8 index = 0);
      virtual ~Ref();

      // reference access
      byte&       operator*();
      const byte& operator*() const;
      const Ref& operator+(uint8 x) const {
        return Ref(base, disp + x);
      }

    private:
      byte * base;
      uint8  disp;
  };
}
#endif // MEM_H //:~
