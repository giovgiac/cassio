/**
 * @file capacity.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <declaration/capacity.h>

namespace cassio {

std::unique_ptr<Capacity> Capacity::Construct(std::list<Token> &tokens) {
  if (tokens.front().GetType() != TokenType::LEFT_PARENTHESIS) return nullptr;
  tokens.pop_front();
  std::unique_ptr<Capacity> result = std::make_unique<Capacity>();

  if (tokens.front().GetType() != TokenType::NUMBER) throw std::runtime_error("Syntax Error");
  result->number_ = std::move(Number::Construct(tokens.front().GetText()));
  tokens.pop_front();

  if (tokens.front().GetType() != TokenType::RIGHT_PARENTHESIS) throw std::runtime_error("Syntax Error");
  tokens.pop_front();

  return result;
}

}

