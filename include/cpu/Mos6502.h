//===-- include/cpu/Mos6502.h - Mos6502 Cpu Class ---------------*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Functional specification for the MOS 6502 CPU. Any and all details related 
/// to the overall operation of the 6502 should be declared here.
///
//===----------------------------------------------------------------------===//
#ifndef MOS_6502_H
#define MOS_6502_H

#include <string>

#include "common/CommonTypes.h"
#include "cpu/AbstractCpu.h"
#include "cpu/Mos6502Mmu.h"
#include "cpu/Mos6502Disassembler.h"
#include "cpu/Mos6502Instruction.h"
#include "memory/Ram.h"
#include "memory/Reference.h"
#include "memory/Mapper.h"

namespace Cpu {

/// \class Mos6502
/// \brief This class is an abstract base that provides common functionality and
/// structure for emulation the Mos6502. Inheritors of this class can use the
/// public and protected interface of this class to provide a more concrete
/// method of emulation.
class Mos6502 : public AbstractCpu {
  public:
    /// Default constructor. Bootstrap a Mos6502 CPU object.
    Mos6502(Memory::Mapper<byte>& memMap) :
        stack(reg.sp, memMap),
        dis(),
        mmu(reg.x, reg.y, memMap) {
      this->cycleCount = 0;
      this->reg.pc.val = 0;
      this->reg.ac = 0;
      this->reg.x = 0;
      this->reg.y = 0;
      this->reg.sr = 0;
      // Stack pointer is initially full
      this->reg.sp = 0xFF;
    }

    void init() override;
    void run() override;
    void step() override;
    void reset() override;
    void trace() override;
    void shutdown() override;

    // Cpu state inspection methods
    /// Get the remaining number of cycles to execute for the current instruction.
    /// \returns The current cycle count.
    inline byte getCycleCount() const;

    /// Increment the cycle count by the input value
    /// \param value Number of cycles to add to the count.
    inline void incrementCycles(const byte value);
    
    /// Decrement the cycle count by one.
    inline void decrementCycles();

    // Status register flag masks
    /// Status register negative flag mask
    static const byte SR_N = 0x80;
    /// Status register overflow flag mask
    static const byte SR_V = 0x40;
    /// Status register break flag mask
    static const byte SR_B = 0x10;
    /// Status register decimal flag mask
    static const byte SR_D = 0x08;
    /// Status register interrupt disable flag mask
    static const byte SR_I = 0x04;
    /// Status register zero flag mask
    static const byte SR_Z = 0x02;
    /// Status register carry flag mask
    static const byte SR_C = 0x01;

  protected:
    /// Fetch opcode from memory. This will retrieve the opcode at the current
    /// value of the program counter and return it for decoding.
    void fetchOpcode() final;

    /// Decode opcode into Mos6502Instruction object. This object provides a lot
    /// of information about the opcodes instruction that can be used for tracing
    /// and execution.
    void decodeOpcode() final;

    /// Execute input instruction. This function will execute a Mos6502Instruction
    /// on the CPU.
    void executeOpcode() final;

    /// Implementation specific details of fetchOpcode
    virtual void fetchOpcodeImpl() = 0;

    /// Implementation specific details of decodeOpcode
    virtual void decodeOpcodeImpl() = 0;

    /// Implementation specific details of executeOpcode
    virtual void executeOpcodeImpl() = 0;

