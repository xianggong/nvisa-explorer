#ifndef MOV_H
#define MOV_H

// C++ headers
#include <string>

// Project headers
#include "Instruction.h"

struct Mov : public Instruction {
  Mov(const uint64_t bits) : Instruction(bits) {
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
    opcode.main = GetBits(63, 51);  // 0x993
    opcode.str = "MOV";
    d.reg = GetBits(7, 0);
    d.str = "R" + (d.reg <= 254 ? DumpAsDec(d.reg) : "Z");
    a.bank_id = GetBits(38, 34);
    a.offset_in_bank = GetBits(33, 20) << 2;
    a.str = "c[" + DumpAsHex(a.bank_id) + "][" + DumpAsHex(a.offset_in_bank) +
        "]";
    b.literal = GetBits(42, 39);
    b.str = b.literal <= 0xe ? DumpAsHex(b.literal) : "";
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
    std::string str;
  } opcode;
  struct {
    uint8_t reg;
    std::string str;
  } d;
  struct {
    uint8_t bank_id;
    int16_t offset_in_bank;
    std::string str;
  } a;
  struct {
    uint8_t literal;
    std::string str;
  } b;
  std::string str;
};

#endif

