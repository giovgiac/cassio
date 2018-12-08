/**
 * @file defined_declaration.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <analyzer/semantic_analyzer.h>
#include <core/semantic_error.h>
#include <core/syntax_error.h>
#include <declaration/defined_declaration.h>

namespace cassio {

std::unique_ptr<Declaration> DefinedDeclaration::Construct(std::list<Token> &tokens) {
  std::unique_ptr<DefinedDeclaration> result = std::make_unique<DefinedDeclaration>();

  result->type_ = std::move(Identifier::Construct(tokens.front().GetText()));
  tokens.pop_front();

  if (tokens.front().GetType() != TokenType::IDENTIFIER)
      throw SyntaxError("expected identifier at declaration",
          tokens.front().GetLine(),
          tokens.front().GetColumn());
  result->identifier_ = std::move(Identifier::Construct(tokens.front().GetText()));
  tokens.pop_front();

  result->capacity_ = std::move(Capacity::Construct(tokens));

  if (tokens.front().GetType() != TokenType::SEMICOLON) throw std::runtime_error("Syntax Error");
  tokens.pop_front();
  result->declaration_ = std::move(Declaration::Construct(tokens));

  return result;
}

std::string DefinedDeclaration::Generate() {
  if (SemanticAnalyzer::variables_.find(identifier_->GetText()) != SemanticAnalyzer::variables_.end()) {
    if (SemanticAnalyzer::user_types_.find(type_->GetText()) != SemanticAnalyzer::user_types_.end()) {
      auto var = SemanticAnalyzer::variables_[identifier_->GetText()];
      auto tp = SemanticAnalyzer::user_types_[type_->GetText()];
      std::ostringstream oss;

      oss << "\t" << var.name_;
      oss << "\t\t" << tp.name_;

      if (var.capacity_ == 0)
        oss << " ?\n";
      else {
        throw SemanticError("user-defined declarations can't be vectors");
      }

      if (declaration_)
        oss << declaration_->Generate();

      return oss.str();
    }
    else {
      throw SemanticError("user-defined type " + type_->GetText() + " is not defined");
    }
  }
  else {
    throw SemanticError("variable " + identifier_->GetText() + " is not defined");
  }
}

void DefinedDeclaration::Semanticate() {
  if (SemanticAnalyzer::variables_.find(identifier_->GetText()) == SemanticAnalyzer::variables_.end()) {
    Variable variable = {};
    variable.name_ = identifier_->GetText() + "Variable";
    variable.type_ = type_->GetText();

    if (capacity_ == nullptr)
      variable.capacity_ = 0;
    else {
      throw SemanticError("user-defined declarations cannot be arrays");
    }

    SemanticAnalyzer::variables_.emplace(std::make_pair(identifier_->GetText(), variable));

    if (declaration_)
      declaration_->Semanticate();
  }
  else {
    throw SemanticError("variable " + identifier_->GetText() + " is being defined multiple times");
  }
}

void DefinedDeclaration::RetrieveType(std::list<MemberType> &sub_types) {
  throw SemanticError("user-defined declarations cannot be contained within other user-defined declarations");
}

}
