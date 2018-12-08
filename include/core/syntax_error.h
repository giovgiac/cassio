/**
 * @file syntax_error.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef CORE_SYNTAX_ERROR_H_
#define CORE_SYNTAX_ERROR_H_

#include <stdexcept>

namespace cassio {

class SyntaxError : public std::runtime_error {
 public:
  explicit SyntaxError(const char *arg, uint64_t line, uint64_t column)
      : runtime_error(arg), text_(arg), line_(line), column_(column) {}
  explicit SyntaxError(const std::string &arg, uint64_t line, uint64_t column)
      : runtime_error(arg), text_(arg), line_(line), column_(column) {}

  uint64_t GetColumn() const { return column_; }
  uint64_t GetLine() const { return line_; }
  std::string GetText() const { return text_; }

 private:
  std::string text_;
  uint64_t line_;
  uint64_t column_;
};

}

#endif // CORE_SYNTAX_ERROR_H_
