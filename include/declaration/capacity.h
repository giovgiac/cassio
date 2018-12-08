/**
 * @file capacity.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef DECLARATION_CAPACITY_H_
#define DECLARATION_CAPACITY_H_

#include <core/number.h>
#include <tokens/token.h>

#include <list>

namespace cassio {

/**
 * @class Capacity
 * @brief
 *
 * ...
 *
 */
class Capacity {
 public:
  static std::unique_ptr<Capacity> Construct(std::list<Token> &tokens);

  uint64_t GetCapacity() const { return number_->GetNumber(); }

 private:
  std::unique_ptr<Number> number_;
};

}

#endif // DECLARATION_CAPACITY_H_
