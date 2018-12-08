/**
 * @file declaration.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef DECLARATION_DECLARATION_H_
#define DECLARATION_DECLARATION_H_

#include <tokens/token.h>

#include <list>
#include <memory>

namespace cassio {

/**
 * @enum DataType
 * @brief
 *
 * ...
 *
 */
enum class DataType {
  BYTE,
  WORD,
  DWORD,
  QWORD
};

/**
 * @class Declaration
 * @brief
 *
 * ...
 *
 */
class Declaration {
 public:
  virtual ~Declaration() = default;

  static std::unique_ptr<Declaration> Construct(std::list<Token> &tokens);
  virtual std::string Generate() = 0;
  virtual void Semanticate() = 0;
  virtual void RetrieveType(std::list<struct MemberType> &sub_types) = 0;
};

}

#endif // DECLARATION_DECLARATION_H_
