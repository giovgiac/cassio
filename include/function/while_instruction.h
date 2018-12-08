/**
 * @file while_instruction.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef FUNCTION_WHILE_INSTRUCTION_H_
#define FUNCTION_WHILE_INSTRUCTION_H_

#include <expressions/expression.h>
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
  std::unique_ptr<Expression> condition_;
  std::unique_ptr<Instruction> instruction_;
};

}

#endif // FUNCTION_WHILE_INSTRUCTION_H_
