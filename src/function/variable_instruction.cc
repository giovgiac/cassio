/**
 * @file variable_instruction.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <core/semantic_error.h>
#include <core/syntax_error.h>
#include <function/variable_instruction.h>

namespace cassio {

std::unique_ptr<Instruction> VariableInstruction::Construct(std::list<Token> &tokens) {
  std::unique_ptr<VariableInstruction> result = std::make_unique<VariableInstruction>();

  result->variable_ = std::move(Child::Construct(tokens));

  if (tokens.front().GetType() == TokenType::LEFT_ARROW) {
    tokens.pop_front();

    result->type_ = VariableInstructionType::ASSIGNMENT;
    result->value_ = std::move(Expression::Construct(tokens, false, true, false));
  }
  else if (tokens.front().GetType() == TokenType::LEFT_PARENTHESIS) {
    tokens.pop_front();

    result->type_ = VariableInstructionType::FUNCTION_CALL;
    result->value_ = std::move(Expression::Construct(tokens, true, true, true));

    if (tokens.front().GetType() != TokenType::RIGHT_PARENTHESIS)
      throw SyntaxError("expected ')' at end of function call",
                        tokens.front().GetLine(),
                        tokens.front().GetColumn());
    tokens.pop_front();
  }
  else {
    throw SyntaxError("no assignment or function call at end of variable",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  }

  if (tokens.front().GetType() != TokenType::SEMICOLON)
    throw SyntaxError("expected ';'",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  tokens.pop_front();

  return result;
}

std::string VariableInstruction::Generate() {
  if (type_ == VariableInstructionType::ASSIGNMENT) {
    throw SemanticError("cannot assign to address");
  }
  else {

  }
}

void VariableInstruction::Semanticate() {
  variable_->Semanticate();



  if (value_)
    value_->Semanticate();

  if (more_)
    more_->Semanticate();
}

}
