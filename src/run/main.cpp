#include "color.h"
#include "intcode.h"

#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char *filename = nullptr;
  bool trace = false;
  bool no_color = false;
  int opt;

  while ((opt = getopt(argc, argv, "tf:C")) != -1) {
    switch (opt) {
    case 't':
      trace = true;
      break;

    case 'f':
      filename = optarg;
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
  interp.trace = trace;

  interp.run();
}
