#ifndef IADD_H
#define IADD_H

// C++ headers
#include <string>

// Project headers
#include "Instruction.h"

struct Iadd : public Instruction {
  Iadd(const uint64_t bits) : Instruction(bits) {
    pred.pred = GetBits(19, 16);
    if (pred.pred <= 6) {
      pred.str = "@P" + DumpAsDec(pred.pred);
    } else if (pred.pred == 7) {
      pred.str = "";
    } else if (pred.pred <= 14) {
      pred.str = "@!P" + DumpAsDec(pred.pred - 8);
    } else {
      pred.str = "@!PT";
    }
    opcode.main = GetBits(63, 51);  // 0x983
    opcode.sat = GetBits(50, 50);
    opcode.x = GetBits(43, 43);
    opcode.str = "IADD";
    opcode.str += opcode.sat? ".SAT" : "";
    opcode.str += opcode.x ? ".X" : "";
    d.cc = GetBits(47, 47);
    d.reg = GetBits(7, 0);
    d.str = "R" + (d.reg <= 254 ? DumpAsDec(d.reg) : "Z") +
        (d.cc ? ".CC" : "");
    a.neg = GetBits(49, 49);
    a.reg = GetBits(15, 8);
    a.str = (a.neg ? "-R" : "R") + (a.reg <= 254 ? DumpAsDec(a.reg) : "Z");
    b.bank_id = GetBits(38, 34);
    b.neg = GetBits(48, 48);
    b.offset_in_bank = GetBits(33, 20) << 2;
    b.str = (b.neg ? "-c[" : "c[") + DumpAsHex(b.bank_id) + "][" +
        DumpAsHex(b.offset_in_bank) + "]";
    if (pred.str != "") {
      str = pred.str + " ";
    } else {
      str = "";
    }
    str += opcode.str;
    if (d.str != "") {
      str += " " + d.str;
    }
    if (a.str != "") {
      str += ", " + a.str;
    }
    if (b.str != "") {
      str += ", " + b.str;
    }
    str += ";";
  }
  struct {
    uint8_t pred;
    std::string str;
  } pred;
  struct {
    uint16_t main;
    bool sat;
    bool x;
    std::string str;
  } opcode;
  struct {
    bool cc;
    uint8_t reg;
    std::string str;
  } d;
  struct {
    bool neg;
    uint8_t reg;
    std::string str;
  } a;
  struct {
    uint8_t bank_id;
    bool neg;
    int16_t offset_in_bank;
    std::string str;
  } b;
  std::string str;
};

#endif

