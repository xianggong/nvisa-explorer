#ifndef SHL_H
#define SHL_H

// C++ headers
#include <string>

// Project headers
#include "Instruction.h"

struct Shl : public Instruction {
  Shl(const uint64_t bits) : Instruction(bits) {
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
    opcode.main = GetBits(63, 51);  // 0x709
    opcode.w = GetBits(39, 39);
    opcode.x = GetBits(43, 43);
    opcode.str = "SHL";
    opcode.str += opcode.w ? ".W" : "";
    opcode.str += opcode.x ? ".X" : "";
    d.cc = GetBits(47, 47);
    d.reg = GetBits(7, 0);
    d.str = "R" + (d.reg <= 254 ? DumpAsDec(d.reg) : "Z") +
        (d.cc ? ".CC" : "");
    a.reg = GetBits(15, 8);
    a.str = "R" + (a.reg <= 254 ? DumpAsDec(a.reg) : "Z");
    b.literal = GetBits(38, 20);
    b.str = DumpAsHex(b.literal);
    str = pred.str + opcode.str;
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
    bool w;
    bool x;
    std::string str;
  } opcode;
  struct {
    bool cc;
    uint8_t reg;
    std::string str;
  } d;
  struct {
    uint8_t reg;
    std::string str;
  } a;
  struct {
    uint8_t literal;
    std::string str;
  } b;
  std::string str;
};

#endif

