#ifndef ISETP_H
#define ISETP_H

// C++ headers
#include <string>

// Project headers
#include "Instruction.h"

struct Isetp : public Instruction {
  Isetp(const uint64_t bits) : Instruction(bits) {
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
    opcode.binary_op = GetBits(46, 45);
    opcode.compare = GetBits(51, 49);
    opcode.main = GetBits(63, 52);  // 0x4b6
    opcode.u32 = GetBits(48, 48);
    opcode.x = GetBits(43, 43);
    opcode.str = "ISETP";
    opcode.str += opcode.compare == 0 ? ".F" :
         opcode.compare == 1 ? ".LT" :
         opcode.compare == 2 ? ".EQ" :
         opcode.compare == 3 ? ".LE" :
         opcode.compare == 4 ? ".GT" :
         opcode.compare == 5 ? ".NE" :
         opcode.compare == 6 ? ".GE" :
         opcode.compare == 7 ? ".T" : "";
    opcode.str += opcode.u32 ? "" : ".U32";
    opcode.str += opcode.x ? ".X" : "";
    opcode.str += opcode.binary_op == 0 ? ".AND" :
         opcode.binary_op == 1 ? ".OR" :
         opcode.binary_op == 2 ? ".XOR" :
         opcode.binary_op == 3 ? ".INVALIDBOP3" : "";
    p.pred = GetBits(5, 3);
    p.str = "P" + (p.pred <= 6 ? DumpAsDec(p.pred) : "T");
    q.pred = GetBits(2, 0);
    q.str = "P" + (q.pred <= 6 ? DumpAsDec(q.pred) : "T");
    a.reg = GetBits(15, 8);
    a.str = "R" + (a.reg <= 254 ? DumpAsDec(a.reg) : "Z");
    b.bank_id = GetBits(38, 34);
    b.offset_in_bank = GetBits(33, 20) << 2;
    b.str = "c[" + DumpAsHex(b.bank_id) + "][" + DumpAsHex(b.offset_in_bank) +
        "]";
    c.pred = GetBits(42, 39);
    if (c.pred <= 6) {
      c.str = "@P" + DumpAsDec(c.pred);
    } else if (c.pred == 7) {
      c.str = "PT";
    } else if (c.pred <= 14) {
      c.str = "@!P" + DumpAsDec(c.pred - 8);
    } else {
      c.str = "@!PT";
    }
    if (pred.str != "") {
      str = pred.str + " ";
    } else {
      str = "";
    }
    str += opcode.str;
    if (p.str != "") {
      str += " " + p.str;
    }
    if (q.str != "") {
      str += ", " + q.str;
    }
    if (a.str != "") {
      str += ", " + a.str;
    }
    if (b.str != "") {
      str += ", " + b.str;
    }
    if (c.str != "") {
      str += ", " + c.str;
    }
    str += ";";
  }
  struct {
    uint8_t pred;
    std::string str;
  } pred;
  struct {
    uint8_t binary_op;
    uint8_t compare;
    uint16_t main;
    bool u32;
    bool x;
    std::string str;
  } opcode;
  struct {
    uint8_t pred;
    std::string str;
  } p;
  struct {
    uint8_t pred;
    std::string str;
  } q;
  struct {
    uint8_t reg;
    std::string str;
  } a;
  struct {
    uint8_t bank_id;
    int16_t offset_in_bank;
    std::string str;
  } b;
  struct {
    uint8_t pred;
    std::string str;
  } c;
  std::string str;
};

#endif

