#ifndef INTERP_H
#define INTERP_H

#include "inst.h"
#include "io.h"
#include "prog.h"

#include <memory>

namespace IntCode {
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

} // namespace IntCode
#endif
