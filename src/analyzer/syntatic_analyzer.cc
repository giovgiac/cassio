/**
 * @file syntatic_analyzer.cc
 * @brief
 *
 * ...
 *
 */

#include <analyzer/syntatic_analyzer.h>

namespace cassio {

std::unique_ptr<Program> Parse(std::list<Token> &tokens) {
  return std::move(Program::Construct(tokens));
}

}

