/**
 * @file register_parameter.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <analyzer/semantic_analyzer.h>
#include <function/register_parameter.h>

namespace cassio {

std::unique_ptr<Parameter> RegisterParameter::Construct(std::list<Token> &tokens, ParameterRegister reg) {
  std::unique_ptr<RegisterParameter> result = std::make_unique<RegisterParameter>();

  result->register_ = reg;
  return result;
}

void RegisterParameter::GetArgument(std::list<cassio::Argument> &args) {
  if (more_)
    more_->GetArgument(args);
}

void RegisterParameter::Semanticate() {
  if (more_)
    more_->Semanticate();
}

}
