#include "intcode.h"
#include <iostream>

int main(int argc, char *argv[]) {

  if (argc < 2) {
    std::cerr << "Invalid invokcation must provide an intcode program"
              << std::endl;

    return 1;
  }

  IntCode::Program prog(argv[1]);
  prog[1] = 12;
  prog[2] = 2;
  IntCode::Interp interp(prog);

  interp.run();

  std::cout << "Answer: " << interp.program[0] << std::endl;
}
