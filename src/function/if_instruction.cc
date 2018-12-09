/**
 * @file if_instruction.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <core/syntax_error.h>
#include <function/if_instruction.h>

namespace cassio {

uint64_t IfInstruction::global_id = 0;

std::unique_ptr<Instruction> IfInstruction::Construct(std::list<Token> &tokens) {
  std::unique_ptr<IfInstruction> result = std::make_unique<IfInstruction>();
  result->id_ = global_id++;

  if (tokens.front().GetType() != TokenType::LEFT_PARENTHESIS)
    throw SyntaxError("expected '(' at if instruction",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  tokens.pop_front();

  std::unique_ptr<Expression> first = std::move(Expression::Construct(tokens));
  result->condition_ = std::move(LogicalExpression::Construct(tokens, std::move(first)));

  if (tokens.front().GetType() != TokenType::RIGHT_PARENTHESIS)
    throw SyntaxError("expected ')' at if instruction",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  tokens.pop_front();

  if (tokens.front().GetType() != TokenType::LEFT_BRACKET)
    throw SyntaxError("expected '{' at if instruction",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  tokens.pop_front();

  result->instruction_ = std::move(Instruction::Construct(tokens));

  if (tokens.front().GetType() != TokenType::RIGHT_BRACKET)
    throw SyntaxError("expected '}' at if instruction",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  tokens.pop_front();

  if (tokens.front().GetType() != TokenType::SEMICOLON)
    throw SyntaxError("expected ';' at end of if instruction",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  tokens.pop_front();

  if (tokens.front().GetType() == TokenType::ELSE) {
    tokens.pop_front();

    if (tokens.front().GetType() != TokenType::LEFT_BRACKET)
      throw SyntaxError("expected '{' at else instruction",
                        tokens.front().GetLine(),
                        tokens.front().GetColumn());
    tokens.pop_front();

    result->else_ = std::move(Instruction::Construct(tokens));

    if (tokens.front().GetType() != TokenType::RIGHT_BRACKET)
      throw SyntaxError("expected '}' at else instruction",
                        tokens.front().GetLine(),
                        tokens.front().GetColumn());
    tokens.pop_front();

    if (tokens.front().GetType() != TokenType::SEMICOLON)
      throw SyntaxError("expected ';' at end of else instruction",
                        tokens.front().GetLine(),
                        tokens.front().GetColumn());
    tokens.pop_front();
  }
  else {
    result->else_ = nullptr;
  }

  return result;
}

std::string IfInstruction::Generate() {
  std::ostringstream oss;

  oss << condition_->Generate() << "if_body" << id_;
  oss << "\n";
  oss << "\tjmp\t" << "else_body" << id_;
  oss << "\n";

  oss << "if_body" << id_ << ":";
  oss << "\n";
  if (instruction_) {
    oss << instruction_->Generate();
  }
  oss << "\tjmp\t" << "if_end" << id_;
  oss << "\n";
  oss << "\n";

  oss << "else_body" << id_ << ":";
  oss << "\n";
  if (else_) {
    oss << else_->Generate();
  }
  oss << "\tjmp\t" << "if_end" << id_;
  oss << "\n";
  oss << "\n";

  oss << "if_end" << id_ << ":";
  oss << "\n";
  if (more_)
    oss << more_->Generate();

  return oss.str();
}

void IfInstruction::Semanticate() {
  condition_->Semanticate();

  if (instruction_)
    instruction_->Semanticate();

  if (else_)
    else_->Semanticate();

  if (more_)
    more_->Semanticate();
}

}
