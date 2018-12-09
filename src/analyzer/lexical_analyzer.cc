//
// Created by ggiacomo on 11/19/18.
//

#include <analyzer/lexical_analyzer.h>

namespace cassio {

std::list<Token> Lex(const std::string_view &source_code) {
  std::list<Token> tokens;
  size_t i{0};
  uint64_t line{1}, column{1};

  while (i < source_code.size()) {
    if (source_code.substr(i, Length(data_literal)) == data_literal) {
      tokens.emplace_back(Token{TokenType::DATA, data_literal, line, column});
      column += Length(data_literal);
      i += Length(data_literal);
      continue;
    }
    else if (source_code.substr(i, Length(code_literal)) == code_literal) {
      tokens.emplace_back(Token{TokenType::CODE, code_literal, line, column});
      column += Length(code_literal);
      i += Length(code_literal);
      continue;
    }
    else if (source_code.substr(i, Length(comma_literal)) == comma_literal) {
      tokens.emplace_back(Token{TokenType::COMMA, comma_literal, line, column});
      column += Length(comma_literal);
      i += Length(comma_literal);
      continue;
    }
    else if (source_code.substr(i, Length(dot_literal)) == dot_literal) {
      tokens.emplace_back(Token{TokenType::DOT, dot_literal, line, column});
      column += Length(dot_literal);
      i += Length(dot_literal);
      continue;
    }
    else if (source_code.substr(i, Length(semicolon_literal)) == semicolon_literal) {
      tokens.emplace_back(Token{TokenType::SEMICOLON, semicolon_literal, line, column});
      column += Length(semicolon_literal);
      i += Length(semicolon_literal);
      continue;
    }
    else if (source_code.substr(i, Length(left_arrow_literal)) == left_arrow_literal) {
      tokens.emplace_back(Token{TokenType::LEFT_ARROW, left_arrow_literal, line, column});
      column += Length(left_arrow_literal);
      i += Length(left_arrow_literal);
      continue;
    }
    else if (source_code.substr(i, Length(byte_literal)) == byte_literal) {
      tokens.emplace_back(Token{TokenType::BYTE, byte_literal, line, column});
      column += Length(byte_literal);
      i += Length(byte_literal);
      continue;
    }
    else if (source_code.substr(i, Length(word_literal)) == word_literal) {
      tokens.emplace_back(Token{TokenType::WORD, word_literal, line, column});
      column += Length(word_literal);
      i += Length(word_literal);
      continue;
    }
    else if (source_code.substr(i, Length(dword_literal)) == dword_literal) {
      tokens.emplace_back(Token{TokenType::DWORD, dword_literal, line, column});
      column += Length(dword_literal);
      i += Length(dword_literal);
      continue;
    }
    else if (source_code.substr(i, Length(qword_literal)) == qword_literal) {
      tokens.emplace_back(Token{TokenType::QWORD, qword_literal, line, column});
      column += Length(qword_literal);
      i += Length(qword_literal);
      continue;
    }
    else if (source_code.substr(i, Length(rax_literal)) == rax_literal) {
      tokens.emplace_back(Token{TokenType::RAX, rax_literal, line, column});
      column += Length(rax_literal);
      i += Length(rax_literal);
      continue;
    }
    else if (source_code.substr(i, Length(rbx_literal)) == rbx_literal) {
      tokens.emplace_back(Token{TokenType::RBX, rbx_literal, line, column});
      column += Length(rbx_literal);
      i += Length(rbx_literal);
      continue;
    }
    else if (source_code.substr(i, Length(rcx_literal)) == rcx_literal) {
      tokens.emplace_back(Token{TokenType::RCX, rcx_literal, line, column});
      column += Length(rcx_literal);
      i += Length(rcx_literal);
      continue;
    }
    else if (source_code.substr(i, Length(rdx_literal)) == rdx_literal) {
      tokens.emplace_back(Token{TokenType::RDX, rdx_literal, line, column});
      column += Length(rdx_literal);
      i += Length(rdx_literal);
      continue;
    }
    else if (source_code.substr(i, Length(rdi_literal)) == rdi_literal) {
      tokens.emplace_back(Token{TokenType::RDI, rdi_literal, line, column});
      column += Length(rdi_literal);
      i += Length(rdi_literal);
      continue;
    }
    else if (source_code.substr(i, Length(rsi_literal)) == rsi_literal) {
      tokens.emplace_back(Token{TokenType::RSI, rsi_literal, line, column});
      column += Length(rsi_literal);
      i += Length(rsi_literal);
      continue;
    }
    else if (source_code.substr(i, Length(struct_literal)) == struct_literal) {
      tokens.emplace_back(Token{TokenType::STRUCT, struct_literal, line, column});
      column += Length(struct_literal);
      i += Length(struct_literal);
      continue;
    }
    else if (source_code.substr(i, Length(function_literal)) == function_literal) {
      tokens.emplace_back(Token{TokenType::FUNCTION, function_literal, line, column});
      column += Length(function_literal);
      i += Length(function_literal);
      continue;
    }
    else if (source_code.substr(i, Length(if_literal)) == if_literal) {
      tokens.emplace_back(Token{TokenType::IF, if_literal, line, column});
      column += Length(if_literal);
      i += Length(if_literal);
      continue;
    }
    else if (source_code.substr(i, Length(else_literal)) == else_literal) {
      tokens.emplace_back(Token{TokenType::ELSE, else_literal, line, column});
      column += Length(else_literal);
      i += Length(else_literal);
      continue;
    }
    else if (source_code.substr(i, Length(while_literal)) == while_literal) {
      tokens.emplace_back(Token{TokenType::WHILE, while_literal, line, column});
      column += Length(while_literal);
      i += Length(while_literal);
      continue;
    }
    else if (source_code.substr(i, Length(return_literal)) == return_literal) {
      tokens.emplace_back(Token{TokenType::RETURN, return_literal, line, column});
      column += Length(return_literal);
      i += Length(return_literal);
      continue;
    }
    else if (source_code.substr(i, Length(not_literal)) == not_literal) {
      tokens.emplace_back(Token{TokenType::NOT, not_literal, line, column});
      column += Length(not_literal);
      i += Length(not_literal);
      continue;
    }
    else if (source_code.substr(i, Length(and_literal)) == and_literal) {
      tokens.emplace_back(Token{TokenType::AND, and_literal, line, column});
      column += Length(and_literal);
      i += Length(and_literal);
      continue;
    }
    else if (source_code.substr(i, Length(or_literal)) == or_literal) {
      tokens.emplace_back(Token{TokenType::OR, or_literal, line, column});
      column += Length(or_literal);
      i += Length(or_literal);
      continue;
    }
    else if (source_code.substr(i, Length(inputi_literal)) == inputi_literal) {
      tokens.emplace_back(Token{TokenType::INPUTI, inputi_literal, line, column});
      column += Length(inputi_literal);
      i += Length(inputi_literal);
      continue;
    }
    else if (source_code.substr(i, Length(inputs_literal)) == inputs_literal) {
      tokens.emplace_back(Token{TokenType::INPUTS, inputs_literal, line, column});
      column += Length(inputs_literal);
      i += Length(inputs_literal);
      continue;
    }
    else if (source_code.substr(i, Length(outputi_literal)) == outputi_literal) {
      tokens.emplace_back(Token{TokenType::OUTPUTI, outputi_literal, line, column});
      column += Length(outputi_literal);
      i += Length(outputi_literal);
      continue;
    }
    else if (source_code.substr(i, Length(outputs_literal)) == outputs_literal) {
      tokens.emplace_back(Token{TokenType::OUTPUTS, outputs_literal, line, column});
      column += Length(outputs_literal);
      i += Length(outputs_literal);
      continue;
    }
    else if (source_code.substr(i, Length(plus_literal)) == plus_literal) {
      tokens.emplace_back(Token{TokenType::PLUS, plus_literal, line, column});
      column += Length(plus_literal);
      i += Length(plus_literal);
      continue;
    }
    else if (source_code.substr(i, Length(minus_literal)) == minus_literal) {
      tokens.emplace_back(Token{TokenType::MINUS, minus_literal, line, column});
      column += Length(minus_literal);
      i += Length(minus_literal);
      continue;
    }
    else if (source_code.substr(i, Length(multiply_literal)) == multiply_literal) {
      tokens.emplace_back(Token{TokenType::MULTIPLY, multiply_literal, line, column});
      column += Length(multiply_literal);
      i += Length(multiply_literal);
      continue;
    }
    else if (source_code.substr(i, Length(divide_literal)) == divide_literal) {
      tokens.emplace_back(Token{TokenType::DIVIDE, divide_literal, line, column});
      column += Length(divide_literal);
      i += Length(divide_literal);
      continue;
    }
    else if (source_code.substr(i, Length(modulus_literal)) == modulus_literal) {
      tokens.emplace_back(Token{TokenType::MODULUS, modulus_literal, line, column});
      column += Length(modulus_literal);
      i += Length(modulus_literal);
      continue;
    }
    else if (source_code.substr(i, Length(equals_literal)) == equals_literal) {
      tokens.emplace_back(Token{TokenType::EQUALS, equals_literal, line, column});
      column += Length(equals_literal);
      i += Length(equals_literal);
      continue;
    }
    else if (source_code.substr(i, Length(not_equal_literal)) == not_equal_literal) {
      tokens.emplace_back(Token{TokenType::NOT_EQUAL, not_equal_literal, line, column});
      column += Length(not_equal_literal);
      i += Length(not_equal_literal);
      continue;
    }
    else if (source_code.substr(i, Length(greater_equals_literal)) == greater_equals_literal) {
      tokens.emplace_back(Token{TokenType::GREATER_EQUALS, greater_equals_literal, line, column});
      column += Length(greater_equals_literal);
      i += Length(greater_equals_literal);
      continue;
    }
    else if (source_code.substr(i, Length(less_equals_literal)) == less_equals_literal) {
      tokens.emplace_back(Token{TokenType::LESS_EQUALS, less_equals_literal, line, column});
      column += Length(less_equals_literal);
      i += Length(less_equals_literal);
      continue;
    }
    else if (source_code.substr(i, Length(greater_than_literal)) == greater_than_literal) {
      tokens.emplace_back(Token{TokenType::GREATER_THAN, greater_than_literal, line, column});
      column += Length(greater_than_literal);
      i += Length(greater_than_literal);
      continue;
    }
    else if (source_code.substr(i, Length(less_than_literal)) == less_than_literal) {
      tokens.emplace_back(Token{TokenType::LESS_THAN, less_than_literal, line, column});
      column += Length(less_than_literal);
      i += Length(less_than_literal);
      continue;
    }
    else if (source_code.substr(i, Length(single_quote_literal)) == single_quote_literal) {
      static bool first = false;

      tokens.emplace_back(Token{TokenType::SINGLE_QUOTE, single_quote_literal, line, column});
      column += Length(single_quote_literal);
      i += Length(single_quote_literal);

      if (!first) {
        std::ostringstream buf;
        size_t j{0};
        while (source_code.substr(i + j, 1) != single_quote_literal) {
          buf << source_code.substr(i + j, 1);
          ++j;

          if (j > 1) {
            throw std::runtime_error("Lexical Error");
          }
        }

        std::string str = buf.str();
        tokens.emplace_back(Token{TokenType::CHARACTER, str, line, column});
        column += str.size();
        i += str.size();

        first = true;
        continue;
      }

      first = false;
      continue;
    }
    else if (source_code.substr(i, Length(double_quote_literal)) == double_quote_literal) {
      static bool first = false;

      tokens.emplace_back(Token{TokenType::DOUBLE_QUOTE, double_quote_literal, line, column});
      column += Length(double_quote_literal);
      i += Length(double_quote_literal);

      if (!first) {
        std::ostringstream buf;
        size_t j{0};
        while (source_code.substr(i + j, 1) != double_quote_literal) {
          buf << source_code.substr(i + j, 1);
          ++j;

          if (j >= source_code.size()) {
            throw std::runtime_error("Lexical Error");
          }
        }

        std::string str = buf.str();
        tokens.emplace_back(Token{TokenType::STRING, str, line, column});
        column += str.size();
        i += str.size();

        first = true;
        continue;
      }

      first = false;
      continue;
    }
    else if (source_code.substr(i, Length(left_parenthesis_literal)) == left_parenthesis_literal) {
      tokens.emplace_back(Token{TokenType::LEFT_PARENTHESIS, left_parenthesis_literal, line, column});
      column += Length(left_parenthesis_literal);
      i += Length(left_parenthesis_literal);
      continue;
    }
    else if (source_code.substr(i, Length(right_parenthesis_literal)) == right_parenthesis_literal) {
      tokens.emplace_back(Token{TokenType::RIGHT_PARENTHESIS, right_parenthesis_literal, line, column});
      column += Length(right_parenthesis_literal);
      i += Length(right_parenthesis_literal);
      continue;
    }
    else if (source_code.substr(i, Length(left_brace_literal)) == left_brace_literal) {
      tokens.emplace_back(Token{TokenType::LEFT_BRACE, left_brace_literal, line, column});
      column += Length(left_brace_literal);
      i += Length(left_brace_literal);
      continue;
    }
    else if (source_code.substr(i, Length(right_brace_literal)) == right_brace_literal) {
      tokens.emplace_back(Token{TokenType::RIGHT_BRACE, right_brace_literal, line, column});
      column += Length(right_brace_literal);
      i += Length(right_brace_literal);
      continue;
    }
    else if (source_code.substr(i, Length(left_bracket_literal)) == left_bracket_literal) {
      tokens.emplace_back(Token{TokenType::LEFT_BRACKET, left_bracket_literal, line, column});
      column += Length(left_bracket_literal);
      i += Length(left_bracket_literal);
      continue;
    }
    else if (source_code.substr(i, Length(right_bracket_literal)) == right_bracket_literal) {
      tokens.emplace_back(Token{TokenType::RIGHT_BRACKET, right_bracket_literal, line, column});
      column += Length(right_bracket_literal);
      i += Length(right_bracket_literal);
      continue;
    }
    else if (source_code.substr(i, 1).find_first_of("0123456789") != std::string::npos) {
      std::ostringstream buf;
      size_t j{1};

      buf << source_code.substr(i, 1);
      while (source_code.substr(i + j, 1).find_first_of("0123456789") != std::string::npos) {
        buf << source_code.substr(i + j, 1);
        ++j;
      }

      std::string str = buf.str();
      tokens.emplace_back(Token{TokenType::NUMBER, str, line, column});
      column += str.size();
      i += str.size();
      continue;
    }
    else if (source_code.substr(i, 1).find_first_of(
        "_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") != std::string::npos) {
      std::ostringstream buf;
      size_t j{1};

      buf << source_code.substr(i, 1);
      while (source_code.substr(i + j, 1).find_first_of(
          "_0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") != std::string::npos) {
        buf << source_code.substr(i + j, 1);
        ++j;
      }

      std::string str = buf.str();
      tokens.emplace_back(Token{TokenType::IDENTIFIER, str, line, column});
      column += str.size();
      i += str.size();
      continue;
    }
    else if (source_code.substr(i, 1) == " ") {
      column += 1;
      i += 1;
      continue;
    }
    else if (source_code.substr(i, 1) == "\t") {
      column += 4;
      i += 1;
      continue;
    }
    else if (source_code.substr(i, 1) == "\r") {
      i += 1;
      continue;
    }
    else if (source_code.substr(i, 1) == "\n") {
      line += 1;
      column = 0;
      i += 1;
      continue;
    }
    else {
      throw std::runtime_error("Lexical Error");
    }
  }

  return tokens;
}

}