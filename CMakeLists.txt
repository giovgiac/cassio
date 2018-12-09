#
# CMakeLists.txt
#
# Copyright (c) 2018 All Rights Reserved.
#

CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(cassio)

INCLUDE_DIRECTORIES(
        "include"
)

# Debug Files
CONFIGURE_FILE(
        ${CMAKE_CURRENT_SOURCE_DIR}/exhaust.cas
        ${CMAKE_CURRENT_BINARY_DIR}
        COPYONLY
)
CONFIGURE_FILE(
        ${CMAKE_CURRENT_SOURCE_DIR}/light.cas
        ${CMAKE_CURRENT_BINARY_DIR}
        COPYONLY
)
CONFIGURE_FILE(
        ${CMAKE_CURRENT_SOURCE_DIR}/vector.cas
        ${CMAKE_CURRENT_BINARY_DIR}
        COPYONLY
)

SET(CMAKE_CXX_STANDARD 17)
SET(SOURCES
        src/cassio.cc
        src/analyzer/lexical_analyzer.cc
        src/utils/file.cc
        src/analyzer/syntatic_analyzer.cc
        src/core/program.cc
        src/declaration/declaration.cc
        src/declaration/struct_declaration.cc
        src/core/identifier.cc
        src/declaration/type_declaration.cc
        src/core/number.cc
        src/declaration/capacity.cc
        src/core/child.cc
        src/expressions/register_expression.cc
        src/expressions/variable_expression.cc
        src/expressions/number_expression.cc
        src/expressions/value_expression.cc
        src/expressions/expression.cc
        src/expressions/low_expression.cc
        src/expressions/math_expression.cc
        src/expressions/logical_expression.cc
        src/expressions/boolean_expression.cc
        src/expressions/not_expression.cc
        src/expressions/function_expression.cc
        src/function/parameter.cc
        src/function/type_parameter.cc
        src/function/register_parameter.cc
        src/function/function.cc
        src/expressions/string_expression.cc
        src/function/return_instruction.cc
        src/function/register_instruction.cc
        src/function/value_instruction.cc
        src/function/instruction.cc
        src/function/variable_instruction.cc
        src/function/while_instruction.cc
        src/function/if_instruction.cc
        src/analyzer/semantic_analyzer.cc
        src/declaration/defined_declaration.cc
        src/analyzer/code_generator.cc
        src/function/output_instruction.cc
        src/expressions/input_expression.cc)
SET(HEADERS
        include/analyzer/lexical_analyzer.h
        include/tokens/token.h
        include/utils/file.h
        include/analyzer/syntatic_analyzer.h
        include/core/program.h
        include/declaration/declaration.h
        include/function/function.h
        include/declaration/type_declaration.h
        include/core/identifier.h
        include/core/number.h
        include/declaration/capacity.h
        include/declaration/struct_declaration.h
        include/expressions/low_expression.h
        include/expressions/expression.h
        include/core/syntax_error.h
        include/core/child.h
        include/expressions/math_expression.h
        include/expressions/register_expression.h
        include/expressions/variable_expression.h
        include/expressions/number_expression.h
        include/expressions/value_expression.h
        include/expressions/logical_expression.h
        include/expressions/boolean_expression.h
        include/expressions/not_expression.h
        include/expressions/function_expression.h
        include/function/parameter.h
        include/function/type_parameter.h
        include/function/register_parameter.h
        include/expressions/string_expression.h
        include/function/instruction.h
        include/function/return_instruction.h
        include/function/register_instruction.h
        include/function/value_instruction.h
        include/function/variable_instruction.h
        include/function/while_instruction.h
        include/function/if_instruction.h
        include/analyzer/semantic_analyzer.h
        include/declaration/defined_declaration.h
        include/analyzer/code_generator.h
        include/core/semantic_error.h
        include/function/output_instruction.h
        include/expressions/input_expression.h)

ADD_EXECUTABLE(cassio
        ${HEADERS} ${SOURCES})
