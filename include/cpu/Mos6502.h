//===-- include/cpu/mos6502.h - Mos6502 Cpu Class ---------------*- C++ -*-===//
//
//                           The OsNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Functional specification for the MOS 6502 CPU. Any and all details related 
/// to the overall operation ofthe 6502 should be declared here.
///
//===----------------------------------------------------------------------===//
#ifndef MOS_6502_H
#define MOS_6502_H

#include <string>
#include <array>

#include "common/CommonTypes.h"
#include "cpu/CpuBase.h"
#include "memory/Reference.h"

namespace Cpu {

class Mos6502 : public CpuBase {
  public:

    // Mos6502 Instruction class
    struct Instruction {
      std::string name;
      byte opcode;
    };

    // CpuBase class methods
    // TODO: Implement
    void init() override;
    void run() override;
    void shutdown() override;

    // Run-time emulation functions
    /// Fetch opcode from memory
    virtual byte fetchOpcode() final;
    /// Decode opcode into Instruction object
    virtual Instruction decodeOpcode(byte opcode) final;
    /// Execute Instruction object
    virtual void executeOpcode(Instruction inst) final;

    // Cpu state inspection methods
    int64 getCycleCount();
    byte getRegPC();
    byte getRegAC();
    byte getRegX();
    byte getRegY();
    byte getRegSR();
    byte getRegSP();

  protected:
    // Addressing mode functions
    // Accumulator addressing
    Memory::Reference<byte> ACC();
    // Absolute addressing
    Memory::Reference<byte> ABS();
    // Absolute addressing X-indexed
    Memory::Reference<byte> ABS_X();
    // Absolute addressing Y-indexed
    Memory::Reference<byte> ABS_Y();
    // Immediate addressing
    Memory::Reference<byte> IMMED();
    // Indirect addressing
    Memory::Reference<byte> IND();
    // X-indexed indirect addressing
    Memory::Reference<byte> X_IND();
    // Indirect addressing Y-indexed
    Memory::Reference<byte> IND_Y();
    // Relative addressing
    Memory::Reference<byte> REL();
    // Zeropage addressing
    Memory::Reference<byte> ZPG();
    // Zeropage addressing X-indexed
    Memory::Reference<byte> ZPG_X();
    // Zeropage addressing Y-indexed
    Memory::Reference<byte> ZPG_Y();

    // CPU Instruction emulation functions
    inline void ADC(const byte);
    inline void AND(const byte);
    inline byte ASL(byte);
    inline void BCC(const byte);
    inline void BCS(const byte);
    inline void BEQ(const byte);
    inline void BIT(const byte);
    inline void BMI(const byte);
    inline void BNE(const byte);
    inline void BPL(const byte);
    inline void BRK();
    inline void BVC(const byte);
    inline void BVS(const byte);
    inline void CLC();
    inline void CLD();
    inline void CLI();
    inline void CLV();
    inline void CMP(const byte);
    inline void CPX(const byte);
    inline void CPY(const byte);
    inline byte DEC(byte);
    inline void DEX();
    inline void DEY();
    inline void EOR(const byte);
    inline byte INC(byte);
    inline void INX();
    inline void INY();
    inline void JMP(const byte, const byte);
    inline void JSR(const byte, const byte);
    inline void LDA(const byte);
    inline void LDX(const byte);
    inline void LDY(const byte);
    inline byte LSR(byte);
    inline void NOP();
    inline void ORA(const byte);
    inline void PHA();
    inline void PHP();
    inline void PLA();
    inline void PLP();
    inline byte ROL(byte);
    inline byte ROR(byte);
    inline void RTI();
    inline void RTS();
    inline void SBC(const byte);
    inline void SEC();
    inline void SED();
    inline void SEI();
    inline byte STA();
    inline byte STX();
    inline byte STY();
    inline void TAX();
    inline void TAY();
    inline void TSX();
    inline void TXA();
    inline void TXS();
    inline void TYA();

  private:
    // Cycles required to execute current instruction
    int64 cycleCount;
    // Register structure
    struct {
      union {
        uint16 pc; // Program Counter
        struct {
#ifdef __BIG_ENDIAN__
          byte pch;
          byte pcl;
#else // Little Endian
          byte pcl;
          byte pch;
#endif // __BIG_ENDIAN__
        };
      };
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

    // Processor stack
    // LIFO, top down, 8 bit range, 0x0100 - 0x01FF
    class Stack {
      public:
        inline void push(byte data) {
          // store data at current location and decrement
          *top = data;
          top--;
        }

        inline byte pull() {
          // retrieve data, increment, and return data
          auto temp = *top;
          top++;
          return temp;
        }

        Stack(std::unique_ptr<byte[]> mem_ptr = nullptr) {
          // If we construct with a non-null unique_ptr, we will move ownership
          // of that memory resource to this stack. Otherwise, we will make our
          // own unique_ptr.
          if(mem_ptr == nullptr) {
            base = std::make_unique<byte[]>(std::numeric_limits<byte>::max() + 1);
          }
          else {
            base = std::move(mem_ptr);
          }
          // Mos6502 stack is top-down, so we must offset top from base.
          top = base.get() + std::numeric_limits<byte>::max();
        }

        ~Stack() {
          // Set both pointers to be nullptr for safety
          top = nullptr;
          base = nullptr;
        }
      private:
        // The stack consists of two pointers, one raw pointer, top,
        // which will point to the 'top' of the stack, and one unique_ptr
        // base, which will control the memory resource associated with this
        // Stack.
        byte* top;
        std::unique_ptr<byte[]> base;
    } stack;
};

// SR Flag Masks
static const byte SR_N = 0x80; // Negative
static const byte SR_V = 0x40; // Overflow
static const byte SR_B = 0x10; // Break
static const byte SR_D = 0x08; // Decimal (use BCD for arithmetics)
static const byte SR_I = 0x04; // Interrupt (IRQ disable)
static const byte SR_Z = 0x02; // Zero
static const byte SR_C = 0x01; // Carry

#include "cpu/Mos6502_Ops.h"

// Include inlinable definition of above functions
#include "cpu/Mos6502_Inst.h"

} // namespace Cpu

#endif // MOS_6502_H //:~
