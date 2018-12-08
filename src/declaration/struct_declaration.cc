/**
 * @file struct_declaration.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <analyzer/semantic_analyzer.h>
#include <core/semantic_error.h>
#include <core/syntax_error.h>
#include <declaration/struct_declaration.h>

namespace cassio {

std::unique_ptr<Declaration> StructDeclaration::Construct(std::list<Token> &tokens) {
  std::unique_ptr<StructDeclaration> result = std::make_unique<StructDeclaration>();

  if (tokens.front().GetType() != TokenType::IDENTIFIER) throw std::runtime_error("Syntax Error");
  result->identifier_ = std::move(Identifier::Construct(tokens.front().GetText()));
  tokens.pop_front();

  if (tokens.front().GetType() != TokenType::LEFT_BRACKET) throw std::runtime_error("Syntax Error");
  tokens.pop_front();
  result->inner_declaration_ = std::move(Declaration::Construct(tokens));

  if (tokens.front().GetType() != TokenType::RIGHT_BRACKET) throw std::runtime_error("Syntax Error");
  tokens.pop_front();

  if (tokens.front().GetType() != TokenType::SEMICOLON)
    throw SyntaxError("expected ';' at end of struct declaration",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  tokens.pop_front();
  result->declaration_ = std::move(Declaration::Construct(tokens));

  return result;
}

std::string StructDeclaration::Generate() {
  if (SemanticAnalyzer::user_types_.find(identifier_->GetText()) != SemanticAnalyzer::user_types_.end()) {
    auto tp = SemanticAnalyzer::user_types_[identifier_->GetText()];
    std::ostringstream oss;

    oss << "struct " << tp.name_ << "\n";
    for (auto& sbtp : tp.members_) {
      oss << "\t" << sbtp.name_ << "\t\t";
      if (sbtp.capacity_ == 0) {
        if (sbtp.type_ == DataType::BYTE)
          oss << "db";
        else if (sbtp.type_ == DataType::WORD)
          oss << "dw";
        else if (sbtp.type_ == DataType::DWORD)
          oss << "dd";
        else if (sbtp.type_ == DataType::QWORD)
          oss << "dq";
        oss << " ?\n";
      }
      else {
        if (sbtp.type_ == DataType::BYTE)
          oss << "db " << sbtp.capacity_ << " dup ";
        else if (sbtp.type_ == DataType::WORD)
          oss << "dw " << sbtp.capacity_ << " dup ";
        else if (sbtp.type_ == DataType::DWORD)
          oss << "dd " << sbtp.capacity_ << " dup ";
        else if (sbtp.type_ == DataType::QWORD)
          oss << "dq " << sbtp.capacity_ << " dup ";
        oss << "(?)\n";
      }
    }
    oss << "ends\n\n";

    if (declaration_)
      oss << declaration_->Generate();

    return oss.str();
  }
  else {
    throw SemanticError("user-defined type " + identifier_->GetText() + " is not defined");
  }
}

void StructDeclaration::Semanticate() {
  if (SemanticAnalyzer::user_types_.find(identifier_->GetText()) == SemanticAnalyzer::user_types_.end()) {
    std::list<MemberType> members;
    inner_declaration_->RetrieveType(members);

    UserType type = {};
    type.name_ = identifier_->GetText() + "Structure";
    type.members_ = members;

    SemanticAnalyzer::user_types_.emplace(std::make_pair(identifier_->GetText(), type));

    if (declaration_)
      declaration_->Semanticate();
  }
  else {
    throw SemanticError("user-defined type " + identifier_->GetText() + " is being defined multiple times");
  }
}

void StructDeclaration::RetrieveType(std::list<MemberType> &sub_types) {
  throw SemanticError("user-defined declarations cannot be contained within other user-defined declarations");
}

}

