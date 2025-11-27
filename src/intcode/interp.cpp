#include "inst.h"
#include "intcode.h"

#include <cctype>
#include <format>
#include <iostream>
#include <stdexcept>

using Program = IntCode::Program;

void handle_add(Program &program, long a, long b, long res);
void handle_mult(Program &program, long a, long b, long res);

IntCode::Interp::Interp(IntCode::Program &program) : program{program} {}

void IntCode::Interp::Interp::run() {
  size_t pc{};

  while (true) {
    Inst inst(program[pc]);

    size_t len = inst.param_size() + 1;
    if (program.size() < pc + len) {
      throw new std::runtime_error("invalid instruction pack");
    }

    switch (inst.operation) {
    case Operation::Add:
      handle_add(program, program[pc + 1], program[pc + 2], program[pc + 3]);
      break;

    case Operation::Mult:
      handle_mult(program, program[pc + 1], program[pc + 2], program[pc + 3]);
      break;

    case Operation::Quit:
      return;
    }

    pc += inst.param_size() + 1;
  }
}

void handle_add(Program &program, long a, long b, long res) {
#ifdef TRACE_OPS
  std::cout << std::format("add({}, {}, {})", a, b, res) << std::endl;
#endif

  program[res] = program[a] + program[b];
}

void handle_mult(Program &program, long a, long b, long res) {
#ifdef TRACE_OPS
  std::cout << std::format("mult({}, {}, {}))", a, b, res) << std::endl;
#endif
  program[res] = program[a] * program[b];
}
