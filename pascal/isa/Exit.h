#ifndef EXIT_H
#define EXIT_H

// C++ headers
#include <string>

// Project headers
#include "Instruction.h"

struct Exit : public Instruction {
  Exit(const uint64_t bits) : Instruction(bits) {
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
    opcode.keeprefcount = GetBits(5, 5);
    opcode.main = GetBits(63, 52);  // 0xe30
    opcode.str = "EXIT";
    opcode.str += opcode.keeprefcount ? ".KEEPREFCOUNT" : "";
    a.a = GetBits(4, 0);
    switch (a.a) {
    case 0: a.str = "CC.F"; break;
    case 1: a.str = "CC.LT"; break;
    case 2: a.str = "CC.EQ"; break;
    case 3: a.str = "CC.LE"; break;
    case 4: a.str = "CC.GT"; break;
    case 5: a.str = "CC.NE"; break;
    case 6: a.str = "CC.GE"; break;
    case 7: a.str = "CC.NUM"; break;
    case 8: a.str = "CC.NAN"; break;
    case 9: a.str = "CC.LTU"; break;
    case 10: a.str = "CC.EQU"; break;
    case 11: a.str = "CC.LEU"; break;
    case 12: a.str = "CC.GTU"; break;
    case 13: a.str = "CC.NEU"; break;
    case 14: a.str = "CC.GEU"; break;
    case 16: a.str = "CC.OFF"; break;
    case 17: a.str = "CC.LO"; break;
    case 18: a.str = "CC.SFF"; break;
    case 19: a.str = "CC.LS"; break;
    case 20: a.str = "CC.HI"; break;
    case 21: a.str = "CC.SFT"; break;
    case 22: a.str = "CC.HS"; break;
    case 23: a.str = "CC.OFT"; break;
    case 24: a.str = "CC.CSM_TA"; break;
    case 25: a.str = "CC.CSM_TR"; break;
    case 26: a.str = "CC.CSM_MX"; break;
    case 27: a.str = "CC.FCSM_TA"; break;
    case 28: a.str = "CC.FCSM_TR"; break;
    case 29: a.str = "CC.FCSM_MX"; break;
    case 30: a.str = "CC.RLE"; break;
    case 31: a.str = "CC.RGT"; break;
    default: a.str = "";
    }
    if (pred.str != "") {
      str = pred.str + " ";
    } else {
      str = "";
    }
    str += opcode.str;
    if (a.str != "") {
      str += " " + a.str;
    }
    str += ";";
  }
  struct {
    uint8_t pred;
    std::string str;
  } pred;
  struct {
    bool keeprefcount;
    uint16_t main;
    std::string str;
  } opcode;
  struct {
    uint8_t a;
    std::string str;
  } a;
  std::string str;

};

#endif
