/**
 * @file math_expression.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef EXPRESSIONS_MATH_EXPRESSION_H_
#define EXPRESSIONS_MATH_EXPRESSION_H_

#include <expressions/expression.h>

#include <memory>

namespace cassio {

/**
 * @enum MathType
 * @brief
 *
 * ...
 *
 */
enum class MathType {
  SUM,
  SUBTRACT
};

/**
 * @class MathExpression
 * @brief
 *
 * ...
 *
 */
class MathExpression : public Expression {
 public:
  static std::unique_ptr<Expression> Construct(std::list<Token> &tokens, std::unique_ptr<Expression> first);
  std::string Generate() override;
  void Semanticate() override;

 private:
  MathType type_;
  std::unique_ptr<Expression> first_;
  std::unique_ptr<Expression> second_;
};

}

#endif // EXPRESSIONS_MATH_EXPRESSION_H_
