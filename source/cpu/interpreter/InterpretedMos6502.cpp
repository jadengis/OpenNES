//===-- source/cpu/InterpretedMos6502.cpp - Interpreted Emulator *- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implemntation of the InterpretedMos6502 class, an 
/// interpreted implementation of a Mos6502 emulator.
///
//===----------------------------------------------------------------------===//
#include <functional>
#include <unordered_map>

#include "common/CommonTypes.h"
#include "cpu/Mos6502_Ops.h"
#include "cpu/interpreter/InterpretedMos6502.h"
#include "memory/Reference.h"

#include "Mos6502_Inst.h"

using namespace Cpu;
using namespace Memory;

InterpretedMos6502::InterpretedMos6502(Memory::Mapper<byte>& memMap) :
    Mos6502(memMap) {
  initializeInstructionMap();    
}

InterpretedMos6502::~InterpretedMos6502() {}

void InterpretedMos6502::fetchOpcodeImpl() {
  // fetch the opcode at the current program counter
  Vaddr vaddr;
  vaddr.val = getRegPC();
  Reference<byte> ref = getMmu().absolute(vaddr);
  setRegIR(ref.read());
  getDis().setReadPosition(ref);
}

void InterpretedMos6502::decodeOpcodeImpl() {
  // decode instruction in the instruction register
  currentInstruction = getDis().disassembleInstruction(getRegIR());
  // Increment the program counter by the number of operands + 1 for
  // the opcode. It is important that we increment the program counter
  // after we decode the instruction, as some instruction behaviour, like
  // jumps and branchs depend on this behaviour.
  incrementRegPC(static_cast<addr>(currentInstruction.type) + 1);
}

void InterpretedMos6502::executeOpcodeImpl() {
  instructionMap[currentInstruction.opcode](currentInstruction);
  incrementCycles(currentInstruction.cycles);
}

using std::placeholders::_1;

