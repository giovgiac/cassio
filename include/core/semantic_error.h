/**
 * @file semantical_error.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef CORE_SEMANTIC_ERROR_H_
#define CORE_SEMANTIC_ERROR_H_

#include <stdexcept>

namespace cassio {

class SemanticError : public std::runtime_error {
 public:
  explicit SemanticError(const char *arg)
      : runtime_error(arg), text_(arg) {}
  explicit SemanticError(const std::string &arg)
      : runtime_error(arg), text_(arg) {}

    std::string GetText() const { return text_; }

 private:
  std::string text_;
};

}

#endif // CORE_SEMANTIC_ERROR_H_
