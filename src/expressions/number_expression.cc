/**
 * @file number_expression.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <expressions/number_expression.h>

namespace cassio {

std::unique_ptr<Expression> NumberExpression::Construct(std::string number) {
  std::unique_ptr<NumberExpression> result = std::make_unique<NumberExpression>();

  result->number_ = std::move(Number::Construct(std::move(number)));
  return result;
}

std::string NumberExpression::Generate(bool generate_more) {
  std::ostringstream oss;
  uint64_t num = number_->GetNumber();

  oss << "\tmov\trax, " << num;
  oss << "\n";

  if (generate_more) {
    if (more_)
      oss << more_->Generate();
  }

  return oss.str();
}

void NumberExpression::Semanticate() {
  if (more_)
    more_->Semanticate();
}

}