void InterpretedMos6502::initializeInstructionMap() {
  // Here we will build the instruction map
  // ADC
  instructionMap[Op::ADC_IMMED] = std::bind(&InterpretedMos6502::adcImmediate, this, _1);
  instructionMap[Op::ADC_ZPG] = std::bind(&InterpretedMos6502::adcZeropage, this, _1);
  instructionMap[Op::ADC_ZPG_X] = std::bind(&InterpretedMos6502::adcZeropageX, this, _1);
  instructionMap[Op::ADC_ABS] = std::bind(&InterpretedMos6502::adcAbsolute, this, _1);
  instructionMap[Op::ADC_ABS_X] = std::bind(&InterpretedMos6502::adcAbsoluteX, this, _1); 
  instructionMap[Op::ADC_ABS_Y] = std::bind(&InterpretedMos6502::adcAbsoluteY, this, _1); 
  instructionMap[Op::ADC_X_IND] = std::bind(&InterpretedMos6502::adcXIndirect, this, _1); 
  instructionMap[Op::ADC_IND_Y] = std::bind(&InterpretedMos6502::adcIndirectY, this, _1); 
  // AND
  instructionMap[Op::AND_IMMED] = std::bind(&InterpretedMos6502::andImmediate, this, _1); 
  instructionMap[Op::AND_ZPG] = std::bind(&InterpretedMos6502::andZeropage, this, _1); 
  instructionMap[Op::AND_ZPG_X] = std::bind(&InterpretedMos6502::andZeropageX, this, _1); 
  instructionMap[Op::AND_ABS] = std::bind(&InterpretedMos6502::andAbsolute, this, _1); 
  instructionMap[Op::AND_ABS_X] = std::bind(&InterpretedMos6502::andAbsoluteX, this, _1); 
  instructionMap[Op::AND_ABS_Y] = std::bind(&InterpretedMos6502::andAbsoluteY, this, _1); 
  instructionMap[Op::AND_X_IND] = std::bind(&InterpretedMos6502::andXIndirect, this, _1); 
  instructionMap[Op::AND_IND_Y] = std::bind(&InterpretedMos6502::andIndirectY, this, _1); 
  // ASL
  instructionMap[Op::ASL_ACC] = std::bind(&InterpretedMos6502::aslAccumulator, this, _1);
  instructionMap[Op::ASL_ZPG] = std::bind(&InterpretedMos6502::aslZeropage, this, _1);
  instructionMap[Op::ASL_ZPG_X] = std::bind(&InterpretedMos6502::aslZeropageX, this, _1);
  instructionMap[Op::ASL_ABS] = std::bind(&InterpretedMos6502::aslAbsolute, this, _1);
  instructionMap[Op::ASL_ABS_X] = std::bind(&InterpretedMos6502::aslAbsoluteX, this, _1);
  // Branch
  instructionMap[Op::BCC_REL] = std::bind(&InterpretedMos6502::bccRelative, this, _1);
  instructionMap[Op::BCS_REL] = std::bind(&InterpretedMos6502::bcsRelative, this, _1);
  instructionMap[Op::BEQ_REL] = std::bind(&InterpretedMos6502::beqRelative, this, _1);
  instructionMap[Op::BMI_REL] = std::bind(&InterpretedMos6502::bmiRelative, this, _1);
  instructionMap[Op::BNE_REL] = std::bind(&InterpretedMos6502::bneRelative, this, _1);
  instructionMap[Op::BPL_REL] = std::bind(&InterpretedMos6502::bplRelative, this, _1);
  instructionMap[Op::BVC_REL] = std::bind(&InterpretedMos6502::bvcRelative, this, _1);
  instructionMap[Op::BVS_REL] = std::bind(&InterpretedMos6502::bvsRelative, this, _1);
  // BIT
  instructionMap[Op::BIT_ZPG] = std::bind(&InterpretedMos6502::bitZeropage, this, _1);
  instructionMap[Op::BIT_ABS] = std::bind(&InterpretedMos6502::bitAbsolute, this, _1);
  // BRK
  instructionMap[Op::BRK_IMPL] = std::bind(&InterpretedMos6502::brkImplied, this, _1);
  // Clears
  instructionMap[Op::CLC_IMPL] = std::bind(&InterpretedMos6502::clcImplied, this, _1);
  instructionMap[Op::CLD_IMPL] = std::bind(&InterpretedMos6502::cldImplied, this, _1);
  instructionMap[Op::CLI_IMPL] = std::bind(&InterpretedMos6502::cliImplied, this, _1);
  instructionMap[Op::CLV_IMPL] = std::bind(&InterpretedMos6502::clvImplied, this, _1);
  // CMP
  instructionMap[Op::CMP_IMMED] = std::bind(&InterpretedMos6502::cmpImmediate, this, _1);
  instructionMap[Op::CMP_ZPG] = std::bind(&InterpretedMos6502::cmpZeropage, this, _1);
  instructionMap[Op::CMP_ZPG_X] = std::bind(&InterpretedMos6502::cmpZeropageX, this, _1);
  instructionMap[Op::CMP_ABS] = std::bind(&InterpretedMos6502::cmpAbsolute, this, _1);
  instructionMap[Op::CMP_ABS_X] = std::bind(&InterpretedMos6502::cmpAbsoluteX, this, _1);
  instructionMap[Op::CMP_ABS_Y] = std::bind(&InterpretedMos6502::cmpAbsoluteY, this, _1);
  instructionMap[Op::CMP_X_IND] = std::bind(&InterpretedMos6502::cmpXIndirect, this, _1);
  instructionMap[Op::CMP_IND_Y] = std::bind(&InterpretedMos6502::cmpIndirectY, this, _1);
  // CPX
  instructionMap[Op::CPX_IMMED] = std::bind(&InterpretedMos6502::cpxImmediate, this, _1);
  instructionMap[Op::CPX_ZPG] = std::bind(&InterpretedMos6502::cpxZeropage, this, _1);
  instructionMap[Op::CPX_ABS] = std::bind(&InterpretedMos6502::cpxAbsolute, this, _1);
  // CPY
  instructionMap[Op::CPY_IMMED] = std::bind(&InterpretedMos6502::cpyImmediate, this, _1);
  instructionMap[Op::CPY_ZPG] = std::bind(&InterpretedMos6502::cpyZeropage, this, _1);
  instructionMap[Op::CPY_ABS] = std::bind(&InterpretedMos6502::cpyAbsolute, this, _1);
  // DEC
  instructionMap[Op::DEC_ZPG] = std::bind(&InterpretedMos6502::decZeropage, this, _1);
  instructionMap[Op::DEC_ZPG_X] = std::bind(&InterpretedMos6502::decZeropageX, this, _1);
  instructionMap[Op::DEC_ABS] = std::bind(&InterpretedMos6502::decAbsolute, this, _1);
  instructionMap[Op::DEC_ABS_X] = std::bind(&InterpretedMos6502::decAbsoluteX, this, _1);
  // DEX
  instructionMap[Op::DEX_IMPL] = std::bind(&InterpretedMos6502::dexImplied, this, _1);
  // DEY
  instructionMap[Op::DEY_IMPL] = std::bind(&InterpretedMos6502::deyImplied, this, _1);
  // EOR
  instructionMap[Op::EOR_IMMED] = std::bind(&InterpretedMos6502::eorImmediate, this, _1);
  instructionMap[Op::EOR_ZPG] = std::bind(&InterpretedMos6502::eorZeropage, this, _1);
  instructionMap[Op::EOR_ZPG_X] = std::bind(&InterpretedMos6502::eorZeropageX, this, _1);
  instructionMap[Op::EOR_ABS] = std::bind(&InterpretedMos6502::eorAbsolute, this, _1);
  instructionMap[Op::EOR_ABS_X] = std::bind(&InterpretedMos6502::eorAbsoluteX, this, _1); 
  instructionMap[Op::EOR_ABS_Y] = std::bind(&InterpretedMos6502::eorAbsoluteY, this, _1); 
  instructionMap[Op::EOR_X_IND] = std::bind(&InterpretedMos6502::eorXIndirect, this, _1); 
  instructionMap[Op::EOR_IND_Y] = std::bind(&InterpretedMos6502::eorIndirectY, this, _1); 
  // INC
  instructionMap[Op::INC_ZPG] = std::bind(&InterpretedMos6502::incZeropage, this, _1);
  instructionMap[Op::INC_ZPG_X] = std::bind(&InterpretedMos6502::incZeropageX, this, _1);
  instructionMap[Op::INC_ABS] = std::bind(&InterpretedMos6502::incAbsolute, this, _1);
  instructionMap[Op::INC_ABS_X] = std::bind(&InterpretedMos6502::incAbsoluteX, this, _1);
  // INX
  instructionMap[Op::INX_IMPL] = std::bind(&InterpretedMos6502::inxImplied, this, _1);
  // INY
  instructionMap[Op::INY_IMPL] = std::bind(&InterpretedMos6502::inyImplied, this, _1);
  // JMP
  instructionMap[Op::JMP_ABS] = std::bind(&InterpretedMos6502::jmpAbsolute, this, _1);
  instructionMap[Op::JMP_IND] = std::bind(&InterpretedMos6502::jmpIndirect, this, _1);
  // JSR
  instructionMap[Op::JSR_ABS] = std::bind(&InterpretedMos6502::jsrAbsolute, this, _1);
  // LDA
  instructionMap[Op::LDA_IMMED] = std::bind(&InterpretedMos6502::ldaImmediate, this, _1);
  instructionMap[Op::LDA_ZPG] = std::bind(&InterpretedMos6502::ldaZeropage, this, _1);
  instructionMap[Op::LDA_ZPG_X] = std::bind(&InterpretedMos6502::ldaZeropageX, this, _1);
  instructionMap[Op::LDA_ABS] = std::bind(&InterpretedMos6502::ldaAbsolute, this, _1);
  instructionMap[Op::LDA_ABS_X] = std::bind(&InterpretedMos6502::ldaAbsoluteX, this, _1);
  instructionMap[Op::LDA_ABS_Y] = std::bind(&InterpretedMos6502::ldaAbsoluteY, this, _1);
  instructionMap[Op::LDA_X_IND] = std::bind(&InterpretedMos6502::ldaXIndirect, this, _1);
  instructionMap[Op::LDA_IND_Y] = std::bind(&InterpretedMos6502::ldaIndirectY, this, _1);
  // LDX
  instructionMap[Op::LDX_IMMED] = std::bind(&InterpretedMos6502::ldxImmediate, this, _1);
  instructionMap[Op::LDX_ZPG] = std::bind(&InterpretedMos6502::ldxZeropage, this, _1);
  instructionMap[Op::LDX_ZPG_Y] = std::bind(&InterpretedMos6502::ldxZeropageY, this, _1);
  instructionMap[Op::LDX_ABS] = std::bind(&InterpretedMos6502::ldxAbsolute, this, _1);
  instructionMap[Op::LDX_ABS_Y] = std::bind(&InterpretedMos6502::ldxAbsoluteY, this, _1);
  // LDY
  instructionMap[Op::LDY_IMMED] = std::bind(&InterpretedMos6502::ldyImmediate, this, _1);
  instructionMap[Op::LDY_ZPG] = std::bind(&InterpretedMos6502::ldyZeropage, this, _1);
  instructionMap[Op::LDY_ZPG_X] = std::bind(&InterpretedMos6502::ldyZeropageX, this, _1);
  instructionMap[Op::LDY_ABS] = std::bind(&InterpretedMos6502::ldyAbsolute, this, _1);
  instructionMap[Op::LDY_ABS_X] = std::bind(&InterpretedMos6502::ldyAbsoluteX, this, _1);
  // LSR
  instructionMap[Op::LSR_ACC] = std::bind(&InterpretedMos6502::lsrAccumulator, this, _1);
  instructionMap[Op::LSR_ZPG] = std::bind(&InterpretedMos6502::lsrZeropage, this, _1);
  instructionMap[Op::LSR_ZPG_X] = std::bind(&InterpretedMos6502::lsrZeropageX, this, _1);
  instructionMap[Op::LSR_ABS] = std::bind(&InterpretedMos6502::lsrAbsolute, this, _1);
  instructionMap[Op::LSR_ABS_X] = std::bind(&InterpretedMos6502::lsrAbsoluteX, this, _1);
  // NOP
  instructionMap[Op::NOP_IMPL] = std::bind(&InterpretedMos6502::nopImplied, this, _1);
  // ORA
  instructionMap[Op::ORA_IMMED] = std::bind(&InterpretedMos6502::oraImmediate, this, _1);
  instructionMap[Op::ORA_ZPG] = std::bind(&InterpretedMos6502::oraZeropage, this, _1);
  instructionMap[Op::ORA_ZPG_X] = std::bind(&InterpretedMos6502::oraZeropageX, this, _1);
  instructionMap[Op::ORA_ABS] = std::bind(&InterpretedMos6502::oraAbsolute, this, _1);
  instructionMap[Op::ORA_ABS_X] = std::bind(&InterpretedMos6502::oraAbsoluteX, this, _1); 
  instructionMap[Op::ORA_ABS_Y] = std::bind(&InterpretedMos6502::oraAbsoluteY, this, _1); 
  instructionMap[Op::ORA_X_IND] = std::bind(&InterpretedMos6502::oraXIndirect, this, _1); 
  instructionMap[Op::ORA_IND_Y] = std::bind(&InterpretedMos6502::oraIndirectY, this, _1); 
  // Stack Operations
  instructionMap[Op::PHA_IMPL] = std::bind(&InterpretedMos6502::phaImplied, this, _1);
  instructionMap[Op::PHP_IMPL] = std::bind(&InterpretedMos6502::phpImplied, this, _1);
  instructionMap[Op::PLA_IMPL] = std::bind(&InterpretedMos6502::plaImplied, this, _1);
  instructionMap[Op::PLP_IMPL] = std::bind(&InterpretedMos6502::plpImplied, this, _1);
  // ROL
  instructionMap[Op::ROL_ACC] = std::bind(&InterpretedMos6502::rolAccumulator, this, _1);
  instructionMap[Op::ROL_ZPG] = std::bind(&InterpretedMos6502::rolZeropage, this, _1);
  instructionMap[Op::ROL_ZPG_X] = std::bind(&InterpretedMos6502::rolZeropageX, this, _1);
  instructionMap[Op::ROL_ABS] = std::bind(&InterpretedMos6502::rolAbsolute, this, _1);
  instructionMap[Op::ROL_ABS_X] = std::bind(&InterpretedMos6502::rolAbsoluteX, this, _1);
  // ROR
  instructionMap[Op::ROR_ACC] = std::bind(&InterpretedMos6502::rorAccumulator, this, _1);
  instructionMap[Op::ROR_ZPG] = std::bind(&InterpretedMos6502::rorZeropage, this, _1);
  instructionMap[Op::ROR_ZPG_X] = std::bind(&InterpretedMos6502::rorZeropageX, this, _1);
  instructionMap[Op::ROR_ABS] = std::bind(&InterpretedMos6502::rorAbsolute, this, _1);
  instructionMap[Op::ROR_ABS_X] = std::bind(&InterpretedMos6502::rorAbsoluteX, this, _1);
  // Returns
  instructionMap[Op::RTI_IMPL] = std::bind(&InterpretedMos6502::rtiImplied, this, _1);
  instructionMap[Op::RTS_IMPL] = std::bind(&InterpretedMos6502::rtsImplied, this, _1);
  // SBC
  instructionMap[Op::SBC_IMMED] = std::bind(&InterpretedMos6502::sbcImmediate, this, _1);
  instructionMap[Op::SBC_ZPG] = std::bind(&InterpretedMos6502::sbcZeropage, this, _1);
  instructionMap[Op::SBC_ZPG_X] = std::bind(&InterpretedMos6502::sbcZeropageX, this, _1);
  instructionMap[Op::SBC_ABS] = std::bind(&InterpretedMos6502::sbcAbsolute, this, _1);
  instructionMap[Op::SBC_ABS_X] = std::bind(&InterpretedMos6502::sbcAbsoluteX, this, _1); 
  instructionMap[Op::SBC_ABS_Y] = std::bind(&InterpretedMos6502::sbcAbsoluteY, this, _1); 
  instructionMap[Op::SBC_X_IND] = std::bind(&InterpretedMos6502::sbcXIndirect, this, _1); 
  instructionMap[Op::SBC_IND_Y] = std::bind(&InterpretedMos6502::sbcIndirectY, this, _1); 
  // Sets
  instructionMap[Op::SEC_IMPL] = std::bind(&InterpretedMos6502::secImplied, this, _1); 
  instructionMap[Op::SED_IMPL] = std::bind(&InterpretedMos6502::sedImplied, this, _1); 
  instructionMap[Op::SEI_IMPL] = std::bind(&InterpretedMos6502::seiImplied, this, _1); 
  // STA
  instructionMap[Op::STA_ZPG] = std::bind(&InterpretedMos6502::staZeropage, this, _1);
  instructionMap[Op::STA_ZPG_X] = std::bind(&InterpretedMos6502::staZeropageX, this, _1);
  instructionMap[Op::STA_ABS] = std::bind(&InterpretedMos6502::staAbsolute, this, _1);
  instructionMap[Op::STA_ABS_X] = std::bind(&InterpretedMos6502::staAbsoluteX, this, _1); 
  instructionMap[Op::STA_ABS_Y] = std::bind(&InterpretedMos6502::staAbsoluteY, this, _1); 
  instructionMap[Op::STA_X_IND] = std::bind(&InterpretedMos6502::staXIndirect, this, _1); 
  instructionMap[Op::STA_IND_Y] = std::bind(&InterpretedMos6502::staIndirectY, this, _1); 
  // STX
  instructionMap[Op::STX_ZPG] = std::bind(&InterpretedMos6502::stxZeropage, this, _1);
  instructionMap[Op::STX_ZPG_Y] = std::bind(&InterpretedMos6502::stxZeropageY, this, _1);
  instructionMap[Op::STX_ABS] = std::bind(&InterpretedMos6502::stxAbsolute, this, _1);
  // STY
  instructionMap[Op::STY_ZPG] = std::bind(&InterpretedMos6502::styZeropage, this, _1);
  instructionMap[Op::STY_ZPG_X] = std::bind(&InterpretedMos6502::styZeropageX, this, _1);
  instructionMap[Op::STY_ABS] = std::bind(&InterpretedMos6502::styAbsolute, this, _1);
  // Transfers
  instructionMap[Op::TAX_IMPL] = std::bind(&InterpretedMos6502::taxImplied, this, _1);
  instructionMap[Op::TAY_IMPL] = std::bind(&InterpretedMos6502::tayImplied, this, _1);
  instructionMap[Op::TSX_IMPL] = std::bind(&InterpretedMos6502::tsxImplied, this, _1);
  instructionMap[Op::TXA_IMPL] = std::bind(&InterpretedMos6502::txaImplied, this, _1);
  instructionMap[Op::TXS_IMPL] = std::bind(&InterpretedMos6502::txsImplied, this, _1);
  instructionMap[Op::TYA_IMPL] = std::bind(&InterpretedMos6502::tyaImplied, this, _1);
  
}