    /// Add memory to accumulator with carry.
    /// \param opd Byte read from memory.
    inline void ADC(const byte opd);
    /// AND memory with accumulator.
    /// \param opd Byte read from memory.
    inline void AND(const byte opd);
    /// Arithmetic shift left.
    /// \param opd Byte read from memory.
    /// \returns Byte to write to memory.
    inline byte ASL(byte opd);
    /// Branch on carry clear.
    /// \param opd Byte read from memory.
    inline void BCC(const byte opd);
    /// Branch on carry set.
    /// \param opd Byte read from memory.
    inline void BCS(const byte opd);
    /// Branch on equal (zero set).
    /// \param opd Byte read from memory.
    inline void BEQ(const byte opd);
    /// Bit test.
    /// \param opd Byte read from memory.
    inline void BIT(const byte opd);
    /// Branch on minus (negative set).
    /// \param opd Byte read from memory.
    inline void BMI(const byte opd);
    /// Branch on not equal (zero clear).
    /// \param opd Byte read from memory.
    inline void BNE(const byte opd);
    /// Branch on plus (negative clear).
    /// \param opd Byte read from memory.
    inline void BPL(const byte opd);
    /// Force interrupt.
    inline void BRK();
    /// Branch on overflow clear.
    /// \param opd Byte read from memory.
    inline void BVC(const byte opd);
    /// Branch on overflow set.
    /// \param opd Byte read from memory.
    inline void BVS(const byte opd);
    /// Clear carry flag.
    inline void CLC();
    /// Clear decimal flag.
    inline void CLD();
    /// Clear interrupt disable flag.
    inline void CLI();
    /// Clear overflow flag.
    inline void CLV();
    /// Compare memory with accumulator.
    /// \param opd Byte read from memory.
    inline void CMP(const byte opd);
    /// Compare memory with X-index register.
    /// \param opd Byte read from memory.
    inline void CPX(const byte opd);
    /// Compare memory with Y-index register.
    /// \param opd Byte read from memory.
    inline void CPY(const byte opd);
    /// Decrement memory by one.
    /// \param opd Byte read from memory.
    /// \returns Byte to write to memory.
    inline byte DEC(byte opd);
    /// Decrement X-index register by one.
    inline void DEX();
    /// Decrement Y-index register by one.
    inline void DEY();
    /// Exclusive OR memory with accumulator.
    /// \param opd Byte read from memory.
    inline void EOR(const byte opd);
    /// Increment memory by one.
    /// \param opd Byte read from memory.
    /// \returns Byte to write to memory.
    inline byte INC(byte opd);
    /// Increment X-index register by one.
    inline void INX();
    /// Increment Y-index register by one.
    inline void INY();
    /// Jump to new location.
    /// \param vaddr Address to jump to..
    inline void JMP(const Vaddr vaddr);
    /// Jump to new location saving return address.
    /// \param vaddr Address to jump to..
    inline void JSR(const Vaddr vaddr);
    /// Load accumulator with memory.
    /// \param opd Byte read from memory.
    inline void LDA(const byte opd);
    /// Load X-index register with memory.
    /// \param opd Byte read from memory.
    inline void LDX(const byte opd);
    /// Load Y-index register with memory.
    /// \param opd Byte read from memory.
    inline void LDY(const byte opd);
    /// Logical shift right.
    /// \param opd Byte read from memory.
    /// \returns Byte to write to memory.
    inline byte LSR(byte opd);
    /// No operation
    inline void NOP();
    /// OR memory with accumulator.
    /// \param opd Byte read from memory.
    inline void ORA(const byte opd);
    /// Push accumulator on processor stack.
    inline void PHA();
    /// Push processor status on processor stack.
    inline void PHP();
    /// Pull accumulator from processor stack.
    inline void PLA();
    /// Pull processor status from processor stack.
    inline void PLP();
    /// Rotate one bit left.
    /// \param opd Byte read from memory.
    /// \returns Byte to write to memory.
    inline byte ROL(byte opd);
    /// Rotate one bit right.
    /// \param opd Byte read from memory.
    /// \returns Byte to write to memory.
    inline byte ROR(byte opd);
    /// Return from interrupt.
    inline void RTI();
    /// Return from subroutine.
    inline void RTS();
    /// Subtract memory from accumulator with borrow.
    /// \param opd Byte read from memory.
    inline void SBC(const byte opd);
    /// Set carry flag.
    inline void SEC();
    /// Set decimal flag.
    inline void SED();
    /// Set interrupt flag.
    inline void SEI();
    /// Store accumulator in memory.
    /// \returns Byte to write to memory.
    inline byte STA();
    /// Store X-index register in memory.
    /// \returns Byte to write to memory.
    inline byte STX();
    /// Store Y-index register in memory.
    /// \returns Byte to write to memory.
    inline byte STY();
    /// Transfer accumulator to X-index register.
    inline void TAX();
    /// Transfer accumulator to Y-index register.
    inline void TAY();
    /// Transfer stack pointer to X-index register.
    inline void TSX();
    /// Transfer X-index register to accumulator.
    inline void TXA();
    /// Transfer X-index register to stack pointer.
    inline void TXS();
    /// Transfer Y-index register to accumulator.
    inline void TYA();

    /// Get the current opcode from the instruction register.
    /// \returns The opcode in the instruction register.
    inline byte getRegIR() const;

    /// Set the current value of the instruction register.
    /// \param value The value to copy into the instruction register.
    inline void setRegIR(const byte value);

    /// Get the current address pointed to by the program counter.
    /// \returns The current value of the program counter.
    inline addr getRegPC() const;

    /// Increment the program counter by the input amount.
    /// \param value Amount to increment the program counter.
    inline void incrementRegPC(const addr value);

    /// Get the current value of the accumulator.
    /// \returns The current value of the accumulator.
    inline byte getRegAC() const;

    /// Set the current value of the accumulator.
    /// \param value The value to copy into the accumulator.
    inline void setRegAC(const byte value);

    /// Get the current value of the X-index register.
    /// \returns The current value of the X-index register.
    inline byte getRegX() const;

    /// Get the current value of the Y-index register.
    /// \returns The current value of the Y-index register.
    inline byte getRegY() const;

    /// Get the current value of the status register.
    /// \returns The current value of the status register.
    inline byte getRegSR() const;

    /// Get the current value of the stack pointer register.
    /// \returns The current value of the stack pointer register.
    inline byte getRegSP() const;

