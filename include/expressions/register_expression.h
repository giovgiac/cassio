/**
 * @file register_expression.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef EXPRESSIONS_REGISTER_EXPRESSION_H_
#define EXPRESSIONS_REGISTER_EXPRESSION_H_

#include <expressions/expression.h>

#include <memory>

namespace cassio {

/**
 * @class RegisterExpression
 * @brief
 *
 * ...
 *
 */
class RegisterExpression : public Expression {
 public:
  static std::unique_ptr<Expression> Construct(RegisterType type);
  std::string Generate(bool generate_more) override;
  void Semanticate() override;

 private:
  RegisterType type_;
};

}

#endif // EXPRESSIONS_REGISTER_EXPRESSION_H_
