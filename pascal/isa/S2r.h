#ifndef S2R_H
#define S2R_H

// C++ headers
#include <string>

// Project headers
#include "Instruction.h"

struct S2r : public Instruction {
  S2r(const uint64_t bits) : Instruction(bits) {
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
    opcode.main = GetBits(63, 51);  // 0x1e19
    opcode.str = "S2R";
    d.reg = GetBits(7, 0);
    d.str = "R" + (d.reg <= 254 ? DumpAsDec(d.reg) : "Z");
    a.literal = GetBits(27, 20);
    switch (a.literal) {
    case 0: a.str = "SR_LANEID"; break;
    case 1: a.str = "SR_CLOCK"; break;
    case 2: a.str = "SR_VIRTCFG"; break;
    case 3: a.str = "SR_VIRTID"; break;
    case 4: a.str = "SR_PM0"; break;
    case 5: a.str = "SR_PM1"; break;
    case 6: a.str = "SR_PM2"; break;
    case 7: a.str = "SR_PM3"; break;
    case 8: a.str = "SR_PM4"; break;
    case 9: a.str = "SR_PM5"; break;
    case 10: a.str = "SR_PM6"; break;
    case 11: a.str = "SR_PM7"; break;
    case 15: a.str = "SR_ORDERING_TICKET"; break;
    case 16: a.str = "SR_PRIM_TYPE"; break;
    case 17: a.str = "SR_INVOCATION_ID"; break;
    case 18: a.str = "SR_Y_DIRECTION"; break;
    case 19: a.str = "SR_THREAD_KILL"; break;
    case 20: a.str = "SM_SHADER_TYPE"; break;
    case 21: a.str = "SR_DIRECTCBEWRITEADDRESSLOW"; break;
    case 22: a.str = "SR_DIRECTCBEWRITEADDRESSHIGH"; break;
    case 23: a.str = "SR_DIRECTCBEWRITEENABLED"; break;
    case 24: a.str = "SR_MACHINE_ID_0"; break;
    case 25: a.str = "SR_MACHINE_ID_1"; break;
    case 26: a.str = "SR_MACHINE_ID_2"; break;
    case 27: a.str = "SR_MACHINE_ID_3"; break;
    case 28: a.str = "SR_AFFINITY"; break;
    case 29: a.str = "SR_INVOCATION_INFO"; break;
    case 30: a.str = "SR_WSCALEFACTOR_XY"; break;
    case 31: a.str = "SR_WSCALEFACTOR_Z"; break;
    case 32: a.str = "SR_TID"; break;
    case 33: a.str = "SR_TID.X"; break;
    case 34: a.str = "SR_TID.Y"; break;
    case 35: a.str = "SR_TID.Z"; break;
    case 36: a.str = "SR_CTA_PARAM"; break;
    case 37: a.str = "SR_CTAID.X"; break;
    case 38: a.str = "SR_CTAID.Y"; break;
    case 39: a.str = "SR_CTAID.Z"; break;
    case 40: a.str = "SR_NTID"; break;
    case 41: a.str = "SR_CirQueueIncrMinusOne"; break;
    case 42: a.str = "SR_NLATC"; break;
    case 44: a.str = "SR_SM_SPA_VERSION"; break;
    case 45: a.str = "SR_MULTIPASSSHADERINFO"; break;
    case 46: a.str = "SR_LWINHI"; break;
    case 47: a.str = "SR_SWINHI"; break;
    case 48: a.str = "SR_SWINLO"; break;
    case 49: a.str = "SR_SWINSZ"; break;
    case 50: a.str = "SR_SMEMSZ"; break;
    case 51: a.str = "SR_SMEMBANKS"; break;
    case 52: a.str = "SR_LWINLO"; break;
    case 53: a.str = "SR_LWINSZ"; break;
    case 54: a.str = "SR_LMEMLOSZ"; break;
    case 55: a.str = "SR_LMEMHIOFF"; break;
    case 56: a.str = "SR_EQMASK"; break;
    case 57: a.str = "SR_LTMASK"; break;
    case 58: a.str = "SR_LEMASK"; break;
    case 59: a.str = "SR_GTMASK"; break;
    case 60: a.str = "SR_GEMASK"; break;
    case 61: a.str = "SR_REGALLOC"; break;
    case 62: a.str = "SR_BARRIERALLOC"; break;
    case 64: a.str = "SR_GLOBALERRORSTATUS"; break;
    case 66: a.str = "SR_WARPERRORSTATUS"; break;
    case 67: a.str = "SR_WARPERRORSTATUSCLEAR"; break;
    case 72: a.str = "SR_PM_HI0"; break;
    case 73: a.str = "SR_PM_HI1"; break;
    case 74: a.str = "SR_PM_HI2"; break;
    case 75: a.str = "SR_PM_HI3"; break;
    case 76: a.str = "SR_PM_HI4"; break;
    case 77: a.str = "SR_PM_HI5"; break;
    case 78: a.str = "SR_PM_HI6"; break;
    case 79: a.str = "SR_PM_HI7"; break;
    case 80: a.str = "SR_CLOCKLO"; break;
    case 81: a.str = "SR_CLOCKHI"; break;
    case 82: a.str = "SR_GLOBALTIMERLO"; break;
    case 83: a.str = "SR_GLOBALTIMERHI"; break;
    case 96: a.str = "SR_HWTASKID"; break;
    case 97: a.str = "SR_CIRCULARQUEUEENTRYINDEX"; break;
    case 98: a.str = "SR_CIRCULARQUEUEENTRYADDRESSLOW"; break;
    case 99: a.str = "SR_CIRCULARQUEUEENTRYADDRESSHIGH"; break;
    default: a.str = "SR" + DumpAsDec(a.literal);
    }
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
    uint16_t main;
    std::string str;
  } opcode;
  struct {
    uint8_t reg;
    std::string str;
  } d;
  struct {
    uint8_t literal;
    std::string str;
  } a;
  std::string str;
};

#endif

