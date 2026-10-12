#include <memory>
#include <print>
#include <string>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

int main(int argc, char *argv[]) {
  std::println("Hello, Verita!");
  std::string source = argc >= 2 ? argv[1] : "__VERITA_SOURCE_NOT_FOUND";
  std::println("Source File: {}", source);
  auto context = std::make_unique<llvm::LLVMContext>();
  auto module = std::make_unique<llvm::Module>("verita_module", *context);

  module->print(llvm::outs(), nullptr);

  return 0;
}
