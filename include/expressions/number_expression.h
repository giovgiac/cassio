/**
 * @file number_expression.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef EXPRESSIONS_NUMBER_EXPRESSION_H_
#define EXPRESSIONS_NUMBER_EXPRESSION_H_

#include <expressions/expression.h>
#include <core/number.h>

namespace cassio {

/**
 * @class NumberExpression
 * @brief
 *
 * ...
 *
 */
class NumberExpression : public Expression {
 public:
  static std::unique_ptr<Expression> Construct(std::string number);
  std::string Generate() override;
  void Semanticate() override;

 private:
  std::unique_ptr<Number> number_;
};

}

#endif // EXPRESSIONS_NUMBER_EXPRESSION_H_
