//===-- source/cpu/Mos6502Disassembler.cpp - Disassembler -------*- C++ -*-===//
//
//                           The OpenNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementation of the Mos6502Disassembler.
///
//===----------------------------------------------------------------------===//
#include "memory/Reference.h"
#include "cpu/CpuException.h"
#include "cpu/Mos6502_Ops.h"
#include "cpu/Mos6502Instruction.h"
#include "cpu/Mos6502Disassembler.h"

#define ADJUSTS_PC false

using namespace Cpu;

// Aliases for this file
using Type = Mos6502Instruction::InstructionType;

Mos6502Instruction Mos6502Disassembler::initInstruction(
    byte opcode, 
    std::string&& name, 
    std::string&& addr, 
    byte cycles,
    Type type,
    bool adjustRegPC) {
  // declare an empty Mos6502Instruction
  Mos6502Instruction instruction;
  instruction.opcode = opcode;
  instruction.name = name;
  instruction.addr = addr;
  instruction.cycles = cycles;
  instruction.type = type;
  instruction.adjustRegPC = adjustRegPC;
  switch(type) {
    case Type::NO_OP:
      instruction.operand.lo = 0;
      instruction.operand.hi = 0;
      break;
    case Type::ONE_OP:
      instruction.operand.lo = (++readPosition).read();
      instruction.operand.hi = 0;
      break;
    case Type::TWO_OP:
      instruction.operand.lo = (++readPosition).read();
      instruction.operand.hi = (++readPosition).read();
      break;
  }
  return instruction;
}

