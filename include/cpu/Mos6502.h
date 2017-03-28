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
#include <array>

#include "common/CommonTypes.h"
#include "cpu/AbstractCpu.h"
#include "cpu/Mos6502Instruction.h"
#include "memory/Ram.h"
#include "memory/Reference.h"

namespace Cpu {

/// \class Mos6502
/// \brief This class is an abstract base that provides common functionality and
/// structure for emulation the Mos6502. Inheritors of this class can use the
/// public and protected interface of this class to provide a more concrete
/// method of emulation.
class Mos6502 : public AbstractCpu {
  public:
    /// Default constructor. Bootstrap a Mos6502 CPU object.
    Mos6502() : stack(reg.sp) {
      this->reg.pc.val = 0;
      this->reg.ac = 0;
      this->reg.x = 0;
      this->reg.y = 0;
      this->reg.sr = 0;
      // Stack pointer is initially full
      this->reg.sp = 0xFF;
    }

    //===------------------------------===//
    // AbstractCpu class methods
    //===------------------------------===//
    void init() override;
    void run() override;
    void reset() override;
    void trace() override;
    void shutdown() override;


    // Run-time emulation functions
    /// Fetch opcode from memory. This will retrieve the opcode at the current
    /// value of the program counter and return it for decoding.
    /// \returns Byte at the current value of the program counter.
    virtual byte fetchOpcode() final;

    /// Decode opcode into Mos6502Instruction object. This object provides a lot
    /// of information about the opcodes instruction that can be used for tracing
    /// and execution.
    /// \param opcode The opcode to decode into a Mos6502Instruction.
    /// \returns Decoded Mos6502Instruction object.
    virtual Mos6502Instruction decodeOpcode(byte opcode) final;

    /// Execute input instruction. This function will execute a Mos6502Instruction
    /// on the CPU.
    /// \param Mos6502Instruction object to execute.
    virtual void executeOpcode(Mos6502Instruction inst) final;

    // Cpu state inspection methods

    /// Get the remaining number of cycles to execute for the current instruction.
    /// \returns The current cycle count.
    int64 getCycleCount();

    /// Get the current address pointed to by the program counter.
    /// \returns The current value of the program counter.
    addr getRegPC();

    /// Get the current value of the accumulator.
    /// \returns The current value of the accumulator.
    byte getRegAC();

    /// Get the current value of the X-index register.
    /// \returns The current value of the X-index register.
    byte getRegX();

    /// Get the current value of the Y-index register.
    /// \returns The current value of the Y-index register.
    byte getRegY();

    /// Get the current value of the status register.
    /// \returns The current value of the status register.
    byte getRegSR();

    /// Get the current value of the stack pointer register.
    /// \returns The current value of the stack pointer register.
    byte getRegSP();

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
    //===------------------------------===//
    // CPU Instruction emulation functions
    //===------------------------------===//
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
    /// \param opdLo Low byte of the new address.
    /// \param opdHi High byte of the new address.
    inline void JMP(const byte opdLo, const byte opdHi);
    /// Jump to new location saving return address.
    /// \param opdLo Low byte of the new address.
    /// \param opdHi High byte of the new address.
    inline void JSR(const byte opdLo, const byte opdHi);
    /// Load accumulator with memory.
    /// \param opd Byte read from memory.
    inline void LDA(const byte);
    /// Load X-index register with memory.
    /// \param opd Byte read from memory.
    inline void LDX(const byte);
    /// Load Y-index register with memory.
    /// \param opd Byte read from memory.
    inline void LDY(const byte);
    /// Logical shift right.
    /// \param opd Byte read from memory.
    /// \returns Byte to write to memory.
    inline byte LSR(byte);
    /// No operation
    inline void NOP();
    /// OR memory with accumulator.
    /// \param opd Byte read from memory.
    inline void ORA(const byte);
    /// Push accumulator on processor stack.
    inline void PHA();
    /// Push processor status on processor stack.
    inline void PHP();
    /// Pul accumulator from processor stack.
    inline void PLA();
    /// Pull processor status from processor stack.
    inline void PLP();
    /// Rotate one bit left.
    /// \param opd Byte read from memory.
    /// \returns Byte to write to memory.
    inline byte ROL(byte);
    /// Rotate one bit right.
    /// \param opd Byte read from memory.
    /// \returns Byte to write to memory.
    inline byte ROR(byte);
    /// Return from interrupt.
    inline void RTI();
    /// Return from subroutine.
    inline void RTS();
    /// Subtract memory from accumulator with borrow.
    /// \param opd Byte read from memory.
    inline void SBC(const byte);
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

  private:
    /// Cycles required to execute current instruction
    int64 cycleCount;
    // Register structure
    struct {
      Vaddr pc; // Program counter
      byte  ac; // Accumulator
      byte  x;  // X Register
      byte  y;  // Y Register
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
            std::shared_ptr<Memory::Ram<byte>> bank = nullptr, 
            std::size_t offset = 0) : stackPointer(stackPointerRegister) {
          // If the memory Ram ptr passed in is null, create a new Ram to contain
          // this stack.
          if(bank == nullptr) {
            bank = std::make_shared<Memory::Ram<byte>>(std::numeric_limits<byte>::max() + 1);
            // if we built our own Ram, base is irrelevant, so set this to 0
            offset = 0;
          }
          // Mos6502 stack is top-down, so we must offset top from base.
          base = Memory::Reference<byte>(bank, offset);
        }

        ~Stack() {}

      private:
        /// Reference to the Mos6502 stack pointer
        byte& stackPointer;
        /// Memory reference to the base memory location of the CPU stack
        Memory::Reference<byte> base;

    } stack;
};

#include "cpu/Mos6502_Ops.h"

} // namespace Cpu

#endif // MOS_6502_H //
