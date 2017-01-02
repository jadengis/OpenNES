
#include "common.h"

#ifndef CPU_H
#define CPU_H
template<class Arch> class CPU {
  public:
    CPU() {};
    virtual ~CPU() {};
    virtual void execute(Arch opcode) = 0;
    virtual Arch fetch() = 0;
};
#endif // CPU_H //:~
