#ifndef FADD_H
#define FADD_H

// C++ headers
#include <string>

// Project headers
#include "Instruction.h"

struct Fadd : public Instruction {
  Fadd(const uint64_t bits) : Instruction(bits) {
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
    opcode.ftz = GetBits(44, 44);
    opcode.main = GetBits(63, 51);  // 0xb8b
    opcode.round_mode = GetBits(40, 39);
    opcode.sat = GetBits(50, 50);
    opcode.str = "FADD";
    opcode.str += opcode.ftz ? ".FTZ" : "";
    opcode.str += opcode.round_mode == 1 ? ".RM" :
         opcode.round_mode == 2 ? ".RP" :
         opcode.round_mode == 3 ? ".RZ" : "";
    opcode.str += opcode.sat ? ".SAT" : "";
    d.cc = GetBits(47, 47);
    d.reg = GetBits(7, 0);
    d.str = "R" + (d.reg <= 254 ? DumpAsDec(d.reg) : "Z") +
        (d.cc ? ".CC" : "");
    a.abs = GetBits(46, 46);
    a.neg = GetBits(48, 48);
    a.reg = GetBits(15, 8);
    a.str = "R" + (a.reg <= 254 ? DumpAsDec(a.reg) : "Z");
    a.str = a.abs ? "|" + a.str + "|" : a.str;
    a.str = a.neg ? "-" : "" + a.str;
    b.abs = GetBits(49, 49);
    b.neg = GetBits(45, 45);
    b.reg = GetBits(27, 20);
    b.str = "R" + (b.reg <= 254 ? DumpAsDec(b.reg) : "Z");
    b.str = b.abs ? "|" + b.str + "|" : b.str;
    b.str = b.neg ? "-" : "" + b.str;
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
    bool ftz;
    uint16_t main;
    uint8_t round_mode;
    bool sat;
    std::string str;
  } opcode;
  struct {
    bool cc;
    uint8_t reg;
    std::string str;
  } d;
  struct {
    bool abs;
    bool neg;
    uint8_t reg;
    std::string str;
  } a;
  struct {
    bool abs;
    bool neg;
    uint8_t reg;
    std::string str;
  } b;
  std::string str;
};

#endif

