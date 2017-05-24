#include "../../isa/Xmad.h"
#include "gtest/gtest.h"

TEST(Xmad, Base) {
  Xmad* xmad = new Xmad(0x4f107f8000270003);
  ASSERT_STREQ(xmad->str.c_str(), "XMAD.MRG R3, R0, c[0x0] [0x8].H1, RZ;");
  delete xmad;
}
