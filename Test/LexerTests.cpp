#include <Lexer.h>
#include <gtest/gtest.h>
#include <sstream>

namespace {
void EXPECT_TOKEN(Lexer::Token token, Lexer::TokenType type,
                  std::string lexeme) {
  EXPECT_EQ(type, token.type);
  EXPECT_EQ(lexeme, token.lexeme);
}

TEST(LexerTest, Print_Hello_World) {
  constexpr char input[] = "print(\"Hello, World!\"); \n";
  std::stringstream ss(input);
  Lexer::Lexer lexer(ss);

  EXPECT_TOKEN(lexer.Lex(), Lexer::IDENTIFIER, "print");
  EXPECT_TOKEN(lexer.Lex(), Lexer::LPAREN, "(");
  EXPECT_TOKEN(lexer.Lex(), Lexer::STRING_LIT, "Hello, World!");
  EXPECT_TOKEN(lexer.Lex(), Lexer::RPAREN, ")");
  EXPECT_TOKEN(lexer.Lex(), Lexer::SEMICOLON, ";");
  EXPECT_TOKEN(lexer.Lex(), Lexer::EOF_, "");
}

TEST(LexerTest, Init_Integer_Variable) {
  constexpr char input[] = "int i = 9000;";
  std::stringstream ss(input);
  Lexer::Lexer lexer(ss);
  EXPECT_TOKEN(lexer.Lex(), Lexer::INTEGER_KEYWORD, "int");
  EXPECT_TOKEN(lexer.Lex(), Lexer::IDENTIFIER, "i");
  EXPECT_TOKEN(lexer.Lex(), Lexer::ASSIGNMENT, "=");
  EXPECT_TOKEN(lexer.Lex(), Lexer::INTEGER_LIT, "9000");
  EXPECT_TOKEN(lexer.Lex(), Lexer::SEMICOLON, ";");
  EXPECT_TOKEN(lexer.Lex(), Lexer::EOF_, "");
}
TEST(LexerTest, Init_String_Variable) {
  constexpr char input[] = "string str = \"this is my string\";";
  std::stringstream ss(input);
  Lexer::Lexer lexer(ss);
  EXPECT_TOKEN(lexer.Lex(), Lexer::STRING_KEYWORD, "string");
  EXPECT_TOKEN(lexer.Lex(), Lexer::IDENTIFIER, "str");
  EXPECT_TOKEN(lexer.Lex(), Lexer::ASSIGNMENT, "=");
  EXPECT_TOKEN(lexer.Lex(), Lexer::STRING_LIT, "this is my string");
  EXPECT_TOKEN(lexer.Lex(), Lexer::SEMICOLON, ";");
  EXPECT_TOKEN(lexer.Lex(), Lexer::EOF_, "");
}

} // namespace
