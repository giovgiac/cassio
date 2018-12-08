/**
 * @file instruction.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <core/syntax_error.h>
#include <function/instruction.h>
#include <function/if_instruction.h>
#include <function/register_instruction.h>
#include <function/return_instruction.h>
#include <function/value_instruction.h>
#include <function/variable_instruction.h>
#include <function/while_instruction.h>

namespace cassio {

std::unique_ptr<Instruction> Instruction::Construct(std::list<Token> &tokens) {
  std::unique_ptr<Instruction> result = nullptr;
  TokenType type = tokens.front().GetType();

  if (type == TokenType::IF) {
    tokens.pop_front();

    result = std::move(IfInstruction::Construct(tokens));
  }
  else if (type == TokenType::WHILE) {
    tokens.pop_front();

    result = std::move(WhileInstruction::Construct(tokens));
  }
  else if (type == TokenType::IDENTIFIER) {
    result = std::move(VariableInstruction::Construct(tokens));
  }
  else if (type == TokenType::LEFT_BRACE) {
    tokens.pop_front();

    result = std::move(ValueInstruction::Construct(tokens));
  }
  else if (type == TokenType::RAX ||
           type == TokenType::RBX ||
           type == TokenType::RCX ||
           type == TokenType::RDX ||
           type == TokenType::RSI ||
           type == TokenType::RDI) {
    tokens.pop_front();

    result = std::move(RegisterInstruction::Construct(tokens, ConvertToRegisterType(type)));
  }
  else if (type == TokenType::RETURN) {
    tokens.pop_front();

    result = std::move(ReturnInstruction::Construct(tokens));
  }
  else {
    return nullptr;
  }

  result->more_ = std::move(Instruction::Construct(tokens));

  return result;
}

}
