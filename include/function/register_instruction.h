/**
 * @file register_instruction.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef FUNCTION_REGISTER_INSTRUCTION_H_
#define FUNCTION_REGISTER_INSTRUCTION_H_

#include <expressions/register_expression.h>
#include <function/instruction.h>

namespace cassio {

/**
 * @class RegisterInstruction
 * @brief
 *
 * ...
 *
 */
class RegisterInstruction : public Instruction {
 public:
  static std::unique_ptr<Instruction> Construct(std::list<Token> &tokens, RegisterType type);
  std::string Generate() override;
  void Semanticate() override;

 private:
  RegisterType type_;
  std::unique_ptr<Expression> value_;
};

}

#endif // FUNCTION_REGISTER_INSTRUCTION_H_
