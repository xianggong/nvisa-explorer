#include "../../isa/Isetp.h"
#include "gtest/gtest.h"

TEST(Isetp, Base) {
  Isetp* isetp = new Isetp(0x4b6d038005670007);
  ASSERT_STREQ(isetp->str.c_str(), "ISETP.GE.AND P0, PT, R0, c[0x0][0x158], PT;");
  delete isetp;
}
