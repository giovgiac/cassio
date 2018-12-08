/**
 * @file function.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef FUNCTION_FUNCTION_H_
#define FUNCTION_FUNCTION_H_

#include <core/identifier.h>
#include <function/instruction.h>
#include <function/parameter.h>

#include <memory>

namespace cassio {

/**
 * @enum ReturnType
 * @brief
 *
 * ...
 *
 */
enum class ReturnType {
  BYTE,
  WORD,
  DWORD,
  QWORD,
  VOID
};

/**
 * @class Function
 * @brief
 *
 * ...
 *
 */
class Function {
 public:
  static std::unique_ptr<Function> Construct(std::list<Token> &tokens);
  std::string Generate();
  void Semanticate();

 private:
  std::unique_ptr<Identifier> identifier_;
  std::unique_ptr<Parameter> parameter_;
  ReturnType return_type_;
  std::unique_ptr<Instruction> instruction_;
  std::unique_ptr<Function> function_;
};

}

#endif // FUNCTION_FUNCTION_H_
