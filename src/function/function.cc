/**
 * @file function.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <analyzer/semantic_analyzer.h>
#include <core/semantic_error.h>
#include <core/syntax_error.h>
#include <function/function.h>

namespace cassio {

ReturnType ConvertToReturnType(TokenType type) {
  switch (type) {
    case TokenType::BYTE:
      return ReturnType::BYTE;
    case TokenType::WORD:
      return ReturnType::WORD;
    case TokenType::DWORD:
      return ReturnType::DWORD;
    case TokenType::QWORD:
      return ReturnType::QWORD;
    default:
      throw std::runtime_error("Invalid Request For Conversion");
  }
}

std::string GetReturnType(ReturnType type) {
  switch (type) {
    case ReturnType::BYTE:
      return "byte";
    case ReturnType::WORD:
      return "word";
    case ReturnType::DWORD:
      return "dword";
    case ReturnType::QWORD:
      return "qword";
    case ReturnType::VOID:
      return "void";
    default:
      throw std::runtime_error("Invalid Request for Conversion");
  }
}

std::unique_ptr<Function> Function::Construct(std::list<Token> &tokens) {
  std::unique_ptr<Function> result = nullptr;

  if (tokens.front().GetType() == TokenType::FUNCTION) {
    tokens.pop_front();

    result = std::make_unique<Function>();

    if (tokens.front().GetType() != TokenType::IDENTIFIER)
      throw SyntaxError("expected identifier at function declaration",
                        tokens.front().GetLine(),
                        tokens.front().GetColumn());
    result->identifier_ = std::move(Identifier::Construct(tokens.front().GetText()));
    tokens.pop_front();

    if (tokens.front().GetType() != TokenType::LEFT_PARENTHESIS)
      throw SyntaxError("expected '(' at function declaration",
                        tokens.front().GetLine(),
                        tokens.front().GetColumn());
    tokens.pop_front();

    result->parameter_ = std::move(Parameter::Construct(tokens));

    if (tokens.front().GetType() != TokenType::RIGHT_PARENTHESIS)
      throw SyntaxError("expected ')' at function declaration",
                        tokens.front().GetLine(),
                        tokens.front().GetColumn());
    tokens.pop_front();

    if (tokens.front().GetType() == TokenType::LEFT_ARROW) {
      tokens.pop_front();

      if (tokens.front().GetType() == TokenType::BYTE ||
          tokens.front().GetType() == TokenType::WORD ||
          tokens.front().GetType() == TokenType::DWORD ||
          tokens.front().GetType() == TokenType::QWORD) {

        result->return_type_ = ConvertToReturnType(tokens.front().GetType());
        tokens.pop_front();
      }
      else {
        throw SyntaxError("unexpected token at function declaration",
                          tokens.front().GetLine(),
                          tokens.front().GetColumn());
      }
    }
    else if (tokens.front().GetType() == TokenType::LEFT_BRACKET) {
      result->return_type_ = ReturnType::VOID;
    }
    else {
      throw SyntaxError("unexpected token at function declaration",
                        tokens.front().GetLine(),
                        tokens.front().GetColumn());
    }

    if (tokens.front().GetType() != TokenType::LEFT_BRACKET)
      throw SyntaxError("expected '{' at function declaration",
                        tokens.front().GetLine(),
                        tokens.front().GetColumn());
    tokens.pop_front();

    result->instruction_ = std::move(Instruction::Construct(tokens));

    if (tokens.front().GetType() != TokenType::RIGHT_BRACKET)
      throw SyntaxError("expected '}' at function declaration",
                        tokens.front().GetLine(),
                        tokens.front().GetColumn());
    tokens.pop_front();

    if (tokens.front().GetType() != TokenType::SEMICOLON)
      throw SyntaxError("expected ';' at function declaration",
                        tokens.front().GetLine(),
                        tokens.front().GetColumn());
    tokens.pop_front();

    result->function_ = std::move(Function::Construct(tokens));
  }

  return result;
}

std::string Function::Generate() {
  if (SemanticAnalyzer::functions_.find(identifier_->GetText()) != SemanticAnalyzer::functions_.end()) {
    auto var = SemanticAnalyzer::functions_[identifier_->GetText()];
    std::ostringstream oss;

    oss << var.name_ << ":";
    oss << "\n";

    if (instruction_)
      oss << instruction_->Generate();

    if (var.name_ == "cassio") {
      oss << "\tcall\t[exit]";
      oss << "\n";
    }
    else {
      oss << "\tret";
      oss << "\n";
    }

    oss << "\n";
    if (function_)
      oss << function_->Generate();

    return oss.str();
  }
  else {
    throw SemanticError("function " + identifier_->GetText() + " is not defined");
  }
}

void Function::Semanticate() {
  if (SemanticAnalyzer::functions_.find(identifier_->GetText()) == SemanticAnalyzer::functions_.end()) {
    Procedure procedure = {};

    if (identifier_->GetText() == "cassio")
      procedure.name_ = identifier_->GetText();
    else
      procedure.name_ = identifier_->GetText() + "Function";

    procedure.return_type_ = GetReturnType(return_type_);

    if (instruction_)
      instruction_->Semanticate();

    SemanticAnalyzer::functions_.emplace(std::make_pair(identifier_->GetText(), procedure));

    if (function_)
      function_->Semanticate();
  }
  else {
    throw SemanticError("function " + identifier_->GetText() + " is being defined multiple times");
  }
}

}