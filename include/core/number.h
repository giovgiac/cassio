/**
 * @file number.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef EXPRESSIONS_NUMBER_H_
#define EXPRESSIONS_NUMBER_H_

#include <string>
#include <memory>

namespace cassio {

/**
 * @class Number
 * @brief
 *
 * ...
 *
 */
class Number {
 public:
  static std::unique_ptr<Number> Construct(std::string number);

  uint64_t GetNumber() const { return std::stoul(number_); }

 private:
  std::string number_;
};

}

#endif // EXPRESSIONS_NUMBER_H_
