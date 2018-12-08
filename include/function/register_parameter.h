/**
 * @file register_parameter.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef FUNCTION_REGISTER_PARAMETER_H_
#define FUNCTION_REGISTER_PARAMETER_H_

#include <function/parameter.h>

namespace cassio {

/**
 * @enum ParameterRegister
 * @brief
 *
 * ...
 *
 */
enum class ParameterRegister {
  RAX,
  RBX,
  RCX,
  RDX,
  RSI,
  RDI
};

/**
 * @class RegisterParameter
 * @brief
 *
 * ...
 *
 */
class RegisterParameter : public Parameter {
 public:
  static std::unique_ptr<Parameter> Construct(std::list<Token> &tokens, ParameterRegister reg);

 private:
  ParameterRegister register_;
};

}

#endif // FUNCTION_REGISTER_PARAMETER_H_
