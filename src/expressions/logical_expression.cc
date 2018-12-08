/**
 * @file logical_expression.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <expressions/logical_expression.h>

namespace cassio {

LogicalType ConvertToLogicalType(TokenType type) {
  switch (type) {
    case TokenType::EQUALS:
      return LogicalType::EQUALS;
    case TokenType::NOT_EQUAL:
      return LogicalType::NOT_EQUALS;
    case TokenType::GREATER_THAN:
      return LogicalType::GREATER_THAN;
    case TokenType::LESS_THAN:
      return LogicalType::LESS_THAN;
    case TokenType::GREATER_EQUALS:
      return LogicalType::GREATER_EQUALS;
    case TokenType::LESS_EQUALS:
      return LogicalType::LESS_EQUALS;
    default:
      throw std::runtime_error("Invalid Request For Conversion");
  }
}

std::unique_ptr<Expression> LogicalExpression::Construct(std::list<Token> &tokens, std::unique_ptr<Expression> first) {
  std::unique_ptr<LogicalExpression> result = nullptr;
  TokenType type = tokens.front().GetType();

  if (type == TokenType::EQUALS ||
      type == TokenType::NOT_EQUAL ||
      type == TokenType::GREATER_THAN ||
      type == TokenType::LESS_THAN ||
      type == TokenType::GREATER_EQUALS ||
      type == TokenType::LESS_EQUALS) {

    tokens.pop_front();

    result = std::make_unique<LogicalExpression>();
    result->type_ = ConvertToLogicalType(type);
    result->first_ = std::move(first);
    result->second_ = std::move(Expression::Construct(tokens));
  }
  else {
    return std::move(first);
  }

  return std::move(result);
}

std::string LogicalExpression::Generate() {

}

void LogicalExpression::Semanticate() {

}

}

