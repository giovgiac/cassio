/**
 * @file output_instruction.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <core/syntax_error.h>
#include <expressions/string_expression.h>
#include <function/output_instruction.h>

namespace cassio {

std::unique_ptr<Instruction> OutputInstruction::Construct(OutputType type, std::list<Token> &tokens) {
  std::unique_ptr<OutputInstruction> result = std::make_unique<OutputInstruction>();

  if (tokens.front().GetType() != TokenType::LEFT_PARENTHESIS)
    throw SyntaxError("expected '(' at output instruction",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  tokens.pop_front();

  result->type_ = type;
  result->argument_ = std::move(Expression::Construct(tokens, false, true, false));

  if (tokens.front().GetType() != TokenType::RIGHT_PARENTHESIS)
    throw SyntaxError("expected ')' at output instruction",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  tokens.pop_front();

  if (tokens.front().GetType() != TokenType::SEMICOLON)
    throw SyntaxError("expected ';' at end of output instruction",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  tokens.pop_front();

  return result;
}

std::string OutputInstruction::Generate() {
  std::ostringstream oss;

  oss << argument_->Generate(false);

  if (type_ == OutputType::INTEGER) {
    oss << "\tmov\trdi, print_integer_fmt";
    oss << "\n";
  }
  else {
    oss << "\tmov\trdi, print_string_fmt";
    oss << "\n";
  }

  oss << "\tmov\trsi, rax";
  oss << "\n";
  oss << "\tcall\t[printf]";
  oss << "\n";

  if (more_)
    oss << more_->Generate();

  return oss.str();
}

void OutputInstruction::Semanticate() {
  argument_->Semanticate();

  if (more_)
    more_->Semanticate();
}

}
