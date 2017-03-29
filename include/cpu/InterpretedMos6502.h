//===-- iclude/cpu/InterpretedMos6502.h - Interpretted Emulator *- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the InterpretedMos6502 class, an interpreted
/// implementation of a Mos6502 emulator.
///
//===----------------------------------------------------------------------===//
#ifndef INTERPRETED_MOS6502_H
#define INTERPRETED_MOS6502_H

#include <functional>
#include <unordered_map>

#include "common/CommonTypes.h"
#include "cpu/Mos6502.h"
#include "cpu/Mos6502Mmu.h"
#include "cpu/Mos6502Instruction.h"
#include "memory/Ram.h"
#include "memory/Reference.h"

namespace Cpu {

/// \class InterpretedMos6502
/// \brief This class is an implementation of an interpreted Mos6502 emulator.
class InterpretedMos6502 : public Mos6502 {
  public:
    /// Default constructor. Bootstrap an IntrepretedMos6502 CPU object.
    InterpretedMos6502();
    ~InterpretedMos6502();

  protected:
    // Add with Carry
    /// Add memory to accumulator with carry, immediate addressing.
    /// \param inst Decoded instruction information.
    void adcImmediate(const Mos6502Instruction& inst); 
    /// Add memory to accumulator with carry, zeropage addressing.
    /// \param inst Decoded instruction information.
    void adcZeropage(const Mos6502Instruction& inst); 
    /// Add memory to accumulator with carry, zeropage X-indexed addressing.
    /// \param inst Decoded instruction information.
    void adcZeropageX(const Mos6502Instruction& inst); 
    /// Add memory to accumulator with carry, absolute addressing.
    /// \param inst Decoded instruction information.
    void adcAbsolute(const Mos6502Instruction& inst); 
    /// Add memory to accumulator with carry, absolute X-indexed addressing.
    /// \param inst Decoded instruction information.
    void adcAbsoluteX(const Mos6502Instruction& inst); 
    /// Add memory to accumulator with carry, absolute Y-indexed addressing.
    /// \param inst Decoded instruction information.
    void adcAbsoluteY(const Mos6502Instruction& inst); 
    /// Add memory to accumulator with carry, X-indexed indirect addressing.
    /// \param inst Decoded instruction information.
    void adcXIndirect(const Mos6502Instruction& inst); 
    /// Add memory to accumulator with carry, indirect Y-indexed addressing.
    /// \param inst Decoded instruction information.
    void adcIndirectY(const Mos6502Instruction& inst); 

    // AND with memory
    /// AND memory with accumulator, immediate addressing.
    /// \param inst Decoded instruction information.
    void andImmediate(const Mos6502Instruction& inst); 
    /// AND memory with accumulator, zeropage addressing.
    /// \param inst Decoded instruction information.
    void andZeropage(const Mos6502Instruction& inst); 
    /// AND memory with accumulator, zeropage X-indexed addressing.
    /// \param inst Decoded instruction information.
    void andZeropageX(const Mos6502Instruction& inst); 
    /// AND memory with accumulator, absolute addressing.
    /// \param inst Decoded instruction information.
    void andAbsolute(const Mos6502Instruction& inst); 
    /// AND memory with accumulator, absolute X-indexed addressing.
    /// \param inst Decoded instruction information.
    void andAbsoluteX(const Mos6502Instruction& inst); 
    /// AND memory with accumulator, absolute Y-indexed addressing.
    /// \param inst Decoded instruction information.
    void andAbsoluteY(const Mos6502Instruction& inst); 
    /// AND memory with accumulator, X-indexed indirect addressing.
    /// \param inst Decoded instruction information.
    void andXIndirect(const Mos6502Instruction& inst); 
    /// AND memory with accumulator, indirect Y-indexed addressing.
    void andIndirectY(const Mos6502Instruction& inst); 

    // Arithmetic shift left
    /// Shift left one bit, accumulator
    /// \param inst Decoded instruction information.
    void aslAccumulator(const Mos6502Instruction& inst);
    /// Shift left one bit, zeropage addressing
    /// \param inst Decoded instruction information.
    void aslZeropage(const Mos6502Instruction& inst);
    /// Shift left one bit, zeropage X-indexed addressing
    /// \param inst Decoded instruction information.
    void aslZeropageX(const Mos6502Instruction& inst);
    /// Shift left one bit, absolute addressing
    /// \param inst Decoded instruction information.
    void aslAbsolute(const Mos6502Instruction& inst);
    /// Shift left one bit, absolute X-indexed addressing
    /// \param inst Decoded instruction information.
    void aslAbsoluteX(const Mos6502Instruction& inst);

