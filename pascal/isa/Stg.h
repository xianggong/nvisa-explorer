#ifndef STG_H
#define STG_H

// C++ headers
#include <string>

// Project headers
#include "Instruction.h"

struct Stg : public Instruction {
  Stg(const uint64_t bits) : Instruction(bits) {
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
    opcode.main = GetBits(63, 51);  // 0x1ddb
    opcode.type = GetBits(50, 48);
    opcode.str = "STG";
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
    d.reg = GetBits(15, 8);
    d.offset = GetBits(43, 20);
    d.str = "[R" + (d.reg <= 254 ? DumpAsDec(d.reg) : "Z");
    d.str += d.offset != 0 ? "+" + DumpAsHex(d.offset) + "]" : "]";
    a.reg = GetBits(7, 0);
    a.str = "R" + (a.reg <= 254 ? DumpAsDec(a.reg) : "Z");
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
    int offset;
    std::string str;
  } d;
  struct {
    uint8_t reg;
    std::string str;
  } a;
  std::string str;
};

#endif

