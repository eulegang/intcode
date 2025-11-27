#include "intcode.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

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
long IntCode::Program::get(size_t pos) {
  return pos < contents.size() ? contents[pos] : 0;
}

size_t IntCode::Program::size() { return contents.size(); }

std::ostream &IntCode::operator<<(std::ostream &out,
                                  const IntCode::Program &prog) {

  std::cout << "loaded: " << prog.contents.size() << " ints" << std::endl;

  for (auto i : prog.contents) {
    std::cout << "  " << i << std::endl;
  }

  return out;
}