    /// Branch on carry clear, relative
    /// \param inst Decoded instruction information.
    void bccRelative(const Mos6502Instruction& inst);

    /// Branch on carry set, relative
    /// \param inst Decoded instruction information.
    void bcsRelative(const Mos6502Instruction& inst);

    /// Branch on zero set, relative
    /// \param inst Decoded instruction information.
    void beqRelative(const Mos6502Instruction& inst);

    /// Branch on negative set, relative
    /// \param inst Decoded instruction information.
    void bmiRelative(const Mos6502Instruction& inst);

    /// Branch on zero clear, relative
    /// \param inst Decoded instruction information.
    void bneRelative(const Mos6502Instruction& inst);

    /// Branch on negative clear, relative
    /// \param inst Decoded instruction information.
    void bplRelative(const Mos6502Instruction& inst);

    /// Branch on overflow clear, relative
    /// \param inst Decoded instruction information.
    void bvcRelative(const Mos6502Instruction& inst);

    /// Branch on overflow set, relative
    /// \param inst Decoded instruction information.
    void bvsRelative(const Mos6502Instruction& inst);

    // Test bits
    /// Test bits in memory with accumulator, zeropage addressing
    /// \param inst Decoded instruction information.
    void bitZeropage(const Mos6502Instruction& inst);
    /// Test bits in memory with accumulator, absolute addressing
    /// \param inst Decoded instruction information.
    void bitAbsolute(const Mos6502Instruction& inst);

    /// Force Break, implied addressing
    /// \param inst Decoded instruction information.
    void brkImplied(const Mos6502Instruction& inst);

    /// Clear carry flag, implied addressing
    /// \param inst Decoded instruction information.
    void clcImplied(const Mos6502Instruction& inst);

    /// Clear decimal flag, implied addressing
    /// \param inst Decoded instruction information.
    void cldImplied(const Mos6502Instruction& inst);

    /// Clear interrupt disable flag, implied addressing
    /// \param inst Decoded instruction information.
    void cliImplied(const Mos6502Instruction& inst);

    /// Clear overflow flag, implied addressing
    /// \param inst Decoded instruction information.
    void clvImplied(const Mos6502Instruction& inst);

    // Compare with memory
    /// Compare memory with accumulator, immediate addressing.
    /// \param inst Decoded instruction information.
    void cmpImmediate(const Mos6502Instruction& inst); 
    /// Compare memory with accumulator, zeropage addressing.
    /// \param inst Decoded instruction information.
    void cmpZeropage(const Mos6502Instruction& inst); 
    /// Compare memory with accumulator, zeropage X-indexed addressing.
    /// \param inst Decoded instruction information.
    void cmpZeropageX(const Mos6502Instruction& inst); 
    /// Compare memory with accumulator, absolute addressing.
    /// \param inst Decoded instruction information.
    void cmpAbsolute(const Mos6502Instruction& inst); 
    /// Compare memory with accumulator, absolute X-indexed addressing.
    /// \param inst Decoded instruction information.
    void cmpAbsoluteX(const Mos6502Instruction& inst); 
    /// Compare memory with accumulator, absolute Y-indexed addressing.
    /// \param inst Decoded instruction information.
    void cmpAbsoluteY(const Mos6502Instruction& inst); 
    /// Compare memory with accumulator, X-indexed indirect addressing.
    /// \param inst Decoded instruction information.
    void cmpXIndirect(const Mos6502Instruction& inst); 
    /// Compare memory with accumulator, indirect Y-indexed addressing.
    void cmpIndirectY(const Mos6502Instruction& inst); 

    /// Compare memory with X-index register, immediate addressing.
    /// \param inst Decoded instruction information.
    void cpxImmediate(const Mos6502Instruction& inst); 
    /// Compare memory with X-index register, zeropage addressing.
    /// \param inst Decoded instruction information.
    void cpxZeropage(const Mos6502Instruction& inst); 
    /// Compare memory with X-index register, absolute addressing.
    /// \param inst Decoded instruction information.
    void cpxAbsolute(const Mos6502Instruction& inst); 

