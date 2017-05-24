#include "../../isa/Mov.h"
#include "gtest/gtest.h"

TEST(Mov, Base) {
  Mov* mov = new Mov(0x4c98078000870001);
  ASSERT_STREQ(mov->str.c_str(), "MOV R1, c[0x0][0x20];");
  delete mov;
}
