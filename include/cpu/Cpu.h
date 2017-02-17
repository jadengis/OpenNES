//===-- include/cpu/cpu.h - Cpu Base Class ----------------------*- C++ -*-===//
//
//                           The OsNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the Cpu template which serves as an abstract base class
/// for all Cpu style classes in the OsNES project.
///
//===----------------------------------------------------------------------===//
#include "common/CommonTypes.h"

#ifndef CPU_H
#define CPU_H

template<class Arch> class Cpu {
  public:
    Cpu() {};
    virtual ~Cpu() {};
    virtual void executeOpcode(Arch opcode) = 0;
    virtual Arch fetchOpcode() = 0;
};

#endif // CPU_H //:~
