#include "../../isa/Bra.h"
#include "gtest/gtest.h"

TEST(Bra, Base) {
  Bra* bra = new Bra(0xe2400fffff07000f);
  ASSERT_STREQ(bra->str.c_str(), "BRA 0xe0;");
  delete bra;
}
