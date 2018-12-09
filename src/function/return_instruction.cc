/**
 * @file return_instruction.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <analyzer/semantic_analyzer.h>
#include <core/semantic_error.h>
#include <core/syntax_error.h>
#include <function/return_instruction.h>

namespace cassio {

std::unique_ptr<Instruction> ReturnInstruction::Construct(std::list<Token> &tokens) {
  std::unique_ptr<ReturnInstruction> result = std::make_unique<ReturnInstruction>();

  result->expression_ = std::move(Expression::Construct(tokens, false, true, false));

  if (tokens.front().GetType() != TokenType::SEMICOLON)
    throw SyntaxError("expected ';' at end of return instruction",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  tokens.pop_front();

  return result;
}

std::string ReturnInstruction::Generate() {
  std::ostringstream oss;

  oss << expression_->Generate(false);
  oss << "\tmov\trsp, rbp";
  oss << "\n";
  oss << "\tpop\trbp";
  oss << "\n";
  oss << "\tret";
  oss << "\n";

  if (more_)
    oss << more_->Generate();

  return oss.str();
}

void ReturnInstruction::Semanticate() {
  if (SemanticAnalyzer::functions_[SemanticAnalyzer::current_function_].return_type_ == "void")
    throw SemanticError("cannot return from a void function");

  if (expression_)
    expression_->Semanticate();

  if (more_)
    more_->Semanticate();
}

}
