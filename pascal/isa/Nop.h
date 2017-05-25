#ifndef NOP_H
#define NOP_H

// C++ headers
#include <string>

// Project headers
#include "Instruction.h"

struct Nop : public Instruction {
  Nop(const uint64_t bits) : Instruction(bits) {
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
    opcode.main = GetBits(63, 51);  // 0xa16
    opcode.trig = GetBits(13, 13);
    opcode.str = "NOP";
    opcode.str += opcode.trig ? ".TRIG" : "";
    a.literal = GetBits(35, 20);
    a.str = a.literal ? DumpAsHex(a.literal) : "";
    b.literal = GetBits(12, 8);
    b.str = b.literal == 0 ? "CC.F" :
        b.literal == 1 ? "CC.LT;" :
        b.literal == 2 ? "CC.EQ;" :
        b.literal == 3 ? "CC.LE;" :
        b.literal == 4 ? "CC.GT;" :
        b.literal == 5 ? "CC.NE;" :
        b.literal == 6 ? "CC.GE;" :
        b.literal == 7 ? "CC.NUM;" :
        b.literal == 8 ? "CC.NAN;" :
        b.literal == 9 ? "CC.LTU;" :
        b.literal == 10 ? "CC.EQU;" :
        b.literal == 11 ? "CC.LEU;" :
        b.literal == 12 ? "CC.GTU;" :
        b.literal == 13 ? "CC.NEU;" :
        b.literal == 14 ? "CC.GEU;" :
        b.literal == 16 ? "CC.OFF;" :
        b.literal == 17 ? "CC.LO;" :
        b.literal == 18 ? "CC.SFF;" :
        b.literal == 19 ? "CC.LS;" :
        b.literal == 20 ? "CC.HI;" :
        b.literal == 21 ? "CC.SFT;" :
        b.literal == 22 ? "CC.HS;" :
        b.literal == 23 ? "CC.OFT;" :
        b.literal == 24 ? "CC.CSM_TA;" :
        b.literal == 25 ? "CC.CSM_TR;" :
        b.literal == 26 ? "CC.CSM_MX;" :
        b.literal == 27 ? "CC.FCSM_TA;" :
        b.literal == 28 ? "CC.FCSM_TR;" :
        b.literal == 29 ? "CC.FCSM_MX;" :
        b.literal == 30 ? "CC.RLE;" :
        b.literal == 31 ? "CC.RGT;" : "";
    if (pred.str != "") {
      str = pred.str + " ";
    } else {
      str = "";
    }
    str += opcode.str;
    if (a.str != "") {
      str += " " + a.str;
    }
    if (b.str != "") {
      str += " " + b.str;
    }
    for (size_t i = str.find(' ') + 1; i < str.size(); ++i) {
      if (str[i] == ' ') {
        str.insert(i, ",");
        ++i;
      }
    }
    str += ";";
  }
  struct {
    uint8_t pred;
    std::string str;
  } pred;
  struct {
    uint16_t main;
    bool trig;
    std::string str;
  } opcode;
  struct {
    uint16_t literal;
    std::string str;
  } a;
  struct {
    uint8_t literal;
    std::string str;
  } b;
  std::string str;
};

#endif

