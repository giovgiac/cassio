/**
 * @file token.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef TOKENS_TOKEN_H_
#define TOKENS_TOKEN_H_

#include <sstream>
#include <string>

namespace cassio {

/**
 * @enum TokenType
 * @brief
 *
 * ...
 *
 */
enum class TokenType {
  DATA,
  CODE,
  COMMA,
  DOT,
  SEMICOLON,
  LEFT_ARROW,
  BYTE,
  WORD,
  DWORD,
  QWORD,
  RAX,
  RBX,
  RCX,
  RDX,
  RDI,
  RSI,
  STRUCT,
  FUNCTION,
  IF,
  ELSE,
  WHILE,
  RETURN,
  NOT,
  AND,
  OR,
  INPUTI,
  INPUTS,
  OUTPUTI,
  OUTPUTS,
  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE,
  MODULUS,
  EQUALS,
  NOT_EQUAL,
  GREATER_THAN,
  LESS_THAN,
  GREATER_EQUALS,
  LESS_EQUALS,
  SINGLE_QUOTE,
  DOUBLE_QUOTE,
  CHARACTER,
  STRING,
  LEFT_PARENTHESIS,
  RIGHT_PARENTHESIS,
  LEFT_BRACE,
  RIGHT_BRACE,
  LEFT_BRACKET,
  RIGHT_BRACKET,
  IDENTIFIER,
  NUMBER
};

/**
 * @class Token
 * @brief
 *
 * ...
 *
 */
class Token {
 public:
  Token(TokenType type, std::string text, uint64_t line, uint64_t column)
      : type_(type), text_(std::move(text)), line_(line), column_(column) {}

  uint64_t GetColumn() const { return column_; }

  uint64_t GetLine() const { return line_; }

  std::string GetText() const { return text_; }

  TokenType GetType() const { return type_; }

  friend std::ostream &operator<<(std::ostream &os, const Token &obj) {
    os << obj.line_ << ":" << obj.column_ << ":"
       << "'" << obj.text_ << "'";
    return os;
  }

 private:
  TokenType type_;
  std::string text_;
  uint64_t line_;
  uint64_t column_;
};

}

#endif // TOKENS_TOKEN_H_
