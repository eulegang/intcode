#include "intcode.h"
#include <gtest/gtest.h>

TEST(IntCode, Load) {
  IntCode::Program prog{{1, 9, 10, 3, 2, 3, 11, 0, 99, 30, 40, 50}};

  ASSERT_EQ(prog.contents.size(), 12);

  ASSERT_EQ(prog.contents[0], 1);
  ASSERT_EQ(prog.contents[1], 9);
  ASSERT_EQ(prog.contents[2], 10);
  ASSERT_EQ(prog.contents[3], 3);
  ASSERT_EQ(prog.contents[4], 2);
  ASSERT_EQ(prog.contents[5], 3);
  ASSERT_EQ(prog.contents[6], 11);
  ASSERT_EQ(prog.contents[7], 0);
  ASSERT_EQ(prog.contents[8], 99);
  ASSERT_EQ(prog.contents[9], 30);
  ASSERT_EQ(prog.contents[10], 40);
  ASSERT_EQ(prog.contents[11], 50);
}

TEST(IntCode, run) {
  IntCode::Program prog{{1, 9, 10, 3, 2, 3, 11, 0, 99, 30, 40, 50}};
  IntCode::Interp interp(prog);

  interp.run();

  ASSERT_EQ(interp.program[0], 3500);
}

TEST(IntCode, Extend) {
  IntCode::Program prog{{1, 9, 10, 3, 2, 3, 11, 0, 99, 30, 40, 50}};
  ASSERT_EQ(prog.contents.size(), 12);
  ASSERT_EQ(prog[49], 0);
  ASSERT_EQ(prog.contents.size(), 50);
}
