
#ifndef EXCEPT_H
#define EXCEPT_H
#include <exception.h>
// Base exception class for OsNES. This will grab the stack 
// TODO: Get the Exception class to grab a stack trace at throw time.
class Exception {

};

class Exception_Bad_Opcode : Exception {
  
};

#endif // EXCEPT_H //:~
