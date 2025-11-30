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
