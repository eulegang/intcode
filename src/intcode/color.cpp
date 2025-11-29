#include "color.h"

#include <ostream>

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

std::ostream &operator<<(std::ostream &os, Basic basic) {
  if (enabled) {
    os << "\x1b[0;3" << static_cast<int>(basic) << "m";
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
