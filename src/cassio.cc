/**
 * @file cassio.cc
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <analyzer/code_generator.h>
#include <analyzer/lexical_analyzer.h>
#include <analyzer/syntatic_analyzer.h>
#include <analyzer/semantic_analyzer.h>
#include <core/semantic_error.h>
#include <core/syntax_error.h>
#include <expressions/expression.h>
#include <function/function.h>
#include <function/parameter.h>
#include <utils/file.h>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc == 3) {
    std::string source_code = cassio::File::ReadFile(argv[1]);
    if (source_code.empty()) {
      std::cout << "\033[1;31merror:\033[0m file not found" << std::endl;
      return EXIT_FAILURE;
    }

    std::string_view source_code_view{source_code};
    std::unique_ptr<cassio::Program> program;
    auto& ref = cassio::SemanticAnalyzer::variables_;

    std::list<cassio::Token> tokens = cassio::Lex(source_code_view);

    try {
      std::ofstream file(argv[2]);

      program = cassio::Parse(tokens);
      program = cassio::SemanticAnalyzer::Semanticate(std::move(program));

      file << cassio::CodeGenerator::Generate(std::move(program));
      file.close();

      std::string cmd = std::string("fasm ") + std::string(argv[2]);
      system(cmd.c_str());
    }
    catch (cassio::SyntaxError &e) {
      char path[256];

      realpath(argv[1], path);
      std::cout << path << ":" << e.GetLine() << ":" << e.GetColumn()
                << ":" << " \033[1;31merror:\033[0m " << e.GetText() << std::endl;
    }
    catch (cassio::SemanticError &e) {
      std::cout << "\033[1;31msemantic error:\033[0m " << e.GetText() << std::endl;
    }

    return EXIT_SUCCESS;
  }
  else {
    std::cout << "EXECUTE AS: cassio <file.cas> <file.asm>" << std::endl;
    return EXIT_FAILURE;
  }
}
