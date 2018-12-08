/**
 * @file variable_instruction.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef FUNCTION_VARIABLE_INSTRUCTION_H_
#define FUNCTION_VARIABLE_INSTRUCTION_H_

#include <core/child.h>
#include <expressions/expression.h>
#include <function/instruction.h>

namespace cassio {

/**
 * @enum VariableInstructionType
 * @brief
 *
 * ...
 *
 */
enum class VariableInstructionType {
  ASSIGNMENT,
  FUNCTION_CALL
};

/**
 * @class VariableInstruction
 * @brief
 *
 * ...
 *
 */
class VariableInstruction : public Instruction {
 public:
  static std::unique_ptr<Instruction> Construct(std::list<Token> &tokens);
  std::string Generate() override;
  void Semanticate() override;

 private:
  VariableInstructionType type_;
  std::unique_ptr<Child> variable_;
  std::unique_ptr<Expression> value_;
};

}

#endif // FUNCTION_VARIABLE_INSTRUCTION_H_
