#pragma once

#include <optional>
#include <unordered_map>

#include <compiler/token/token.h>

namespace compiler {

class KeywordTable final {
 public:
  KeywordTable();

  std::optional<Keyword> TryFind(const std::string& string) const noexcept;

 private:
  std::unordered_map<std::string, Keyword> keywords_;
};

}  // namespace compiler