//===----------------------------------------------------------------------===//
// For all instruction emulation functions, we use the instruction information to
// build the virtual address (if needed), feed that into the MMU to get an
// appropriate memory refrence, and read an write to that memory as needed.
// 
// For immediate and relative addressing, we read the immediate value from the 
// lo byte of the input instruction.
//===----------------------------------------------------------------------===//

/// Helper function for computing the virtual address referenced by a
/// Mos6502Instruction.
/// \param inst The instruction whose operands build the address.
/// \returns The virtual address.
static inline Vaddr computeAddress(const Mos6502Instruction& inst) {
  Vaddr vaddr;
  vaddr.ll = inst.operand.lo;
  vaddr.hh = inst.operand.hi;
  return vaddr;
}

/// Helper function for computing the virtual address referenced by a
/// Memory::Reference.
/// \param ref The reference which points to the address.
/// \returns The virtual address.
static inline Vaddr computeAddress(const Reference<byte>& ref) {
  Vaddr vaddr;
  vaddr.ll = ref.read();
  vaddr.hh = ref.read(1);
  return vaddr;
}

// Add with carry
void InterpretedMos6502::adcImmediate(const Mos6502Instruction& inst) {
  ADC(inst.operand.lo);
}

void InterpretedMos6502::adcZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  ADC(ref.read());
}

