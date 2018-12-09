/**
 * @file variable_expression.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef EXPRESSIONS_VARIABLE_EXPRESSION_H_
#define EXPRESSIONS_VARIABLE_EXPRESSION_H_

#include <core/child.h>
#include <expressions/expression.h>

namespace cassio {

/**
 * @class VariableExpression
 * @brief
 *
 * ...
 *
 */
class VariableExpression : public Expression {
 public:
  static std::unique_ptr<Expression> Construct(std::list<Token> &tokens);
  std::string Generate(bool generate_more) override;
  void Semanticate() override;

 private:
  std::unique_ptr<Child> variable_;
};

}

#endif // EXPRESSIONS_VARIABLE_EXPRESSION_H_
