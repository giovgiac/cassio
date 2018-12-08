/**
 * @file if_instruction.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef FUNCTION_IF_INSTRUCTION_H_
#define FUNCTION_IF_INSTRUCTION_H_

#include <expressions/expression.h>
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
  std::unique_ptr<Expression> condition_;
  std::unique_ptr<Instruction> instruction_;
  std::unique_ptr<Instruction> else_;
};

}

#endif // FUNCTION_IF_INSTRUCTION_H_