    /// Compare memory with Y-index register, immediate addressing.
    /// \param inst Decoded instruction information.
    void cpyImmediate(const Mos6502Instruction& inst); 
    /// Compare memory with Y-index register, zeropage addressing.
    /// \param inst Decoded instruction information.
    void cpyZeropage(const Mos6502Instruction& inst); 
    /// Compare memory with Y-index register, absolute addressing.
    /// \param inst Decoded instruction information.
    void cpyAbsolute(const Mos6502Instruction& inst); 

    // Decrement memory
    /// Decrement memory by one, zeropage addressing
    /// \param inst Decoded instruction information.
    void decZeropage(const Mos6502Instruction& inst); 
    /// Decrement memory by one, zeropage X-indexed addressing
    /// \param inst Decoded instruction information.
    void decZeropageX(const Mos6502Instruction& inst); 
    /// Decrement memory by one, absolute addressing
    /// \param inst Decoded instruction information.
    void decAbsolute(const Mos6502Instruction& inst); 
    /// Decrement memory by one, absolute X-indexed addressing
    /// \param inst Decoded instruction information.
    void decAbsoluteX(const Mos6502Instruction& inst); 

    /// Decrement X-index register by one, implied addressing
    /// \param inst Decoded instruction information.
    void dexImplied(const Mos6502Instruction& inst);
    /// Decrement Y-index register by one, implied addressing
    /// \param inst Decoded instruction information.
    void deyImplied(const Mos6502Instruction& inst);

    // Exclusive OR with memory
    /// Exclusive OR memory with accumulator, immediate addressing.
    /// \param inst Decoded instruction information.
    void eorImmediate(const Mos6502Instruction& inst); 
    /// Exclusive OR memory with accumulator, zeropage addressing.
    /// \param inst Decoded instruction information.
    void eorZeropage(const Mos6502Instruction& inst); 
    /// Exclusive OR memory with accumulator, zeropage X-indexed addressing.
    /// \param inst Decoded instruction information.
    void eorZeropageX(const Mos6502Instruction& inst); 
    /// Exclusive OR memory with accumulator, absolute addressing.
    /// \param inst Decoded instruction information.
    void eorAbsolute(const Mos6502Instruction& inst); 
    /// Exclusive OR memory with accumulator, absolute X-indexed addressing.
    /// \param inst Decoded instruction information.
    void eorAbsoluteX(const Mos6502Instruction& inst); 
    /// Exclusive OR memory with accumulator, absolute Y-indexed addressing.
    /// \param inst Decoded instruction information.
    void eorAbsoluteY(const Mos6502Instruction& inst); 
    /// Exclusive OR memory with accumulator, X-indexed indirect addressing.
    /// \param inst Decoded instruction information.
    void eorXIndirect(const Mos6502Instruction& inst); 
    /// Exclusive OR memory with accumulator, indirect Y-indexed addressing.
    /// \param inst Decoded instruction information.
    void eorIndirectY(const Mos6502Instruction& inst); 

    // Increment memory
    /// Increment memory by one, zeropage addressing
    /// \param inst Decoded instruction information.
    void incZeropage(const Mos6502Instruction& inst); 
    /// Increment memory by one, zeropage X-indexed addressing
    /// \param inst Decoded instruction information.
    void incZeropageX(const Mos6502Instruction& inst); 
    /// Increment memory by one, absolute addressing
    /// \param inst Decoded instruction information.
    void incAbsolute(const Mos6502Instruction& inst); 
    /// Increment memory by one, absolute X-indexed addressing
    /// \param inst Decoded instruction information.
    void incAbsoluteX(const Mos6502Instruction& inst); 

    /// Increment X-index register by one, implied addressing
    /// \param inst Decoded instruction information.
    void inxImplied(const Mos6502Instruction& inst);
    /// Increment Y-index register by one, implied addressing
    /// \param inst Decoded instruction information.
    void inyImplied(const Mos6502Instruction& inst);

    // Jumps
    /// Jump to a new location, absolute addressing
    /// \param inst Decoded instruction information.
    void jmpAbsolute(const Mos6502Instruction& inst);
    /// Jump to a new location, indirect addressing
    /// \param inst Decoded instruction information.
    void jmpIndirect(const Mos6502Instruction& inst);

    /// Jump to a new location, saving return address, absolute addressing
    void jsrAbsolute(const Mos6502Instruction& inst);

