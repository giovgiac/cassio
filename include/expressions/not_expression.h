/**
 * @file not_expression.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef EXPRESSIONS_NOT_EXPRESSION_H_
#define EXPRESSIONS_NOT_EXPRESSION_H_

#include <expressions/expression.h>

namespace cassio {

/**
 * @class NotExpression
 * @brief
 *
 * ...
 *
 */
class NotExpression : public Expression {
 public:
  static std::unique_ptr<Expression> Construct(std::unique_ptr<Expression> first);
  std::string Generate(bool generate_more) override;
  void Semanticate() override;

 private:
  std::unique_ptr<Expression> first_;
};

}

#endif // EXPRESSIONS_NOT_EXPRESSION_H_
