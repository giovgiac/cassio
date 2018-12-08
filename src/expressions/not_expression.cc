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

std::string NotExpression::Generate() {

}

void NotExpression::Semanticate() {

}

}
