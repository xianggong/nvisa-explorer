#include "../../isa/Nop.h"
#include "gtest/gtest.h"

TEST(Nop, Base) {
  Nop* nop = new Nop(0x50b0000000070f00);
  ASSERT_STREQ(nop->str.c_str(), "NOP;");
  delete nop;
}
