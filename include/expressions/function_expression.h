/**
 * @file function_expression.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef EXPRESSIONS_FUNCTION_CALL_H_
#define EXPRESSIONS_FUNCTION_CALL_H_

#include <core/child.h>
#include <expressions/expression.h>
#include <expressions/variable_expression.h>

namespace cassio {

class FunctionExpression : public Expression {
 public:
  static std::unique_ptr<Expression> Construct(std::list<Token> &tokens);
  std::string Generate(bool generate_more) override;
  void Semanticate() override;

 private:
  std::unique_ptr<Child> variable_;
  std::unique_ptr<Expression> argument_;
};

}

#endif // EXPRESSIONS_FUNCTION_CALL_H_
