#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H
#include "common.h"

// An array based stack implmentation to be used as the 6502 program Stack
// This implementation has been left intentionally unsafe to account for
// the possibility of real overflow when emulating NES programs.
// Note that this Stack is designed to use an external stack pointer (e.g
// the SP reg on the MOS 6502.
template <class T> class CPU_Array_Stack {
  private:
    bool memory_allocated;
    T *base;

  public:
    // Constructors & Deconstructors
    // An Array_Stack can be initialized with a pointer or an initial size
    // where the memory for the array is dynamically alocatted. Memory is
    // is assumed to have been previously allocated if a pointer is used.
    CPU_Array_Stack(T size = MAX_SIZE_8BIT) {
      memory_allocated = true;
      base = new T[size];
    }

    CPU_Array_Stack(T* input_base) {
      memory_allocated = false;
      base = input_base;
    }

    ~CPU_Array_Stack() {
      // Clean up any allocated memory
      if(memory_allocated) {
        delete[] base;
      }
    }

    // Stack Interface
    void push(T new_top, T& sp_reg) {
      sp_reg++
      *(base + sp_reg) = new_top;
    }

    T pop(T& sp_reg) {
      T old_top = *(base + sp_reg);
      sp_reg--;
      return old_top;
    }
};
#endif // ARRAY_STACK_H //:~
