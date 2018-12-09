/**
 * @file boolean_expression.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <expressions/boolean_expression.h>

namespace cassio {

BooleanType ConvertToBooleanType(TokenType type) {
  switch (type) {
    case TokenType::AND:
      return BooleanType::AND;
    case TokenType::OR:
      return BooleanType::OR;
    default:
      throw std::runtime_error("Invalid Request For Conversion");
  }
}

std::unique_ptr<Expression> BooleanExpression::Construct(std::list<Token> &tokens, std::unique_ptr<Expression> first) {
  std::unique_ptr<BooleanExpression> result = nullptr;
  TokenType type = tokens.front().GetType();

  if (type == TokenType::AND ||
      type == TokenType::OR) {

    tokens.pop_front();

    result = std::make_unique<BooleanExpression>();
    result->type_ = ConvertToBooleanType(type);
    result->first_ = std::move(first);
    result->second_ = std::move(Expression::Construct(tokens));
  }
  else {
    return std::move(first);
  }

  return std::move(result);
}

std::string BooleanExpression::Generate(bool generate_more) {
  std::ostringstream oss;

  if (type_ == BooleanType::AND) {
    oss << second_->Generate();
    oss << "\tmov\trbx, rax";
    oss << "\n";
    oss << first_->Generate();
    oss << "\tand\trax, rbx";
    oss << "\n";
  }
  else {
    oss << second_->Generate();
    oss << "\tmov\trbx, rax";
    oss << "\n";
    oss << first_->Generate();
    oss << "\tor\trax, rbx";
    oss << "\n";
  }

  if (generate_more) {
    if (more_)
      oss << more_->Generate();
  }

  return oss.str();
}

void BooleanExpression::Semanticate() {
  if (first_)
    first_->Semanticate();

  if (second_)
    second_->Semanticate();

  if (more_)
    more_->Semanticate();
}

}