    // Load Accumulator
    /// Load accumulator with memory, immediate addressing.
    /// \param inst Decoded instruction information.
    void ldaImmediate(const Mos6502Instruction& inst); 
    /// Load accumulator with memory, zeropage addressing.
    /// \param inst Decoded instruction information.
    void ldaZeropage(const Mos6502Instruction& inst); 
    /// Load accumulator with memory, zeropage X-indexed addressing.
    /// \param inst Decoded instruction information.
    void ldaZeropageX(const Mos6502Instruction& inst); 
    /// Load accumulator with memory, absolute addressing.
    /// \param inst Decoded instruction information.
    void ldaAbsolute(const Mos6502Instruction& inst); 
    /// Load accumulator with memory, absolute X-indexed addressing.
    /// \param inst Decoded instruction information.
    void ldaAbsoluteX(const Mos6502Instruction& inst); 
    /// Load accumulator with memory, absolute Y-indexed addressing.
    /// \param inst Decoded instruction information.
    void ldaAbsoluteY(const Mos6502Instruction& inst); 
    /// Load accumulator with memory, X-indexed indirect addressing.
    /// \param inst Decoded instruction information.
    void ldaXIndirect(const Mos6502Instruction& inst); 
    /// Load accumulator with memory, indirect Y-indexed addressing.
    /// \param inst Decoded instruction information.
    void ldaIndirectY(const Mos6502Instruction& inst); 

    // Load X-index
    /// Load X-index register with memory, immediate addressing.
    /// \param inst Decoded instruction information.
    void ldxImmediate(const Mos6502Instruction& inst); 
    /// Load X-index register with memory, zeropage addressing.
    /// \param inst Decoded instruction information.
    void ldxZeropage(const Mos6502Instruction& inst); 
    /// Load X-index register with memory, zeropage Y-indexed addressing.
    /// \param inst Decoded instruction information.
    void ldxZeropageY(const Mos6502Instruction& inst); 
    /// Load X-index register with memory, absolute addressing.
    /// \param inst Decoded instruction information.
    void ldxAbsolute(const Mos6502Instruction& inst); 
    /// Load X-index register with memory, absolute Y-indexed addressing.
    /// \param inst Decoded instruction information.
    void ldxAbsoluteY(const Mos6502Instruction& inst); 

    // Load Y-index
    /// Load X-index register with memory, immediate addressing.
    /// \param inst Decoded instruction information.
    void ldyImmediate(const Mos6502Instruction& inst); 
    /// Load X-index register with memory, zeropage addressing.
    /// \param inst Decoded instruction information.
    void ldyZeropage(const Mos6502Instruction& inst); 
    /// Load X-index register with memory, zeropage X-indexed addressing.
    /// \param inst Decoded instruction information.
    void ldyZeropageX(const Mos6502Instruction& inst); 
    /// Load X-index register with memory, absolute addressing.
    /// \param inst Decoded instruction information.
    void ldyAbsolute(const Mos6502Instruction& inst); 
    /// Load X-index register with memory, absolute X-indexed addressing.
    /// \param inst Decoded instruction information.
    void ldyAbsoluteX(const Mos6502Instruction& inst); 

    // Logical shift right
    /// Shift right one bit, accumulator
    /// \param inst Decoded instruction information.
    void lsrAccumulator(const Mos6502Instruction& inst);
    /// Shift right one bit, zeropage addressing
    /// \param inst Decoded instruction information.
    void lsrZeropage(const Mos6502Instruction& inst);
    /// Shift right one bit, zeropage X-indexed addressing
    /// \param inst Decoded instruction information.
    void lsrZeropageX(const Mos6502Instruction& inst);
    /// Shift right one bit, absolute addressing
    /// \param inst Decoded instruction information.
    void lsrAbsolute(const Mos6502Instruction& inst);
    /// Shift right one bit, absolute X-indexed addressing
    /// \param inst Decoded instruction information.
    void lsrAbsoluteX(const Mos6502Instruction& inst);

    /// No operation, implied addressing
    /// \param inst Decoded instruction information.
    void nopImplied(const Mos6502Instruction& inst);
    
