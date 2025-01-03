#pragma once
#include <istream>
#include <string>

namespace Lexer {

// _<type>_ ::= "int" | "bool" | "char" | "string" | "void" | "float";
enum KeywordType { INT, BOOL, CHAR, STRING, VOID, FLOAT };
enum TokenType {
  // Keywords
  INTEGER_KEYWORD,
  STRING_KEYWORD,
  BOOL_KEYWORD,

  // Literals
  INTEGER_LIT,
  STRING_LIT,
  TRUE_LIT,
  FALSE_LIT,

  // Equality operators
  BANG_EQUAL,  // !=
  EQUAL_EQUAL, // ==

  // Comparison Operators
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,

  // Operators
  ASSIGNMENT, // =
  BANG,       // !
  PLUS,
  MINUS,
  MUL,
  DIV,
  MOD,

  IDENTIFIER,

  // Parenthesis
  LPAREN,
  RPAREN,
  // Curly Braces
  LBRACE,
  RBRACE,

  SEMICOLON,

  EOF_
};
class Token {
public:
  Token(TokenType type, std::string lexeme) : type(type), lexeme(lexeme) {}
  TokenType type;
  std::string lexeme;
};

class Lexer {
public:
  Lexer(std::istream &input) : _input(input) {}
  Token Lex();
  Token token = Token(TokenType::EOF_, "");

private:
  std::istream &_input;
  // Lookahead are extra characters peeked
  char c; // Current character. May contain lookahead
  bool hasLookAhead = false;
};
} // namespace Lexer
