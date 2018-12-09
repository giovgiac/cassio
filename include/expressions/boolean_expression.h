/**
 * @file boolean_expression.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef EXPRESSIONS_BOOLEAN_EXPRESSION_H_
#define EXPRESSIONS_BOOLEAN_EXPRESSION_H_

#include <expressions/expression.h>

namespace cassio {

/**
 * @enum BooleanType
 * @brief
 *
 * ...
 *
 */
enum class BooleanType {
  AND,
  OR
};

/**
 * @class BooleanExpression
 * @brief
 *
 * ...
 *
 */
class BooleanExpression : public Expression {
 public:
  static std::unique_ptr<Expression> Construct(std::list<Token> &tokens, std::unique_ptr<Expression> first);
  std::string Generate(bool generate_more) override;
  void Semanticate() override;

 private:
  BooleanType type_;
  std::unique_ptr<Expression> first_;
  std::unique_ptr<Expression> second_;
};

}

#endif // EXPRESSIONS_BOOLEAN_EXPRESSION_H_
