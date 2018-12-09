/**
 * @file parameter.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef FUNCTION_PARAMETER_H_
#define FUNCTION_PARAMETER_H_

#include <tokens/token.h>

#include <memory>
#include <list>

namespace cassio {

/**
 * @class Parameter
 * @brief
 *
 * ...
 *
 */
class Parameter {
 public:
  static std::unique_ptr<Parameter> Construct(std::list<Token> &tokens, bool can_be_empty = true);
  virtual void GetArgument(std::list<struct Argument> &args) = 0;
  virtual void Semanticate() = 0;

 protected:
  std::unique_ptr<Parameter> more_;
};

}

#endif // FUNCTION_PARAMETER_H_
