#ifndef BRA_H
#define BRA_H

// C++ headers
#include <string>

// Project headers
#include "Instruction.h"

struct Bra : public Instruction {
  Bra(const uint64_t bits) : Instruction(bits) {
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
    opcode.lmt = GetBits(6, 6);
    opcode.main = GetBits(63, 53);  // 0x712
    opcode.u = GetBits(7, 7);
    opcode.str = "BRA";
    opcode.str += opcode.lmt ? ".LMT" : "";
    opcode.str += opcode.u ? ".U" : "";
    a.literal = GetBits(4, 0);
    a.str = a.literal == 0 ? "CC.F" :
        a.literal == 1 ? "CC.LT;" :
        a.literal == 2 ? "CC.EQ;" :
        a.literal == 3 ? "CC.LE;" :
        a.literal == 4 ? "CC.GT;" :
        a.literal == 5 ? "CC.NE;" :
        a.literal == 6 ? "CC.GE;" :
        a.literal == 7 ? "CC.NUM;" :
        a.literal == 8 ? "CC.NAN;" :
        a.literal == 9 ? "CC.LTU;" :
        a.literal == 10 ? "CC.EQU;" :
        a.literal == 11 ? "CC.LEU;" :
        a.literal == 12 ? "CC.GTU;" :
        a.literal == 13 ? "CC.NEU;" :
        a.literal == 14 ? "CC.GEU;" :
        a.literal == 16 ? "CC.OFF;" :
        a.literal == 17 ? "CC.LO;" :
        a.literal == 18 ? "CC.SFF;" :
        a.literal == 19 ? "CC.LS;" :
        a.literal == 20 ? "CC.HI;" :
        a.literal == 21 ? "CC.SFT;" :
        a.literal == 22 ? "CC.HS;" :
        a.literal == 23 ? "CC.OFT;" :
        a.literal == 24 ? "CC.CSM_TA;" :
        a.literal == 25 ? "CC.CSM_TR;" :
        a.literal == 26 ? "CC.CSM_MX;" :
        a.literal == 27 ? "CC.FCSM_TA;" :
        a.literal == 28 ? "CC.FCSM_TR;" :
        a.literal == 29 ? "CC.FCSM_MX;" :
        a.literal == 30 ? "CC.RLE;" :
        a.literal == 31 ? "CC.RGT;" : "";
    b.offset = GetBits(43, 43) ? 0xff000000 | GetBits(43, 20): GetBits(42, 20);
    // Target PC should be printed instead of offset
    b.str = DumpAsHex(b.offset);
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
    bool lmt;
    uint16_t main;
    bool u;
    std::string str;
  } opcode;
  struct {
    uint8_t literal;
    std::string str;
  } a;
  struct {
    int offset;
    std::string str;
  } b;
  std::string str;
};

#endif

