/**
 * @file expression.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <core/syntax_error.h>
#include <expressions/expression.h>
#include <expressions/boolean_expression.h>
#include <expressions/function_expression.h>
#include <expressions/input_expression.h>
#include <expressions/logical_expression.h>
#include <expressions/low_expression.h>
#include <expressions/math_expression.h>
#include <expressions/not_expression.h>
#include <expressions/number_expression.h>
#include <expressions/string_expression.h>
#include <expressions/register_expression.h>
#include <expressions/value_expression.h>
#include <expressions/variable_expression.h>
#include <expressions/logical_expression.h>
#include <expressions/not_expression.h>

namespace cassio {

RegisterType ConvertToRegisterType(TokenType type) {
  switch (type) {
    case TokenType::RAX:
      return RegisterType::RAX;
    case TokenType::RBX:
      return RegisterType::RBX;
    case TokenType::RCX:
      return RegisterType::RCX;
    case TokenType::RDX:
      return RegisterType::RDX;
    case TokenType::RSI:
      return RegisterType::RSI;
    case TokenType::RDI:
      return RegisterType::RDI;
    default:
      throw std::runtime_error("Invalid Request For Conversion");
  }
}

std::unique_ptr<Expression> Expression::Construct(std::list<Token> &tokens,
                                                  bool can_be_empty,
                                                  bool can_have_string,
                                                  bool can_have_comma) {
  std::unique_ptr<Expression> result = nullptr;
  TokenType type = tokens.front().GetType();

  if (type == TokenType::IDENTIFIER) {
    size_t i{0};
    bool constructed = false;

    for (auto& tk : tokens) {
      if (i >= 1) {
        if (tk.GetType() == TokenType::LEFT_PARENTHESIS) {
          result = FunctionExpression::Construct(tokens);
          constructed = true;
          break;
        }
      }

      if (tk.GetType() == TokenType::DOT || tk.GetType() == TokenType::IDENTIFIER)
        ++i;
      else {
        result = VariableExpression::Construct(tokens);
        constructed = true;
        break;
      }
    }

    if (!constructed) {
      result = VariableExpression::Construct(tokens);
      constructed = true;
    }

    result = LowExpression::Construct(tokens, std::move(result));
    result = MathExpression::Construct(tokens, std::move(result));
    //result = LogicalExpression::Construct(tokens, std::move(result));
    result = BooleanExpression::Construct(tokens, std::move(result));
  }
  else if (type == TokenType::LEFT_BRACE) {
    tokens.pop_front();

    result = ValueExpression::Construct(tokens);

    if (tokens.front().GetType() != TokenType::RIGHT_BRACE)
      throw SyntaxError("expected ']' at value expression",
          tokens.front().GetLine(),
          tokens.front().GetColumn());

    tokens.pop_front();

    result = LowExpression::Construct(tokens, std::move(result));
    result = MathExpression::Construct(tokens, std::move(result));
    //result = LogicalExpression::Construct(tokens, std::move(result));
    result = BooleanExpression::Construct(tokens, std::move(result));
  }
  else if (type == TokenType::RAX ||
           type == TokenType::RBX ||
           type == TokenType::RCX ||
           type == TokenType::RDX ||
           type == TokenType::RSI ||
           type == TokenType::RDI) {

    tokens.pop_front();

    result = RegisterExpression::Construct(ConvertToRegisterType(type));
    result = LowExpression::Construct(tokens, std::move(result));
    result = MathExpression::Construct(tokens, std::move(result));
    //result = LogicalExpression::Construct(tokens, std::move(result));
    result = BooleanExpression::Construct(tokens, std::move(result));
  }
  else if (type == TokenType::NUMBER) {
    result = std::move(NumberExpression::Construct(tokens.front().GetText()));
    tokens.pop_front();
    result = std::move(LowExpression::Construct(tokens, std::move(result)));
    result = std::move(MathExpression::Construct(tokens, std::move(result)));
    //result = LogicalExpression::Construct(tokens, std::move(result));
    result = std::move(BooleanExpression::Construct(tokens, std::move(result)));
  }
  else if (type == TokenType::LEFT_PARENTHESIS) {
    tokens.pop_front();

    result = Expression::Construct(tokens);

    if (tokens.front().GetType() != TokenType::RIGHT_PARENTHESIS)
      throw SyntaxError("expected ')' at end of expression",
          tokens.front().GetLine(),
          tokens.front().GetColumn());

    tokens.pop_front();

    result = LowExpression::Construct(tokens, std::move(result));
    result = MathExpression::Construct(tokens, std::move(result));
    //result = LogicalExpression::Construct(tokens, std::move(result));
    result = BooleanExpression::Construct(tokens, std::move(result));
  }
  else if (type == TokenType::NOT) {
    tokens.pop_front();

    result = NotExpression::Construct(std::move(Expression::Construct(tokens)));
    result = LowExpression::Construct(tokens, std::move(result));
    result = MathExpression::Construct(tokens, std::move(result));
    //result = LogicalExpression::Construct(tokens, std::move(result));
    result = BooleanExpression::Construct(tokens, std::move(result));
  }
  else if (type == TokenType::SINGLE_QUOTE) {
    tokens.pop_front();

    if (tokens.front().GetType() != TokenType::CHARACTER)
      throw SyntaxError("expected character",
                        tokens.front().GetLine(),
                        tokens.front().GetColumn());

    result = NumberExpression::Construct(tokens.front().GetText());
    tokens.pop_front();

    tokens.pop_front();
  }
  else if (type == TokenType::DOUBLE_QUOTE && can_have_string) {
    tokens.pop_front();

    if (tokens.front().GetType() != TokenType::STRING)
      throw SyntaxError("expected string",
                        tokens.front().GetLine(),
                        tokens.front().GetColumn());
    result = StringExpression::Construct(tokens.front().GetText());
    tokens.pop_front();

    tokens.pop_front();
  }
  else if (type == TokenType::INPUTI) {
    tokens.pop_front();

    result = std::move(InputExpression::Construct(InputType::INTEGER, tokens));
  }
  else if (type == TokenType::INPUTS) {
    tokens.pop_front();

    result = std::move(InputExpression::Construct(InputType::STRING, tokens));
  }
  else {
    if (can_be_empty) {
      return nullptr;
    }
    else {
      throw SyntaxError("invalid expression",
                        tokens.front().GetLine(),
                        tokens.front().GetColumn());
    }
  }

  if (can_have_comma) {
    if (tokens.front().GetType() == TokenType::COMMA) {
      tokens.pop_front();
      result->more_ = std::move(Expression::Construct(tokens, false, true, true));
    }
    else {
      result->more_ = nullptr;
    }
  }
  else {
    result->more_ = nullptr;
  }

  return std::move(result);
}

}
