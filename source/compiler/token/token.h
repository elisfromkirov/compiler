#pragma once

#include <string>
#include <utility>
#include <variant>

namespace compiler::detail {

template <typename... Functors>
struct OverloadingSet : Functors... {
  using Functors::operator()...;
};

template <typename... Functors>
OverloadingSet(Functors&&...) -> OverloadingSet<Functors...>;

}  // namespace compiler::detail

namespace compiler {

/// @brief An enumeration represents fixed set operators, braces, etc.
enum Control {
  kOpenBracket,                         // "("
  kCloseBracket,                        // ")"
  kOpenSquareBracket,                   // "["
  kCloseSquareBracket,                  // "]"
  kOpenBrace,                           // "{"
  kCloseBrace,                          // "}"
  kQuestion,                            // "?"
  kExclamation,                         // "!"
  kTilde,                               // "~"
  kColon,                               // ":"
  kSemicolon,                           // ";"
  kComma,                               // ","
  kPeriod,                              // "."
  kElipsis,                             // "..."
  kAmpersand,                           // "&"
  kAmpersandAmpersand,                  // "&&"
  kAmpersandEqual,                      // "&="
  kPipe,                                // "|"
  kPipePipe,                            // "||"
  kPipeEqual,                           // "|="
  kPlus,                                // "+"
  kPlusPlus,                            // "++"
  kPlusEqual,                           // "+="
  kMinus,                               // "-"
  kMinusMinus,                          // "--"
  kMinusEqual,                          // "-="
  kStar,                                // "*"
  kStarEqual,                           // "*="
  kSlash,                               // "/"
  kSlashEqual,                          // "/="
  kPercent,                             // "%"
  kPercentEqual,                        // "%="
  kEqual,                               // "="
  kEqualEqual,                          // "=="
  kCaret,                               // "^"
  kCaretEqual,                          // "^="
  kLess,                                // "<"
  kLessLess,                            // "<<"
  kLessEqual,                           // "<="
  kLessLessEqual,                       // "<<="
  kGreater,                             // ">"
  kGreaterGreater,                      // ">>"
  kGreaterEqual,                        // ">="
  kGreaterGreaterEqual,                 // ">>="
};

/// @brief An enumeration represents extensible set of keywords.
enum Keyword {
  kBreak,                               // break
  kCase,                                // case
  kChar,                                // char
  kConst,                               // const
  kContinue,                            // continue
  kDefault,                             // default
  kDo,                                  // do
  kDouble,                              // double
  kElse,                                // else
  kEnum,                                // enum
  kExtern,                              // extern
  kFloat,                               // float
  kFor,                                 // for
  kGoto,                                // goto
  kIf,                                  // if
  kInline,                              // inline
  kInt,                                 // int
  kLong,                                // long
  kRestrict,                            // restrict
  kReturn,                              // return
  kShort,                               // short
  kSigned,                              // signed
  kSizeof,                              // sizeof
  kStatic,                              // static
  kStruct,                              // struct
  KSwitch,                              // switch
  kTypedef,                             // typedef
  kUnion,                               // union
  kUnsigned,                            // unsigned
  kVoid,                                // void
  kVolatile,                            // volatile
  kWhile                                // while
};

struct CompilationUnitEnd {
};

struct CharacterLiteral {
  char value;
};

struct StringLiteral {
  std::string value;
};

struct NumericLiteral {
  int value;
};

struct Identifier {
  std::string value;
};

class Token {
 public:
  static Token FromCompilationUnitEnd();

  static Token FromKeyword(Keyword keyword);

  static Token FromControl(Control control);

  static Token FromCharacterLiteral(char character_literal);

  static Token FromNumericLiteral(int numeric_literal);

  static Token FromStringLiteral(std::string string_literal);

  static Token FromIdentifier(std::string identifier);

 public:
  template <typename... TMatchers>
  void Match(TMatchers&&... matchers) {
    std::visit(detail::OverloadingSet{std::forward<TMatchers&&>(matchers)...}, value_);
  }

 private:
  using TokenValue = std::variant<CompilationUnitEnd,
                                  Keyword,
                                  Control,
                                  CharacterLiteral,
                                  NumericLiteral,
                                  StringLiteral,
                                  Identifier>;

 private:
  Token() noexcept;

 private:
  TokenValue value_;
};

}  // namespace compiler