void InterpretedMos6502::adcZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  ADC(ref.read());
}

void InterpretedMos6502::adcAbsolute(const Mos6502Instruction& inst) { 
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  ADC(ref.read());
}

void InterpretedMos6502::adcAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  ADC(ref.read());
}

void InterpretedMos6502::adcAbsoluteY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteYIndexed(computeAddress(inst));
  ADC(ref.read());
}

void InterpretedMos6502::adcXIndirect(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().xIndexedIndirect(computeAddress(inst));
  ADC(ref.read());
}

void InterpretedMos6502::adcIndirectY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().indirectYIndexed(computeAddress(inst));
  ADC(ref.read());
}

// AND with memory
void InterpretedMos6502::andImmediate(const Mos6502Instruction& inst) {
  AND(inst.operand.lo);
}

void InterpretedMos6502::andZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  AND(ref.read());
}

void InterpretedMos6502::andZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  AND(ref.read());
}

void InterpretedMos6502::andAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  AND(ref.read());
}

void InterpretedMos6502::andAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  AND(ref.read());
}

void InterpretedMos6502::andAbsoluteY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteYIndexed(computeAddress(inst));
  AND(ref.read());
}

void InterpretedMos6502::andXIndirect(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().xIndexedIndirect(computeAddress(inst));
  AND(ref.read());
}

