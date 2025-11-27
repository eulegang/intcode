#include <iostream>
#include <vector>

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
  size_t size();
};

struct Interp {
  Program &program;

  Interp(Program &program);
  void run();
};

std::ostream &operator<<(std::ostream &out, const IntCode::Program &prog);
}; // namespace IntCode