    /// Get the internal disassembler object for the Mos6502 object.
    /// \returns The internal disassembler.
    inline Mos6502Disassembler& getDis();
    
    /// Get the internal memory management object for the Mos6502 object.
    /// \returns The internal Mos6502Mmu object.
    inline const Mos6502Mmu& getMmu() const;

  private:
    // Mos6502 private static consts
    /// Low byte location of memory containing non-maskable interrupt vector
    static constexpr const Vaddr& NMI_VECTOR = { 0xFFFA };
    /// Low byte location of memory containing reset vector
    static constexpr const Vaddr& RESET_VECTOR = { 0xFFFC };
    /// Low byte location of memory containing maskable interrupt vector
    static constexpr const Vaddr& IRQ_VECTOR = { 0xFFFE };

    /// Cycles required to execute current instruction
    byte cycleCount;
    // Register structure
    struct {
      byte ir; // Instruction register
      Vaddr pc; // Program counter
      byte ac; // Accumulator
      byte x;  // X Register
      byte y;  // Y Register
      union {
        byte sr; // Status Register [NV-BDIZC]
        struct {
#ifdef __BIG_ENDIAN__
          byte n       : 1; // Negative
          byte v       : 1; // Overflow
          byte ignored : 1; // Ignored
          byte b       : 1; // Break
          byte d       : 1; // Decimal (use BCD for arithmetic)
          byte i       : 1; // Interrupt (IRQ diable)
          byte z       : 1; // Zero
          byte c       : 1; // Carry
#else // Little Endian
          byte c       : 1; // Carry
          byte z       : 1; // Zero
          byte i       : 1; // Interrupt (IRQ diable)
          byte d       : 1; // Decimal (use BCD for arithmetic)
          byte b       : 1; // Break
          byte ignored : 1; // Ignored
          byte v       : 1; // Overflow
          byte n       : 1; // Negative
#endif // __BIG_ENDIAN__
        }      srf; // Status Register Fields
      };
      byte  sp; // Stack Pointer
    } reg;

    /// \class Stack
    /// \brief Mos6502 processor stack.
    /// LIFO, top down, 8 bit range, 0x0100 - 0x01FF.
    class Stack {
      public:
        /// Base address of the Mos6502 stack.
        static constexpr const Vaddr& BASE_ADDRESS = {0x0100};

        /// Push data onto the processor stack
        /// \param data Byte to push.
        inline void push(byte data) {
          // Retrieve stack pointer, write to the given location, and then
          // decrement the stack pointer.
          base.write(stackPointer--, data);
        }

        /// Pull data from the processor stack
        /// \return Byte from top of stack
        inline byte pull() {
          // increment the stack pointer, and read from the given location
          auto temp = base.read(++stackPointer);
          return temp;
        }

        Stack(
            byte& stackPointerRegister,
            const Memory::Mapper<byte>& memMap) 
            : stackPointer(stackPointerRegister) {
          auto bankPtr = memMap.mapToHardware(BASE_ADDRESS);
          // Mos6502 stack is top-down, so we must offset top from base.
          base = Memory::Reference<byte>(bankPtr,
              BASE_ADDRESS.val - bankPtr->getBaseAddress().val);
        }

        ~Stack() {}

      private:
        /// Reference to the Mos6502 stack pointer
        byte& stackPointer;
        /// Memory reference to the base memory location of the CPU stack
        Memory::Reference<byte> base;

    } stack;

    /// The disassembler for the Mos6502.
    Mos6502Disassembler dis;

    /// The memory management unit for the Mos6502.
    const Mos6502Mmu mmu;

};

// Inlinable Cpu state inspection methods.
byte Mos6502::getCycleCount() const {
  return cycleCount;
}

void Mos6502::incrementCycles(const byte value) {
  this->cycleCount += value;
}

void Mos6502::decrementCycles() {
  this->cycleCount--;
}

byte Mos6502::getRegIR() const {
  return reg.ir;
}

void Mos6502::setRegIR(const byte value) {
  this->reg.ir = value;
}

addr Mos6502::getRegPC() const {
  return reg.pc.val;
}

void Mos6502::incrementRegPC(const addr value) {
  this->reg.pc.val += value;
}

byte Mos6502::getRegAC() const {
  return reg.ac;
}

void Mos6502::setRegAC(const byte value) {
  this->reg.ac = value;
}

byte Mos6502::getRegX() const {
  return reg.x;
}

byte Mos6502::getRegY() const {
  return reg.y;
}

byte Mos6502::getRegSR() const {
  return reg.sr;
}

byte Mos6502::getRegSP() const {
  return reg.sp;
}

Mos6502Disassembler& Mos6502::getDis() {
  return dis;
}

const Mos6502Mmu& Mos6502::getMmu() const {
  return mmu;
}

#include "cpu/Mos6502_Ops.h"

} // namespace Cpu

#endif // MOS_6502_H //