void InterpretedMos6502::andIndirectY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().xIndexedIndirect(computeAddress(inst));
  AND(ref.read());
}

// Arithmetic shift left
void InterpretedMos6502::aslAccumulator(const Mos6502Instruction& inst) { 
  setRegAC(ASL(getRegAC()));
}

void InterpretedMos6502::aslZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  ref.write(ASL(ref.read()));
}

void InterpretedMos6502::aslZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  ref.write(ASL(ref.read()));
}

void InterpretedMos6502::aslAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  ref.write(ASL(ref.read()));
}

void InterpretedMos6502::aslAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  ref.write(ASL(ref.read()));
}

// Branching
void InterpretedMos6502::bccRelative(const Mos6502Instruction& inst) {
  BCC(inst.operand.lo);
}

void InterpretedMos6502::bcsRelative(const Mos6502Instruction& inst) {
  BCS(inst.operand.lo);
}

void InterpretedMos6502::beqRelative(const Mos6502Instruction& inst) {
  BEQ(inst.operand.lo);
}

void InterpretedMos6502::bmiRelative(const Mos6502Instruction& inst) {
  BMI(inst.operand.lo);
}

void InterpretedMos6502::bneRelative(const Mos6502Instruction& inst) {
  BNE(inst.operand.lo);
}

