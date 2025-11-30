#include "color.h"
#include "inst.h"
#include "intcode.h"

#include <array>
#include <cctype>
#include <memory>
#include <stdexcept>

using namespace IntCode;

struct Flags {
  bool jumped;
};

struct HandlerCall {
  Interp &interp;
  size_t &pc;
  Flags &flags;
  const Inst &inst;
  const std::array<long, 3> &params;
};

using Handler = void(HandlerCall call);

Handler handle_add, handle_mult, handle_input, handle_output, handle_jump_t,
    handle_jump_f, handle_less_than, handle_equal;

Interp::Interp(Program &program)
    : program{program}, input{std::make_unique<StdInput>()},
      output{std::make_unique<StdOutput>()}, trace{false} {}

Interp::Interp(Program &program, std::unique_ptr<Input> input,
               std::unique_ptr<Output> output)
    : program{program}, input{std::move(input)}, output{std::move(output)},
      trace{false} {}

bool jump_operation(Operation op) {
  return op == Operation::JumpTrue || op == Operation::JumpFalse;
}

void Interp::Interp::run() {
  size_t pc{};

  while (true) {
    const Inst inst(program[pc]);
    const size_t len = inst.param_size() + 1;
    Flags flags = {
        .jumped = false,
    };

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

    case Operation::JumpTrue:
      handler = &handle_jump_t;
      break;

    case Operation::JumpFalse:
      handler = &handle_jump_f;
      break;

    case Operation::LessThan:
      handler = &handle_less_than;
      break;

    case Operation::Equals:
      handler = &handle_equal;
      break;

    case Operation::Quit:
      return;
    }

    if (trace) {
      std::cout << Color::cyan << make_pair(inst, params) << Color::clear
                << std::endl;
    }

    handler({*this, pc, flags, inst, params});

    if (!flags.jumped) {
      pc += inst.param_size() + 1;
    }
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

void handle_add(HandlerCall call) {
  auto [first, second, third] = call.params;

  auto first_value = call.interp.resolve(first, call.inst.first);
  auto second_value = call.interp.resolve(second, call.inst.second);

  call.interp.program[third] = first_value + second_value;
}

void handle_mult(HandlerCall call) {
  auto [first, second, third] = call.params;
  auto first_value = call.interp.resolve(first, call.inst.first);
  auto second_value = call.interp.resolve(second, call.inst.second);

  call.interp.program[third] = first_value * second_value;
}

void handle_input(HandlerCall call) {
  auto [first, second, third] = call.params;

  const long in_value = call.interp.input->read();

  call.interp.program[first] = in_value;
}

void handle_output(HandlerCall call) {
  auto [first, second, third] = call.params;
  const long addr = call.interp.resolve(first, call.inst.first);

  call.interp.output->write(addr);
}

void handle_jump_t(HandlerCall call) {
  auto [first, second, third] = call.params;
  const long test = call.interp.resolve(first, call.inst.first);
  const long loc = call.interp.resolve(second, call.inst.second);

  if (test) {
    call.pc = loc;
    call.flags.jumped = true;
  }
}

void handle_jump_f(HandlerCall call) {
  auto [first, second, third] = call.params;
  const long test = call.interp.resolve(first, call.inst.first);
  const long loc = call.interp.resolve(second, call.inst.second);

  if (!test) {
    call.pc = loc;
    call.flags.jumped = true;
  }
}

void handle_less_than(HandlerCall call) {
  auto [first, second, third] = call.params;
  const long a = call.interp.resolve(first, call.inst.first);
  const long b = call.interp.resolve(second, call.inst.second);
  const long res = third;

  call.interp.program[res] = a < b ? 1 : 0;
}

void handle_equal(HandlerCall call) {
  auto [first, second, third] = call.params;
  const long a = call.interp.resolve(first, call.inst.first);
  const long b = call.interp.resolve(second, call.inst.second);
  const long res = third;

  std::cout << "eql " << a << ", " << b << ", " << res << std::endl;

  call.interp.program[res] = a == b ? 1 : 0;

  std::cout << "result " << call.interp.program[res] << std::endl;
}
