#include "../../isa/Shl.h"
#include "gtest/gtest.h"

TEST(Shl, Base) {
  Shl* shl = new Shl(0x3848000000270006);
  ASSERT_STREQ(shl->str.c_str(), "SHL R6, R0, 0x2;");
  delete shl;
}
