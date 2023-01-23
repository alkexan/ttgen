#ifndef SRC__ABSTRACT_SYNTAX_TREE__HPP
#define SRC__ABSTRACT_SYNTAX_TREE__HPP

#include "TBoolean.hpp"
#include "Token.hpp"

#include <memory>

namespace thl {
class NumberExprAST;
class VariableExprAST;
class UnaryExprAST;
class BinaryExprAST;
class PrototypeAST;
class FunctionAST;
class CallExprAST;

class Visitor {
public:
  virtual ~Visitor() = default;

  virtual TBoolean visit(NumberExprAST &ast) = 0;
  virtual TBoolean visit(VariableExprAST &ast) = 0;
  virtual TBoolean visit(UnaryExprAST &ast) = 0;
  virtual TBoolean visit(BinaryExprAST &ast) = 0;
  virtual TBoolean visit(PrototypeAST &ast) = 0;
  virtual TBoolean visit(FunctionAST &ast) = 0;
  virtual TBoolean visit(CallExprAST &ast) = 0;
};

/**
 * @brief Base Exception AST lead class.
 */
class ExpressionAst {
public:
  virtual ~ExpressionAst() = default;
  virtual TBoolean accept(Visitor &visitor) = 0;
};

/**
 * @brief AST leaf class for Number constants in ternary logic (constants {-1, 0, 1}).
 */
class NumberExprAST : public ExpressionAst {
public:
  NumberExprAST(int val) : m_val(val) {}

  TBoolean accept(Visitor &visitor) override { return visitor.visit(*this); }

  inline int getValue() const { return m_val; }

private:
  int m_val;
};

/**
 * @brief AST leaf class for Variable when must calculate.
 */
class VariableExprAST : public ExpressionAst {
public:
  VariableExprAST(const std::string &name) : m_name(name) {}

  TBoolean accept(Visitor &visitor) override { return visitor.visit(*this); }

  inline std::string getName() const { return m_name; }

private:
  std::string m_name;
};

/**
 * @brief AST Leaf class for unary functions ternary logic.
 */
class UnaryExprAST : public ExpressionAst {
public:
  UnaryExprAST(TokenType op, std::unique_ptr<ExpressionAst> rhs)
      : m_op(op), m_rhs(std::move(rhs)) {}

  TBoolean accept(Visitor &visitor) override { return visitor.visit(*this); }

  inline TokenType getOperator() const { return m_op; }

  inline ExpressionAst *getRhs() const { return m_rhs.get(); }

private:
  TokenType m_op;
  std::unique_ptr<ExpressionAst> m_rhs;
};

/**
 * @brief AST Leaf class for binary functions ternary logic.
 */
class BinaryExprAST : public ExpressionAst {
public:
  BinaryExprAST(TokenType op, std::unique_ptr<ExpressionAst> lhs,
                std::unique_ptr<ExpressionAst> rhs)
      : m_op(op), m_lhs(std::move(lhs)), m_rhs(std::move(rhs)) {}

  TBoolean accept(Visitor &visitor) override { return visitor.visit(*this); }

  inline TokenType getOperator() const { return m_op; }

  inline ExpressionAst *getLhs() const { return m_lhs.get(); }

  inline ExpressionAst *getRhs() const { return m_rhs.get(); }

private:
  TokenType m_op;
  std::unique_ptr<ExpressionAst> m_lhs;
  std::unique_ptr<ExpressionAst> m_rhs;
};

/**
 * @brief AST leaf class for any function prototype.
 */
class PrototypeAST : public ExpressionAst {
public:
  PrototypeAST(const std::string &name, const std::vector<std::string> &args)
      : m_name(name), m_args(args) {}

  TBoolean accept(Visitor &visitor) override { return visitor.visit(*this); }

  inline std::string getName() const { return m_name; }

  inline std::vector<std::string> getArgs() const { return m_args; }

private:
  std::string m_name;
  std::vector<std::string> m_args;
};

/**
 * @brief AST leaf for any function. Full function description
 */
class FunctionAST : public ExpressionAst {
public:
  FunctionAST(std::unique_ptr<PrototypeAST> prototype,
              std::unique_ptr<ExpressionAst> body)
      : m_prototype(std::move(prototype)), m_body(std::move(body)) {}

  TBoolean accept(Visitor &visitor) override { return visitor.visit(*this); }

  inline ExpressionAst *getPrototype() const { return m_prototype.get(); }

  inline ExpressionAst *getBody() const { return m_body.get(); }

private:
  std::unique_ptr<PrototypeAST> m_prototype;
  std::unique_ptr<ExpressionAst> m_body;
};

/**
 * @brief AST leaf fot call function.
 *
 * @todo needs to be finalized
 */
class CallExprAST : public ExpressionAst {
public:
  CallExprAST(const std::string &callee,
              std::vector<std::unique_ptr<ExpressionAst>> args)
      : m_name(callee), m_args(std::move(args)) {}

  TBoolean accept(Visitor &visitor) override { return visitor.visit(*this); }

  inline std::string getName() const { return m_name; }

  inline std::vector<std::unique_ptr<ExpressionAst>> getArgs() {
    return std::move(m_args);
  }

private:
  std::string m_name;
  std::vector<std::unique_ptr<ExpressionAst>> m_args;
};
} // namespace thl

#endif // SRC__ABSTRACT_SYNTAX_TREE__HPP
