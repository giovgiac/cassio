/**
 * @file program.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef CORE_PROGRAM_H_
#define CORE_PROGRAM_H_

#include <declaration/declaration.h>
#include <function/function.h>
#include <tokens/token.h>

#include <list>
#include <memory>

namespace cassio {

/**
 * @class Program
 * @brief
 *
 * ...
 *
 */
class Program {
 public:
  static std::unique_ptr<Program> Construct(std::list<Token> &tokens);
  std::string Generate();
  void Semanticate();

 private:
  std::unique_ptr<Declaration> declaration_;
  std::unique_ptr<Function> function_;
};

}

#endif // CORE_PROGRAM_H_