void InterpretedMos6502::bplRelative(const Mos6502Instruction& inst) {
  BPL(inst.operand.lo);
}

void InterpretedMos6502::bvcRelative(const Mos6502Instruction& inst) {
  BVC(inst.operand.lo);
}

void InterpretedMos6502::bvsRelative(const Mos6502Instruction& inst) {
  BVS(inst.operand.lo);
}

// Test bits
void InterpretedMos6502::bitZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  BIT(ref.read());
}

void InterpretedMos6502::bitAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  BIT(ref.read());
}

// Force break
void InterpretedMos6502::brkImplied(const Mos6502Instruction& inst) {
  BRK();
}

// Clear flags
void InterpretedMos6502::clcImplied(const Mos6502Instruction& inst) {
  CLC();
}

void InterpretedMos6502::cldImplied(const Mos6502Instruction& inst) {
  CLD();
}

void InterpretedMos6502::cliImplied(const Mos6502Instruction& inst) {
  CLI();
}

void InterpretedMos6502::clvImplied(const Mos6502Instruction& inst) {
  CLV();
}

// Compare with memory
void InterpretedMos6502::cmpImmediate(const Mos6502Instruction& inst) {
  CMP(inst.operand.lo);
}

void InterpretedMos6502::cmpZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  CMP(ref.read());
}

void InterpretedMos6502::cmpZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  CMP(ref.read());
}

void InterpretedMos6502::cmpAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  CMP(ref.read());
}

void InterpretedMos6502::cmpAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  CMP(ref.read());
}

void InterpretedMos6502::cmpAbsoluteY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteYIndexed(computeAddress(inst));
  CMP(ref.read());
}

void InterpretedMos6502::cmpXIndirect(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().xIndexedIndirect(computeAddress(inst));
  CMP(ref.read());
}

void InterpretedMos6502::cmpIndirectY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().indirectYIndexed(computeAddress(inst));
  CMP(ref.read());
}

void InterpretedMos6502::cpxImmediate(const Mos6502Instruction& inst) {
  CPX(inst.operand.lo);
}

void InterpretedMos6502::cpxZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  CPX(ref.read());
}

void InterpretedMos6502::cpxAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  CPX(ref.read());
}

void InterpretedMos6502::cpyImmediate(const Mos6502Instruction& inst) {
  CPY(inst.operand.lo);
}

void InterpretedMos6502::cpyZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  CPY(ref.read());
}

void InterpretedMos6502::cpyAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  CPY(ref.read());
}

// Decrement memory
void InterpretedMos6502::decZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  ref.write(DEC(ref.read()));
}

void InterpretedMos6502::decZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  ref.write(DEC(ref.read()));
}

void InterpretedMos6502::decAbsolute(const Mos6502Instruction& inst) { 
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  ref.write(DEC(ref.read()));
}

void InterpretedMos6502::decAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  ref.write(DEC(ref.read()));
}

void InterpretedMos6502::dexImplied(const Mos6502Instruction& inst) {
  DEX();
}

void InterpretedMos6502::deyImplied(const Mos6502Instruction& inst) {
  DEY();
}

// Exclusive OR with memory
void InterpretedMos6502::eorImmediate(const Mos6502Instruction& inst) {
  EOR(inst.operand.lo);
}

void InterpretedMos6502::eorZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  EOR(ref.read());
}

void InterpretedMos6502::eorZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  EOR(ref.read());
}

void InterpretedMos6502::eorAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  EOR(ref.read());
}

void InterpretedMos6502::eorAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  EOR(ref.read());
}

