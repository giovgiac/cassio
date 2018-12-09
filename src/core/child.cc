/**
 * @file child.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <analyzer/semantic_analyzer.h>
#include <core/semantic_error.h>
#include <core/syntax_error.h>
#include <core/child.h>

namespace cassio {

std::unique_ptr<Child> Child::Construct(std::list<Token> &tokens) {
  std::unique_ptr<Child> result = std::make_unique<Child>();
  result->is_parameter = false;

  if (tokens.front().GetType() != TokenType::IDENTIFIER)
    throw SyntaxError("expected identifier",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  result->parent_ = std::move(Identifier::Construct(tokens.front().GetText()));
  tokens.pop_front();

  if (tokens.front().GetType() == TokenType::DOT) {
    tokens.pop_front();
    result->child_ = std::move(Child::Construct(tokens));
  }
  else {
    result->child_ = nullptr;
  }

  return result;
}

std::string Child::Generate() {
  std::ostringstream oss;

  if (!is_parameter) {
    if (child_) {
      oss << SemanticAnalyzer::variables_[parent_->GetText()].name_;
      oss << "." << child_->parent_->GetText();
    } else {
      oss << SemanticAnalyzer::variables_[parent_->GetText()].name_;
    }
  }
  else {
    auto var = SemanticAnalyzer::functions_[SemanticAnalyzer::current_function_];

    uint64_t max_offset = 0;
    for (auto& a: var.argument_)
      max_offset += 8;

    uint64_t cummulative_offset = 0;
    for (auto& a: var.argument_) {
      if (parent_->GetText() == a.name_) {
        uint64_t off = max_offset - cummulative_offset + 8;
        oss << "rbp + " << off;
      }

      cummulative_offset += 8;
    }
  }

  return oss.str();
}

std::string Child::GetName() const {
  return parent_->GetText();
}

std::string Child::GetType() const {
  if (child_) {
    auto var = SemanticAnalyzer::variables_[parent_->GetText()];
    auto tp = SemanticAnalyzer::user_types_[var.type_];

    for (auto& mb : tp.members_) {
      if (mb.name_ == child_->parent_->GetText()) {
        switch (mb.type_) {
          case DataType::BYTE:
            return "byte";
          case DataType::WORD:
            return "word";
          case DataType::DWORD:
            return "dword";
          case DataType::QWORD:
            return "qword";
        }
      }
    }

    return "";
  }
  else {
    if (SemanticAnalyzer::variables_.find(parent_->GetText()) != SemanticAnalyzer::variables_.end()) {
      return SemanticAnalyzer::variables_[parent_->GetText()].type_;
    }
    else {
      if (!SemanticAnalyzer::current_function_.empty()) {
        auto var = SemanticAnalyzer::functions_[SemanticAnalyzer::current_function_];

        for (auto& a: var.argument_) {
          if (parent_->GetText() == a.name_) {
            return a.type_;
          }
        }
      }
    }
  }

  return "";
}

void Child::Semanticate(bool is_variable) {
  if (SemanticAnalyzer::variables_.find(parent_->GetText()) != SemanticAnalyzer::variables_.end()) {
    auto var = SemanticAnalyzer::variables_[parent_->GetText()];

    if (child_) {
      auto tp = SemanticAnalyzer::user_types_[var.type_];
      bool found = false;

      for (auto &mb : tp.members_) {
        if (mb.name_ == child_->parent_->GetText())
          found = true;
      }

      if (!found) {
        throw SemanticError(child_->parent_->GetText() + " is not a member of " + var.type_);
      }
    }
  }
  else if (SemanticAnalyzer::functions_.find(parent_->GetText()) != SemanticAnalyzer::functions_.end()) {
    if (child_) {
      throw SemanticError("function cannot have child");
    }
  }
  else {
    if (!SemanticAnalyzer::current_function_.empty()) {
      auto var = SemanticAnalyzer::functions_[SemanticAnalyzer::current_function_];
      bool found = false;

      for (auto& a: var.argument_) {
        if (parent_->GetText() == a.name_) {
          found = true;
          is_parameter = true;
          break;
        }
      }

      if (is_variable)
        throw SemanticError("cannot use parameter `" + parent_->GetText() + "` address");

      if (!found)
        throw SemanticError(parent_->GetText() + " is not defined");
    }
    else {
      throw SemanticError(parent_->GetText() + " is not defined");
    }
  }
}

}
