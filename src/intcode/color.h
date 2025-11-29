#ifndef COLOR_H
#define COLOR_H

#include <cstdint>
#include <ostream>

namespace Color {
/**
 * Enables colors in the output
 */
std::ostream &enable(std::ostream &);

std::ostream &disable(std::ostream &);

enum Basic : uint8_t {
  black = 0,
  red = 1,
  green = 2,
  yellow = 3,
  blue = 4,
  purple = 5,
  cyan = 6,
  white = 7,
};

extern struct Clear {
} clear;

std::ostream &operator<<(std::ostream &, Basic);

std::ostream &operator<<(std::ostream &, Clear);

} // namespace Color

#endif
