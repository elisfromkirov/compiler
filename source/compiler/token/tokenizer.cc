#include <cctype>

#include <compiler/common/common.h>

#include <compiler/token/tokenizer.h>

namespace compiler::detail {

bool IsAlphabetic(char character) noexcept {
  return std::isalpha(character);
}

bool IsNumeric(char character) noexcept {
  return std::isdigit(character);
}

bool IsWhitespace(char character) noexcept {
  return std::isspace(character);
}

bool IsPunctuation(char character) noexcept {
  return std::ispunct(character) && character != '$' &&
                                    character != '@' &&
                                    character != '#' &&
                                    character != '"' &&
                                    character != '\'';
}

bool IsQuotation(char character) noexcept {
  return character == '\'';
}

bool IsDoubleQuotation(char character) noexcept {
  return character == '\"';
}

bool IsNull(char character) noexcept {
  return character == '\0';
}

bool IsEscape(char character) noexcept {
  return character == '\\';
}

bool IsUnderscore(char character) noexcept {
  return character == '_';
}

}  // namespace compiler::detail

namespace compiler {

const char* UnsupportedCharacter::what() const noexcept {
  return "read unsupported character";
}

const char* IllFormedCharacterLiteral::what() const noexcept {
  return "ill-formed character literal";
}

const char* IllFormedNumericLiteral::what() const noexcept {
  return "ill-formed numeric literal";
}

const char* IllFormedStringLiteral::what() const noexcept {
  return "ill-formed string literal";
}

Tokenizer::Tokenizer(IReader& reader) noexcept
  : reader_{reader}
  , keyword_table_{} {
}

Token Tokenizer::Tokenize() {
  while (true) {
    auto character = reader_.Peek();
    if (detail::IsWhitespace(character)) {
      SkipWhitespace();
      character = reader_.Peek();
    }
    if (detail::IsNull(character)) {
      return Token::FromCompilationUnitEnd();
    }
    if (detail::IsAlphabetic(character) || detail::IsUnderscore(character)) {
      return ParseIdentifierOrKeyword();
    }
    if (detail::IsPunctuation(character)) {
      return ParseControl();
    }
    if (detail::IsQuotation(character)) {
      return ParseCharacterLiteral();
    }
    if (detail::IsNumeric(character)) {
      return ParseNumericLiteral();
    }
    if (detail::IsDoubleQuotation(character)) {
      return ParseStringLiteral();
    }
    throw UnsupportedCharacter{};
  }
  UNREACHABLE();
}

void Tokenizer::SkipWhitespace() noexcept {
  while (detail::IsWhitespace(reader_.Peek())) {
    reader_.Advance();
  }
}

Token Tokenizer::ParseIdentifierOrKeyword() {
  std::string string{};
  while (detail::IsAlphabetic(reader_.Peek()) ||
         detail::IsUnderscore(reader_.Peek())) {
    string.push_back(reader_.Read());
  }
  if (auto keyword = keyword_table_.TryFind(string)) {
    return Token::FromKeyword(*keyword);
  }
  return Token::FromIdentifier(string);
}

Token Tokenizer::ParseControl() {
  switch (reader_.Read()) {
    case '(': {
      return Token::FromControl(kOpenBracket);
    }
    case ')': {
      return Token::FromControl(kCloseBracket);
    }
    case '[': {
      return Token::FromControl(kOpenSquareBracket);
    }
    case ']': {
      return Token::FromControl(kCloseSquareBracket);
    }
    case '{': {
      return Token::FromControl(kOpenBrace);
    }
    case '}': {
      return Token::FromControl(kCloseBrace);
    }
    case '?': {
      return Token::FromControl(kQuestion);
    }
    case '!': {
      return Token::FromControl(kExclamation);
    }
    case '~': {
      return Token::FromControl(kTilde);
    }
    case ':': {
      return Token::FromControl(kColon);
    }
    case ';': {
      return Token::FromControl(kSemicolon);
    }
    case ',': {
      return Token::FromControl(kComma);
    }
    case '.': {
      if (reader_.Peek() == '.') {
        reader_.Advance();
        if (reader_.Peek() == '.') {
          return Token::FromControl(kElipsis);
        } else {
          // TODO(elisfromkirov): Throw an exception `ill-formed control`
        }
      } else {
        return Token::FromControl(kPeriod);
      }
    }
    case '+': {
      switch (reader_.Peek()) {
        case '+': {
          reader_.Advance();
          return Token::FromControl(kPlusPlus);
        }
        case '=': {
          reader_.Advance();
          return Token::FromControl(kPlusEqual);
        }
        default: {
          return Token::FromControl(kPlus);
        }
      }
    }
    case '-': {
      switch (reader_.Peek()) {
        case '-': {
          reader_.Advance();
          return Token::FromControl(kMinusMinus);
        }
        case '=': {
          reader_.Advance();
          return Token::FromControl(kMinusEqual);
        }
        default: {
          return Token::FromControl(kMinus);
        }
      }
    }
    case '&': {
      switch (reader_.Peek()) {
        case '&': {
          reader_.Advance();
          return Token::FromControl(kAmpersandAmpersand);
        }
        case '=': {
          reader_.Advance();
          return Token::FromControl(kAmpersandEqual);
        }
        default: {
          return Token::FromControl(kAmpersand);
        }
      }
    }
    case '|': {
      switch (reader_.Peek()) {
        case '|': {
          reader_.Advance();
          return Token::FromControl(kAmpersandAmpersand);
        }
        case '=': {
          reader_.Advance();
          return Token::FromControl(kAmpersandEqual);
        }
        default: {
          return Token::FromControl(kAmpersand);
        }
      }
    }
    case '*': {
      switch (reader_.Peek()) {
        case '=': {
          reader_.Advance();
          return Token::FromControl(kStarEqual);
        }
        default: {
          return Token::FromControl(kStar);
        }
      }
    }
    case '/': {
      switch (reader_.Peek()) {
        case '=': {
          reader_.Advance();
          return Token::FromControl(kSlashEqual);
        }
        default: {
          return Token::FromControl(kSlash);
        }
      }
    }
    case '%': {
      switch (reader_.Peek()) {
        case '=': {
          reader_.Advance();
          return Token::FromControl(kPercentEqual);
        }
        default: {
          return Token::FromControl(kPercent);
        }
      }
    }
    case '=': {
      switch (reader_.Peek()) {
        case '=': {
          reader_.Advance();
          return Token::FromControl(kEqualEqual);
        }
        default: {
          return Token::FromControl(kEqual);
        }
      }
    }
    case '<': {
      switch (reader_.Peek()) {
        case '<': {
          reader_.Advance();
          switch (reader_.Peek()) {
            case '=': {
              reader_.Advance();
              return Token::FromControl(kLessLessEqual);
            }
            default: {
              return Token::FromControl(kLessLess);
            }
          }
        }
        case '=': {
          reader_.Advance();
          return Token::FromControl(kLessEqual);
        }
        default: {
          return Token::FromControl(kLess);
        }
      }
    }
    case '>': {
      switch (reader_.Peek()) {
        case '>': {
          reader_.Advance();
          switch (reader_.Peek()) {
            case '=': {
              reader_.Advance();
              return Token::FromControl(kGreaterGreaterEqual);
            }
            default: {
              return Token::FromControl(kGreaterGreater);
            }
          }
        }
        case '=': {
          reader_.Advance();
          return Token::FromControl(kGreaterEqual);
        }
        default: {
          return Token::FromControl(kGreater);
        }
      }
    }
  }
  UNREACHABLE();
}

Token Tokenizer::ParseCharacterLiteral() {
  ASSERT(detail::IsQuotation(reader_.Read()));

  char character_literal = reader_.Read();
  if (!detail::IsQuotation(reader_.Peek())) {
    throw IllFormedCharacterLiteral{};
  }
  return Token::FromCharacterLiteral(character_literal);
}

Token Tokenizer::ParseNumericLiteral() {
  ASSERT(detail::IsNumeric(reader_.Read()));

  int value{};
  while (detail::IsNumeric(reader_.Peek())) {
    value *= 10;
    value += static_cast<int>(reader_.Read()) - static_cast<int>('0');
  }
  return Token::FromNumericLiteral(value);
}

Token Tokenizer::ParseStringLiteral() {
  ASSERT(detail::IsDoubleQuotation(reader_.Read()));

  std::string string_literal{};
  while (true) {
    auto character = reader_.Peek();
    if (detail::IsNull(character)) {
      throw IllFormedStringLiteral{};
    }
    if (detail::IsDoubleQuotation(character)) {
      break;
    }
    if (detail::IsEscape(character)) {
      reader_.Advance();
      character = reader_.Peek();
    }
    reader_.Advance();
    string_literal.push_back(character);
  }
  return Token::FromStringLiteral(string_literal);
}

}  // namespace compiler