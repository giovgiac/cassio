/**
 * @file type_declaration.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef DECLARATION_TYPE_DECLARATION_H_
#define DECLARATION_TYPE_DECLARATION_H_

#include <declaration/capacity.h>
#include <declaration/declaration.h>
#include <core/identifier.h>

#include <memory>

namespace cassio {

/**
 * @class TypeDeclaration
 * @brief
 *
 * ...
 *
 */
class TypeDeclaration : public Declaration {
 public:
  static std::unique_ptr<Declaration> Construct(std::list<Token> &tokens, DataType type);
  std::string Generate() override;
  void Semanticate() override;

  void RetrieveType(std::list<struct MemberType> &sub_types) override;

 private:
  DataType type_;
  std::unique_ptr<Identifier> identifier_;
  std::unique_ptr<Capacity> capacity_;
  std::unique_ptr<Declaration> declaration_;
};

}

#endif // DECLARATION_TYPE_DECLARATION_H_
