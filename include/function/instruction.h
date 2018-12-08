/**
 * @file instruction.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef FUNCTION_INSTRUCTION_H_
#define FUNCTION_INSTRUCTION_H_

#include <tokens/token.h>

#include <list>
#include <memory>

namespace cassio {

/**
 * @class Instruction
 * @brief
 *
 * ...
 *
 */
class Instruction {
 public:
  virtual ~Instruction() = default;

  static std::unique_ptr<Instruction> Construct(std::list<Token> &tokens);
  virtual std::string Generate() = 0;
  virtual void Semanticate() = 0;

 protected:
  std::unique_ptr<Instruction> more_;
};

}

#endif // FUNCTION_INSTRUCTION_H_
