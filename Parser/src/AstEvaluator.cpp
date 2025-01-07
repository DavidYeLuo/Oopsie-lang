#include "AstEvaluator.h"
#include "Lexer.h"
#include <exception>
namespace Parser {
std::string AstEvaluator::Eval(Expr &expr) {
  expr.Accept(*this);
  Data data = ret[&expr];
  std::string result = "";
  switch (data.dataType) {
  case Lexer::INTEGER_LIT:
    result = std::to_string(data.intData);
    break;
  case Lexer::STRING_LIT:
    result = data.stringData;
    break;
  case Lexer::TRUE_LIT:
    result = "true";
    break;
  case Lexer::FALSE_LIT:
    result = "false";
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
    temp.dataType = Lexer::TokenType::INTEGER_LIT;
    temp.intData = d.intData * -1;
    break;
  case Lexer::TokenType::BANG:
    temp.boolData = !d.boolData;
    temp.dataType = temp.boolData ? Lexer::TokenType::TRUE_LIT
                                  : Lexer::TokenType::FALSE_LIT;
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
  case Lexer::PLUS:
    temp.dataType = Lexer::INTEGER_LIT;
    temp.intData = l.intData + r.intData;
    break;
  case Lexer::MINUS:
    temp.dataType = Lexer::INTEGER_LIT;
    temp.intData = l.intData - r.intData;
    break;
  case Lexer::MUL:
    temp.dataType = Lexer::INTEGER_LIT;
    temp.intData = l.intData * r.intData;
    break;
  case Lexer::DIV:
    temp.dataType = Lexer::INTEGER_LIT;
    temp.intData = l.intData / r.intData;
    break;
  case Lexer::MOD:
    temp.dataType = Lexer::INTEGER_LIT;
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
  temp.dataType = Lexer::TokenType::INTEGER_LIT;
  temp.intData = expr.value;
  ret[&expr] = temp;
}
void AstEvaluator::VisitLiteralExpr(Literal<std::string> &expr) {
  Data temp;
  temp.dataType = Lexer::TokenType::STRING_LIT;
  temp.stringData = expr.value;
  ret[&expr] = temp;
}
void AstEvaluator::VisitLiteralExpr(Literal<bool> &expr) {
  Data temp;
  temp.dataType =
      expr.value ? Lexer::TokenType::TRUE_LIT : Lexer::TokenType::FALSE_LIT;
  temp.boolData = expr.value;
  ret[&expr] = temp;
}
} // namespace Parser
