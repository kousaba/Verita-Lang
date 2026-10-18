#pragma once

#include <span>
#include <string>
#include <string_view>
#include <vector>

namespace verita{
struct CompilerOptions {
  std::string input_file_path;
  std::string output_file_path = "a.out";
  bool dump_tokens = false;
  bool dump_ast = false;
  bool dump_ir = false;
  bool verify_only = false; // Do not run codegen
};

class Driver{
public:
  Driver() = default;

  int run(std::span<const std::string_view> args);

private:
    bool parse_arguments(std::span<const std::string_view> args, CompilerOptions& options);
    bool compile(const CompilerOptions& options);
};
}
