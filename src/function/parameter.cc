/**
 * @file parameter.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <core/syntax_error.h>
#include <function/parameter.h>
#include <function/register_parameter.h>
#include <function/type_parameter.h>

namespace cassio {

ParameterRegister ConvertToParameterRegister(TokenType type) {
  switch (type) {
    case TokenType::RAX:
      return ParameterRegister::RAX;
    case TokenType::RBX:
      return ParameterRegister::RBX;
    case TokenType::RCX:
      return ParameterRegister::RCX;
    case TokenType::RDX:
      return ParameterRegister::RDX;
    case TokenType::RSI:
      return ParameterRegister::RSI;
    case TokenType::RDI:
      return ParameterRegister::RDI;
    default:
      throw std::runtime_error("Invalid Request For Conversion");
  }
}

ParameterType ConvertToParameterType(TokenType type) {
  switch (type) {
    case TokenType::BYTE:
      return ParameterType::BYTE;
    case TokenType::WORD:
      return ParameterType::WORD;
    case TokenType::DWORD:
      return ParameterType::DWORD;
    case TokenType::QWORD:
      return ParameterType::QWORD;
    default:
      throw std::runtime_error("Invalid Request For Conversion");
  }
}

std::unique_ptr<Parameter> Parameter::Construct(std::list<Token> &tokens, bool can_be_empty) {
  std::unique_ptr<Parameter> result = nullptr;
  TokenType type = tokens.front().GetType();

  if (type == TokenType::BYTE ||
      type == TokenType::WORD ||
      type == TokenType::DWORD ||
      type == TokenType::QWORD) {

    tokens.pop_front();
    result = TypeParameter::Construct(tokens, ConvertToParameterType(type));
  }
  else if (type == TokenType::RAX ||
           type == TokenType::RBX ||
           type == TokenType::RCX ||
           type == TokenType::RDX ||
           type == TokenType::RSI ||
           type == TokenType::RDI) {

    tokens.pop_front();
    result = RegisterParameter::Construct(tokens, ConvertToParameterRegister(type));
  }
  else {
    if (can_be_empty) {
      return result;
    }
    else {
      throw SyntaxError("expected parameter",
                        tokens.front().GetLine(),
                        tokens.front().GetColumn());
    }
  }

  if (tokens.front().GetType() == TokenType::COMMA) {
    tokens.pop_front();
    result->more_ = Parameter::Construct(tokens, false);
  }
  else {
    result->more_ = nullptr;
  }

  return result;
}

}
