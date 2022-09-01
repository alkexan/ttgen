#include "CodeGenerator.hpp"

#include <iostream>
#include <math.h>

using namespace thl;

TBoolean CodeGenerator::visit(NumberExprAST &ast) { return ast.getValue(); }

TBoolean CodeGenerator::visit(VariableExprAST &ast) {
  return m_values[ast.getName()][m_valuePosition];
}

TBoolean CodeGenerator::visit(UnaryExprAST &ast) {
  TBoolean result = 0;
  switch (ast.getOperator()) {
  case TokenType::NOT: {
    result = ~ast.getRhs()->accept(*this);
    break;
  }
  case TokenType::DECREMENT: {
    result = --ast.getRhs()->accept(*this);
    break;
  }
  case TokenType::INCREMENT: {
    result = ++ast.getRhs()->accept(*this);
    break;
  }
  default: {
    throw ParseException("Invalid unary operator");
    break;
  }
  }

  return result;
}

TBoolean CodeGenerator::visit(BinaryExprAST &ast) {
  TBoolean result = 0;
  switch (ast.getOperator()) {
  case TokenType::IMPLICATION: {
    result = ast.getLhs()->accept(*this).impl(ast.getRhs()->accept(*this));
    break;
  }
  case TokenType::IMPLICATIONB: {
    result = ast.getLhs()->accept(*this).implb(ast.getRhs()->accept(*this));
    break;
  }
  case TokenType::OR: {
    result = ast.getLhs()->accept(*this) | ast.getRhs()->accept(*this);
    break;
  }
  case TokenType::XOR: {
    result = ast.getLhs()->accept(*this) ^ ast.getRhs()->accept(*this);
    break;
  }
  case TokenType::SUB: {
    result = ast.getLhs()->accept(*this) - ast.getRhs()->accept(*this);
    break;
  }
  case TokenType::ADD: {
    result = ast.getLhs()->accept(*this) + ast.getRhs()->accept(*this);
    break;
  }
  case TokenType::AND: {
    result = ast.getLhs()->accept(*this) & ast.getRhs()->accept(*this);
    break;
  }
  case TokenType::MUL: {
    result = ast.getLhs()->accept(*this) * ast.getRhs()->accept(*this);
    break;
  }
  case TokenType::ASSIGMENT: {
    throw ParseException("ASSIGMENT operation");
    break;
  }
  default: {
    throw ParseException("Invalid binary operator");
    break;
  }
  }

  return result;
}

TBoolean CodeGenerator::visit(PrototypeAST &ast) {

  auto args = ast.getArgs();

  for (int i = 0; i < args.size(); i++) {
    int value = -1;
    int k = 0;
    int count = pow(3, args.size() - i - 1);

    m_valuesCount = pow(3, args.size());
    for (int j = 0; j < m_valuesCount; j++) {
      m_values[args[i]].push_back(value);
      k++;
      if (k == count) {
        value++;
        if (value > 1) {
          value = -1;
        }
        k = 0;
      }
    }
  }
  return 0;
}

TBoolean CodeGenerator::visit(FunctionAST &ast) {
  ast.getPrototype()->accept(*this);

  std::cout << "|\t";
  for (auto i = m_values.begin(); i != m_values.end(); i++) {
    std::cout << i->first << "\t|\t";
  }
  std::cout << "f\t|" << std::endl;

  m_valuePosition = 0;
  do {
    std::cout << "|\t";
    for (auto mapIterator = m_values.begin(); mapIterator != m_values.end();
         mapIterator++) {
      std::cout << mapIterator->second[m_valuePosition] << "\t|\t";
    }

    TBoolean result = ast.getBody()->accept(*this);
    std::cout << (int)result << "\t|" << std::endl;
    m_valuePosition++;
  } while (m_valuePosition < m_valuesCount);

  m_values.clear();
  m_valuePosition = 0;
  m_valuesCount = 0;
  return 0;
}

TBoolean CodeGenerator::visit(CallExprAST &ast) {

  auto args = ast.getArgs();
  for (int i = 0; i < args.size(); i++) {
    args[i]->accept(*this);
  }

  return 0;
}