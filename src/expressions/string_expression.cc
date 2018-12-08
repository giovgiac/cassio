/**
 * @file string_expression.cc
 * @brief
 *
 * ...
 *
 */

#include <analyzer/semantic_analyzer.h>
#include <expressions/string_expression.h>

namespace cassio {

uint64_t StringExpression::global_id = 0;

std::unique_ptr<StringExpression> StringExpression::Construct(std::string string) {
  std::unique_ptr<StringExpression> result = std::make_unique<StringExpression>();

  result->string_ = std::move(string);
  result->id_ = global_id++;
  return result;
}

std::string StringExpression::Generate() {
  std::ostringstream oss;

  oss << "\tmov\trax, string" << SemanticAnalyzer::literals_[id_].id_;
  oss << "\n";

  if (more_)
    oss << more_->Generate();

  return oss.str();
}

void StringExpression::Semanticate() {
  Literal lt = {};
  lt.string_ = string_;
  lt.id_ = id_;

  SemanticAnalyzer::literals_.emplace(std::make_pair(id_, lt));

  if (more_)
    more_->Semanticate();
}

}
