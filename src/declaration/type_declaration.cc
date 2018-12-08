/**
 * @file type_declaration.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <analyzer/semantic_analyzer.h>
#include <core/semantic_error.h>
#include <declaration/type_declaration.h>

namespace cassio {

std::string ExtractType(DataType type) {
  switch (type) {
    case DataType::BYTE:
      return "byte";
    case DataType::WORD:
      return "word";
    case DataType::DWORD:
      return "dword";
    case DataType::QWORD:
      return "qword";
    default:
      throw std::runtime_error("Invalid Request For Conversion");
  }
}

std::unique_ptr<Declaration> TypeDeclaration::Construct(std::list<Token> &tokens, DataType type) {
  std::unique_ptr<TypeDeclaration> result = std::make_unique<TypeDeclaration>();

  result->type_ = type;

  if (tokens.front().GetType() != TokenType::IDENTIFIER) throw std::runtime_error("Syntax Error");
  result->identifier_ = std::move(Identifier::Construct(tokens.front().GetText()));
  tokens.pop_front();

  result->capacity_ = std::move(Capacity::Construct(tokens));

  if (tokens.front().GetType() != TokenType::SEMICOLON) throw std::runtime_error("Syntax Error");
  tokens.pop_front();

  result->declaration_ = std::move(Declaration::Construct(tokens));

  return result;
}

std::string TypeDeclaration::Generate() {
  if (SemanticAnalyzer::variables_.find(identifier_->GetText()) != SemanticAnalyzer::variables_.end()) {
    auto var = SemanticAnalyzer::variables_[identifier_->GetText()];
    std::ostringstream oss;

    oss << "\t" << var.name_;

    if (var.capacity_ == 0) {
      if (var.type_ == "byte")
        oss << "\t\tdb ?\n";
      else if (var.type_ == "word")
        oss << "\t\tdw ?\n";
      else if (var.type_ == "dword")
        oss << "\t\tdd ?\n";
      else if (var.type_ == "qword")
        oss << "\t\tdq ?\n";
    }
    else {
      if (var.type_ == "byte")
        oss << "\t\tdb " << var.capacity_ << " dup " << "(?)\n";
      else if (var.type_ == "word")
        oss << "\t\tdw " << var.capacity_ << " dup " << "(?)\n";
      else if (var.type_ == "dword")
        oss << "\t\tdd " << var.capacity_ << " dup " << "(?)\n";
      else if (var.type_ == "qword")
        oss << "\t\tdq " << var.capacity_ << " dup " << "(?)\n";
    }

    if (declaration_)
      oss << declaration_->Generate();

    return oss.str();
  }
  else {
    throw SemanticError("variable " + identifier_->GetText() + " is not defined");
  }
}

void TypeDeclaration::Semanticate() {
  if (SemanticAnalyzer::variables_.find(identifier_->GetText()) == SemanticAnalyzer::variables_.end()) {
    Variable variable = {};
    variable.name_ = identifier_->GetText() + "Variable";
    variable.type_ = ExtractType(type_);

    if (capacity_ == nullptr)
      variable.capacity_ = 0;
    else
      variable.capacity_ = capacity_->GetCapacity();

    SemanticAnalyzer::variables_.emplace(std::make_pair(identifier_->GetText(), variable));

    if (declaration_)
      declaration_->Semanticate();
  }
  else {
    throw SemanticError("variable " + identifier_->GetText() + " is being defined multiple times");
  }
}

void TypeDeclaration::RetrieveType(std::list<MemberType> &sub_types) {
  MemberType type = {};
  type.name_ = identifier_->GetText();
  type.type_ = type_;

  if (capacity_ == nullptr)
    type.capacity_ = 0;
  else
    type.capacity_ = capacity_->GetCapacity();

  sub_types.emplace_back(type);

  if (declaration_)
    declaration_->RetrieveType(sub_types);
}

}
