#include "color.h"

#include <iostream>

namespace Color {
bool enabled{};
Clear clear;

std::ostream &enable(std::ostream &os) {
  enabled = true;
  return os;
}

std::ostream &disable(std::ostream &os) {
  enabled = false;
  return os;
}

Hex::Hex(int code)
    : red{(code >> 16) & 0xFF}, green{(code >> 8) & 0xFF}, blue{(code) & 0xFF}

{}

std::ostream &operator<<(std::ostream &os, Basic basic) {
  if (enabled) {
    os << "\x1b[0;3" << static_cast<int>(basic) << "m";
  }

  return os;
}

std::ostream &operator<<(std::ostream &os, Hex hex) {
  if (enabled) {
    os << "\x1b[38;2;" << static_cast<int>(hex.red) << ";"
       << static_cast<int>(hex.green) << ";" << static_cast<int>(hex.blue)
       << "m";
  }

  return os;
}

std::ostream &operator<<(std::ostream &os, Clear _) {
  if (enabled) {
    os << "\x1b[0m";
  }

  return os;
}

} // namespace Color
