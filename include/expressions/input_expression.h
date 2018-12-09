/**
 * @file input_expression.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef EXPRESSIONS_INPUT_EXPRESSION_H_
#define EXPRESSIONS_INPUT_EXPRESSION_H_

#include <expressions/expression.h>

namespace cassio {

/**
 * @enum InputType
 * @brief
 *
 * ...
 *
 */
enum class InputType {
  INTEGER,
  STRING
};

/**
 * @class InputExpression
 * @brief
 *
 * ...
 *
 */
class InputExpression : public Expression {
 public:
  static std::unique_ptr<Expression> Construct(InputType type, std::list<Token> &tokens);
  std::string Generate(bool generate_more) override;
  void Semanticate() override;

 private:
  InputType type_;
};

}

#endif // EXPRESSIONS_INPUT_EXPRESSION_H_
