#pragma once
#include "Parser.h"
namespace Parser {
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
} // namespace Parser
