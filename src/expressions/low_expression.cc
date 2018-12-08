/**
 * @file low_expression.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <expressions/low_expression.h>

namespace cassio {

LowType ConvertToLowType(TokenType type) {
  switch (type) {
    case TokenType::MULTIPLY:
      return LowType::MULTIPLY;
    case TokenType::DIVIDE:
      return LowType::DIVIDE;
    case TokenType::MODULUS:
      return LowType::MODULUS;
    default:
      throw std::runtime_error("Invalid Request For Conversion");
  }
}

std::unique_ptr<Expression> LowExpression::Construct(std::list<Token> &tokens, std::unique_ptr<Expression> first) {
  std::unique_ptr<LowExpression> result = nullptr;
  TokenType type = tokens.front().GetType();

  if (type == TokenType::MULTIPLY ||
      type == TokenType::DIVIDE ||
      type == TokenType::MODULUS) {

    tokens.pop_front();

    result = std::make_unique<LowExpression>();
    result->type_ = ConvertToLowType(type);
    result->first_ = std::move(first);
    result->second_ = std::move(Expression::Construct(tokens));
  }
  else {
    return std::move(first);
  }

  return std::move(result);
}

std::string LowExpression::Generate() {
  std::ostringstream oss;

  if (type_ == LowType::MULTIPLY) {
    oss << second_->Generate();
    oss << "\tmov\trbx, rax";
    oss << "\n";
    oss << first_->Generate();
    oss << "\tmul\trbx";
    oss << "\n";
  }
  else if (type_ == LowType::DIVIDE) {
    oss << second_->Generate();
    oss << "\tmov\trbx, rax";
    oss << "\n";
    oss << first_->Generate();
    oss << "\txor\trdx, rdx";
    oss << "\n";
    oss << "\tdiv\trbx";
    oss << "\n";
  }

  if (more_)
    oss << more_->Generate();

  return oss.str();
}

void LowExpression::Semanticate() {
  if (first_)
    first_->Semanticate();

  if (second_)
    second_->Semanticate();
}

}