void InterpretedMos6502::eorAbsoluteY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteYIndexed(computeAddress(inst));
  EOR(ref.read());
}

void InterpretedMos6502::eorXIndirect(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().xIndexedIndirect(computeAddress(inst));
  EOR(ref.read());
}

void InterpretedMos6502::eorIndirectY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().indirectYIndexed(computeAddress(inst));
  EOR(ref.read());
}

// Increment memory
void InterpretedMos6502::incZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  ref.write(INC(ref.read()));
}

void InterpretedMos6502::incZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  ref.write(INC(ref.read()));
}

void InterpretedMos6502::incAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  ref.write(INC(ref.read()));
}

void InterpretedMos6502::incAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  ref.write(INC(ref.read()));
}

void InterpretedMos6502::inxImplied(const Mos6502Instruction& inst) {
  INX();
}

void InterpretedMos6502::inyImplied(const Mos6502Instruction& inst) {
  INY();
}

// Jumps
void InterpretedMos6502::jmpAbsolute(const Mos6502Instruction& inst) {
  JMP(computeAddress(inst));
}

void InterpretedMos6502::jmpIndirect(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  JMP(computeAddress(ref));
}

void InterpretedMos6502::jsrAbsolute(const Mos6502Instruction& inst) {
  JMP(computeAddress(inst));
}

// Loads
void InterpretedMos6502::ldaImmediate(const Mos6502Instruction& inst) {
  LDA(inst.operand.lo);
}

void InterpretedMos6502::ldaZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  LDA(ref.read());
}

void InterpretedMos6502::ldaZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  LDA(ref.read());
}

void InterpretedMos6502::ldaAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  LDA(ref.read());
}

void InterpretedMos6502::ldaAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  LDA(ref.read());
}

void InterpretedMos6502::ldaAbsoluteY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteYIndexed(computeAddress(inst));
  LDA(ref.read());
}

void InterpretedMos6502::ldaXIndirect(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().xIndexedIndirect(computeAddress(inst));
  LDA(ref.read());
}

void InterpretedMos6502::ldaIndirectY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().indirectYIndexed(computeAddress(inst));
  LDA(ref.read());
}

void InterpretedMos6502::ldxImmediate(const Mos6502Instruction& inst) {
  LDX(inst.operand.lo);
}

void InterpretedMos6502::ldxZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  LDX(ref.read());
}

void InterpretedMos6502::ldxZeropageY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageYIndexed(computeAddress(inst));
  LDX(ref.read());
}

void InterpretedMos6502::ldxAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  LDX(ref.read());
}

void InterpretedMos6502::ldxAbsoluteY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteYIndexed(computeAddress(inst));
  LDX(ref.read());
}

void InterpretedMos6502::ldyImmediate(const Mos6502Instruction& inst) {
  LDY(inst.operand.lo);
}

void InterpretedMos6502::ldyZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  LDY(ref.read());
}

void InterpretedMos6502::ldyZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  LDY(ref.read());
}

void InterpretedMos6502::ldyAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  LDY(ref.read());
}

void InterpretedMos6502::ldyAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  LDY(ref.read());
}

// Logical shift right
void InterpretedMos6502::lsrAccumulator(const Mos6502Instruction& inst) {
  setRegAC(LSR(getRegAC()));
}

void InterpretedMos6502::lsrZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  ref.write(LSR(ref.read()));
}

void InterpretedMos6502::lsrZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  ref.write(LSR(ref.read()));
}

void InterpretedMos6502::lsrAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  ref.write(LSR(ref.read()));
}

void InterpretedMos6502::lsrAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  ref.write(LSR(ref.read()));
}

/// No operation
void InterpretedMos6502::nopImplied(const Mos6502Instruction& inst) {
  NOP();
}

//  OR with memory
void InterpretedMos6502::oraImmediate(const Mos6502Instruction& inst) {
  ORA(inst.operand.lo);
}

void InterpretedMos6502::oraZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  ORA(ref.read());
}

void InterpretedMos6502::oraZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  ORA(ref.read());
}

void InterpretedMos6502::oraAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  ORA(ref.read());
}

void InterpretedMos6502::oraAbsoluteX(const Mos6502Instruction& inst) { 
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  ORA(ref.read());
}

void InterpretedMos6502::oraAbsoluteY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteYIndexed(computeAddress(inst));
  ORA(ref.read());
}

void InterpretedMos6502::oraXIndirect(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().xIndexedIndirect(computeAddress(inst));
  ORA(ref.read());
}

void InterpretedMos6502::oraIndirectY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().xIndexedIndirect(computeAddress(inst));
  ORA(ref.read());
}

// Stack operations
void InterpretedMos6502::phaImplied(const Mos6502Instruction& inst) {
  PHA();
}

