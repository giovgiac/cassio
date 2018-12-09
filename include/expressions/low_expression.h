/**
 * @file low_expression.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef EXPRESSIONS_LOW_H_
#define EXPRESSIONS_LOW_H_

#include <expressions/expression.h>

#include <memory>

namespace cassio {

/**
 * @enum LowType
 * @brief
 *
 * ...
 *
 */
enum class LowType {
  MULTIPLY,
  DIVIDE,
  MODULUS
};

/**
 * @class LowExpression
 * @brief
 *
 * ...
 *
 */
class LowExpression : public Expression {
 public:
  static std::unique_ptr<Expression> Construct(std::list<Token> &tokens, std::unique_ptr<Expression> first);
  std::string Generate(bool generate_more) override;
  void Semanticate() override;

 private:
  LowType type_;
  std::unique_ptr<Expression> first_;
  std::unique_ptr<Expression> second_;
};

}

#endif // EXPRESSIONS_LOW_H_
