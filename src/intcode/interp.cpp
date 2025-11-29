#include "inst.h"
#include "intcode.h"

#include <array>
#include <cctype>
#include <memory>
#include <stdexcept>

using namespace IntCode;

using Handler = void(Interp &, const Inst &, const std::array<long, 3> &);

Handler handle_add, handle_mult, handle_input, handle_output;

Interp::Interp(Program &program)
    : program{program}, input{std::make_unique<StdInput>()},
      output{std::make_unique<StdOutput>()} {}

Interp::Interp(Program &program, std::unique_ptr<Input> input,
               std::unique_ptr<Output> output)
    : program{program}, input{std::move(input)}, output{std::move(output)} {}

void Interp::Interp::run() {
  size_t pc{};

  while (true) {
    const Inst inst(program[pc]);
    const size_t len = inst.param_size() + 1;

    if (program.size() < pc + len) {
      throw new std::runtime_error("invalid instruction pack");
    }

    Handler *handler;
    const std::array<long, 3> params{program.get(pc + 1), program.get(pc + 2),
                                     program.get(pc + 3)};
    switch (inst.operation) {
    case Operation::Add:
      handler = &handle_add;
      break;

    case Operation::Mult:
      handler = &handle_mult;
      break;

    case Operation::Input:
      handler = &handle_input;
      break;

    case Operation::Output:
      handler = &handle_output;
      break;

    case Operation::Quit:
      return;
    }

    handler(*this, inst, params);

    pc += inst.param_size() + 1;
  }
}

long Interp::resolve(long value, Mode mode) {
  switch (mode) {
  case Mode::Position:
    return program[value];
  case Mode::Immediate:
    return value;

  default:
    throw new std::runtime_error("invalid mode");
  }
}

void handle_add(Interp &interp, const Inst &inst,
                const std::array<long, 3> &params) {
  auto [first, second, third] = params;
#ifdef TRACE_OPS
  std::cout << std::format("add({}, {}, {})", a, b, res) << std::endl;
#endif

  auto first_value = interp.resolve(first, inst.first);
  auto second_value = interp.resolve(second, inst.second);

  interp.program[third] = first_value + second_value;
}

void handle_mult(Interp &interp, const Inst &inst,
                 const std::array<long, 3> &params) {
  auto [first, second, third] = params;
  auto first_value = interp.resolve(first, inst.first);
  auto second_value = interp.resolve(second, inst.second);

  interp.program[third] = first_value * second_value;
}

void handle_input(Interp &interp, const Inst &inst,
                  const std::array<long, 3> &params) {
  auto [first, second, third] = params;

  const long in_value = interp.input->read();

  interp.program[first] = in_value;
}

void handle_output(Interp &interp, const Inst &inst,
                   const std::array<long, 3> &params) {
  auto [first, second, third] = params;

  interp.output->write(first);
}
