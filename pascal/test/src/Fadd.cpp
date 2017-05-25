#include "../../isa/Fadd.h"
#include "gtest/gtest.h"

TEST(Fadd, Base) {
  Fadd* fadd = new Fadd(0x5c58000000570000);
  ASSERT_STREQ(fadd->str.c_str(), "FADD R0, R0, R5;");
  delete fadd;
}
