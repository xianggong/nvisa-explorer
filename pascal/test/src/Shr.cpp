#include "../../isa/Shr.h"
#include "gtest/gtest.h"

TEST(Shr, Base) {
  Shr* shr = new Shr(0x3829000001e70007);
  ASSERT_STREQ(shr->str.c_str(), "SHR R7, R0, 0x1e;");
  delete shr;
}
