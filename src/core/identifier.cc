/**
 * @file identifier.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <core/identifier.h>

namespace cassio {

std::unique_ptr<Identifier> Identifier::Construct(std::string identifier) {
  std::unique_ptr<Identifier> result{new Identifier};

  result->identifier_ = std::move(identifier);
  return result;
}

}
