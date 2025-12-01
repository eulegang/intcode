#include "intcode.h"
#include <gtest/gtest.h>
#include <initializer_list>
#include <memory>
#include <vector>

using namespace IntCode;

TEST(IntCode, Day5Examples) {
  {
    Program prog{{
        3, 9,        // input *9
        8, 9, 10, 9, // eql *9, *10, *9
        4, 9,        // output *9
        99,          // quit
        -1,          // - spare space
        8            // const 8
    }};

    const auto input = {8l};
    std::vector<long> output{};

    Interp interp(prog, std::make_unique<RecInput>(input),
                  std::make_unique<RecOutput>(output));
    interp.run();
    ASSERT_EQ(output, std::vector<long>{1});
  }

  {
    Program prog{{
        3, 9,        // input *9
        8, 9, 10, 9, // eql *9, *10, *9
        4, 9,        // output *9
        99,          // quit
        -1,          // - spare space
        8            // const 8
    }};

    const auto input = {42l};
    std::vector<long> output{};

    Interp interp(prog, std::make_unique<RecInput>(input),
                  std::make_unique<RecOutput>(output));
    interp.run();
    ASSERT_EQ(output, std::vector<long>{0});
  }
}

TEST(IntCode, Day9Examples) {

  {
    Program prog{{109, 1, 204, -1, 1001, 100, 1, 100, 1008, 100, 16, 101, 1006,
                  101, 0, 99}};
    std::vector<long> output{};

    Interp interp(prog, std::make_unique<RecInput>(),
                  std::make_unique<RecOutput>(output));
    interp.run();
    std::vector<long> expected{109,  1,   204, -1,  1001, 100, 1, 100,
                               1008, 100, 16,  101, 1006, 101, 0, 99};

    ASSERT_EQ(output, expected);
  }

  {

    Program prog{{1102, 34915192, 34915192, 7, 4, 7, 99, 0}};
    std::vector<long> output{};

    Interp interp(prog, std::make_unique<RecInput>(),
                  std::make_unique<RecOutput>(output));
    interp.run();
    std::vector<long> expected{1219070632396864};
    ASSERT_EQ(output, expected);
  }

  {

    Program prog{{104, 1125899906842624, 99}};
    std::vector<long> output{};

    Interp interp(prog, std::make_unique<RecInput>(),
                  std::make_unique<RecOutput>(output));
    interp.run();
    std::vector<long> expected{1125899906842624};
    ASSERT_EQ(output, expected);
  }
}
