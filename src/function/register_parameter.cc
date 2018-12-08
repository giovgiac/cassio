/**
 * @file register_parameter.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <function/register_parameter.h>

namespace cassio {

std::unique_ptr<Parameter> RegisterParameter::Construct(std::list<Token> &tokens, ParameterRegister reg) {
  std::unique_ptr<RegisterParameter> result = std::make_unique<RegisterParameter>();

  result->register_ = reg;
  return result;
}

}
