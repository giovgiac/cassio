/**
 * @file expression.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef EXPRESSIONS_EXPRESSION_H_
#define EXPRESSIONS_EXPRESSION_H_

#include <tokens/token.h>

#include <list>
#include <memory>

namespace cassio {

/**
 * @enum RegisterType
 * @brief
 *
 * ...
 *
 */
enum class RegisterType {
  RAX,
  RBX,
  RCX,
  RDX,
  RSI,
  RDI
};

/**
 * @fn ConvertToRegisterType
 * @brief
 *
 * ...
 *
 * @param type
 *
 * @return
 *
 */
RegisterType ConvertToRegisterType(TokenType type);

/**
 * @class Expression
 * @brief
 *
 * ...
 *
 */
class Expression {
 public:
  virtual ~Expression() = default;

  static std::unique_ptr<Expression> Construct(std::list<Token> &tokens,
                                               bool can_be_empty = false,
                                               bool can_have_string = false,
                                               bool can_have_comma = false);
  virtual std::string Generate(bool generate_more = true) = 0;
  virtual void Semanticate() = 0;

  std::unique_ptr<Expression> GetMore() { return std::move(more_); }

 protected:
  std::unique_ptr<Expression> more_;
};

}

#endif // EXPRESSIONS_EXPRESSION_H_
