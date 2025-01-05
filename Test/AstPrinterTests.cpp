#include "AstPrinter.h"
#include "Lexer.h"
#include "Parser.h"
#include <gtest/gtest.h>
#include <sstream>
#include <string>

namespace {
TEST(AstPrinter_Test, IntLiteral) {
  Parser::Literal<int> lit(100);
  ASSERT_EQ(lit.value, 100);
}
TEST(AstPrinter_Test, StringLiteral) {
  Parser::Literal<std::string> lit("Hello World");

  std::ostringstream ss;
  Parser::AstPrinter printer(ss);
  lit.Accept(printer);
  ASSERT_EQ(ss.str(), "(string \"Hello World\")");
}
TEST(AstPrinter_Test, BoolLiteral) {
  Parser::Literal<bool> t(true);
  Parser::Literal<bool> f(false);
  std::ostringstream ss;
  Parser::AstPrinter printer(ss);
  t.Accept(printer);
  ASSERT_EQ(ss.str(), "(bool true)");
  ss.str("");
  f.Accept(printer);
  ASSERT_EQ(ss.str(), "(bool false)");
}
TEST(AstPrinter_Test, SumTwoInt) {
  auto a = std::make_unique<Parser::Literal<int>>(100);
  auto b = std::make_unique<Parser::Literal<int>>(23);
  Lexer::Token op(Lexer::TokenType::PLUS, "+");
  Parser::Binary sum(std::move(a), op, std::move(b));

  std::ostringstream ss;
  Parser::AstPrinter printer(ss);

  sum.Accept(printer);
  ASSERT_EQ(ss.str(), "(+ (int 100) (int 23))");
}
} // namespace
