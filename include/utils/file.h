/**
 * @file file.h
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#ifndef UTILS_FILE_H_
#define UTILS_FILE_H_

#include <fstream>
#include <string>

namespace cassio {

/**
 * @class File
 * @brief
 *
 * ...
 *
 */
class File {
 public:
  /**
   * @fn ReadFile
   * @brief
   *
   * ...
   *
   * @param filename
   *
   * @return
   *
   */
  static std::string ReadFile(const char *filename);
};

}

#endif // UTILS_FILE_H_