    //  OR with memory
    /// OR memory with accumulator, immediate addressing.
    /// \param inst Decoded instruction information.
    void oraImmediate(const Mos6502Instruction& inst); 
    /// OR memory with accumulator, zeropage addressing.
    /// \param inst Decoded instruction information.
    void oraZeropage(const Mos6502Instruction& inst); 
    /// OR memory with accumulator, zeropage X-indexed addressing.
    /// \param inst Decoded instruction information.
    void oraZeropageX(const Mos6502Instruction& inst); 
    /// OR memory with accumulator, absolute addressing.
    /// \param inst Decoded instruction information.
    void oraAbsolute(const Mos6502Instruction& inst); 
    /// OR memory with accumulator, absolute X-indexed addressing.
    /// \param inst Decoded instruction information.
    void oraAbsoluteX(const Mos6502Instruction& inst); 
    /// OR memory with accumulator, absolute Y-indexed addressing.
    /// \param inst Decoded instruction information.
    void oraAbsoluteY(const Mos6502Instruction& inst); 
    /// OR memory with accumulator, X-indexed indirect addressing.
    /// \param inst Decoded instruction information.
    void oraXIndirect(const Mos6502Instruction& inst); 
    /// OR memory with accumulator, indirect Y-indexed addressing.
    /// \param inst Decoded instruction information.
    void oraIndirectY(const Mos6502Instruction& inst); 

    /// Push accumulator on stack, implied addressing
    /// \param inst Decoded instruction information.
    void phaImplied(const Mos6502Instruction& inst);

    /// Push processor status on stack, implied addressing
    /// \param inst Decoded instruction information.
    void phpImplied(const Mos6502Instruction& inst);

    /// Pull accumulator from stack, implied addressing
    /// \param inst Decoded instruction information.
    void plaImplied(const Mos6502Instruction& inst);

    /// Pull processor status from stack, implied addressing
    /// \param inst Decoded instruction information.
    void phaImplied(const Mos6502Instruction& inst);

    // Rotate left
    /// Rotate left one bit, accumulator
    /// \param inst Decoded instruction information.
    void rolAccumulator(const Mos6502Instruction& inst);
    /// Rotate left one bit, zeropage addressing
    /// \param inst Decoded instruction information.
    void rolZeropage(const Mos6502Instruction& inst);
    /// Rotate left one bit, zeropage X-indexed addressing
    /// \param inst Decoded instruction information.
    void rolZeropageX(const Mos6502Instruction& inst);
    /// Rotate left one bit, absolute addressing
    /// \param inst Decoded instruction information.
    void rolAbsolute(const Mos6502Instruction& inst);
    /// Rotate left one bit, absolute X-indexed addressing
    /// \param inst Decoded instruction information.
    void rolAbsoluteX(const Mos6502Instruction& inst);

    // Rotate right
    /// Rotate right one bit, accumulator
    /// \param inst Decoded instruction information.
    void rorAccumulator(const Mos6502Instruction& inst);
    /// Rotate right one bit, zeropage addressing
    /// \param inst Decoded instruction information.
    void rorZeropage(const Mos6502Instruction& inst);
    /// Rotate right one bit, zeropage X-indexed addressing
    /// \param inst Decoded instruction information.
    void rorZeropageX(const Mos6502Instruction& inst);
    /// Rotate right one bit, absolute addressing
    /// \param inst Decoded instruction information.
    void rorAbsolute(const Mos6502Instruction& inst);
    /// Rotate right one bit, absolute X-indexed addressing
    /// \param inst Decoded instruction information.
    void rorAbsoluteX(const Mos6502Instruction& inst);

    /// Return from interrupt, implied addressing
    /// \param inst Decoded instruction information.
    void rtiImplied(const Mos6502Instruction& inst);

    /// Return from subroutine, implied addressing
    /// \param inst Decoded instruction information.
    void rtsImplied(const Mos6502Instruction& inst);

    // Subtract with borrow
    /// Subtract memory from accumulator with borrow, immediate addressing.
    /// \param inst Decoded instruction information.
    void sbcImmediate(const Mos6502Instruction& inst); 
    /// Subtract memory from accumulator with borrow, zeropage addressing.
    /// \param inst Decoded instruction information.
    void sbcZeropage(const Mos6502Instruction& inst); 
    /// Subtract memory from accumulator with borrow, zeropage X-indexed addressing.
    /// \param inst Decoded instruction information.
    void sbcZeropageX(const Mos6502Instruction& inst); 
    /// Subtract memory from accumulator with borrow, absolute addressing.
    /// \param inst Decoded instruction information.
    void sbcAbsolute(const Mos6502Instruction& inst); 
    /// Subtract memory from accumulator with borrow, absolute X-indexed addressing.
    /// \param inst Decoded instruction information.
    void sbcAbsoluteX(const Mos6502Instruction& inst); 
    /// Subtract memory from accumulator with borrow, absolute Y-indexed addressing.
    /// \param inst Decoded instruction information.
    void sbcAbsoluteY(const Mos6502Instruction& inst); 
    /// Subtract memory from accumulator with borrow, X-indexed indirect addressing.
    /// \param inst Decoded instruction information.
    void sbcXIndirect(const Mos6502Instruction& inst); 
    /// Subtract memory from accumulator with borrow, indirect Y-indexed addressing.
    /// \param inst Decoded instruction information.
    void sbcIndirectY(const Mos6502Instruction& inst); 

