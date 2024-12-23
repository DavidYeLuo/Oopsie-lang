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
TEST(LexerTest, Init_Bool_Variable_As_True) {
  constexpr char input[] = "bool isTrue = true;";
  std::stringstream ss(input);
  Lexer::Lexer lexer(ss);
  EXPECT_TOKEN(lexer.Lex(), Lexer::BOOL_KEYWORD, "bool");
  EXPECT_TOKEN(lexer.Lex(), Lexer::IDENTIFIER, "isTrue");
  EXPECT_TOKEN(lexer.Lex(), Lexer::ASSIGNMENT, "=");
  EXPECT_TOKEN(lexer.Lex(), Lexer::TRUE_LIT, "true");
  EXPECT_TOKEN(lexer.Lex(), Lexer::SEMICOLON, ";");
  EXPECT_TOKEN(lexer.Lex(), Lexer::EOF_, "");
}
TEST(LexerTest, Init_Bool_Variable_As_False) {
  constexpr char input[] = "bool isTrue = false;";
  std::stringstream ss(input);
  Lexer::Lexer lexer(ss);
  EXPECT_TOKEN(lexer.Lex(), Lexer::BOOL_KEYWORD, "bool");
  EXPECT_TOKEN(lexer.Lex(), Lexer::IDENTIFIER, "isTrue");
  EXPECT_TOKEN(lexer.Lex(), Lexer::ASSIGNMENT, "=");
  EXPECT_TOKEN(lexer.Lex(), Lexer::FALSE_LIT, "false");
  EXPECT_TOKEN(lexer.Lex(), Lexer::SEMICOLON, ";");
  EXPECT_TOKEN(lexer.Lex(), Lexer::EOF_, "");
}
TEST(LexerTest, Init_Integer_Sum) {
  constexpr char input[] = "int i = 9 + 10;";
  std::stringstream ss(input);
  Lexer::Lexer lexer(ss);
  EXPECT_TOKEN(lexer.Lex(), Lexer::INTEGER_KEYWORD, "int");
  EXPECT_TOKEN(lexer.Lex(), Lexer::IDENTIFIER, "i");
  EXPECT_TOKEN(lexer.Lex(), Lexer::ASSIGNMENT, "=");
  EXPECT_TOKEN(lexer.Lex(), Lexer::INTEGER_LIT, "9");
  EXPECT_TOKEN(lexer.Lex(), Lexer::PLUS, "+");
  EXPECT_TOKEN(lexer.Lex(), Lexer::INTEGER_LIT, "10");
  EXPECT_TOKEN(lexer.Lex(), Lexer::SEMICOLON, ";");
  EXPECT_TOKEN(lexer.Lex(), Lexer::EOF_, "");
}
TEST(LexerTest, Init_Integer_Minus) {
  constexpr char input[] = "int i = 9 - 10;";
  std::stringstream ss(input);
  Lexer::Lexer lexer(ss);
  EXPECT_TOKEN(lexer.Lex(), Lexer::INTEGER_KEYWORD, "int");
  EXPECT_TOKEN(lexer.Lex(), Lexer::IDENTIFIER, "i");
  EXPECT_TOKEN(lexer.Lex(), Lexer::ASSIGNMENT, "=");
  EXPECT_TOKEN(lexer.Lex(), Lexer::INTEGER_LIT, "9");
  EXPECT_TOKEN(lexer.Lex(), Lexer::MINUS, "-");
  EXPECT_TOKEN(lexer.Lex(), Lexer::INTEGER_LIT, "10");
  EXPECT_TOKEN(lexer.Lex(), Lexer::SEMICOLON, ";");
  EXPECT_TOKEN(lexer.Lex(), Lexer::EOF_, "");
}
TEST(LexerTest, Init_Integer_Mult) {
  constexpr char input[] = "int i = 9 * 10;";
  std::stringstream ss(input);
  Lexer::Lexer lexer(ss);
  EXPECT_TOKEN(lexer.Lex(), Lexer::INTEGER_KEYWORD, "int");
  EXPECT_TOKEN(lexer.Lex(), Lexer::IDENTIFIER, "i");
  EXPECT_TOKEN(lexer.Lex(), Lexer::ASSIGNMENT, "=");
  EXPECT_TOKEN(lexer.Lex(), Lexer::INTEGER_LIT, "9");
  EXPECT_TOKEN(lexer.Lex(), Lexer::MUL, "*");
  EXPECT_TOKEN(lexer.Lex(), Lexer::INTEGER_LIT, "10");
  EXPECT_TOKEN(lexer.Lex(), Lexer::SEMICOLON, ";");
  EXPECT_TOKEN(lexer.Lex(), Lexer::EOF_, "");
}
TEST(LexerTest, Init_Integer_Div) {
  constexpr char input[] = "int i = 9 / 10;";
  std::stringstream ss(input);
  Lexer::Lexer lexer(ss);
  EXPECT_TOKEN(lexer.Lex(), Lexer::INTEGER_KEYWORD, "int");
  EXPECT_TOKEN(lexer.Lex(), Lexer::IDENTIFIER, "i");
  EXPECT_TOKEN(lexer.Lex(), Lexer::ASSIGNMENT, "=");
  EXPECT_TOKEN(lexer.Lex(), Lexer::INTEGER_LIT, "9");
  EXPECT_TOKEN(lexer.Lex(), Lexer::DIV, "/");
  EXPECT_TOKEN(lexer.Lex(), Lexer::INTEGER_LIT, "10");
  EXPECT_TOKEN(lexer.Lex(), Lexer::SEMICOLON, ";");
  EXPECT_TOKEN(lexer.Lex(), Lexer::EOF_, "");
}
TEST(LexerTest, Init_Integer_Mod) {
  constexpr char input[] = "int i = 9 % 10;";
  std::stringstream ss(input);
  Lexer::Lexer lexer(ss);
  EXPECT_TOKEN(lexer.Lex(), Lexer::INTEGER_KEYWORD, "int");
  EXPECT_TOKEN(lexer.Lex(), Lexer::IDENTIFIER, "i");
  EXPECT_TOKEN(lexer.Lex(), Lexer::ASSIGNMENT, "=");
  EXPECT_TOKEN(lexer.Lex(), Lexer::INTEGER_LIT, "9");
  EXPECT_TOKEN(lexer.Lex(), Lexer::MOD, "%");
  EXPECT_TOKEN(lexer.Lex(), Lexer::INTEGER_LIT, "10");
  EXPECT_TOKEN(lexer.Lex(), Lexer::SEMICOLON, ";");
  EXPECT_TOKEN(lexer.Lex(), Lexer::EOF_, "");
}

} // namespace
