#include "lib.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

size_t param_size(long code);

enum Inst {
  InstAdd = 1,
  InstMult = 2,
  InstQuit = 99,

};

IntCode::Program::Program(std::initializer_list<long> elements) : contents{} {
  for (auto elem : elements) {
    contents.push_back(elem);
  }
}

IntCode::Program::Program(char *filename) : contents{} {
  std::string line;
  std::ifstream file(filename);

  bool valid{};
  long partial{};

  if (!file.is_open()) {
    throw new std::runtime_error("Invalid file");
  }

  while (file) {
    std::getline(file, line);

    for (auto ch : line) {
      if (ch == ',') {
        contents.push_back(partial);
        valid = false;
        partial = 0;
        continue;
      }

      if (std::isspace(ch) && valid) {
        contents.push_back(partial);
        valid = false;
        partial = 0;
        continue;
      }

      if ('0' <= ch && ch <= '9') {
        partial *= 10;
        partial += ch - '0';
        valid = true;
        continue;
      }

      throw std::runtime_error("invalid input given");
    }

    if (valid) {
      contents.push_back(partial);
    }
  }
}

long &IntCode::Program::operator[](size_t pos) { return contents[pos]; }
size_t IntCode::Program::size() { return contents.size(); }

std::ostream &IntCode::operator<<(std::ostream &out,
                                  const IntCode::Program &prog) {

  std::cout << "loaded: " << prog.contents.size() << " ints" << std::endl;

  for (auto i : prog.contents) {
    std::cout << "  " << i << std::endl;
  }

  return out;
}

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
      handle_add(program[pc + 1], program[pc + 2], program[pc + 3]);
      break;

    case InstMult:
      handle_mult(program[pc + 1], program[pc + 2], program[pc + 3]);
      break;
    }

    pc += param_size(code) + 1;
  }
}

void IntCode::Interp::handle_add(long a, long b, long res) {
#ifndef NDEBUG
  std::cout << "add(" << a << ", " << b << ", " << res << ")" << std::endl;
#endif
  program[res] = program[a] + program[b];
}
void IntCode::Interp::handle_mult(long a, long b, long res) {
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
