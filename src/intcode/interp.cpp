#include "intcode.h"
#include <cctype>
#include <iostream>
#include <stdexcept>

using Program = IntCode::Program;

size_t param_size(long code);

enum Inst {
  InstAdd = 1,
  InstMult = 2,
  InstQuit = 99,
};

void handle_add(Program &program, long a, long b, long res);
void handle_mult(Program &program, long a, long b, long res);

IntCode::Interp::Interp(IntCode::Program &program) : program{program} {}

void IntCode::Interp::Interp::run() {
  size_t pc{};

  while (true) {
    long code = program[pc];
    size_t len = param_size(code) + 1;
    if (program.size() < pc + len) {
      throw new std::runtime_error("invalid instruction pack");
    }

    if (code == InstQuit) {
      return;
    }

    switch (code) {
    case InstAdd:
      handle_add(program, program[pc + 1], program[pc + 2], program[pc + 3]);
      break;

    case InstMult:
      handle_mult(program, program[pc + 1], program[pc + 2], program[pc + 3]);
      break;
    }

    pc += param_size(code) + 1;
  }
}

void handle_add(Program &program, long a, long b, long res) {
#ifndef NDEBUG
  std::cout << "add(" << a << ", " << b << ", " << res << ")" << std::endl;
#endif
  program[res] = program[a] + program[b];
}

void handle_mult(Program &program, long a, long b, long res) {
#ifndef NDEBUG
  std::cout << "mult(" << a << ", " << b << ", " << res << ")" << std::endl;
#endif
  program[res] = program[a] * program[b];
}

size_t param_size(long code) {
  switch (code) {
  case InstAdd:
    return 3;
  case InstMult:
    return 3;
  case InstQuit:
    return 0;

  default:
    throw new std::runtime_error("Invalid code");
  }
}
