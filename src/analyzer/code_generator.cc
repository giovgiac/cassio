/**
 * @file code_generator.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <analyzer/code_generator.h>

namespace cassio {

std::string CodeGenerator::Generate(std::unique_ptr<Program> program) {
  return program->Generate();
}

}

