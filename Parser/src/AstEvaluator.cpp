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
    throw std::runtime_error("Unknown data type: " +
                             std::to_string(data.dataType));
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
    temp.dataType = EvalType::INTEGER;
    temp.intData = d.intData * -1;
    break;
  case Lexer::TokenType::BANG:
    temp.dataType = EvalType::BOOL;
    temp.boolData = !d.boolData;
    break;
  default:
    throw std::runtime_error("Unknown unary operator: " + expr.op.lexeme);
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
    temp.dataType = EvalType::INTEGER;
    temp.intData = l.intData + r.intData;
    break;
  case Lexer::TokenType::MINUS:
    temp.dataType = EvalType::INTEGER;
    temp.intData = l.intData - r.intData;
    break;
  case Lexer::TokenType::MUL:
    temp.dataType = EvalType::INTEGER;
    temp.intData = l.intData * r.intData;
    break;
  case Lexer::TokenType::DIV:
    temp.dataType = EvalType::INTEGER;
    temp.intData = l.intData / r.intData;
    break;
  case Lexer::TokenType::MOD:
    temp.dataType = EvalType::INTEGER;
    temp.intData = l.intData % r.intData;
    break;
  default:
    throw std::runtime_error("Unknown Binary operator: " + expr.op.lexeme);
  }

  ret[&expr] = temp;
}
void AstEvaluator::VisitGroupingExpr(Grouping &expr) {
  expr.expression->Accept(*this);
  ret[&expr] = ret[expr.expression.get()];
}
void AstEvaluator::VisitLiteralExpr(Literal<int> &expr) {
  Data temp;
  temp.dataType = EvalType::INTEGER;
  temp.intData = expr.value;
  ret[&expr] = temp;
}
void AstEvaluator::VisitLiteralExpr(Literal<std::string> &expr) {
  Data temp;
  temp.dataType = EvalType::INTEGER;
  temp.stringData = expr.value;
  ret[&expr] = temp;
}
void AstEvaluator::VisitLiteralExpr(Literal<bool> &expr) {
  Data temp;
  temp.dataType = EvalType::BOOL;
  temp.boolData = expr.value;
  ret[&expr] = temp;
}
} // namespace Parser
