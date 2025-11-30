#include "inst.h"
#include "color.h"

#include <array>
#include <stdexcept>

using namespace IntCode;

Operation validate_operation(long code) {
  static std::array all{
      Operation::Add,      Operation::Mult,     Operation::Input,
      Operation::Output,   Operation::JumpTrue, Operation::JumpFalse,
      Operation::LessThan, Operation::Equals,   Operation::Quit};

  for (Operation i : all) {
    if (static_cast<long>(i) == code)
      return i;
  }

  throw bad_inst{};
}

Mode validate_mode(long code) {
  static std::array all{Mode::Position, Mode::Immediate};

  for (Mode i : all) {
    if (static_cast<long>(i) == code)
      return i;
  }

  throw bad_inst{};
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
  case Operation::LessThan:
  case Operation::Equals:
    return 3;

  case Operation::JumpTrue:
  case Operation::JumpFalse:
    return 2;

  case Operation::Input:
  case Operation::Output:
    return 1;

  case Operation::Quit:
    return 0;
  }

  throw std::runtime_error("invalid operation");
}

std::ostream &print_param(std::ostream &out, long param, Mode mode) {
  switch (mode) {
  case Mode::Position:
    return out << Color::purple << "*" << param << "";
  case Mode::Immediate:
    return out << Color::yellow << param;
  }

  throw std::runtime_error("invalid mode");
}

std::ostream &
IntCode::operator<<(std::ostream &out,
                    std::pair<const Inst &, const std::array<long, 3> &> p) {
  const auto [inst, params] = p;

  out << "  " << inst.operation << " ";

  switch (inst.param_size()) {
  case 0:
    break;
  case 1:
    print_param(out, params[0], inst.first);
    break;
  case 2:
    print_param(out, params[0], inst.first);
    out << Color::cyan << ", ";
    print_param(out, params[1], inst.second);
    break;
  case 3:
    print_param(out, params[0], inst.first);
    out << Color::cyan << ", ";
    print_param(out, params[1], inst.second);
    out << Color::cyan << ", ";
    print_param(out, params[2], inst.third);
    break;
  }

  return out;
}

std::ostream &IntCode::operator<<(std::ostream &out, Operation op) {
  switch (op) {
  case Operation::Add:
    return out << "add";
  case Operation::Mult:
    return out << "mult";
  case Operation::Input:
    return out << "input";
  case Operation::Output:
    return out << "output";

  case Operation::JumpTrue:
    return out << "jmp_t";
  case Operation::JumpFalse:
    return out << "jmp_f";
  case Operation::LessThan:
    return out << "less_than";
  case Operation::Equals:
    return out << "eql";

  case Operation::Quit:
    return out << "quit";
  }

  throw std::runtime_error("invalid operation");
}

std::ostream &IntCode::operator<<(std::ostream &out, Mode mode) {
  switch (mode) {
  case Mode::Position:
    return out << "position";
  case Mode::Immediate:
    return out << "immediate";
  }

  throw std::runtime_error("invalid mode");
}
