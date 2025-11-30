#include "color.h"
#include "intcode.h"

#include <iostream>
#include <memory>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char *filename = nullptr;
  char *inputs = nullptr;
  bool trace = false;
  bool no_color = false;
  int opt;

  while ((opt = getopt(argc, argv, "tf:i:C")) != -1) {
    switch (opt) {
    case 't':
      trace = true;
      break;

    case 'f':
      filename = optarg;
      break;

    case 'i':
      inputs = optarg;
      break;

    case 'C':
      no_color = true;
      break;

    case '?':
      std::cerr << "usage: " << argv[0] << " [-t] [-f <file>]" << std::endl;
      return 1;
    }
  }

  if (!filename) {
    std::cerr << "Invalid invokcation must provide an intcode program"
              << std::endl;

    return 1;
  }

  if (!no_color) {
    std::cout << Color::enable;
  }

  IntCode::Program prog(filename);
  IntCode::Interp interp(prog);
  if (inputs) {
    interp.input = std::make_unique<IntCode::RecInput>(inputs);
  }

  interp.trace = trace;

  interp.run();
}
