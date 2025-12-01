#include "intcode.h"

#include <gtest/gtest.h>

using namespace IntCode;

TEST(Inst, DecodeOperation) {
  {
    Inst inst(1);
    EXPECT_EQ(inst.operation, Operation::Add);
  }

  {
    Inst inst(2);
    EXPECT_EQ(inst.operation, Operation::Mult);
  }

  {
    Inst inst(3);
    EXPECT_EQ(inst.operation, Operation::Input);
  }

  {
    Inst inst(4);
    EXPECT_EQ(inst.operation, Operation::Output);
  }

  {
    Inst inst(99);
    EXPECT_EQ(inst.operation, Operation::Quit);
  }

  {
    EXPECT_ANY_THROW({ Inst inst(98); });
  }
}

TEST(Inst, DecodeMode) {
  {
    Inst inst(11101);
    EXPECT_EQ(inst.modes[0], Mode::Immediate);
    EXPECT_EQ(inst.modes[1], Mode::Immediate);
    EXPECT_EQ(inst.modes[2], Mode::Immediate);
  }

  {
    Inst inst(1);
    EXPECT_EQ(inst.modes[0], Mode::Position);
    EXPECT_EQ(inst.modes[1], Mode::Position);
    EXPECT_EQ(inst.modes[2], Mode::Position);
  }

  {
    Inst inst(11001);
    EXPECT_EQ(inst.modes[0], Mode::Position);
    EXPECT_EQ(inst.modes[1], Mode::Immediate);
    EXPECT_EQ(inst.modes[2], Mode::Immediate);
  }
}
