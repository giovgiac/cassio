/**
 * @file defined_declaration.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef DECLARATION_DEFINED_DECLARATION_H_
#define DECLARATION_DEFINED_DECLARATION_H_

#include <core/identifier.h>
#include <declaration/capacity.h>
#include <declaration/declaration.h>

namespace cassio {

class DefinedDeclaration : public Declaration {
 public:
  static std::unique_ptr<Declaration> Construct(std::list<Token> &tokens);
  std::string Generate() override;
  void Semanticate() override;
  void RetrieveType(std::list<struct MemberType> &sub_types) override;

 private:
  std::unique_ptr<Identifier> identifier_;
  std::unique_ptr<Identifier> type_;
  std::unique_ptr<Capacity> capacity_;
  std::unique_ptr<Declaration> declaration_;
};

}

#endif // DECLARATION_DEFINED_DECLARATION_H_
