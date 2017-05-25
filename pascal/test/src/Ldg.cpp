#include "../../isa/Ldg.h"
#include "gtest/gtest.h"

TEST(Ldg, Base) {
  Ldg* ldg = new Ldg(0xeed4200000070405);
  ASSERT_STREQ(ldg->str.c_str(), "LDG.E R5, [R4];");
  delete ldg;
}
