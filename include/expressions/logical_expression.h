/**
 * @file logical_expression.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef EXPRESSIONS_LOGICAL_EXPRESSION_H_
#define EXPRESSIONS_LOGICAL_EXPRESSION_H_

#include <expressions/expression.h>

namespace cassio {

/**
 * @enum LogicalType
 * @brief
 *
 */
enum class LogicalType {
  EQUALS,
  NOT_EQUALS,
  GREATER_THAN,
  LESS_THAN,
  GREATER_EQUALS,
  LESS_EQUALS
};

/**
 * @class LogicalExpression
 * @brief
 *
 * ...
 *
 */
class LogicalExpression : public Expression {
 public:
  static std::unique_ptr<Expression> Construct(std::list<Token> &tokens, std::unique_ptr<Expression> first);
  std::string Generate() override;
  void Semanticate() override;

 private:
  LogicalType type_;
  std::unique_ptr<Expression> first_;
  std::unique_ptr<Expression> second_;
};

}

#endif // EXPRESSIONS_LOGICAL_EXPRESSION_H_
