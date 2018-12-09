/**
 * @file input_expression.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <core/syntax_error.h>
#include <expressions/input_expression.h>

namespace cassio {

std::unique_ptr<Expression> InputExpression::Construct(cassio::InputType type, std::list<cassio::Token> &tokens) {
  std::unique_ptr<InputExpression> result = std::make_unique<InputExpression>();
  result->type_ = type;

  if (tokens.front().GetType() != TokenType::LEFT_PARENTHESIS)
    throw SyntaxError("expected '(' at output instruction",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  tokens.pop_front();

  if (tokens.front().GetType() != TokenType::RIGHT_PARENTHESIS)
    throw SyntaxError("expected ')' at output instruction",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  tokens.pop_front();

  return result;
}

std::string InputExpression::Generate(bool generate_more) {
  std::ostringstream oss;

  if (type_ == InputType::INTEGER) {
    oss << "\tmov\trdi, scanf_integer_fmt";
    oss << "\n";
    oss << "\tmov\trsi, scanf_read";
    oss << "\n";
    oss << "\tcall\t[scanf]";
    oss << "\n";
    oss << "\tmov\trax, qword [scanf_read]";
    oss << "\n";
  }
  else {
    oss << "\tmov\trdi, scanf_string_fmt";
    oss << "\n";
    oss << "\tmov\trsi, scanf_read";
    oss << "\n";
    oss << "\tcall\t[scanf]";
    oss << "\n";
    oss << "\tmov\trax, scanf_read";
    oss << "\n";
  }

  if (generate_more) {
    if (more_)
      oss << more_->Generate();
  }

  return oss.str();
}

void InputExpression::Semanticate() {
  if (more_)
    more_->Semanticate();
}

}
