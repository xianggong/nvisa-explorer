#include "../../isa/Iadd.h"
#include "gtest/gtest.h"

TEST(Iadd, Base) {
  Iadd* iadd = new Iadd(0x4c10800005070604);
  ASSERT_STREQ(iadd->str.c_str(), "IADD R4.CC, R6, c[0x0][0x140];");
  delete iadd;
}
