/**
 * @file value_expression.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <core/semantic_error.h>
#include <expressions/value_expression.h>

namespace cassio {

std::unique_ptr<Expression> ValueExpression::Construct(std::list<Token> &tokens) {
  std::unique_ptr<ValueExpression> result = std::make_unique<ValueExpression>();

  result->variable_ = std::move(Child::Construct(tokens));
  return result;
}

std::string ValueExpression::Generate() {
  std::ostringstream oss;

  if (variable_->GetType() == "byte") {
    oss << "\tmov\tal, ";
    oss << variable_->GetType() << " [" << variable_->Generate() << "]";
    oss << "\n";
  }
  else if (variable_->GetType() == "word") {
    oss << "\tmov\tax, ";
    oss << variable_->GetType() << " [" << variable_->Generate() << "]";
    oss << "\n";
  }
  else if (variable_->GetType() == "dword") {
    oss << "\tmov\teax, ";
    oss << variable_->GetType() << " [" << variable_->Generate() << "]";
    oss << "\n";
  }
  else if (variable_->GetType() == "qword") {
    oss << "\tmov\trax, ";
    oss << variable_->GetType() << " [" << variable_->Generate() << "]";
    oss << "\n";
  }

  if (more_)
    oss << more_->Generate();

  return oss.str();
}

void ValueExpression::Semanticate() {
  variable_->Semanticate();

  if (variable_->GetType() != "byte" && variable_->GetType() != "word" && variable_->GetType() != "dword"
      && variable_->GetType() != "qword") {
    throw SemanticError("user-defined types not supported at expressions");
  }

  if (more_)
    more_->Semanticate();
}

}

