#pragma once
#include "Lexer.h"
#include <cstdio>
#include <initializer_list>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

namespace Parser {

class Expr;
class Unary;
class Binary;
class Grouping;
template <typename T> class Literal;

class Visitor {
public:
  virtual void VisitUnaryExpr(Unary &expr) = 0;
  virtual void VisitBinaryExpr(Binary &expr) = 0;
  virtual void VisitGroupingExpr(Grouping &expr) = 0;
  virtual void VisitLiteralExpr(Literal<int> &expr) = 0;
  virtual void VisitLiteralExpr(Literal<std::string> &expr) = 0;
  virtual void VisitLiteralExpr(Literal<bool> &expr) = 0;
};

class Expr {
public:
  virtual ~Expr() {}
  virtual void Accept(Visitor &visitor) {}
};

class Unary : public Expr {
public:
  const Lexer::Token op;
  std::unique_ptr<Expr> right;
  Unary(Lexer::Token op, std::unique_ptr<Expr> right)
      : op(op), right(std::move(right)) {}
  ~Unary() override { right.reset(); }
  void Accept(Visitor &visitor) override { visitor.VisitUnaryExpr(*this); }
};

class Binary : public Expr {
public:
  std::unique_ptr<Expr> left;
  const Lexer::Token op;
  std::unique_ptr<Expr> right;
  Binary(std::unique_ptr<Expr> left, Lexer::Token op,
         std::unique_ptr<Expr> right)
      : left(std::move(left)), op(op), right(std::move(right)) {}
  ~Binary() override {
    left.reset();
    right.reset();
  }
  void Accept(Visitor &visitor) override { visitor.VisitBinaryExpr(*this); }
};

class Grouping : public Expr {
public:
  std::unique_ptr<Expr> expression;
  Grouping(std::unique_ptr<Expr> expression)
      : expression(std::move(expression)) {}
  ~Grouping() override { expression.reset(); }
  void Accept(Visitor &visitor) override { visitor.VisitGroupingExpr(*this); }
};

// TODO: make literal for each
template <typename T> class Literal : public Expr {
public:
  T value;
  Literal(T value) : value(value) {}
  void Accept(Visitor &visitor) override { visitor.VisitLiteralExpr(*this); }
};

class AstPrinter : public Visitor {
public:
  AstPrinter(std::ostream &ss) : ss(ss) {}
  void VisitUnaryExpr(Unary &expr) override;
  void VisitBinaryExpr(Binary &expr) override;
  void VisitGroupingExpr(Grouping &expr) override;
  void VisitLiteralExpr(Literal<int> &expr) override;
  void VisitLiteralExpr(Literal<std::string> &expr) override;
  void VisitLiteralExpr(Literal<bool> &expr) override;

private:
  std::ostream &ss;
  void Parenthesize(std::string name, std::initializer_list<Expr *> exprs);
};

class RecursiveDescentParser {
public:
  RecursiveDescentParser(const std::vector<Lexer::Token> tokens)
      : tokens(tokens) {
    current = 0;
  }
  std::unique_ptr<Expr> Parse();

private:
  const std::vector<Lexer::Token> tokens;
  int current;

  // Parsing
  std::unique_ptr<Expr> Expression();
  std::unique_ptr<Expr> Equality();
  std::unique_ptr<Expr> Comparison();
  std::unique_ptr<Expr> Term();
  std::unique_ptr<Expr> Factor();
  std::unique_ptr<Expr> Unary();
  std::unique_ptr<Expr> Primary();

  // Helper for parsing
  bool Check(Lexer::TokenType type);
  bool IsAtEnd();
  bool Match(std::vector<Lexer::TokenType> types);
  Lexer::Token Peek();
  Lexer::Token Previous();
  Lexer::Token Advance();
  Lexer::Token Consume(Lexer::TokenType type, std::string msg);
};
} // namespace Parser
