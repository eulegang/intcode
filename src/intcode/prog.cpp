#include "prog.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace IntCode;

Program::Program(std::initializer_list<long> elements) : contents{} {
  for (auto elem : elements) {
    contents.push_back(elem);
  }
}

Program::Program(char *filename) : contents{} {
  std::string line;
  std::ifstream file(filename);

  if (!file.is_open()) {
    throw new std::runtime_error("Invalid file");
  }

  while (file) {
    std::getline(file, line);
    read_longs(contents, line);
  }
}

long &Program::operator[](size_t pos) { return contents[pos]; }
long Program::get(size_t pos) const {
  return pos < contents.size() ? contents[pos] : 0;
}

size_t Program::size() const { return contents.size(); }

std::ostream &operator<<(std::ostream &out, const IntCode::Program &prog) {

  std::cout << "loaded: " << prog.contents.size() << " ints" << std::endl;

  for (auto i : prog.contents) {
    std::cout << "  " << i << std::endl;
  }

  return out;
}

void IntCode::read_longs(std::vector<long> &longs, std::string_view line) {
  bool valid{};
  long partial{};
  bool neg{};

  for (auto ch : line) {
    if (ch == ',') {
      long value = neg ? -partial : partial;

      longs.push_back(value);
      partial = 0;
      valid = false;
      neg = false;
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
    longs.push_back(neg ? -partial : partial);
  }
}
