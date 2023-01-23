#pragma once

#include "AbstractSyntaxTree.hpp"
#include "ParseException.hpp"
#include "TBoolean.hpp"
#include "Token.hpp"
#include <vector>

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

  void printTable();

  std::vector<TBoolean> getResults() {
    return m_results;
  }

private:
  int m_valuePosition = 0;
  int m_valuesCount = 0;
  
  std::map<std::string, std::vector<int>> m_values;
  std::vector<TBoolean> m_results;
};

} // namespace thl
