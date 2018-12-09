/**
 * @file type_parameter.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <analyzer/semantic_analyzer.h>
#include <core/semantic_error.h>
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

void TypeParameter::GetArgument(std::list<cassio::Argument> &args) {
  Argument arg = {};
  arg.name_ = identifier_->GetText();

  if (type_ == ParameterType::BYTE) {
    arg.type_ = "byte";
    arg.offset_ = 1;
  }
  else if (type_ == ParameterType::WORD) {
    arg.type_ = "word";
    arg.offset_ = 2;
  }
  else if (type_ == ParameterType::DWORD) {
    arg.type_ = "dword";
    arg.offset_ = 4;
  }
  else if (type_ == ParameterType::QWORD) {
    arg.type_ = "qword";
    arg.offset_ = 8;
  }

  for (auto& a: args) {
    if (a.name_ == identifier_->GetText())
      throw SemanticError("parameter " + identifier_->GetText() + " already defined in the same function");
  }
  args.emplace_back(arg);

  if (more_)
    more_->GetArgument(args);
}


void TypeParameter::Semanticate() {
  if (SemanticAnalyzer::variables_.find(identifier_->GetText()) != SemanticAnalyzer::variables_.end())
    throw SemanticError("parameter " + identifier_->GetText() + " already exists as variable");

  if (more_)
    more_->Semanticate();
}

}
