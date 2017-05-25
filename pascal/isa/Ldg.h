#ifndef LDG_H
#define LDG_H

// C++ headers
#include <string>

// Project headers
#include "Instruction.h"

struct Ldg : public Instruction {
  Ldg(const uint64_t bits) : Instruction(bits) {
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
    opcode.cache_op = GetBits(47, 46);
    opcode.e = GetBits(45, 45);
    opcode.main = GetBits(63, 51);  // 0x1dda
    opcode.type = GetBits(50, 48);
    opcode.str = "LDG";
    opcode.str += opcode.e ? ".E" : "";
    opcode.str += opcode.type == 0 ? ".U8" :
        opcode.type == 1 ? ".S8" :
        opcode.type == 2 ? ".U16" :
        opcode.type == 3 ? ".S16" :
        opcode.type == 5 ? ".64" :
        opcode.type == 6 ? ".128" :
        opcode.type == 7 ? ".U.128" : "";
    opcode.str += opcode.cache_op == 1 ? ".CG" :
        opcode.cache_op == 2 ? ".CI" :
        opcode.cache_op == 3 ? ".CV" : "";
    d.reg = GetBits(7, 0);
    d.str = "R" + (d.reg <= 254 ? DumpAsDec(d.reg) : "Z");
    a.reg = GetBits(15, 8);
    a.offset = GetBits(43, 43) ? 0xff000000 | GetBits(43, 20): GetBits(42, 20);
    a.str = "[R" + (a.reg <= 254 ? DumpAsDec(a.reg) : "Z");
    a.str += a.offset != 0 ? "+" + DumpAsHex(a.offset) + "]" : "]";
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
    str += ";";
  }
  struct {
    uint8_t pred;
    std::string str;
  } pred;
  struct {
    uint8_t cache_op;
    bool e;
    uint16_t main;
    uint8_t type;
    std::string str;
  } opcode;
  struct {
    uint8_t reg;
    std::string str;
  } d;
  struct {
    uint8_t reg;
    int offset;
    std::string str;
  } a;
  std::string str;
};

#endif

