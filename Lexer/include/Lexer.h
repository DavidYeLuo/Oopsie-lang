#pragma once
#include <istream>
#include <string>
#include <unordered_map>
#include <vector>

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
  Lexer(std::istream &input) : _input(input) {
    // Start at a known character
    if (!_input.eof()) {
      c = _input.get();
    }
  }
  Token Lex();
  Token token = Token(TokenType::EOF_, "");

private:
  std::istream &_input;
  char c;
  bool hasLookAhead = false;

  /// Move on to the next character
  char Advance();
  /// Returns true if End of File
  bool IsAtEnd();

  /// Returns true when current character is c
  bool Check(char c);

  /// Returns true and advance when character is c
  bool Match(char c);
  /// Returns true and advance when c is one of the characters
  bool Match(const std::vector<char> &characters);
};
} // namespace Lexer