void InterpretedMos6502::phpImplied(const Mos6502Instruction& inst) {
  PHP();
}

void InterpretedMos6502::plaImplied(const Mos6502Instruction& inst) {
  PLA();
}

void InterpretedMos6502::plpImplied(const Mos6502Instruction& inst) {
  PLP();
}

// Rotate left
void InterpretedMos6502::rolAccumulator(const Mos6502Instruction& inst) {
  setRegAC(ROL(getRegAC()));
}

void InterpretedMos6502::rolZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  ref.write(ROL(ref.read()));
}

void InterpretedMos6502::rolZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  ref.write(ROL(ref.read()));
}

void InterpretedMos6502::rolAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  ref.write(ROL(ref.read()));
}

void InterpretedMos6502::rolAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  ref.write(ROL(ref.read()));
}

// Rotate right
void InterpretedMos6502::rorAccumulator(const Mos6502Instruction& inst) {
  setRegAC(ROR(getRegAC()));
}

void InterpretedMos6502::rorZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  ref.write(ROR(ref.read()));
}

void InterpretedMos6502::rorZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  ref.write(ROR(ref.read()));
}

void InterpretedMos6502::rorAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  ref.write(ROR(ref.read()));
}

void InterpretedMos6502::rorAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  ref.write(ROR(ref.read()));
}

// Returns
void InterpretedMos6502::rtiImplied(const Mos6502Instruction& inst) {
  RTI();
}

void InterpretedMos6502::rtsImplied(const Mos6502Instruction& inst) {
  RTS();
}

// Subtract with borrow
void InterpretedMos6502::sbcImmediate(const Mos6502Instruction& inst) {
  SBC(inst.operand.lo);
}

void InterpretedMos6502::sbcZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  SBC(ref.read());
}

void InterpretedMos6502::sbcZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  SBC(ref.read());
}

void InterpretedMos6502::sbcAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  SBC(ref.read());
}

void InterpretedMos6502::sbcAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  SBC(ref.read());
}

void InterpretedMos6502::sbcAbsoluteY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteYIndexed(computeAddress(inst));
  SBC(ref.read());
}

void InterpretedMos6502::sbcXIndirect(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().xIndexedIndirect(computeAddress(inst));
  SBC(ref.read());
}

void InterpretedMos6502::sbcIndirectY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().indirectYIndexed(computeAddress(inst));
  SBC(ref.read());
}

// Set flags
void InterpretedMos6502::secImplied(const Mos6502Instruction& inst) {
  SEC();
}

void InterpretedMos6502::sedImplied(const Mos6502Instruction& inst) {
  SED();
}

void InterpretedMos6502::seiImplied(const Mos6502Instruction& inst) {
  SEI();
}

// Store accumulator
void InterpretedMos6502::staZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  ref.write(STA());
}

void InterpretedMos6502::staZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  ref.write(STA());
}

void InterpretedMos6502::staAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  ref.write(STA());
}

void InterpretedMos6502::staAbsoluteX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteXIndexed(computeAddress(inst));
  ref.write(STA());
}

void InterpretedMos6502::staAbsoluteY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absoluteYIndexed(computeAddress(inst));
  ref.write(STA());
}

void InterpretedMos6502::staXIndirect(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().xIndexedIndirect(computeAddress(inst));
  ref.write(STA());
}

void InterpretedMos6502::staIndirectY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().indirectYIndexed(computeAddress(inst));
  ref.write(STA());
}

// Store X-index register
void InterpretedMos6502::stxZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  ref.write(STX());
}

void InterpretedMos6502::stxZeropageY(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageYIndexed(computeAddress(inst));
  ref.write(STX());
}

void InterpretedMos6502::stxAbsolute(const Mos6502Instruction& inst) { 
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  ref.write(STX());
}

// Store Y-index register
void InterpretedMos6502::styZeropage(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropage(computeAddress(inst));
  ref.write(STY());
}

void InterpretedMos6502::styZeropageX(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().zeropageXIndexed(computeAddress(inst));
  ref.write(STY());
}

void InterpretedMos6502::styAbsolute(const Mos6502Instruction& inst) {
  Reference<byte> ref = getMmu().absolute(computeAddress(inst));
  ref.write(STY());
}

// Transfers
void InterpretedMos6502::taxImplied(const Mos6502Instruction& inst) {
  TAX();
}

void InterpretedMos6502::tayImplied(const Mos6502Instruction& inst) {
  TAY();
}

void InterpretedMos6502::tsxImplied(const Mos6502Instruction& inst) {
  TSX();
}

void InterpretedMos6502::txaImplied(const Mos6502Instruction& inst) {
  TXA();
}

void InterpretedMos6502::txsImplied(const Mos6502Instruction& inst) {
  TXS();
}

void InterpretedMos6502::tyaImplied(const Mos6502Instruction& inst) {
  TYA();
}
