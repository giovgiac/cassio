/**
 * @file struct_declaration.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef DECLARATION_STRUCT_DECLARATION_H_
#define DECLARATION_STRUCT_DECLARATION_H_

#include <declaration/declaration.h>
#include <core/identifier.h>

#include <memory>

namespace cassio {

/**
 * @class StructDeclaration
 * @brief
 *
 * ...
 *
 */
class StructDeclaration : public Declaration {
 public:
  static std::unique_ptr<Declaration> Construct(std::list<Token> &tokens);
  std::string Generate() override;
  void Semanticate() override;
  void RetrieveType(std::list<struct MemberType> &sub_types) override;

 private:
  std::unique_ptr<Identifier> identifier_;
  std::unique_ptr<Declaration> inner_declaration_;
  std::unique_ptr<Declaration> declaration_;
};

}

#endif // DECLARATION_STRUCT_DECLARATION_H_
