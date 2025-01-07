#pragma once
#include "Parser.h"

namespace Parser {
enum EvalType {
  INTEGER,
  BOOL,
  STRING,
};

/// Helper used to represent the evaluated operation
/// In Lox, the author used Java's Object class to represent many types
/// I haven't found a clever workaround in C++
struct Data {
  EvalType dataType;
  std::string stringData;
  int intData;
  bool boolData;
};
class AstEvaluator : public Visitor {
public:
  /// Returns the evaluated expression in string
  std::string Eval(Expr &expr);

  void VisitUnaryExpr(Unary &expr) override;
  void VisitBinaryExpr(Binary &expr) override;
  void VisitGroupingExpr(Grouping &expr) override;
  void VisitLiteralExpr(Literal<int> &expr) override;
  void VisitLiteralExpr(Literal<std::string> &expr) override;
  void VisitLiteralExpr(Literal<bool> &expr) override;

private:
  /// Evaluated output is placed in ret variable
  /// The author in Lox had their visitor pattern return a template type
  /// In C++ we can't have template virtual functions so this is a workaround
  std::unordered_map<Expr *, Data> ret;
};
} // namespace Parser
