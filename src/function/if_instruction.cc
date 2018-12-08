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

std::unique_ptr<Instruction> IfInstruction::Construct(std::list<Token> &tokens) {
  std::unique_ptr<IfInstruction> result = std::make_unique<IfInstruction>();

  if (tokens.front().GetType() != TokenType::LEFT_PARENTHESIS)
    throw SyntaxError("expected '(' at if instruction",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  tokens.pop_front();

  result->condition_ = std::move(Expression::Construct(tokens, false, false, false));

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

}

void IfInstruction::Semanticate() {

}

}
