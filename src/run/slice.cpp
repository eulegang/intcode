#include "intcode.h"

#include <iostream>
#include <memory>
#include <unistd.h>

struct Expr {
  virtual bool contains(size_t i) = 0;
  static std::unique_ptr<Expr> parse(std::string_view str);
};

int main(int argc, char *argv[]) {
  char *filename = nullptr;
  std::vector<std::unique_ptr<Expr>> exprs{};
  int opt{};

  while ((opt = getopt(argc, argv, "f:e:")) != -1) {
    switch (opt) {
    case 'f':
      filename = optarg;
      break;

    case 'e':
      exprs.push_back(Expr::parse(optarg));
      break;
    }
  }

  if (!filename) {
    std::cerr << "Invalid invokcation must provide an intcode program"
              << std::endl;

    return 1;
  }

  IntCode::Program prog(filename);

  bool first = true;
  for (size_t i{}; i < prog.size(); i++) {
    bool pred = false;

    for (auto &expr : exprs) {
      pred |= expr->contains(i);
    }

    if (pred) {
      if (!first) {
        std::cout << ",";
      } else {
        first = false;
      }

      std::cout << prog[i];
    }
  }

  std::cout << std::endl;

  return 0;
}

struct Exact : Expr {
  size_t pos;

  Exact(size_t pos) : pos{pos} {}

  bool contains(size_t i) override { return i == pos; }
};

struct Range : Expr {
  size_t start;
  size_t end;

  Range(size_t start, size_t end) : start{start}, end{end} {}

  bool contains(size_t i) override { return start <= i && i < end; }
};

std::unique_ptr<Expr> Expr::parse(std::string_view line) {
  long partial{};
  long start{};
  bool second{};

  for (auto ch : line) {
    if ('0' <= ch && ch <= '9') {
      partial *= 10;
      partial += ch - '0';
    } else if ('-' == ch) {
      start = partial;
      partial = 0;
      second = true;
    } else {
      throw std::runtime_error("invalid index given");
    }
  }

  if (second) {
    return std::make_unique<Range>(start, partial);
  } else {
    return std::make_unique<Exact>(partial);
  }
}
