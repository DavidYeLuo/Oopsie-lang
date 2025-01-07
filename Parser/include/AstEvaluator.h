#pragma once
#include "Parser.h"

namespace Parser {
struct Data {
  Lexer::TokenType dataType;
  std::string stringData;
  int intData;
  bool boolData;
};
class AstEvaluator : public Visitor {
public:
  AstEvaluator() {}
  std::string Eval(Expr &expr);
  void VisitUnaryExpr(Unary &expr) override;
  void VisitBinaryExpr(Binary &expr) override;
  void VisitGroupingExpr(Grouping &expr) override;
  void VisitLiteralExpr(Literal<int> &expr) override;
  void VisitLiteralExpr(Literal<std::string> &expr) override;
  void VisitLiteralExpr(Literal<bool> &expr) override;

private:
  std::unordered_map<Expr *, Data> ret;
};
} // namespace Parser
