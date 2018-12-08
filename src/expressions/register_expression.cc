/**
 * @file register_expression.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <expressions/register_expression.h>

namespace cassio {

std::unique_ptr<Expression> RegisterExpression::Construct(RegisterType type) {
  std::unique_ptr<RegisterExpression> result = std::make_unique<RegisterExpression>();

  result->type_ = type;
  return result;
}

std::string RegisterExpression::Generate() {
  std::ostringstream oss;

  if (type_ == RegisterType::RAX) {
    oss << "\tmov\trax, rax";
  }
  else if (type_ == RegisterType::RBX) {
    oss << "\tmov\trax, rbx";
  }
  else if (type_ == RegisterType::RCX) {
    oss << "\tmov\trax, rcx";
  }
  else if (type_ == RegisterType::RDX) {
    oss << "\tmov\trax, rdx";
  }
  else if (type_ == RegisterType::RSI) {
    oss << "\tmov\trax, rsi";
  }
  else if (type_ == RegisterType::RDI) {
    oss << "\tmov\trax, rdi";
  }

  oss << "\n";
  if (more_)
    more_->Generate();

  return oss.str();
}

void RegisterExpression::Semanticate() {
  if (more_)
    more_->Semanticate();
}

}

