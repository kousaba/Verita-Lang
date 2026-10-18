#include <iostream>
#include <verita/Basic/Log/Logger.hpp>
#include <verita/Driver/Driver.hpp>

namespace verita {

int Driver::run(std::span<const std::string_view> args) {
  CompilerOptions options;
  if (!parse_arguments(args, options)) {
    std::cerr << "Failed to parse args." << std::endl;
    return 1; // Couldnt parse args
  }
  if (!compile(options)) {
    std::cerr << "Failed to Compile." << std::endl;
    return 1; // Couldnt compile
  }

  std::cout << "Compilation succeeded!" << std::endl;
  return 0;
}

bool Driver::parse_arguments(std::span<const std::string_view> args,
                             CompilerOptions &options) {
  if (args.size() < 2) {
    std::cerr << "TODO: write usage." << std::endl;
    return false;
  }

  for (size_t i = 1; i < args.size(); i++) {
    auto arg = args[i];
    if (arg == "--dump-tokens")
      options.dump_tokens = true;
    else if (arg == "--dump-ast")
      options.dump_ast = true;
    else if (arg == "--dump-ir")
      options.dump_ir = true;
    else if (arg == "--verify-only")
      options.verify_only = true;
    else if (arg == "--debug")
      Logger::getInstance().enable_debug_logs();
    else if (!arg.starts_with("-"))
      options.input_file_path = std::string(arg);
    else {
      std::cerr << "Unknown option: " << arg << std::endl;
      return true;
    }
  }
  return true;
}

bool Driver::compile(const CompilerOptions &options) {
  std::cout << "Compiling: " << options.input_file_path << "...\n";
  return true;
}
} // namespace verita
