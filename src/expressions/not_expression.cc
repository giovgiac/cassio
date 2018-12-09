/**
 * @file not_expression.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <expressions/not_expression.h>

namespace cassio {

std::unique_ptr<Expression> NotExpression::Construct(std::unique_ptr<Expression> first) {
  std::unique_ptr<NotExpression> result = std::make_unique<NotExpression>();

  result->first_ = std::move(first);
  return std::move(result);
}

std::string NotExpression::Generate(bool generate_more) {
  std::ostringstream oss;

  oss << first_->Generate();
  oss << "\tnot\trax";
  oss << "\n";

  if (generate_more) {
    if (more_)
      oss << more_->Generate();
  }

  return oss.str();
}

void NotExpression::Semanticate() {
  if (first_)
    first_->Semanticate();

  if (more_)
    more_->Semanticate();
}

}
