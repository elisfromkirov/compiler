#include <compiler/token/keyword_table.h>

namespace compiler {

KeywordTable::KeywordTable()
  : keywords_{} {
  keywords_.emplace("break", kBreak);
  keywords_.emplace("case", kCase);
  keywords_.emplace("char", kChar);
  keywords_.emplace("const", kConst);
  keywords_.emplace("continue", kContinue);
  keywords_.emplace("default", kDefault);
  keywords_.emplace("do", kDo);
  keywords_.emplace("double", kDouble);
  keywords_.emplace("else", kElse);
  keywords_.emplace("enum", kEnum);
  keywords_.emplace("extern", kExtern);
  keywords_.emplace("float", kFloat);
  keywords_.emplace("for", kFor);
  keywords_.emplace("goto", kGoto);
  keywords_.emplace("if", kIf);
  keywords_.emplace("inline", kInline);
  keywords_.emplace("int", kInt);
  keywords_.emplace("long", kLong);
  keywords_.emplace("restrict", kRestrict);
  keywords_.emplace("return", kReturn);
  keywords_.emplace("short", kShort);
  keywords_.emplace("signed", kSigned);
  keywords_.emplace("sizeof", kSizeof);
  keywords_.emplace("static", kStatic);
  keywords_.emplace("struct", kStruct);
  keywords_.emplace("switch", KSwitch);
  keywords_.emplace("typedef", kTypedef);
  keywords_.emplace("union", kUnion);
  keywords_.emplace("unsigned", kUnsigned);
  keywords_.emplace("void", kVoid);
  keywords_.emplace("volatile", kVolatile);
  keywords_.emplace("while", kWhile);
}

std::optional<Keyword> KeywordTable::TryFind(const std::string& string) const noexcept {
  auto iterator = keywords_.find(string);
  if (iterator == keywords_.cend()) {
    return std::nullopt;
  }
  return iterator->second;
}

}  // namespace compiler