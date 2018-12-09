/**
 * @file math_expression.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <core/semantic_error.h>
#include <expressions/math_expression.h>
#include <expressions/string_expression.h>

namespace cassio {

MathType ConvertToMathType(TokenType type) {
  switch (type) {
    case TokenType::PLUS:
      return MathType::SUM;
    case TokenType::MINUS:
      return MathType::SUBTRACT;
    default:
      throw std::runtime_error("Invalid Request For Conversion");
  }
}

std::unique_ptr<Expression> MathExpression::Construct(std::list<Token> &tokens, std::unique_ptr<Expression> first) {
  std::unique_ptr<MathExpression> result = nullptr;
  TokenType type = tokens.front().GetType();

  if (type == TokenType::PLUS ||
      type == TokenType::MINUS) {

    tokens.pop_front();

    result = std::make_unique<MathExpression>();
    result->type_ = ConvertToMathType(type);
    result->first_ = std::move(first);
    result->second_ = std::move(Expression::Construct(tokens));
  }
  else {
    return std::move(first);
  }

  return std::move(result);
}

std::string MathExpression::Generate(bool generate_more) {
  std::ostringstream oss;

  if (type_ == MathType::SUM) {
    oss << second_->Generate();
    oss << "\tmov\trbx, rax";
    oss << "\n";
    oss << first_->Generate();
    oss << "\tadd\trax, rbx";
    oss << "\n";
  }
  else {
    oss << second_->Generate();
    oss << "\tmov\trbx, rax";
    oss << "\n";
    oss << first_->Generate();
    oss << "\tsub\trax, rbx";
    oss << "\n";
  }

  if (generate_more) {
    if (more_)
      oss << more_->Generate();
  }

  return oss.str();
}

void MathExpression::Semanticate() {
  if (first_)
    first_->Semanticate();

  if (second_)
    second_->Semanticate();

  if (more_)
    more_->Semanticate();
}

}

