/**
 * @file type_parameter.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <core/syntax_error.h>
#include <function/type_parameter.h>

namespace cassio {

std::unique_ptr<Parameter> TypeParameter::Construct(std::list<Token> &tokens, ParameterType type) {
  std::unique_ptr<TypeParameter> result = std::make_unique<TypeParameter>();

  result->type_ = type;

  if (tokens.front().GetType() != TokenType::IDENTIFIER)
    throw SyntaxError("expected identifier",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());

  result->identifier_ = std::move(Identifier::Construct(tokens.front().GetText()));
  tokens.pop_front();

  return result;
}

}
