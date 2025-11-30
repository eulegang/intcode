#ifndef INTERP_H
#define INTERP_H

#include <cstdint>
#include <exception>
#include <ostream>
#include <utility>

namespace IntCode {
enum class Operation : long {
  Add = 1,
  Mult = 2,
  Input = 3,
  Output = 4,
  JumpTrue = 5,
  JumpFalse = 6,
  LessThan = 7,
  Equals = 8,

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

std::ostream &operator<<(std::ostream &, Operation);
std::ostream &operator<<(std::ostream &, Mode);
std::ostream &operator<<(std::ostream &,
                         std::pair<const Inst &, const std::array<long, 3> &>);

class bad_inst : private std::exception {
  [[nodiscard]] const char *what() const noexcept override {
    return "bad instruction";
  }
};

} // namespace IntCode
#endif
