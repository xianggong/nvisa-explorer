#include "../../isa/Stg.h"
#include "gtest/gtest.h"

TEST(Stg, Base) {
  Stg* stg = new Stg(0xeedc200000070600);
  ASSERT_STREQ(stg->str.c_str(), "STG.E [R6], R0;");
  delete stg;
}