Mos6502Instruction Mos6502Disassembler::disassembleInstruction(byte opcode) {
  // Lookup the fetched opcode
  switch(opcode) {
    // HI-NIBBLE == 0x00
    case Op::BRK_IMPL: 
      return initInstruction(opcode, "BRK", "impl", 7, Type::NO_OP, ADJUSTS_PC);
    case Op::ORA_X_IND:
      return initInstruction(opcode, "ORA", "X,ind", 6, Type::ONE_OP);
    case Op::ORA_ZPG:
      return initInstruction(opcode, "ORA", "zpg", 3, Type::ONE_OP);
    case Op::ASL_ZPG:
      return initInstruction(opcode, "ASL", "zpg", 5, Type::ONE_OP);
    case Op::PHP_IMPL:
      return initInstruction(opcode, "PHP", "impl", 3, Type::NO_OP);
    case Op::ORA_IMMED:
      return initInstruction(opcode, "ORA", "#", 2, Type::ONE_OP);
    case Op::ASL_ACC:
      return initInstruction(opcode, "ASL", "A", 2, Type::NO_OP);
    case Op::ORA_ABS:
      return initInstruction(opcode, "ORA", "abs", 4, Type::TWO_OP);
    case Op::ASL_ABS:
      return initInstruction(opcode, "ASL", "abs", 6, Type::TWO_OP);

    // HI-NIBBLE == 0x10
    case Op::BPL_REL:
      return initInstruction(opcode, "BPL", "rel", 2, Type::ONE_OP, ADJUSTS_PC);
    case Op::ORA_IND_Y:
      return initInstruction(opcode, "ORA", "ind,Y", 5, Type::ONE_OP);
    case Op::ORA_ZPG_X:
      return initInstruction(opcode, "ORA", "zpg,X", 4, Type::ONE_OP);
    case Op::ASL_ZPG_X:
      return initInstruction(opcode, "ASL", "zpg,X", 6, Type::ONE_OP);
    case Op::CLC_IMPL:
      return initInstruction(opcode, "CLC", "impl", 2, Type::NO_OP);
    case Op::ORA_ABS_Y:
      return initInstruction(opcode, "ORA", "abs,Y", 4, Type::TWO_OP);
    case Op::ORA_ABS_X:
      return initInstruction(opcode, "ORA", "abs,X", 4, Type::TWO_OP);
    case Op::ASL_ABS_X:
      return initInstruction(opcode, "ASL", "abs,X", 7, Type::TWO_OP);

    // HI-NIBBLE == 0x20
    case Op::JSR_ABS:
      return initInstruction(opcode, "JSR", "abs", 6, Type::TWO_OP, ADJUSTS_PC);
    case Op::AND_X_IND:
      return initInstruction(opcode, "AND", "X,ind", 6, Type::ONE_OP);
    case Op::BIT_ZPG:
      return initInstruction(opcode, "BIT", "zpg", 3, Type::ONE_OP);
    case Op::AND_ZPG:
      return initInstruction(opcode, "AND", "zpg", 3, Type::ONE_OP);
    case Op::ROL_ZPG:
      return initInstruction(opcode, "ROL", "zpg", 5, Type::ONE_OP);
    case Op::PLP_IMPL:
      return initInstruction(opcode, "PLP", "impl", 4, Type::NO_OP);
    case Op::AND_IMMED:
      return initInstruction(opcode, "AND", "#", 2, Type::ONE_OP);
    case Op::ROL_ACC:
      return initInstruction(opcode, "ROL", "A", 2, Type::NO_OP);
    case Op::BIT_ABS:
      return initInstruction(opcode, "BIT", "abs", 4, Type::TWO_OP);
    case Op::AND_ABS:
      return initInstruction(opcode, "AND", "abs", 4, Type::TWO_OP);
    case Op::ROL_ABS:
      return initInstruction(opcode, "ROL", "abs", 6, Type::TWO_OP);

    // HI-NIBBLE == 0x30
    case Op::BMI_REL:
      return initInstruction(opcode, "BMI", "rel", 2, Type::ONE_OP, ADJUSTS_PC);
    case Op::AND_IND_Y:
      return initInstruction(opcode, "AND", "ind,Y", 5, Type::ONE_OP);
    case Op::AND_ZPG_X:
      return initInstruction(opcode, "AND", "zpg,X", 4, Type::ONE_OP);
    case Op::ROL_ZPG_X:
      return initInstruction(opcode, "ROL", "zpg,X", 6, Type::ONE_OP);
    case Op::SEC_IMPL:
      return initInstruction(opcode, "SEC", "impl", 2, Type::NO_OP);
    case Op::AND_ABS_Y:
      return initInstruction(opcode, "AND", "abs,Y", 4, Type::TWO_OP);
    case Op::AND_ABS_X:
      return initInstruction(opcode, "AND", "abs,X", 4, Type::TWO_OP);
    case Op::ROL_ABS_X:
      return initInstruction(opcode, "ROL", "abs,X", 7, Type::TWO_OP);

    // HI-NIBBLE == 0x40
    case Op::RTI_IMPL:
      return initInstruction(opcode, "RTI", "impl", 6, Type::NO_OP, ADJUSTS_PC);
    case Op::EOR_X_IND:
      return initInstruction(opcode, "EOR", "X,ind", 6, Type::ONE_OP);
    case Op::EOR_ZPG:
      return initInstruction(opcode, "EOR", "zpg", 3, Type::ONE_OP);
    case Op::LSR_ZPG:
      return initInstruction(opcode, "LSR", "zpg", 5, Type::ONE_OP);
    case Op::PHA_IMPL:
      return initInstruction(opcode, "PHA", "impl", 3, Type::NO_OP);
    case Op::EOR_IMMED:
      return initInstruction(opcode, "EOR", "#", 2, Type::ONE_OP);
    case Op::LSR_ACC:
      return initInstruction(opcode, "LSR", "A", 2, Type::NO_OP);
    case Op::JMP_ABS:
      return initInstruction(opcode, "JMP", "abs", 3, Type::TWO_OP, ADJUSTS_PC);
    case Op::EOR_ABS:
      return initInstruction(opcode, "EOR", "abs", 4, Type::TWO_OP);
    case Op::LSR_ABS:
      return initInstruction(opcode, "LSR", "abs", 6, Type::TWO_OP);

    // HI-NIBBLE == 0x50
    case Op::BVC_REL:
      return initInstruction(opcode, "BVC", "rel", 2, Type::ONE_OP, ADJUSTS_PC);
    case Op::EOR_IND_Y:
      return initInstruction(opcode, "EOR", "ind,Y", 5, Type::ONE_OP);
    case Op::EOR_ZPG_X:
      return initInstruction(opcode, "EOR", "zpg,X", 4, Type::ONE_OP);
    case Op::LSR_ZPG_X:
      return initInstruction(opcode, "LSR", "zpg,X", 6, Type::ONE_OP);
    case Op::CLI_IMPL:
      return initInstruction(opcode, "CLI", "impl", 2, Type::NO_OP);
    case Op::EOR_ABS_Y:
      return initInstruction(opcode, "EOR", "abs,Y", 4, Type::TWO_OP);
    case Op::EOR_ABS_X:
      return initInstruction(opcode, "EOR", "abs,X", 4, Type::TWO_OP);
    case Op::LSR_ABS_X:
      return initInstruction(opcode, "LSR", "abs,X", 7, Type::TWO_OP);

    // HI-NIBBLE == 0x60
    case Op::RTS_IMPL:
      return initInstruction(opcode, "RTS", "impl", 6, Type::NO_OP, ADJUSTS_PC);
    case Op::ADC_X_IND:
      return initInstruction(opcode, "ADC", "X,ind", 6, Type::ONE_OP);
    case Op::ADC_ZPG:
      return initInstruction(opcode, "ADC", "zpg", 3, Type::ONE_OP);
    case Op::ROR_ZPG:
      return initInstruction(opcode, "ROR", "zpg", 5, Type::ONE_OP);
    case Op::PLA_IMPL:
      return initInstruction(opcode, "PLA", "impl", 4, Type::NO_OP);
    case Op::ADC_IMMED:
      return initInstruction(opcode, "ADC", "#", 2, Type::ONE_OP);
    case Op::ROR_ACC:
      return initInstruction(opcode, "ROR", "A", 2, Type::NO_OP);
    case Op::JMP_IND:
      return initInstruction(opcode, "JMP", "ind", 5, Type::TWO_OP, ADJUSTS_PC);
    case Op::ADC_ABS:
      return initInstruction(opcode, "ADC", "abs", 4, Type::TWO_OP);
    case Op::ROR_ABS:
      return initInstruction(opcode, "ROR", "abs", 6, Type::TWO_OP);

    // HI-NIBBLE == 0x70
    case Op::BVS_REL:
      return initInstruction(opcode, "BVS", "rel", 2, Type::ONE_OP, ADJUSTS_PC);
    case Op::ADC_IND_Y:
      return initInstruction(opcode, "ADC", "ind,Y", 5, Type::ONE_OP);
    case Op::ADC_ZPG_X:
      return initInstruction(opcode, "ADC", "zpg,X", 4, Type::ONE_OP);
    case Op::ROR_ZPG_X:
      return initInstruction(opcode, "ROR", "zpg,X", 6, Type::ONE_OP);
    case Op::SEI_IMPL:
      return initInstruction(opcode, "SEI", "impl", 2, Type::NO_OP);
    case Op::ADC_ABS_Y:
      return initInstruction(opcode, "ADC", "abs,Y", 4, Type::TWO_OP);
    case Op::ADC_ABS_X:
      return initInstruction(opcode, "ADC", "abs,X", 4, Type::TWO_OP);
    case Op::ROR_ABS_X:
      return initInstruction(opcode, "ROR", "abs,X", 7, Type::TWO_OP);

    // HI-NIBBLE == 0x80
    case Op::STA_X_IND:
      return initInstruction(opcode, "STA", "X,ind", 6, Type::ONE_OP);
    case Op::STY_ZPG:
      return initInstruction(opcode, "STY", "zpg", 3, Type::ONE_OP);
    case Op::STA_ZPG:
      return initInstruction(opcode, "STA", "zpg", 3, Type::ONE_OP);
    case Op::STX_ZPG:
      return initInstruction(opcode, "STX", "zpg", 3, Type::ONE_OP);
    case Op::DEY_IMPL:
      return initInstruction(opcode, "DEY", "impl", 2, Type::NO_OP);
    case Op::TXA_IMPL:
      return initInstruction(opcode, "TXA", "impl", 2, Type::NO_OP);
    case Op::STY_ABS:
      return initInstruction(opcode, "STY", "abs", 4, Type::TWO_OP);
    case Op::STA_ABS:
      return initInstruction(opcode, "STA", "abs", 4, Type::TWO_OP);
    case Op::STX_ABS:
      return initInstruction(opcode, "STX", "abs", 4, Type::TWO_OP);

    // HI-NIBBLE == 0x90
    case Op::BCC_REL:
      return initInstruction(opcode, "BCC", "rel", 2, Type::ONE_OP, ADJUSTS_PC);
    case Op::STA_IND_Y:
      return initInstruction(opcode, "STA", "ind,Y", 6, Type::ONE_OP);
    case Op::STY_ZPG_X:
      return initInstruction(opcode, "STY", "zpg,X", 4, Type::ONE_OP);
    case Op::STA_ZPG_X:
      return initInstruction(opcode, "STA", "zpg,X", 4, Type::ONE_OP);
    case Op::STX_ZPG_Y:
      return initInstruction(opcode, "STX", "zpg,Y", 4, Type::ONE_OP);
    case Op::TYA_IMPL:
      return initInstruction(opcode, "TYA", "impl", 2, Type::NO_OP);
    case Op::STA_ABS_Y:
      return initInstruction(opcode, "STA", "abs,Y", 5, Type::TWO_OP);
    case Op::TXS_IMPL:
      return initInstruction(opcode, "TXS", "impl", 2, Type::NO_OP);
    case Op::STA_ABS_X:
      return initInstruction(opcode, "STA", "abs,X", 5, Type::TWO_OP);

    // HI-NIBBLE == 0xA0
    case Op::LDY_IMMED:
      return initInstruction(opcode, "LDY", "#", 2, Type::ONE_OP);
    case Op::LDA_X_IND:
      return initInstruction(opcode, "LDA", "X,ind", 6, Type::ONE_OP);
    case Op::LDX_IMMED:
      return initInstruction(opcode, "LDX", "#", 2, Type::ONE_OP);
    case Op::LDY_ZPG:
      return initInstruction(opcode, "LDY", "zpg", 3, Type::ONE_OP);
    case Op::LDA_ZPG:
      return initInstruction(opcode, "LDA", "zpg", 3, Type::ONE_OP);
    case Op::LDX_ZPG:
      return initInstruction(opcode, "LDX", "zpg", 3, Type::ONE_OP);
    case Op::TAY_IMPL:
      return initInstruction(opcode, "TAY", "impl", 2, Type::NO_OP);
    case Op::LDA_IMMED:
      return initInstruction(opcode, "LDA", "#", 2, Type::ONE_OP);
    case Op::TAX_IMPL:
      return initInstruction(opcode, "TAX", "impl", 2, Type::NO_OP);
    case Op::LDY_ABS:
      return initInstruction(opcode, "LDY", "abs", 4, Type::TWO_OP);
    case Op::LDA_ABS:
      return initInstruction(opcode, "LDA", "abs", 4, Type::TWO_OP);
    case Op::LDX_ABS:
      return initInstruction(opcode, "LDX", "abs", 4, Type::TWO_OP);

    // HI-NIBBLE == 0xB0
    case Op::BCS_REL:
      return initInstruction(opcode, "BCS", "rel", 2, Type::ONE_OP, ADJUSTS_PC);
    case Op::LDA_IND_Y:
      return initInstruction(opcode, "LDA", "ind,Y", 5, Type::ONE_OP);
    case Op::LDY_ZPG_X:
      return initInstruction(opcode, "LDY", "zpg,X", 4, Type::ONE_OP);
    case Op::LDA_ZPG_X:
      return initInstruction(opcode, "LDA", "zpg,X", 4, Type::ONE_OP);
    case Op::LDX_ZPG_Y:
      return initInstruction(opcode, "LDX", "zpg,Y", 4, Type::ONE_OP);
    case Op::CLV_IMPL:
      return initInstruction(opcode, "CLV", "impl", 2, Type::NO_OP);
    case Op::LDA_ABS_Y:
      return initInstruction(opcode, "LDA", "abs,Y", 4, Type::TWO_OP);
    case Op::TSX_IMPL:
      return initInstruction(opcode, "TSX", "impl", 2, Type::NO_OP);
    case Op::LDY_ABS_X:
      return initInstruction(opcode, "LDY", "abs,X", 4, Type::TWO_OP);
    case Op::LDA_ABS_X:
      return initInstruction(opcode, "LDA", "abs,X", 4, Type::TWO_OP);
    case Op::LDX_ABS_Y:
      return initInstruction(opcode, "LDX", "abs,Y", 4, Type::TWO_OP);

    // HI-NIBBLE == 0xC0
    case Op::CPY_IMMED:
      return initInstruction(opcode, "CPY", "#", 2, Type::ONE_OP);
    case Op::CMP_X_IND:
      return initInstruction(opcode, "CMP", "X,ind", 6, Type::ONE_OP);
    case Op::CPY_ZPG:
      return initInstruction(opcode, "CPY", "zpg", 3, Type::ONE_OP);
    case Op::CMP_ZPG:
      return initInstruction(opcode, "CMP", "zpg", 3, Type::ONE_OP);
    case Op::DEC_ZPG:
      return initInstruction(opcode, "DEC", "zpg", 5, Type::ONE_OP);
    case Op::INY_IMPL:
      return initInstruction(opcode, "INY", "impl", 2, Type::NO_OP);
    case Op::CMP_IMMED:
      return initInstruction(opcode, "CMP", "#", 2, Type::ONE_OP);
    case Op::DEX_IMPL:
      return initInstruction(opcode, "DEX", "impl", 2, Type::NO_OP);
    case Op::CPY_ABS:
      return initInstruction(opcode, "CPY", "abs", 4, Type::TWO_OP);
    case Op::CMP_ABS:
      return initInstruction(opcode, "CMP", "abs", 4, Type::TWO_OP);
    case Op::DEC_ABS:
      return initInstruction(opcode, "DEC", "abs", 6, Type::TWO_OP);

    // HI-NIBBLE == 0xD0
    case Op::BNE_REL:
      return initInstruction(opcode, "BNE", "rel", 2, Type::ONE_OP, ADJUSTS_PC);
    case Op::CMP_IND_Y:
      return initInstruction(opcode, "CMP", "ind,Y", 5, Type::ONE_OP);
    case Op::CMP_ZPG_X:
      return initInstruction(opcode, "CMP", "zpg,X", 4, Type::ONE_OP);
    case Op::DEC_ZPG_X:
      return initInstruction(opcode, "DEC", "zpg,X", 6, Type::ONE_OP);
    case Op::CLD_IMPL:
      return initInstruction(opcode, "CLD", "impl", 2, Type::NO_OP);
    case Op::CMP_ABS_Y:
      return initInstruction(opcode, "CMP", "abs,Y", 4, Type::TWO_OP);
    case Op::CMP_ABS_X:
      return initInstruction(opcode, "CMP", "abs,X", 4, Type::TWO_OP);
    case Op::DEC_ABS_X:
      return initInstruction(opcode, "DEC", "abs,X", 7, Type::TWO_OP);

    // HI-NIBBLE == 0xE0
    case Op::CPX_IMMED:
      return initInstruction(opcode, "CPX", "#", 2, Type::ONE_OP);
    case Op::SBC_X_IND:
      return initInstruction(opcode, "SBC", "X,ind", 6, Type::ONE_OP);
    case Op::CPX_ZPG:
      return initInstruction(opcode, "CPX", "zpg", 3, Type::ONE_OP);
    case Op::SBC_ZPG:
      return initInstruction(opcode, "SBC", "zpg", 3, Type::ONE_OP);
    case Op::INC_ZPG:
      return initInstruction(opcode, "INC", "zpg", 5, Type::ONE_OP);
    case Op::INX_IMPL:
      return initInstruction(opcode, "INX", "impl", 2, Type::NO_OP);
    case Op::SBC_IMMED:
      return initInstruction(opcode, "SBC", "#", 2, Type::ONE_OP);
    case Op::NOP_IMPL:
      return initInstruction(opcode, "NOP", "impl", 2, Type::NO_OP);
    case Op::CPX_ABS:
      return initInstruction(opcode, "CPX", "abs", 4, Type::TWO_OP);
    case Op::SBC_ABS:
      return initInstruction(opcode, "SBC", "abs", 4, Type::TWO_OP);
    case Op::INC_ABS:
      return initInstruction(opcode, "INC", "abs", 6, Type::TWO_OP);

    // HI-NIBBLE == 0xF0
    case Op::BEQ_REL:
      return initInstruction(opcode, "BEQ", "rel", 2, Type::ONE_OP, ADJUSTS_PC);
    case Op::SBC_IND_Y:
      return initInstruction(opcode, "SBC", "ind,Y", 5, Type::ONE_OP);
    case Op::SBC_ZPG_X:
      return initInstruction(opcode, "SBC", "zpg,X", 4, Type::ONE_OP);
    case Op::INC_ZPG_X:
      return initInstruction(opcode, "INC", "zpg,X", 6, Type::ONE_OP);
    case Op::SED_IMPL:
      return initInstruction(opcode, "SED", "impl", 2, Type::NO_OP);
    case Op::SBC_ABS_Y:
      return initInstruction(opcode, "SBC", "abs,Y", 4, Type::TWO_OP);
    case Op::SBC_ABS_X:
      return initInstruction(opcode, "SBC", "abs,X", 4, Type::TWO_OP);
    case Op::INC_ABS_X:
      return initInstruction(opcode, "INC", "abs,X", 7, Type::TWO_OP);
    default:
      // opcode must be unrecognized, throw exception
      throw Exception::InvalidOpcodeException(opcode);
      break;
  }

}
