#pragma once

namespace compiler {

class IReader {
 public:
  virtual ~IReader() noexcept = default;

  virtual void Advance() noexcept = 0;

  virtual char Peek() const noexcept = 0;

  virtual char Read() noexcept = 0;
};

}  // namespace compiler