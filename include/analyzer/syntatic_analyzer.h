/**
 * @file syntatic_analyzer.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef ANALYZER_SYNTATIC_ANALYZER_H_
#define ANALYZER_SYNTATIC_ANALYZER_H_

#include <core/program.h>
#include <tokens/token.h>

namespace cassio {

/**
 * @fn Parse
 * @brief
 *
 * ...
 *
 * @param tokens
 *
 * @return
 *
 */
std::unique_ptr<Program> Parse(std::list<Token> &tokens);

}

#endif // ANALYZER_SYNTATIC_ANALYZER_H_
