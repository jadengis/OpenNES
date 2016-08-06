
#include "common.h"

#ifndef MEMORY_H
#define MEMORY_H
template<class WordSize> class Memory {
  public:
    Memory() {};
    virtual ~Memory() {};
    virtual void execute() = 0;
};

class NESMemory : public Memory<uint8> {
  private: 
    uint8 mem[MAX_SIZE_8BIT][MAX_SIZE_8BIT];
};
#endif // MEMORY_H //:~
