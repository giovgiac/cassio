/**
 * @file file.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <utils/file.h>

namespace cassio {

std::string File::ReadFile(const char *filename) {
  std::ifstream file(filename);
  return std::string(
      std::istreambuf_iterator<char>(file),
      std::istreambuf_iterator<char>());
}

}

