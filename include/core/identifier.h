/**
 * @file identifier.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef EXPRESSIONS_IDENTIFIER_H_
#define EXPRESSIONS_IDENTIFIER_H_

#include <string>
#include <memory>

namespace cassio {

/**
 * @class Identifier
 * @brief
 *
 * ...
 *
 */
class Identifier {
 public:
  static std::unique_ptr<Identifier> Construct(std::string identifier);

  std::string GetText() const { return identifier_; }

 private:
  std::string identifier_;
};

}

#endif // EXPRESSIONS_IDENTIFIER_H_
