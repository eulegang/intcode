#include "inst.h"
#include "intcode.h"

#include <cctype>
#include <format>
#include <iostream>
#include <stdexcept>

using namespace IntCode;

using Handler = void (*)(Program &, const Inst &, const std::array<long, 3> &);

void handle_add(Program &program, const Inst &, const std::array<long, 3> &);
void handle_mult(Program &program, const Inst &, const std::array<long, 3> &);

Interp::Interp(Program &program) : program{program} {}

void Interp::Interp::run() {
  size_t pc{};

  while (true) {
    Inst inst(program[pc]);

    size_t len = inst.param_size() + 1;
    if (program.size() < pc + len) {
      throw new std::runtime_error("invalid instruction pack");
    }

    Handler handler;
    const std::array<long, 3> params{program.get(pc + 1), program.get(pc + 2),
                                     program.get(pc + 3)};
    switch (inst.operation) {
    case Operation::Add:
      handler = &handle_add;
      break;

    case Operation::Mult:
      handler = &handle_mult;
      break;

    case Operation::Quit:
      return;
    }

    handler(program, inst, params);

    pc += inst.param_size() + 1;
  }
}

void handle_add(Program &program, const Inst &inst,
                const std::array<long, 3> &params) {
  auto [a, b, res] = params;
#ifdef TRACE_OPS
  std::cout << std::format("add({}, {}, {})", a, b, res) << std::endl;
#endif

  program[res] = program[a] + program[b];
}

void handle_mult(Program &program, const Inst &inst,
                 const std::array<long, 3> &params) {
  auto [a, b, res] = params;
#ifdef TRACE_OPS
  std::cout << std::format("mult({}, {}, {}))", a, b, res) << std::endl;
#endif
  program[res] = program[a] * program[b];
}
