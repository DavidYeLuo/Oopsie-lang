#include <Parser.h>
#include <gtest/gtest.h>
#include <sstream>

namespace {
TEST(ParserTest, ExpressionTest) {
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
  Parser::AstPrinter printer(printer_ss);

  std::unique_ptr<Parser::Expr> expr = parser.Parse();

  expr->Accept(printer);

  ASSERT_EQ(printer_ss.str(), "(* (- (int 123)) (group (int 45)))");
}

} // namespace
