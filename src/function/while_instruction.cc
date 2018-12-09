/**
 * @file while_instruction.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <core/syntax_error.h>
#include <function/while_instruction.h>

namespace cassio {

uint64_t WhileInstruction::global_id = 0;

std::unique_ptr<Instruction> WhileInstruction::Construct(std::list<Token> &tokens) {
  std::unique_ptr<WhileInstruction> result = std::make_unique<WhileInstruction>();
  result->id_ = global_id++;

  if (tokens.front().GetType() != TokenType::LEFT_PARENTHESIS)
    throw SyntaxError("expected '(' at while instruction",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  tokens.pop_front();

  std::unique_ptr<Expression> first = std::move(Expression::Construct(tokens));
  result->condition_ = std::move(LogicalExpression::Construct(tokens, std::move(first)));

  if (tokens.front().GetType() != TokenType::RIGHT_PARENTHESIS)
    throw SyntaxError("expected ')' at while instruction",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  tokens.pop_front();

  if (tokens.front().GetType() != TokenType::LEFT_BRACKET)
    throw SyntaxError("expected '{' at while instruction",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  tokens.pop_front();

  result->instruction_ = std::move(Instruction::Construct(tokens));

  if (tokens.front().GetType() != TokenType::RIGHT_BRACKET)
    throw SyntaxError("expected '}' at while instruction",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  tokens.pop_front();

  if (tokens.front().GetType() != TokenType::SEMICOLON)
    throw SyntaxError("expected ';' at end of while instruction",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  tokens.pop_front();

  return result;
}

std::string WhileInstruction::Generate() {
  std::ostringstream oss;

  oss << "\n";
  oss << "while_cond" << id_ << ":";
  oss << "\n";
  oss << condition_->Generate(false) << "while_body" << id_;
  oss << "\n";
  oss << "\tjmp\t" << "while_end" << id_;
  oss << "\n";
  oss << "\n";

  oss << "while_body" << id_ << ":";
  oss << "\n";
  if (instruction_) {
    oss << instruction_->Generate();
  }
  oss << "\tjmp\t" << "while_cond" << id_;
  oss << "\n";
  oss << "\n";

  oss << "while_end" << id_ << ":";
  oss << "\n";
  if (more_)
    oss << more_->Generate();

  return oss.str();
}

void WhileInstruction::Semanticate() {
  condition_->Generate(false);

  if (instruction_)
    instruction_->Semanticate();

  if (more_)
    more_->Semanticate();
}

}
