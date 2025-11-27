#ifndef INTERP_H
#define INTERP_H

#include <cstdint>

namespace IntCode {
enum class Operation : long {
  Add = 1,
  Mult = 2,
  Quit = 99,
};

enum class Mode : uint8_t {
  Position = 0,
  Immediate = 1,
};

struct Inst {
  Operation operation;
  Mode first, second, third;

  Inst(long code);

  std::size_t param_size();
};

} // namespace IntCode
#endif
