
#include "io.h"
#include "prog.h"

#include <iostream>
#include <stdexcept>
#include <vector>

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

RecInput::RecInput(std::string_view line) : record{} {
  std::vector<long> values;
  IntCode::read_longs(values, line);
  record.insert(record.begin(), values.begin(), values.end());
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

RecOutput::RecOutput(std::vector<long> &record) : record{record} {}
void RecOutput::write(long num) {
  std::cout << "writing " << num << std::endl;

  record.push_back(num);
}
