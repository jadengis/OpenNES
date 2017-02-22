//===-- include/cpu/TestMos6502.h - Mos6502 Test Class -----------*- C++ -*-===//
//
//                           The OsNES Project
//
// This file is distributed under GPL v2. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Inherited class for testing Mos6502 protected methods.
///
//===----------------------------------------------------------------------===//
#ifndef TEST_MOS_6502_H
#define TEST_MOS_6502_H

#include "common/CommonTypes.h"
#include "cpu/Mos6502.h"

#include "Mos6502_Inst.h"

namespace Test {

class TestMos6502 : public Cpu::Mos6502 {
  public:

    // CPU Instruction emulation accessor functions
    void testADC(const byte opnd) {
      ADC(opnd);
    }

    void testAND(const byte opnd) {
      AND(opnd);
    }

    byte testASL(byte opnd) {
      return ASL(opnd);
    }

    void testBCC(const byte opnd) {
      BCC(opnd);
    }

    void testBCS(const byte opnd) {
      BCS(opnd);
    }

    void testBEQ(const byte opnd) {
      BEQ(opnd);
    }

    void testBIT(const byte opnd) {
      BIT(opnd);
    }

    void testBMI(const byte opnd) {
      BMI(opnd);
    }

    void testBNE(const byte opnd) {
      BNE(opnd);
    }

    void testBPL(const byte opnd) {
      BPL(opnd);
    }

    void testBRK() {
      BRK();
    }

    void testBVC(const byte opnd) {
      BVC(opnd);
    }

    void testBVS(const byte opnd) {
      BVS(opnd);
    }

    void testCLC() {
      CLC();
    }

    void testCLD() {
      CLD();
    }

    void testCLI() {
      CLI();
    }

    void testCLV() {
      CLV();
    }

    void testCMP(const byte opnd) {
      CMP(opnd);
    }

    void testCPX(const byte opnd) {
      CPX(opnd);
    }

    void testCPY(const byte opnd) {
      CPY(opnd);
    }

    byte testDEC(byte opnd) {
      return DEC(opnd);
    }

    void testDEX() {
      DEX();
    }

    void testDEY() {
      DEY();
    }

    void testEOR(const byte opnd) {
      EOR(opnd);
    }

    byte testINC(byte opnd) {
      return INC(opnd);
    }

    void testINX() {
      INX();
    }

    void testINY() {
      INY();
    }

    void testJMP(const byte opnd1, const byte opnd2) {
      JMP(opnd1, opnd2);
    }

    void testJSR(const byte opnd1, const byte opnd2) {
      JSR(opnd1, opnd2);
    }

    void testLDA(const byte opnd) {
      LDA(opnd);
    }

    void testLDX(const byte opnd) {
      LDX(opnd);
    }

    void testLDY(const byte opnd) {
      LDY(opnd);
    }

    byte testLSR(byte opnd) {
      return LSR(opnd);
    }

    void testNOP() {
      NOP();
    }

    void testORA(const byte opnd) {
      ORA(opnd);
    }

    void testPHA() {
      PHA();
    }

    void testPHP() {
      PHP();
    }

    void testPLA() {
      PLA();
    }

    void testPLP() {
      PLP();
    }

    byte testROL(byte opnd) {
      return ROL(opnd);
    }

    byte testROR(byte opnd) {
      return ROR(opnd);
    }

    void testRTI() {
      RTI();
    }

    void testRTS() {
      RTS();
    }

    void testSBC(const byte opnd) {
      SBC(opnd);
    }

    void testSEC() {
      SEC();
    }

    void testSED() {
      SED();
    }

    void testSEI() {
      SEI();
    }

    byte testSTA() {
      return STA();
    }

    byte testSTX() {
      return STX();
    }

    byte testSTY() {
      return STY();
    }

    void testTAX() {
      TAX();
    }

    void testTAY() {
      TAY();
    }

    void testTSX() {
      TSX();
    }

    void testTXA() {
      TXA();
    }

    void testTXS() {
      TXS();
    }

    void testTYA() {
      TYA();
    }

};

} // namespace Test

#endif // TEST_MOS_6502_H //:~
