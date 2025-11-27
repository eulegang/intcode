#include <iostream>
#include <vector>

namespace IntCode {
struct Program {
  std::vector<long> contents;

  Program(char *filename);
  Program(std::initializer_list<long> li);

  Program(Program &&) = delete;
  Program &operator=(Program &&) = delete;

  long &operator[](size_t pos);
  size_t size();
};

class Interp {
  void handle_add(long a, long b, long res);
  void handle_mult(long a, long b, long res);

public:
  Program &program;

  Interp(Program &program);
  void run();
};

std::ostream &operator<<(std::ostream &out, const IntCode::Program &prog);
}; // namespace IntCode
