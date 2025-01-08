#include "AstEvaluator.h"
#include "Lexer.h"
#include <exception>
namespace Parser {
std::string AstEvaluator::Eval(Expr &expr) {
  ret.clear(); // In case we evaluate again but expr is changed and the object
               // is reused
  expr.Accept(*this);
  Data data = ret[&expr];
  std::string result = "";
  switch (data.dataType) {
  case EvalType::INTEGER:
    result = std::to_string(data.intData);
    break;
  case EvalType::STRING:
    result = data.stringData;
    break;
  case EvalType::BOOL:
    result = std::to_string(data.boolData);
    break;
  default:
    throw EvalError(data, "Unknown Datatype.");
    result = "";
    break;
  }
  return result;
}
void AstEvaluator::VisitUnaryExpr(Unary &expr) {
  expr.right->Accept(*this);
  Data d = ret[expr.right.get()];
  Data temp;
  switch (expr.op.type) {
  case Lexer::TokenType::MINUS:
    temp = Data(d.intData * -1);
    break;
  case Lexer::TokenType::BANG:
    temp = Data(!d.boolData);
    break;
  default:
    throw EvalError(d, "Unknown Unary Operator.");
  }
  ret[&expr] = temp;
}
void AstEvaluator::VisitBinaryExpr(Binary &expr) {
  expr.left->Accept(*this);
  expr.right->Accept(*this);
  Data l = ret[expr.left.get()];
  Data r = ret[expr.right.get()];
  Data temp;

  switch (expr.op.type) {
  case Lexer::TokenType::PLUS:
    temp = Data(l.intData + r.intData);
    break;
  case Lexer::TokenType::MINUS:
    temp = Data(l.intData - r.intData);
    break;
  case Lexer::TokenType::MUL:
    temp = Data(l.intData * r.intData);
    break;
  case Lexer::TokenType::DIV:
    temp = Data(l.intData / r.intData);
    break;
  case Lexer::TokenType::MOD:
    temp = Data(l.intData % r.intData);
    break;
  default:
    throw EvalError(l, r, "Unknown Binary Operator");
  }

  ret[&expr] = temp;
}
void AstEvaluator::VisitGroupingExpr(Grouping &expr) {
  expr.expression->Accept(*this);
  ret[&expr] = ret[expr.expression.get()];
}
void AstEvaluator::VisitLiteralExpr(Literal<int> &expr) {
  ret[&expr] = Data(expr.value);
}
void AstEvaluator::VisitLiteralExpr(Literal<std::string> &expr) {
  ret[&expr] = Data(expr.value);
}
void AstEvaluator::VisitLiteralExpr(Literal<bool> &expr) {
  ret[&expr] = Data(expr.value);
}
bool AstEvaluator::CheckForNumber(Data &data) {
  if (data.dataType == EvalType::INTEGER)
    return true;
  throw EvalError(data, "Param isn't a number");
  return false;
}
bool AstEvaluator::CheckForNumber(Data &left, Data &right) {
  if (CheckForNumber(left) && CheckForNumber(right))
    return true;
  return false;
}
} // namespace Parser
