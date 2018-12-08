/**
 * @file child.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef EXPRESSIONS_CHILD_H_
#define EXPRESSIONS_CHILD_H_

#include <core/identifier.h>
#include <tokens/token.h>

#include <list>

namespace cassio {

/**
 * @class Child
 * @brief
 *
 * ...
 *
 */
class Child {
 public:
  static std::unique_ptr<Child> Construct(std::list<Token> &tokens);
  std::string Generate();
  void Semanticate();

  std::string GetType() const;

 private:
  std::unique_ptr<Identifier> parent_;
  std::unique_ptr<Child> child_;
};

}

#endif // EXPRESSIONS_CHILD_H_
