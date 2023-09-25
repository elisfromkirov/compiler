#pragma once

#include <exception>

#include <compiler/io/reader.h>

#include <compiler/token/keyword_table.h>
#include <compiler/token/token.h>

namespace compiler {

class UnsupportedCharacter : public std::exception {
 public:
  const char* what() const noexcept override;
};

class IllFormedCharacterLiteral : public std::exception {
 public:
  const char* what() const noexcept override;
};

class IllFormedNumericLiteral : public std::exception {
 public:
  const char* what() const noexcept override;
};

class IllFormedStringLiteral : public std::exception {
 public:
  const char* what() const noexcept override;
};

class Tokenizer final {
 public:
  Tokenizer(IReader& reader) noexcept;

  Token Tokenize();

 private:
  void SkipWhitespace() noexcept;

  Token ParseIdentifierOrKeyword();

  Token ParseControl();

  Token ParseCharacterLiteral();

  Token ParseNumericLiteral();

  Token ParseStringLiteral();

 private:
  IReader& reader_;
  KeywordTable keyword_table_;
};

}  // namespace compiler