/**
 * @file while_instruction.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef FUNCTION_WHILE_INSTRUCTION_H_
#define FUNCTION_WHILE_INSTRUCTION_H_

#include <expressions/logical_expression.h>
#include <function/instruction.h>

namespace cassio {

/**
 * @class WhileInstruction
 * @brief
 *
 * ...
 *
 */
class WhileInstruction : public Instruction {
 public:
  static std::unique_ptr<Instruction> Construct(std::list<Token> &tokens);
  std::string Generate() override;
  void Semanticate() override;

 private:
  uint64_t id_;
  std::unique_ptr<LogicalExpression> condition_;
  std::unique_ptr<Instruction> instruction_;

  static uint64_t global_id;
};

}

#endif // FUNCTION_WHILE_INSTRUCTION_H_