    /// Set carry flag, implied addressing
    /// \param inst Decoded instruction information.
    void secImplied(const Mos6502Instruction& inst);

    /// Set decimal flag, implied addressing
    /// \param inst Decoded instruction information.
    void sedImplied(const Mos6502Instruction& inst);

    /// Set interrupt disable flag, implied addressing.
    /// \param inst Decoded instruction information.
    void seiImplied(const Mos6502Instruction& inst);

    // Store accumulator
    /// Store accumulator in memory, zeropage addressing.
    /// \param inst Decoded instruction information.
    void staZeropage(const Mos6502Instruction& inst); 
    /// Store accumulator in memory, zeropage X-indexed addressing.
    /// \param inst Decoded instruction information.
    void staZeropageX(const Mos6502Instruction& inst); 
    /// Store accumulator in memory, absolute addressing.
    /// \param inst Decoded instruction information.
    void staAbsolute(const Mos6502Instruction& inst); 
    /// Store accumulator in memory, absolute X-indexed addressing.
    /// \param inst Decoded instruction information.
    void staAbsoluteX(const Mos6502Instruction& inst); 
    /// Store accumulator in memory, absolute Y-indexed addressing.
    /// \param inst Decoded instruction information.
    void staAbsoluteY(const Mos6502Instruction& inst); 
    /// Store accumulator in memory, X-indexed indirect addressing.
    /// \param inst Decoded instruction information.
    void staXIndirect(const Mos6502Instruction& inst); 
    /// Store accumulator in memory, indirect Y-indexed addressing.
    /// \param inst Decoded instruction information.
    void staIndirectY(const Mos6502Instruction& inst); 

    // Store X-index register
    /// Store X-index register in memory, zeropage addressing.
    /// \param inst Decoded instruction information.
    void stxZeropage(const Mos6502Instruction& inst); 
    /// Store X-index register in memory, zeropage Y-indexed addressing.
    /// \param inst Decoded instruction information.
    void stxZeropageY(const Mos6502Instruction& inst); 
    /// Store X-index register in memory, absolute addressing.
    /// \param inst Decoded instruction information.
    void stxAbsolute(const Mos6502Instruction& inst); 

    // Store Y-index register
    /// Store Y-index register in memory, zeropage addressing.
    /// \param inst Decoded instruction information.
    void styZeropage(const Mos6502Instruction& inst); 
    /// Store Y-index register in memory, zeropage X-indexed addressing.
    /// \param inst Decoded instruction information.
    void styZeropageX(const Mos6502Instruction& inst); 
    /// Store Y-index register in memory, absolute addressing.
    /// \param inst Decoded instruction information.
    void styAbsolute(const Mos6502Instruction& inst); 

    /// Transfer accumulator to X-index register, implied addressing.
    /// \param inst Decoded instruction information.
    void taxImplied(const Mos6502Instruction& inst);

    /// Transfer accumulator to Y-index register, implied addressing.
    /// \param inst Decoded instruction information.
    void tayImplied(const Mos6502Instruction& inst);

    /// Transfer stack pointer to X-index register, implied addressing.
    /// \param inst Decoded instruction information.
    void tsxImplied(const Mos6502Instruction& inst);

    /// Transfer X-index register to accumulator, implied addressing.
    /// \param inst Decoded instruction information.
    void txaImplied(const Mos6502Instruction& inst);

    /// Transfer X-index register to stack pointer, implied addressing.
    /// \param inst Decoded instruction information.
    void txsImplied(const Mos6502Instruction& inst);

    /// Transfer Y-index register to accumulator, implied addressing.
    /// \param inst Decoded instruction information.
    void tyaImplied(const Mos6502Instruction& inst);

  private:
    /// Map between opcode and their interpreted implementation.
    std::unordered_map<byte, std::function<void(const Mos6502Instruction&)>> instructionMap;
};

} // namespace Cpu

#endif // INTERPRETED_MOS6502_H //
