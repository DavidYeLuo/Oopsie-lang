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
TEST(ParserEvaluatorErrorTests, SingleInteger) {
  const char expected[] = "message int: 1234";
  Parser::Data data;
  data.dataType = Parser::EvalType::INTEGER;
  data.intData = 1234;
  Parser::EvalError err(data, "message");

  ASSERT_STREQ(err.msg.c_str(), expected);
}
TEST(ParserEvaluatorErrorTests, SingleBool) {
  const char expected[] = "message bool: true";
  Parser::Data data;
  data.dataType = Parser::EvalType::BOOL;
  data.boolData = true;
  Parser::EvalError err(data, "message");

  ASSERT_STREQ(err.msg.c_str(), expected);
}
TEST(ParserEvaluatorErrorTests, SingleString) {
  const char expected[] = "message string: hello world";
  Parser::Data data;
  data.dataType = Parser::EvalType::STRING;
  data.stringData = "hello world";
  Parser::EvalError err(data, "message");

  ASSERT_STREQ(err.msg.c_str(), expected);
}
TEST(ParserEvaluatorErrorTests, DoubleInteger) {
  const char expected[] = "message left int: 1234, right int: 4321";
  Parser::Data left;
  left.dataType = Parser::EvalType::INTEGER;
  left.intData = 1234;
  Parser::Data right;
  right.dataType = Parser::EvalType::INTEGER;
  right.intData = 4321;
  Parser::EvalError err(left, right, "message");

  ASSERT_STREQ(err.msg.c_str(), expected);
}
TEST(ParserEvaluatorErrorTests, OperatorError) {
  const char expected[] = "Unexpected token. Token: +";
  Lexer::Token token(Lexer::TokenType::PLUS, "+");
  Parser::EvalOperatorError err(token, "Unexpected token.");

  ASSERT_STREQ(err.msg.c_str(), expected);
}
} // namespace
