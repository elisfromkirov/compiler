#pragma once

#include <string>

#include <compiler/io/reader.h>

namespace compiler {

class SourceFile final : public IReader {
 public:
  SourceFile(const char* file_name);

  void Advance() noexcept override;

  char Peek() const noexcept override;

  char Read() noexcept override;

 private:
  std::string buffer_;
  std::size_t cursor_;
};

}  // namespace compiler