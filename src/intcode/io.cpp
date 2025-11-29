
#include "io.h"

#include <iostream>
#include <stdexcept>

using namespace IntCode;

long StdInput::read() {
  std::cout << ">> ";
  long res;
  std::cin >> res;
  return res;
}

RecInput::RecInput(std::initializer_list<long> list) : record{} {
  for (long li : list) {
    record.push_back(li);
  }
}

long RecInput::read() {
  if (record.empty()) {
    throw std::runtime_error("out of input");
  }
  long res = record[0];
  record.pop_front();

  return res;
}

void StdOutput::write(long num) { std::cout << "<< " << num << std::endl; }

void RecOutput::write(long num) { record.push_back(num); }
