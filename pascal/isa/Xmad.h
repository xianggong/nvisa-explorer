#ifndef XMAD_H
#define XMAD_H

// C++ headers
#include <string>

// Project headers
#include "Instruction.h"

struct Xmad : public Instruction {
  Xmad(const uint64_t bits) : Instruction(bits) {
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
    opcode.clo = GetBits(51, 50);
    opcode.main = GetBits(63, 57);  // 0x27
    opcode.mrg = GetBits(56, 56);
    opcode.psl = GetBits(55, 55);
    opcode.type = GetBits(49, 48);
    opcode.x = GetBits(54, 54);
    opcode.str = "XMAD";
    opcode.str += opcode.clo == 1 ? ".CLO" :
         opcode.clo == 2 ? ".CHI" :
         opcode.clo == 3 ? ".CSFU" : "";
    opcode.str += opcode.mrg ? ".MRG" : "";
    opcode.str += opcode.psl ? ".PSL" : "";
    opcode.str += opcode.type == 0 ? "" :
        opcode.type == 1 ? ".S16.U16" :
        opcode.type == 2 ? ".U16.S16" :
        opcode.type == 3 ? ".S16.S16" : "";
    opcode.str += opcode.x ? ".X" : "";
    d.cc = GetBits(47, 47);
    d.reg = GetBits(7, 0);
    d.str = "R" + (d.reg <= 254 ? DumpAsDec(d.reg) : "Z") +
        (d.cc ? ".CC" : "");
    a.h1 = GetBits(53, 53);
    a.reg = GetBits(15, 8);
    a.str = "R" + (a.reg <= 254 ? DumpAsDec(a.reg) : "Z") +
        (a.h1 ? ".H1" : "");
    b.bank_id = GetBits(38, 34);
    b.h1 = GetBits(52, 52);
    b.offset_in_bank = GetBits(33, 20) << 2;
    b.str = "c[" + DumpAsHex(b.bank_id) + "][" + DumpAsHex(b.offset_in_bank) +
        "]" + (b.h1 ? ".H1" : "");
    c.reg = GetBits(46, 39);
    c.str = "R" + (c.reg <= 254 ? DumpAsDec(c.reg) : "Z");
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
    uint8_t clo;
    uint8_t main;
    bool mrg;
    bool psl;
    uint8_t type;
    bool x;
    std::string str;
  } opcode;
  struct {
    bool cc;
    uint8_t reg;
    std::string str;
  } d;
  struct {
    bool h1;
    uint8_t reg;
    std::string str;
  } a;
  struct {
    uint8_t bank_id;
    bool h1;
    int16_t offset_in_bank;
    std::string str;
  } b;
  struct {
    uint8_t reg;
    std::string str;
  } c;
  std::string str;
};

#endif

