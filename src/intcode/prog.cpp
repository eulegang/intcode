#include "prog.h"

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
  bool neg{};

  if (!file.is_open()) {
    throw new std::runtime_error("Invalid file");
  }

  auto commit = [this, &partial, &neg, &valid]() {
    long value = neg ? -partial : partial;

    contents.push_back(value);
    partial = 0;
    valid = false;
    neg = false;
  };

  while (file) {
    std::getline(file, line);

    for (auto ch : line) {
      if (ch == ',') {
        commit();
      } else if (std::isspace(ch)) {
      } else if ('0' <= ch && ch <= '9') {
        partial *= 10;
        partial += ch - '0';
        valid = true;
      } else if ('-' == ch) {
        neg = true;
      } else if (';' == ch) {
        break;
      } else {
        throw std::runtime_error("invalid input given");
      }
    }

    if (valid) {
      contents.push_back(neg ? -partial : partial);
    }
  }
}

long &IntCode::Program::operator[](size_t pos) { return contents[pos]; }
long IntCode::Program::get(size_t pos) const {
  return pos < contents.size() ? contents[pos] : 0;
}

size_t IntCode::Program::size() const { return contents.size(); }

std::ostream &operator<<(std::ostream &out, const IntCode::Program &prog) {

  std::cout << "loaded: " << prog.contents.size() << " ints" << std::endl;

  for (auto i : prog.contents) {
    std::cout << "  " << i << std::endl;
  }

  return out;
}
