#include <compiler/token/token.h>

namespace compiler {

Token Token::FromCompilationUnitEnd() {
  Token token{};
  token.value_.emplace<0>();
  return token;
}

Token Token::FromKeyword(Keyword keyword) {
  Token token{};
  token.value_.emplace<1>(keyword);
  return token;
}

Token Token::FromControl(Control control) {
  Token token{};
  token.value_.emplace<2>(control);
  return token;
}

Token Token::FromCharacterLiteral(char character_literal) {
  Token token{};
  token.value_.emplace<3>(CharacterLiteral{character_literal});
  return token;
}

Token Token::FromNumericLiteral(int numeric_literal) {
  Token token{};
  token.value_.emplace<4>(NumericLiteral{numeric_literal});
  return token;
}

Token Token::FromStringLiteral(std::string string_literal) {
  Token token{};
  token.value_.emplace<5>(StringLiteral{string_literal});
  return token;
}

Token Token::FromIdentifier(std::string identifier) {
  Token token{};
  token.value_.emplace<6>(Identifier{identifier});
  return token;
}

Token::Token() noexcept
  : value_{} {
}

}  // namespace compiler