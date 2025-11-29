#include "inst.h"

#include <array>
#include <stdexcept>

using Operation = IntCode::Operation;
using Mode = IntCode::Mode;

Operation validate_operation(long code) {
  static std::array<Operation, 5> all{Operation::Add, Operation::Mult,
                                      Operation::Input, Operation::Output,
                                      Operation::Quit};

  for (Operation i : all) {
    if (static_cast<long>(i) == code)
      return i;
  }

  throw new std::runtime_error{"invalid instruction"};
}

Mode validate_mode(long code) {
  static std::array<Mode, 3> all{Mode::Position, Mode::Immediate};

  for (Mode i : all) {
    if (static_cast<long>(i) == code)
      return i;
  }

  throw new std::runtime_error{"invalid instruction"};
}

IntCode::Inst::Inst(long code)
    : operation{validate_operation(code % 100)},
      first{validate_mode((code / 100) % 10)},
      second{validate_mode((code / 1000) % 10)},
      third{validate_mode((code / 10000) % 10)} {}

std::size_t IntCode::Inst::param_size() const {
  switch (this->operation) {
  case Operation::Add:
  case Operation::Mult:
    return 3;
  case Operation::Input:
  case Operation::Output:
    return 1;
  case Operation::Quit:
    return 0;
  }

  throw std::runtime_error("invalid operation");
}
