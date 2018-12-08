/**
 * @file declaration.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <declaration/declaration.h>
#include <declaration/defined_declaration.h>
#include <declaration/struct_declaration.h>
#include <declaration/type_declaration.h>

namespace cassio {

DataType ConvertToDataType(TokenType type) {
  switch (type) {
    case TokenType::BYTE:
      return DataType::BYTE;
    case TokenType::WORD:
      return DataType::WORD;
    case TokenType::DWORD:
      return DataType::DWORD;
    case TokenType::QWORD:
      return DataType::QWORD;
    default:
      throw std::runtime_error("Invalid Request For Conversion");
  }
}

std::unique_ptr<Declaration> Declaration::Construct(std::list<Token> &tokens) {
  std::unique_ptr<Declaration> result = nullptr;
  TokenType type = tokens.front().GetType();

  if (type == TokenType::STRUCT) {
    tokens.pop_front();
    result = std::move(StructDeclaration::Construct(tokens));
  }
  else if (type == TokenType::BYTE  ||
           type == TokenType::WORD  ||
           type == TokenType::DWORD ||
           type == TokenType::QWORD) {
    tokens.pop_front();
    result = std::move(TypeDeclaration::Construct(tokens, ConvertToDataType(type)));
  }
  else if (type == TokenType::IDENTIFIER) {
    result = std::move(DefinedDeclaration::Construct(tokens));
  }

  return result;
}

}
