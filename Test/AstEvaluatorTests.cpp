#include "AstEvaluator.h"
#include "Lexer.h"
#include "Parser.h"
#include <gtest/gtest.h>
#include <sstream>
#include <string>

namespace {
TEST(ParserEvaluatorTests, SimpleSum) {
  constexpr char input[] = "-123 * (45)";
  std::stringstream ss(input);
  Lexer::Lexer lexer(ss);
  std::vector<Lexer::Token> tokens;
  Lexer::Token token = lexer.Lex();
  while (token.type != Lexer::TokenType::EOF_) {
    tokens.push_back(token);
    token = lexer.Lex();
  }
  tokens.push_back(token);
  Parser::RecursiveDescentParser parser(tokens);

  std::stringstream printer_ss;
  Parser::AstEvaluator evaluator;

  std::unique_ptr<Parser::Expr> expr = parser.Parse();

  ASSERT_EQ(evaluator.Eval(*expr), "-5535");
}

} // namespace
