/**
 * @file value_instruction.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <core/semantic_error.h>
#include <core/syntax_error.h>
#include <function/value_instruction.h>

namespace cassio {

std::unique_ptr<Instruction> ValueInstruction::Construct(std::list<Token> &tokens) {
  std::unique_ptr<ValueInstruction> result = std::make_unique<ValueInstruction>();

  if (tokens.front().GetType() == TokenType::RAX ||
      tokens.front().GetType() == TokenType::RBX ||
      tokens.front().GetType() == TokenType::RCX ||
      tokens.front().GetType() == TokenType::RDX ||
      tokens.front().GetType() == TokenType::RSI ||
      tokens.front().GetType() == TokenType::RDI) {

    if (tokens.front().GetType() == TokenType::RAX) {
      result->type_ = ValueType::REGISTER;
      result->register_ = RAX;
      result->variable_ = nullptr;
    }
    else if (tokens.front().GetType() == TokenType::RBX) {
      result->type_ = ValueType::REGISTER;
      result->register_ = RBX;
      result->variable_ = nullptr;
    }
    else if (tokens.front().GetType() == TokenType::RCX) {
      result->type_ = ValueType::REGISTER;
      result->register_ = RCX;
      result->variable_ = nullptr;
    }
    else if (tokens.front().GetType() == TokenType::RDX) {
      result->type_ = ValueType::REGISTER;
      result->register_ = RDX;
      result->variable_ = nullptr;
    }
    else if (tokens.front().GetType() == TokenType::RSI) {
      result->type_ = ValueType::REGISTER;
      result->register_ = RSI;
      result->variable_ = nullptr;
    }
    else if (tokens.front().GetType() == TokenType::RDI) {
      result->type_ = ValueType::REGISTER;
      result->register_ = RDI;
      result->variable_ = nullptr;
    }

    tokens.pop_front();
  }
  else {
    result->type_ = ValueType::VARIABLE;
    result->register_ = ValueRegister::NONE;
    result->variable_ = std::move(Child::Construct(tokens));
  }

  if (tokens.front().GetType() != TokenType::RIGHT_BRACE)
    throw SyntaxError("expected ']' at value assignment",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  tokens.pop_front();

  if (tokens.front().GetType() != TokenType::LEFT_ARROW)
    throw SyntaxError("expected '<-' at value assignment",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  tokens.pop_front();

  result->value_ = std::move(Expression::Construct(tokens, false, false, false));

  if (tokens.front().GetType() != TokenType::SEMICOLON)
    throw SyntaxError("expected ';' at end of value assignment",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  tokens.pop_front();

  return result;
}

std::string ValueInstruction::Generate() {
  std::ostringstream oss;

  if (type_ == ValueType::VARIABLE) {
    if (variable_->GetType() == "byte") {
      oss << value_->Generate();
      oss << "\tmov\t";
      oss << variable_->GetType() << " [" << variable_->Generate() << "]";
      oss << ", al";
      oss << "\n";
    } else if (variable_->GetType() == "word") {
      oss << value_->Generate();
      oss << "\tmov\t";
      oss << variable_->GetType() << " [" << variable_->Generate() << "]";
      oss << ", ax";
      oss << "\n";
    } else if (variable_->GetType() == "dword") {
      oss << value_->Generate();
      oss << "\tmov\t";
      oss << variable_->GetType() << " [" << variable_->Generate() << "]";
      oss << ", eax";
      oss << "\n";
    } else if (variable_->GetType() == "qword") {
      oss << value_->Generate();
      oss << "\tmov\t";
      oss << variable_->GetType() << " [" << variable_->Generate() << "]";
      oss << ", rax";
      oss << "\n";
    } else {
      throw SemanticError("user-defined types are not supported for assignments");
    }
  }
  else {
    if (register_ == ValueRegister::RAX) {
      throw SemanticError("rax cannot be used for address dereferencing");
    }
    else if (register_ == ValueRegister::RBX) {
      oss << value_->Generate();
      oss << "\tmov\t[rbx], rax";
      oss << "\n";
    }
    else if (register_ == ValueRegister::RCX) {
      oss << value_->Generate();
      oss << "\tmov\t[rcx], rax";
      oss << "\n";
    }
    else if (register_ == ValueRegister::RDX) {
      oss << value_->Generate();
      oss << "\tmov\t[rdx], rax";
      oss << "\n";
    }
    else if (register_ == ValueRegister::RSI) {
      oss << value_->Generate();
      oss << "\tmov\t[rsi], rax";
      oss << "\n";
    }
    else if (register_ == ValueRegister::RDI) {
      oss << value_->Generate();
      oss << "\tmov\t[rdi], rax";
      oss << "\n";
    }
  }

  if (more_)
    oss << more_->Generate();

  return oss.str();
}

void ValueInstruction::Semanticate() {
  value_->Semanticate();

  if (variable_) {
    variable_->Semanticate();

    if (variable_->GetType() != "byte" && variable_->GetType() != "word" && variable_->GetType() != "dword"
        && variable_->GetType() != "qword") {
      throw SemanticError("user-defined types are not supported for assignments");
    }
  }

  if (more_)
    more_->Semanticate();
}

}
