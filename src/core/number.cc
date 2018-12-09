/**
 * @file number.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <core/number.h>

namespace cassio {

std::unique_ptr<Number> Number::Construct(std::string number) {
  std::unique_ptr<Number> result = std::make_unique<Number>();

  result->number_ = std::move(number);
  return std::move(result);
}

}
