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

  if (tokens.front().GetType() == TokenType::RAX) {
    tokens.pop_front();

    result->type_ = RegisterType::RAX;
    result->variable_ = nullptr;

    return result;
  }
  else if (tokens.front().GetType() == TokenType::RBX) {
    tokens.pop_front();

    result->type_ = RegisterType::RBX;
    result->variable_ = nullptr;

    return result;
  }
  else if (tokens.front().GetType() == TokenType::RCX) {
    tokens.pop_front();

    result->type_ = RegisterType::RCX;
    result->variable_ = nullptr;

    return result;
  }
  else if (tokens.front().GetType() == TokenType::RDX) {
    tokens.pop_front();

    result->type_ = RegisterType::RDX;
    result->variable_ = nullptr;

    return result;
  }
  else if (tokens.front().GetType() == TokenType::RSI) {
    tokens.pop_front();

    result->type_ = RegisterType::RSI;
    result->variable_ = nullptr;

    return result;
  }
  else if (tokens.front().GetType() == TokenType::RDI) {
    tokens.pop_front();

    result->type_ = RegisterType::RDI;
    result->variable_ = nullptr;

    return result;
  }

  result->variable_ = std::move(Child::Construct(tokens));
  return result;
}

std::string ValueExpression::Generate(bool generate_more) {
  std::ostringstream oss;

  if (variable_) {
    if (variable_->GetType() == "byte") {
      oss << "\tmov\tal, ";
      oss << variable_->GetType() << " [" << variable_->Generate() << "]";
      oss << "\n";
    } else if (variable_->GetType() == "word") {
      oss << "\tmov\tax, ";
      oss << variable_->GetType() << " [" << variable_->Generate() << "]";
      oss << "\n";
    } else if (variable_->GetType() == "dword") {
      oss << "\tmov\teax, ";
      oss << variable_->GetType() << " [" << variable_->Generate() << "]";
      oss << "\n";
    } else if (variable_->GetType() == "qword") {
      oss << "\tmov\trax, ";
      oss << variable_->GetType() << " [" << variable_->Generate() << "]";
      oss << "\n";
    }
  }
  else {
    if (type_ == RegisterType::RAX) {
      oss << "\tmov\trax, [rax]";
      oss << "\n";
    }
    else if (type_ == RegisterType::RBX) {
      oss << "\tmov\trax, [rbx]";
      oss << "\n";
    }
    else if (type_ == RegisterType::RCX) {
      oss << "\tmov\trax, [rcx]";
      oss << "\n";
    }
    else if (type_ == RegisterType::RDX) {
      oss << "\tmov\trax, [rdx]";
      oss << "\n";
    }
    else if (type_ == RegisterType::RSI) {
      oss << "\tmov\trax, [rsi]";
      oss << "\n";
    }
    else if (type_ == RegisterType::RDI) {
      oss << "\tmov\trax, [rdi]";
      oss << "\n";
    }
  }

  if (generate_more) {
    if (more_)
      oss << more_->Generate();
  }

  return oss.str();
}

void ValueExpression::Semanticate() {
  if (variable_) {
    variable_->Semanticate();

    if (variable_->GetType() != "byte" && variable_->GetType() != "word" && variable_->GetType() != "dword"
        && variable_->GetType() != "qword") {
      throw SemanticError("user-defined types not supported at expressions");
    }
  }

  if (more_)
    more_->Semanticate();
}

}

