/**
 * @file output_instruction.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef FUNCTION_OUTPUT_INSTRUCTION_H_
#define FUNCTION_OUTPUT_INSTRUCTION_H_

#include <expressions/expression.h>
#include <function/instruction.h>

namespace cassio {

/**
 * @enum OutputType
 * @brief
 *
 * ...
 *
 */
enum class OutputType {
  INTEGER,
  STRING
};

/**
 * @class OutputInstruction
 * @brief
 *
 * ...
 *
 */
class OutputInstruction : public Instruction {
 public:
  static std::unique_ptr<Instruction> Construct(OutputType type, std::list<Token> &tokens);
  std::string Generate() override;
  void Semanticate() override;

 private:
  OutputType type_;
  std::unique_ptr<Expression> argument_;
};

}

#endif // FUNCTION_OUTPUT_INSTRUCTION_H_
