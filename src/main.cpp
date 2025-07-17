#include "file.h"
#include "helpers.h"
#include "program.h"

#include <expected>
#include <iostream>

int main(int argc, const char *argv[]) {
  std::expected<std::string, std::string> result =
      Helpers::check_args(argc, argv);

  if (result) {
    Program::execute(*result);
  } else {
    std::cerr << result.error() << "\n";
  }
}
