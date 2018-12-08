/**
 * @file code_generator.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef ANALYZER_CODE_GENERATOR_H_
#define ANALYZER_CODE_GENERATOR_H_

#include <core/program.h>

namespace cassio {

/**
 * @class CodeGenerator
 * @brief
 *
 * ...
 *
 */
class CodeGenerator {
 public:
  static std::string Generate(std::unique_ptr<Program> program);
};

}

#endif // ANALYZER_CODE_GENERATOR_H_
