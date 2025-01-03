#include "Lexer.h"
#include <cstdio>
Lexer::Token Lexer::Lexer::Lex() {
  if (!hasLookAhead) {
    c = _input.get();
  }
  hasLookAhead = false;

  // skip whitespace
  while (c == ' ' || c == '\t' || c == '\n') {
    c = _input.get();
  }

  switch (c) {
  case '(':
    return Token(TokenType::LPAREN, "(");
  case ')':
    return Token(TokenType::RPAREN, ")");
  case '{':
    return Token(TokenType::LBRACE, "{");
  case '}':
    return Token(TokenType::RBRACE, "}");
  case ';':
    return Token(TokenType::SEMICOLON, ";");
  case '+':
    return Token(TokenType::PLUS, "+");
  case '-':
    return Token(TokenType::MINUS, "-");
  case '*':
    return Token(TokenType::MUL, "*");
  case '/':
    return Token(TokenType::DIV, "/");
  case '%':
    return Token(TokenType::MOD, "%");
  case '=':
    c = _input.get();
    if (c == '=')
      return Token(TokenType::EQUAL_EQUAL, "==");
    else {
      hasLookAhead = true;
      return Token(TokenType::ASSIGNMENT, "=");
    }
  case '!':
    c = _input.get();
    if (c == '=') {
      return Token(TokenType::BANG_EQUAL, "!=");
    } else {
      hasLookAhead = true;
      return Token(TokenType::BANG, "!=");
    }
  case '>':
    c = _input.get();
    if (c == '=')
      return Token(TokenType::GREATER_EQUAL, ">=");
    else {
      hasLookAhead = true;
      return Token(TokenType::GREATER, ">");
    }
  case '<':
    c = _input.get();
    if (c == '=')
      return Token(TokenType::LESS_EQUAL, "<=");
    else {
      hasLookAhead = true;
      return Token(TokenType::LESS, "<");
    }
  case EOF:
    return Token(TokenType::EOF_, "");
  default:
    if (isdigit(c)) {
      std::string lexeme = "";
      // TODO: add support for floating point numbers
      while (isdigit(c)) {
        lexeme += c;
        c = _input.get();
      }
      hasLookAhead = true;
      return Token(TokenType::INTEGER_LIT, lexeme);
    } else if (c == '"') {
      std::string lexeme = "";
      c = _input.get(); // consumes opening quotes
      while (c != '"') {
        lexeme += c;
        c = _input.get();
      }
      // NOTE: Let the next Lex() call consume the closing quote
      // _input.get(); // consumes closing quotes
      return Token(TokenType::STRING_LIT, lexeme);
    } else if (isalpha(c)) { // It is either an identifier or keyword
      std::string lexeme = "";
      while (isalpha(c) || isdigit(c)) {
        lexeme += c;
        c = _input.get();
      }
      hasLookAhead = true;

      // TODO: avoid using hardcoded keywords
      if (lexeme == "int") {
        return Token(TokenType::INTEGER_KEYWORD, lexeme);
      } else if (lexeme == "string") {
        return Token(TokenType::STRING_KEYWORD, lexeme);
      } else if (lexeme == "bool") {
        return Token(TokenType::BOOL_KEYWORD, lexeme);
      } else if (lexeme == "true") {
        return Token(TokenType::TRUE_LIT, lexeme);
      } else if (lexeme == "false") {
        return Token(TokenType::FALSE_LIT, lexeme);
      }

      return Token(TokenType::IDENTIFIER, lexeme);
    }
  }
  return Token(TokenType::EOF_, "Shouldn't get here");
}
