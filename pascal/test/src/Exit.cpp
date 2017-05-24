#include "../../isa/Exit.h"
#include "gtest/gtest.h"

TEST(Exit, Base) {
  Exit* exit = new Exit(0xe30000000000000f);
  ASSERT_STREQ(exit->str.c_str(), "@P0 EXIT;");
  delete exit;
}
