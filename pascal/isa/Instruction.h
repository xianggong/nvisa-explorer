#ifndef INSTRUCTION_H
#define INSTRUCTION_H

// C++ headers
#include <cstdint>
#include <ios>
#include <sstream>
#include <string>

struct Instruction {
  Instruction(const uint64_t b) : bits(b) {}
  uint64_t GetBits(uint8_t hi, uint8_t lo) {
    if (hi < lo) {
      const uint8_t tmp = hi;
      hi = lo;
      lo = tmp;
    }
    return (bits >> lo) & ((1LL << (hi - lo + 1)) - 1);
  }
  std::string DumpAsDec(uint32_t value) {
    std::stringstream ss;
    ss << std::dec << value;
    return ss.str();
  }
  std::string DumpAsHex(int value) {
    std::stringstream ss;
    if (value >= 0) {
        ss << "0x" << std::hex << value;
    } else {
        ss << "-0x" << std::hex << -value;
    }
    return ss.str();
  }
  const uint64_t bits;
};

#endif

