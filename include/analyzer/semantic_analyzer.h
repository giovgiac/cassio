/**
 * @file semantic_analyzer.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef ANALYZER_SEMANTIC_ANALYZER_H_
#define ANALYZER_SEMANTIC_ANALYZER_H_

#include <core/program.h>

#include <map>

namespace cassio {

/**
 * @struct MemberType
 * @brief
 *
 * ...
 *
 */
struct MemberType {
  std::string name_;
  DataType type_;
  uint64_t capacity_;
};

/**
 * @struct UserType
 * @brief
 *
 * ...
 *
 */
struct UserType {
  std::string name_;
  std::list<MemberType> members_;
};

/**
 * @struct Variable
 * @brief
 *
 * ...
 *
 */
struct Variable {
  std::string name_;
  std::string type_;
  uint64_t capacity_;
};

struct Argument {
  std::string name_;
  std::string type_;
  uint64_t offset_;
};

/**
 * @struct Procedure
 * @brief
 *
 * ...
 *
 */
struct Procedure {
  std::string name_;
  std::string return_type_;
  std::list<Argument> argument_;
};

/**
 *
 */
struct Literal {
  std::string string_;
  uint64_t id_;
};

/**
 * @class SemanticAnalyzer
 * @brief
 *
 * ...
 *
 */
class SemanticAnalyzer {
 public:
  static std::unique_ptr<Program> Semanticate(std::unique_ptr<Program> program);

 public:
  static std::map<std::string, Variable> variables_;
  static std::map<std::string, UserType> user_types_;
  static std::map<std::string, Procedure> functions_;
  static std::map<uint64_t, Literal> literals_;
  static std::string current_function_;
};

}

#endif // ANALYZER_SEMANTIC_ANALYZER_H_
