#include <fstream>

#include <compiler/io/source_file.h>

namespace compiler {

SourceFile::SourceFile(const char* file_name)
  : buffer_{}
  , cursor_{} {
  std::ifstream stream{file_name};
  while (stream.peek(), !stream.eof()) {
    buffer_.push_back(stream.get());
  }
}

void SourceFile::Advance() noexcept {
  if (cursor_ < buffer_.size()) {
    ++cursor_;
  }
}

char SourceFile::Peek() const noexcept {
  if (cursor_ < buffer_.size()) {
    return buffer_[cursor_];
  }
  return '\0';
}

char SourceFile::Read() noexcept {
  auto character = Peek();
  Advance();
  return character;
}

}  // namespace compiler