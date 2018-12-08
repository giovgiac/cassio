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

std::unique_ptr<Instruction> WhileInstruction::Construct(std::list<Token> &tokens) {
  std::unique_ptr<WhileInstruction> result = std::make_unique<WhileInstruction>();

  if (tokens.front().GetType() != TokenType::LEFT_PARENTHESIS)
    throw SyntaxError("expected '(' at while instruction",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  tokens.pop_front();

  result->condition_ = std::move(Expression::Construct(tokens, false, false, false));

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

}

void WhileInstruction::Semanticate() {

}

}
