/**
 * @file logical_expression.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <core/semantic_error.h>
#include <core/syntax_error.h>
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

std::unique_ptr<LogicalExpression> LogicalExpression::Construct(std::list<Token> &tokens, std::unique_ptr<Expression> first) {
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
    throw SyntaxError("expected a logical expression at if condition",
        tokens.front().GetLine(),
        tokens.front().GetColumn());
  }

  return std::move(result);
}

std::string LogicalExpression::Generate() {
  std::ostringstream oss;

  oss << second_->Generate();
  oss << "\tmov\trcx, rax";
  oss << "\n";
  oss << first_->Generate();
  oss << "\tcmp\trax, rcx";
  oss << "\n";

  if (type_ == LogicalType::EQUALS) {
    oss << "\tje\t";
  }
  else if (type_ == LogicalType::NOT_EQUALS) {
    oss << "\tjne\t";
  }
  else if (type_ == LogicalType::GREATER_THAN) {
    oss << "\tjg\t";
  }
  else if (type_ == LogicalType::GREATER_EQUALS) {
    oss << "\tjge\t";
  }
  else if (type_ == LogicalType::LESS_THAN) {
    oss << "\tjb\t";
  }
  else if (type_ == LogicalType::LESS_EQUALS) {
    oss << "\tjbe\t";
  }

  if (more_)
    oss << more_->Generate();

  return oss.str();
}

void LogicalExpression::Semanticate() {

  if (more_)
    throw SemanticError("unexpected multiple expressions at logical expression");
}

}

