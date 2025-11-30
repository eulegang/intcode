#ifndef IO_H
#define IO_H

#include <deque>
#include <initializer_list>
#include <vector>

namespace IntCode {

struct Input {
  virtual long read() = 0;
};

struct Output {
  virtual void write(long) = 0;
};

struct StdInput : Input {
  StdInput() = default;
  long read() override;
};

struct RecInput : Input {
  RecInput(std::initializer_list<long>);
  long read() override;

private:
  std::deque<long> record;
};

struct StdOutput : Output {
  StdOutput() = default;
  void write(long) override;
};

struct RecOutput : Output {
  std::vector<long> &record;

  RecOutput(std::vector<long> &record);
  void write(long) override;
};

} // namespace IntCode

#endif
