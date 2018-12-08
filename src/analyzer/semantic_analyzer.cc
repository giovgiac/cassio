/**
 * @file semantic_analyzer.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <analyzer/semantic_analyzer.h>

namespace cassio {

std::map<std::string, Variable> SemanticAnalyzer::variables_ = {};
std::map<std::string, UserType> SemanticAnalyzer::user_types_ = {};
std::map<std::string, Procedure> SemanticAnalyzer::functions_ = {};
std::map<uint64_t, Literal> SemanticAnalyzer::literals_ = {};

std::unique_ptr<Program> SemanticAnalyzer::Semanticate(std::unique_ptr<Program> program) {
  program->Semanticate();
  return std::move(program);
}

}
