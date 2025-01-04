#include "Lexer.h"
#include <cstdio>

namespace Lexer {
const std::unordered_map<char, TokenType> simpleSymbolMap{
    {'(', TokenType::LPAREN},    {')', TokenType::RPAREN},
    {'{', TokenType::LBRACE},    {'}', TokenType::RBRACE},

    {';', TokenType::SEMICOLON},

    {'+', TokenType::PLUS},      {'-', TokenType::MINUS},
    {'*', TokenType::MUL},       {'/', TokenType::DIV},
    {'%', TokenType::MOD},
};
const std::unordered_map<std::string, TokenType> keywordMap{
    {"int", TokenType::INTEGER_KEYWORD}, {"string", TokenType::STRING_KEYWORD},
    {"bool", TokenType::BOOL_KEYWORD},

    {"true", TokenType::TRUE_LIT},       {"false", TokenType::FALSE_LIT},
};
} // namespace Lexer

Lexer::Token Lexer::Lexer::Lex() {
  /// Removes white space
  while (Match({' ', '\t', '\n'}))
    ;
  if (IsAtEnd()) {
    return Token(TokenType::EOF_, "");
  }

  TokenType _tokenType;
  std::string _lexeme;
  auto simpleType = simpleSymbolMap.find(c);
  if (simpleType != simpleSymbolMap.end()) {
    _tokenType = simpleType->second;
    _lexeme = simpleType->first;
    Advance();
  } else if (Match('=')) {
    _tokenType = TokenType::ASSIGNMENT;
    _lexeme = "=";
    if (Match('=')) {
      _tokenType = TokenType::EQUAL_EQUAL;
      _lexeme = "==";
    }
  } else if (Match('!')) {
    _tokenType = TokenType::BANG;
    _lexeme = "!";
    if (Match('=')) {
      _tokenType = TokenType::BANG_EQUAL;
      _lexeme = "!=";
    }
  } else if (Match('>')) {
    _tokenType = TokenType::GREATER;
    _lexeme = ">";
    if (Match('=')) {
      _tokenType = TokenType::GREATER_EQUAL;
      _lexeme = ">=";
    }
  } else if (Match('<')) {
    _tokenType = TokenType::LESS;
    _lexeme = "<";
    if (Match('=')) {
      _tokenType = TokenType::LESS_EQUAL;
      _lexeme = "<=";
    }
  } else if (isdigit(c)) {
    std::string lexeme = "";
    // Parse Int Literal
    // TODO: add support for floating point numbers
    while (isdigit(c)) {
      lexeme += c;
      Advance();
    }
    _tokenType = TokenType::INTEGER_LIT;
    _lexeme = lexeme;
  } else if (Match('"')) {
    // Parse String Literal
    std::string lexeme = "";
    while (!Match('"')) {
      lexeme += c;
      Advance();
    }
    _tokenType = TokenType::STRING_LIT;
    _lexeme = lexeme;
  } else if (isalpha(c)) { // It is either an identifier or keyword
    std::string lexeme = "";
    while (isalpha(c) || isdigit(c)) {
      lexeme += c;
      Advance();
    }
    _tokenType = TokenType::IDENTIFIER;
    _lexeme = lexeme;

    // TODO: avoid using hardcoded keywords
    auto it = keywordMap.find(lexeme);
    if (it != keywordMap.end()) {
      _tokenType = it->second;
    }
  }
  return Token(_tokenType, _lexeme);
}

char Lexer::Lexer::Advance() {
  char prev = c;
  c = _input.get();
  return prev;
}

bool Lexer::Lexer::Check(char c) { return c == this->c; }

bool Lexer::Lexer::Match(char c) {
  bool isMatch = Check(c);
  if (isMatch)
    Advance();
  return isMatch;
}

bool Lexer::Lexer::Match(const std::vector<char> &characters) {
  for (const char &c : characters) {
    if (Check(c)) {
      Advance();
      return true;
    }
  }
  return false;
}

bool Lexer::Lexer::IsAtEnd() { return _input.eof(); }
