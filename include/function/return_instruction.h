/**
 * @file return_instruction.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef FUNCTION_RETURN_INSTRUCTION_H_
#define FUNCTION_RETURN_INSTRUCTION_H_

#include <expressions/expression.h>
#include <function/instruction.h>

namespace cassio {

/**
 * @class ReturnInstruction
 * @brief
 *
 * ...
 *
 */
class ReturnInstruction : public Instruction {
 public:
  static std::unique_ptr<Instruction> Construct(std::list<Token> &tokens);
  std::string Generate() override;
  void Semanticate() override;

 private:
  std::unique_ptr<Expression> expression_;
};

}

#endif // FUNCTION_RETURN_INSTRUCTION_H_
