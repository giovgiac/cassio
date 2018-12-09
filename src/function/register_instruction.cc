/**
 * @file register_instruction.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <core/syntax_error.h>
#include <function/register_instruction.h>

namespace cassio {

std::unique_ptr<Instruction> RegisterInstruction::Construct(std::list<Token> &tokens, RegisterType type) {
  std::unique_ptr<RegisterInstruction> result = std::make_unique<RegisterInstruction>();

  result->type_ = type;

  if (tokens.front().GetType() != TokenType::LEFT_ARROW)
    throw SyntaxError("expected '<-' at register assignment",
        tokens.front().GetLine(),
        tokens.front().GetColumn());
  tokens.pop_front();

  result->value_ = std::move(Expression::Construct(tokens, false, true, false));

  if (tokens.front().GetType() != TokenType::SEMICOLON)
    throw SyntaxError("expected ';' at end of register assignment",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  tokens.pop_front();

  return result;
}

std::string RegisterInstruction::Generate() {
  std::ostringstream oss;

  oss << value_->Generate(false);

  if (type_ == RegisterType::RAX) {
    oss << "\tmov\trax, rax";
  }
  else if (type_ == RegisterType::RBX) {
    oss << "\tmov\trbx, rax";
  }
  else if (type_ == RegisterType::RCX) {
    oss << "\tmov\trcx, rax";
  }
  else if (type_ == RegisterType::RDX) {
    oss << "\tmov\trdx, rax";
  }
  else if (type_ == RegisterType::RSI) {
    oss << "\tmov\trsi, rax";
  }
  else if (type_ == RegisterType::RDI) {
    oss << "\tmov\trdi, rax";
  }

  oss << "\n";
  if (more_)
    oss << more_->Generate();

  return oss.str();
}

void RegisterInstruction::Semanticate() {
  value_->Semanticate();

  if (more_)
    more_->Semanticate();
}

}
