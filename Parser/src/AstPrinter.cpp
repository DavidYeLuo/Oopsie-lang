#include "Parser.h"
#include <string>

void Parser::AstPrinter::Parenthesize(
    std::string name, std::initializer_list<Parser::Expr *> exprs) {
  ss << "(" << name;
  for (auto expr : exprs) {
    ss << " ";
    expr->Accept(*this);
  }
  ss << ")";
}
void Parser::AstPrinter::VisitUnaryExpr(Parser::Unary &expr) {
  Parser::Expr *right = expr.right.get();
  Parenthesize(expr.op.lexeme, {right});
}
void Parser::AstPrinter::VisitBinaryExpr(Parser::Binary &expr) {
  Parser::Expr *right = expr.right.get();
  Parser::Expr *left = expr.left.get();
  Parenthesize(expr.op.lexeme, {left, right});
}
void Parser::AstPrinter::VisitGroupingExpr(Parser::Grouping &expr) {
  Parser::Expr *expression = expr.expression.get();
  Parenthesize("group", {expression});
}
void Parser::AstPrinter::VisitLiteralExpr(Parser::Literal<int> &expr) {
  ss << "(int " << expr.value << ")";
}
void Parser::AstPrinter::VisitLiteralExpr(Parser::Literal<std::string> &expr) {
  ss << "(string \"" << expr.value << "\")";
}
void Parser::AstPrinter::VisitLiteralExpr(Parser::Literal<bool> &expr) {
  ss << "(bool " << (expr.value ? "true" : "false") << ")";
}
