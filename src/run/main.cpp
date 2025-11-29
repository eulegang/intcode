#include "intcode.h"
#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char *filename = nullptr;
  bool trace = false;
  int opt;

  while ((opt = getopt(argc, argv, "tf:")) != -1) {
    switch (opt) {
    case 't':
      trace = true;
      break;
    case 'f':
      filename = optarg;
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

  IntCode::Program prog(filename);
  IntCode::Interp interp(prog);
  interp.trace = trace;

  interp.run();
}
