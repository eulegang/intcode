#include "intcode.h"
#include <format>
#include <iostream>

int main(int argc, char *argv[]) {

  if (argc < 2) {
    std::cerr << "Invalid invokcation must provide an intcode program"
              << std::endl;

    return 1;
  }

  IntCode::Program prog(argv[1]);

  bool found = false;
  for (int noun{}; noun < 99; noun++) {
    if (found)
      break;

    for (int verb{}; verb < 99; verb++) {
      IntCode::Program universe(prog);
      universe[1] = noun;
      universe[2] = verb;

      IntCode::Interp interp(universe);
      interp.run();

      if (universe[0] == 19690720) {
        std::cout << std::format("Solution: {}", 100 * noun + verb)
                  << std::endl;
        found = true;
        break;
      }
    }
  }

  if (!found) {
    std::cout << "Solution not found";
  }
}
