#include <iostream>

#include <compiler/io/source_file.h>

#include <compiler/token/tokenizer.h>

int main() {
  compiler::SourceFile source_file{"test.txt"};

  compiler::Tokenizer tokenizer{source_file};

  bool compilation_unit_found{false};
  while (!compilation_unit_found) {
    auto token = tokenizer.Tokenize();
    token.Match(
      [&](compiler::CompilationUnitEnd) {
        compilation_unit_found = true;
      },
      [](compiler::Keyword keyword) {
        std::cout << "keyword: " << keyword << std::endl;
      },
      [](compiler::Control control) {
        std::cout << "control: " << control << std::endl;
      },
      [](compiler::CharacterLiteral literal) {
        std::cout << "character literal: '" << literal.value << "'" << std::endl;
      },
      [](compiler::NumericLiteral literal) {
        std::cout << "numeric literal: " << literal.value << std::endl;
      },
      [](const compiler::StringLiteral& literal) {
        std::cout << "string literal: '" << literal.value << "'" << std::endl;
      },
      [](const compiler::Identifier& identifier) {
        std::cout << "identifier: '" << identifier.value << "'" << std::endl;
      }
    );
  }

  return 0;
}