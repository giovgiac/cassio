/**
 * @file string_expression.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef EXPRESSIONS_STRING_EXPRESSION_H_
#define EXPRESSIONS_STRING_EXPRESSION_H_

#include <expressions/expression.h>

namespace cassio {

/**
 * @class StringExpression
 * @brief
 *
 * ...
 *
 */
class StringExpression : public Expression {
 public:
  static std::unique_ptr<StringExpression> Construct(std::string string);
  std::string Generate() override;
  void Semanticate() override;

 private:
  std::string string_;
  uint64_t id_;

  static uint64_t global_id;
};

}

#endif // EXPRESSIONS_STRING_EXPRESSION_H_
