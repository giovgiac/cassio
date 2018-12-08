/**
 * @file value_instruction.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef FUNCTION_VALUE_INSTRUCTION_H_
#define FUNCTION_VALUE_INSTRUCTION_H_

#include <core/child.h>
#include <expressions/expression.h>
#include <function/instruction.h>

namespace cassio {

/**
 * @enum ValueType
 * @brief
 *
 * ...
 *
 */
enum ValueType {
  REGISTER,
  VARIABLE
};

/**
 * @enum ValueRegister
 * @brief
 *
 * ...
 *
 */
enum ValueRegister {
  RAX,
  RBX,
  RCX,
  RDX,
  RSI,
  RDI,
  NONE
};

/**
 * @class ValueInstruction
 * @brief
 *
 * ...
 *
 */
class ValueInstruction : public Instruction {
 public:
  static std::unique_ptr<Instruction> Construct(std::list<Token> &tokens);
  std::string Generate() override;
  void Semanticate() override;

 private:
  ValueType type_;
  ValueRegister register_;
  std::unique_ptr<Child> variable_;
  std::unique_ptr<Expression> value_;
};

}

#endif // FUNCTION_VALUE_INSTRUCTION_H_
