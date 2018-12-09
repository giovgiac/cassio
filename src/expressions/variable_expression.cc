/**
 * @file variable_expression.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <core/semantic_error.h>
#include <expressions/variable_expression.h>

namespace cassio {

std::unique_ptr<Expression> VariableExpression::Construct(std::list<Token> &tokens) {
  std::unique_ptr<VariableExpression> result = std::make_unique<VariableExpression>();

  result->variable_ = std::move(Child::Construct(tokens));
  return result;
}

std::string VariableExpression::Generate(bool generate_more) {
  std::ostringstream oss;

  oss << "\tmov\trax, " << variable_->Generate();
  oss << "\n";

  if (generate_more) {
    if (more_)
      oss << more_->Generate();
  }

  return oss.str();
}

void VariableExpression::Semanticate() {
  variable_->Semanticate(true);

  if (variable_->GetType() != "byte" && variable_->GetType() != "word" && variable_->GetType() != "dword"
      && variable_->GetType() != "qword") {
    throw SemanticError("user-defined types not supported at expressions");
  }

  if (more_)
    more_->Semanticate();
}

}
