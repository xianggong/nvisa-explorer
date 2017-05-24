#include "../../isa/S2r.h"
#include "gtest/gtest.h"

TEST(S2r, Base) {
  S2r* s2r = new S2r(0xf0c8000002570000);
  ASSERT_STREQ(s2r->str.c_str(), "S2R R0, SR_CTAID.X;");
  delete s2r;
}
