#include "Parser.h"
#include "Lexer.h"

std::unique_ptr<Parser::Expr> Parser::RecursiveDescentParser::Parse() {
  std::unique_ptr<Expr> expr = std::make_unique<Parser::Binary>(
      std::move(std::make_unique<Parser::Literal<int>>(100)),
      Lexer::Token(Lexer::TokenType::PLUS, "+"),
      std::move(std::make_unique<Parser::Literal<int>>(200)));
  std::ostringstream ss;
  Parser::AstPrinter visitor(ss);
  expr->Accept(visitor);
  std::printf("%s\n", ss.str().c_str());
  return expr;
}
//
// Parser::Expr &Parser::RecursiveDescentParser::Expression() {
//   return Equality();
// }
// Parser::Expr &Parser::RecursiveDescentParser::Equality() {
//   Parser::Expr &expr = Comparison();
//
//   while (
//       Match({Lexer::TokenType::BANG_EQUAL, ::Lexer::TokenType::EQUAL_EQUAL}))
//       {
//     Lexer::Token op = Parser::RecursiveDescentParser::Previous();
//     Parser::Expr &right = Parser::RecursiveDescentParser::Comparison();
//     expr = *(new Parser::Binary(expr, op, right));
//     // TODO: Push heapAlloc the expr
//   }
//   return expr;
// }
// Parser::Expr &Parser::RecursiveDescentParser::Term() {
//   // while(Match({Lexer::TokenType::}))
// }
// Parser::Expr &Parser::RecursiveDescentParser::Primary() {
//   Expr *expr_ = nullptr;
//   if (Match({Lexer::TokenType::TRUE_LIT, Lexer::TokenType::FALSE_LIT,
//              Lexer::TokenType::INTEGER_LIT, Lexer::TokenType::STRING_LIT})) {
//     expr_ = new Parser::Literal(Previous().lexeme);
//   } else {
//     printf("Not a Non terminal.\n");
//   }
//
//   heapAlloc.push_back(expr_);
//   return *expr_;
// }

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
  if (!IsAtEnd())
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
