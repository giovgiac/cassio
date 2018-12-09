/**
 * @file type_parameter.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef FUNCTION_TYPE_PARAMETER_H_
#define FUNCTION_TYPE_PARAMETER_H_

#include <core/identifier.h>
#include <function/parameter.h>

namespace cassio {

/**
 * @enum ParameterType
 * @brief
 *
 * ...
 *
 */
enum class ParameterType {
  BYTE,
  WORD,
  DWORD,
  QWORD
};

/**
 * @class Type Parameter
 * @brief
 *
 * ...
 *
 */
class TypeParameter : public Parameter {
 public:
  static std::unique_ptr<Parameter> Construct(std::list<Token> &tokens, ParameterType type);
  void GetArgument(std::list<struct Argument> &args) override;
  void Semanticate() override;

 private:
  ParameterType type_;
  std::unique_ptr<Identifier> identifier_;
};

}

#endif // FUNCTION_TYPE_PARAMETER_H_
