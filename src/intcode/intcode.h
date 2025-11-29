#ifndef INTCODE_H
#define INTCODE_H

#include <iostream>
#include <memory>
#include <vector>

#include "inst.h"
#include "io.h"

namespace IntCode {
struct Program {
  std::vector<long> contents;

  Program(char *filename);
  Program(std::initializer_list<long> li);
  Program(Program &program) = default;
  Program &operator=(Program &) = default;

  Program(Program &&) = delete;
  Program &operator=(Program &&) = delete;

  long &operator[](size_t pos);
  [[nodiscard]]
  long get(size_t pos) const;
  [[nodiscard]]
  size_t size() const;
};

struct Interp {
  Program &program;
  std::unique_ptr<Input> input;
  std::unique_ptr<Output> output;

  Interp(Program &program);
  Interp(Program &program, std::unique_ptr<Input>, std::unique_ptr<Output>);
  void run();
  long resolve(long arg, IntCode::Mode mode);

  bool trace;
};

std::ostream &operator<<(std::ostream &out, const IntCode::Program &prog);
}; // namespace IntCode
#endif
