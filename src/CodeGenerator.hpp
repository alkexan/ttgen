#pragma once

#include "AbstractSyntaxTree.hpp"
#include "ParseException.hpp"
#include "TBoolean.hpp"
#include "Util.hpp"

namespace thl {
class CodeGenerator : public Visitor {
public:
  TBoolean visit(NumberExprAST &ast) override;

  TBoolean visit(VariableExprAST &ast) override;

  TBoolean visit(UnaryExprAST &ast) override;

  TBoolean visit(BinaryExprAST &ast) override;

  TBoolean visit(PrototypeAST &ast) override;

  TBoolean visit(FunctionAST &ast) override;

  TBoolean visit(CallExprAST &ast) override;

private:
  std::map<std::string, std::vector<int>> m_values;
  int m_valuePosition = 0;
  int m_valuesCount = 0;
};

class AssignOperator : public Visitor {
public:
private:
};

class ImplicationOperator : public Visitor {
public:
private:
};

class ImplicationbOperator : public Visitor {
public:
private:
};

class NotOperator : public Visitor {
public:
private:
};

class DecrementOperator : public Visitor {
public:
private:
};

class IncrementOperator : public Visitor {
public:
private:
};

class OrOperator : public Visitor {
public:
private:
};

class XorOperator : public Visitor {
public:
private:
};

class SubOperator : public Visitor {
public:
private:
};

class AddOperator : public Visitor {
public:
private:
};

class AndOperator : public Visitor {
public:
private:
};

class MulOperator : public Visitor {
public:
private:
};

} // namespace thl
