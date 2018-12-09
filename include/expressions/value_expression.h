/**
 * @file value_expression.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef EXPRESSIONS_VALUE_EXPRESSION_H_
#define EXPRESSIONS_VALUE_EXPRESSION_H_

#include <core/child.h>
#include <expressions/expression.h>

namespace cassio {

/**
 * @class ValueExpression
 * @brief
 *
 * ...
 *
 */
class ValueExpression : public Expression {
 public:
  static std::unique_ptr<Expression> Construct(std::list<Token> &tokens);
  std::string Generate(bool generate_more) override;
  void Semanticate() override;

 private:
  RegisterType type_;
  std::unique_ptr<Child> variable_;
};

}

#endif // EXPRESSIONS_VALUE_EXPRESSION_H_
