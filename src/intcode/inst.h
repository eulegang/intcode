#ifndef INTERP_H
#define INTERP_H

#include <cstdint>

namespace IntCode {
enum class Operation : long {
  Add = 1,
  Mult = 2,
  Input = 3,
  Output = 4,
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

  [[nodiscard]] std::size_t param_size() const;
};

} // namespace IntCode
#endif
