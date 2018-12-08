/**
 * @file lexical_analyzer.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef ANALYZER_LEXICAL_ANALYZER_H_
#define ANALYZER_LEXICAL_ANALYZER_H_

#include <list>
#include <string_view>
#include <tokens/token.h>

namespace cassio {

template <size_t N>
constexpr size_t Length(char const(&)[N]) { return (N - 1); }

constexpr const char data_literal[] = "data";
constexpr const char code_literal[] = "code";
constexpr const char comma_literal[] = ",";
constexpr const char dot_literal[] = ".";
constexpr const char semicolon_literal[] = ";";
constexpr const char left_arrow_literal[] = "<-";
constexpr const char byte_literal[] = "byte ";
constexpr const char word_literal[] = "word ";
constexpr const char dword_literal[] = "dword ";
constexpr const char qword_literal[] = "qword ";
constexpr const char rax_literal[] = "rax";
constexpr const char rbx_literal[] = "rbx";
constexpr const char rcx_literal[] = "rcx";
constexpr const char rdx_literal[] = "rdx";
constexpr const char rdi_literal[] = "rdi";
constexpr const char rsi_literal[] = "rsi";
constexpr const char struct_literal[] = "struct ";
constexpr const char function_literal[] = "function ";
constexpr const char if_literal[] = "if";
constexpr const char else_literal[] = "else";
constexpr const char while_literal[] = "while";
constexpr const char return_literal[] = "return ";
constexpr const char not_literal[] = "not";
constexpr const char and_literal[] = "and";
constexpr const char or_literal[] = "or";
constexpr const char inputi_literal[] = "inputi";
constexpr const char inputs_literal[] = "inputs";
constexpr const char outputi_literal[] = "outputi";
constexpr const char outputs_literal[] = "outputs";
constexpr const char plus_literal[] = "+";
constexpr const char minus_literal[] = "-";
constexpr const char multiply_literal[] = "*";
constexpr const char divide_literal[] = "/";
constexpr const char modulus_literal[] = "%";
constexpr const char equals_literal[] = "==";
constexpr const char not_equal_literal[] = "!=";
constexpr const char greater_than_literal[] = ">";
constexpr const char less_than_literal[] = "<";
constexpr const char greater_equals_literal[] = ">=";
constexpr const char less_equals_literal[] = "<=";
constexpr const char single_quote_literal[] = "'";
constexpr const char double_quote_literal[] = "\"";
constexpr const char left_parenthesis_literal[] = "(";
constexpr const char right_parenthesis_literal[] = ")";
constexpr const char left_brace_literal[] = "[";
constexpr const char right_brace_literal[] = "]";
constexpr const char left_bracket_literal[] = "{";
constexpr const char right_bracket_literal[] = "}";

std::list<Token> Lex(const std::string_view &source_code);

}

#endif // ANALYZER_LEXICAL_ANALYZER_H_
