#pragma once
#include "Parser.h"

namespace Parser {
enum EvalType {
  INTEGER,
  BOOL,
  STRING,
  NIL,
};

/// Helper used to represent the evaluated operation
/// In Lox, the author used Java's Object class to represent many types
/// I haven't found a clever workaround in C++
struct Data {
  EvalType dataType;
  std::string stringData;
  int intData;
  bool boolData;
  Data() : dataType(EvalType::NIL) {}
  Data(int data) : intData(data) { dataType = EvalType::INTEGER; }
  Data(bool data) : boolData(data) { dataType = EvalType::BOOL; }
  Data(std::string data) : stringData(data) { dataType = EvalType::STRING; }
};
/// Returns "datatype: value"
inline std::string to_str(const Data &data) {
  std::string dataTypeString;
  switch (data.dataType) {
  case EvalType::INTEGER:
    dataTypeString = "int: " + std::to_string(data.intData);
    break;
  case EvalType::BOOL: {
    std::string val = data.boolData ? "true" : "false";
    dataTypeString = "bool: " + val;
  } break;
  case EvalType::STRING:
    dataTypeString = "string: " + data.stringData;
    break;
  case EvalType::NIL:
    dataTypeString = "null";
    break;
  }
  return dataTypeString;
}
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

  bool CheckForNumber(Data &data);
  bool CheckForNumber(Data &left, Data &right);
};
class EvalError : public std::exception {
public:
  std::string msg;
  Data left;
  Data right;

  EvalError(Data data, std::string msg) : left(data) {
    this->msg = msg + " " + to_str(data);
  }
  EvalError(Data left, Data right, std::string msg) : left(left), right(right) {
    this->msg = msg + " left " + to_str(left) + ", right " + to_str(right);
  }
  const char *what() const noexcept override { return msg.c_str(); }
};
class EvalOperatorError : public std::exception {
public:
  std::string msg;
  Lexer::Token token;
  EvalOperatorError(Lexer::Token &token, std::string msg) : token(token) {
    this->msg = msg + " Token: " + token.lexeme;
  }
  const char *what() const noexcept override { return msg.c_str(); }
};
} // namespace Parser
