/**
 * @file if_instruction.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef FUNCTION_IF_INSTRUCTION_H_
#define FUNCTION_IF_INSTRUCTION_H_

#include <expressions/logical_expression.h>
#include <function/instruction.h>

namespace cassio {

/**
 * @class IfInstruction
 * @brief
 *
 * ...
 *
 */
class IfInstruction : public Instruction {
 public:
  static std::unique_ptr<Instruction> Construct(std::list<Token> &tokens);
  std::string Generate() override;
  void Semanticate() override;

 private:
  uint64_t id_;
  std::unique_ptr<LogicalExpression> condition_;
  std::unique_ptr<Instruction> instruction_;
  std::unique_ptr<Instruction> else_;

  static uint64_t global_id;
};

}

#endif // FUNCTION_IF_INSTRUCTION_H_
