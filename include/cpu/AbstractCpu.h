//===-- include/cpu/AbstractCpu.h - Cpu Base Class --------------*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the Cpu template which serves as an abstract base class
/// for all Cpu style classes in the OpenNES project.
///
//===----------------------------------------------------------------------===//
#include "common/CommonTypes.h"

#ifndef ABSTRACT_CPU_H
#define ABSTRACT_CPU_H

namespace Cpu {

/// \class AbstractCpu
/// \brief This class represents an abstract CPU.
/// It provides the interface that any CPU must implement regardless of architecture.
class AbstractCpu {
  public:
    /// Virtual destructor for AbstractCpu
    virtual ~AbstractCpu() {};

    /// Initialize the CPU. This can include all necessary steps to boot the CPU into
    /// running mode.
    virtual void init() = 0;

    /// Put the CPU into running mode. In running mode, the CPU should fetch, decode
    /// and execute instructions in time with the clock.
    virtual void run() = 0;
    
    /// Reset the CPU. This can involved setting the program counter to its RESET 
    /// value.
    virtual void reset() = 0;

    /// Execute one cycle on the Cpu.
    virtual void step() = 0;

    /// Trace the CPU. Tracing the CPU should be used for debugging and should provide
    /// information about the status of the CPU e.g. contents of registers, stack, 
    /// current instruction etc.
    virtual void trace() = 0;

    /// Shutdown the CPU. That is, perform all steps required to safety shutdown the
    /// CPU.
    virtual void shutdown() = 0;

  protected:
    /// Fetch opcode from current program counter position, and store in instruction
    /// register.
    virtual void fetchOpcode() = 0;

    /// Decode the opcode in the instruction register into an understandable Cpu
    /// instruction.
    virtual void decodeOpcode() = 0;

    /// Execute the last decoded instruction.
    virtual void executeOpcode() = 0;
};

} // namespace Cpu

#endif // ABSTRACT_CPU_H //
