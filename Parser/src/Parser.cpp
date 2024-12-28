#include "Parser.h"
#include "Lexer.h"

std::unique_ptr<Parser::Expr> Parser::RecursiveDescentParser::Parse() {
  return Expression();
}
//
std::unique_ptr<Parser::Expr> Parser::RecursiveDescentParser::Expression() {
  return Equality();
}
std::unique_ptr<Parser::Expr> Parser::RecursiveDescentParser::Equality() {
  std::unique_ptr<Parser::Expr> expr = Comparison();

  while (
      Match({Lexer::TokenType::BANG_EQUAL, ::Lexer::TokenType::EQUAL_EQUAL})) {
    Lexer::Token op = Previous();
    std::unique_ptr<Parser::Expr> right = Comparison();
    expr =
        std::make_unique<Parser::Binary>(std::move(expr), op, std::move(right));
  }
  return expr;
}
std::unique_ptr<Parser::Expr> Parser::RecursiveDescentParser::Comparison() {
  std::unique_ptr<Parser::Expr> expr = Term();

  while (Match({Lexer::TokenType::LESS, Lexer::TokenType::LESS_EQUAL,
                Lexer::TokenType::GREATER, Lexer::TokenType::GREATER_EQUAL})) {
    Lexer::Token op = Previous();
    std::unique_ptr<Parser::Expr> right = Term();
    expr =
        std::make_unique<Parser::Binary>(std::move(expr), op, std::move(right));
  }
  return expr;
}
std::unique_ptr<Parser::Expr> Parser::RecursiveDescentParser::Term() {
  std::unique_ptr<Parser::Expr> expr = Factor();

  while (Match({Lexer::TokenType::PLUS, Lexer::TokenType::MINUS})) {
    Lexer::Token op = Previous();
    std::unique_ptr<Parser::Expr> right = Factor();
    expr =
        std::make_unique<Parser::Binary>(std::move(expr), op, std::move(right));
  }
  return expr;
}
std::unique_ptr<Parser::Expr> Parser::RecursiveDescentParser::Factor() {
  std::unique_ptr<Parser::Expr> expr = Unary();

  while (Match({Lexer::TokenType::MUL, Lexer::TokenType::DIV})) {
    Lexer::Token op = Previous();
    std::unique_ptr<Parser::Expr> right = Unary();
    expr =
        std::make_unique<Parser::Binary>(std::move(expr), op, std::move(right));
  }
  return expr;
}
std::unique_ptr<Parser::Expr> Parser::RecursiveDescentParser::Unary() {
  if (Match({Lexer::TokenType::BANG, Lexer::TokenType::MINUS})) {
    Lexer::Token op = Previous();
    std::unique_ptr<Parser::Expr> right = Unary();
    return std::make_unique<Parser::Unary>(op, std::move(right));
  }
  return Primary();
}
std::unique_ptr<Parser::Expr> Parser::RecursiveDescentParser::Primary() {
  std::unique_ptr<Expr> expr_ = nullptr;
  if (Match({Lexer::TokenType::FALSE_LIT})) {
    expr_ = std::make_unique<Parser::Literal<bool>>(false);
  } else if (Match({Lexer::TokenType::TRUE_LIT})) {
    expr_ = std::make_unique<Parser::Literal<bool>>(true);
  } else if (Match({Lexer::TokenType::STRING_LIT})) {
    expr_ = std::make_unique<Parser::Literal<std::string>>(Previous().lexeme);
  } else if (Match({Lexer::TokenType::INTEGER_LIT})) {
    int i = std::stoi(Previous().lexeme);
    expr_ = std::make_unique<Parser::Literal<int>>(i);
  } else if (Match({Lexer::TokenType::LPAREN})) {
    std::unique_ptr<Parser::Expr> group = Expression();
    Consume(Lexer::TokenType::RPAREN, "Expect ')' after expression.");
    expr_ = std::make_unique<Parser::Grouping>(std::move(group));
  } else {
    // TODO: Handle error properly
    printf("Not a Non terminal. (%s)\n", Peek().lexeme.c_str());
  }
  return expr_;
}

bool Parser::RecursiveDescentParser::Match(
    std::vector<Lexer::TokenType> types) {
  for (auto &type : types) {
    if (Check(type)) {
      Advance();
      return true;
    }
  }
  return false;
}

bool Parser::RecursiveDescentParser::Check(Lexer::TokenType type) {
  if (IsAtEnd())
    return false;
  return Peek().type == type;
}

Lexer::Token Parser::RecursiveDescentParser::Peek() { return tokens[current]; }

Lexer::Token Parser::RecursiveDescentParser::Advance() {
  if (!IsAtEnd()) {
    current++;
  }
  return Previous();
}
Lexer::Token Parser::RecursiveDescentParser::Previous() {
  return tokens[current - 1];
}
bool Parser::RecursiveDescentParser::IsAtEnd() {
  return Peek().type == Lexer::TokenType::EOF_;
}
Lexer::Token Parser::RecursiveDescentParser::Consume(Lexer::TokenType type,
                                                     std::string msg) {
  if (Check(type))
    return Advance();
  printf("Parse Error: %s\n", msg.c_str());
  return Lexer::Token(Lexer::TokenType::EOF_, msg);
}
