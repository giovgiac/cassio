/**
 * @file function_expression.c
 * @brief
 *
 * @copyright Copyright (c) 2018 All Rights Reserved.
 *
 */

#include <analyzer/semantic_analyzer.h>
#include <core/semantic_error.h>
#include <core/syntax_error.h>
#include <expressions/function_expression.h>

namespace cassio {

std::unique_ptr<Expression> FunctionExpression::Construct(std::list<Token> &tokens) {
  std::unique_ptr<FunctionExpression> result = std::make_unique<FunctionExpression>();

  result->variable_ = std::move(Child::Construct(tokens));

  if (tokens.front().GetType() != TokenType::LEFT_PARENTHESIS)
    throw SyntaxError("expected '(' at function call",
                      tokens.front().GetLine(),
                      tokens.front().GetColumn());
  tokens.pop_front();

  result->argument_ = std::move(Expression::Construct(tokens, true, true, true));

  if (tokens.front().GetType() != TokenType::RIGHT_PARENTHESIS)
    throw SyntaxError("expected ')' at function call",
        tokens.front().GetLine(),
        tokens.front().GetColumn());
  tokens.pop_front();

  return result;
}

std::string FunctionExpression::Generate(bool generate_more) {
  auto var = SemanticAnalyzer::functions_[variable_->GetName()];
  std::ostringstream oss;

  uint64_t num = 0;
  std::unique_ptr<Expression> current = std::move(argument_);
  for (auto& a: var.argument_) {
    if (current) {
      oss << current->Generate(false);
      oss << "\tpush\trax";
      oss << "\n";

      current = std::move(current->GetMore());
      num++;
    }
    else {
      break;
    }
  }

  if (num != var.argument_.size())
    throw SemanticError("unexpected number of arguments at " + variable_->GetName() + " function call");

  oss << "\tcall\t" << var.name_;
  oss << "\n";

  for (auto& a: var.argument_) {
    oss << "\tpop\trsi";
    oss << "\n";
  }

  if (generate_more) {
    if (more_)
      oss << more_->Generate();
  }

  return oss.str();
}

void FunctionExpression::Semanticate() {
  variable_->Semanticate();

  if (argument_)
    argument_->Semanticate();

  if (more_)
    more_->Semanticate();
}

}
