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
  case Token::NOT: {
    result = ~ast.getRhs()->accept(*this);
    break;
  }
  case Token::DECREMENT: {
    result = --ast.getRhs()->accept(*this);
    break;
  }
  case Token::INCREMENT: {
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
  case Token::IMPLICATION: {
    result = ast.getLhs()->accept(*this).impl(ast.getRhs()->accept(*this));
    break;
  }
  case Token::IMPLICATIONB: {
    result = ast.getLhs()->accept(*this).implb(ast.getRhs()->accept(*this));
    break;
  }
  case Token::OR: {
    result = ast.getLhs()->accept(*this) | ast.getRhs()->accept(*this);
    break;
  }
  case Token::XOR: {
    result = ast.getLhs()->accept(*this) ^ ast.getRhs()->accept(*this);
    break;
  }
  case Token::SUB: {
    result = ast.getLhs()->accept(*this) - ast.getRhs()->accept(*this);
    break;
  }
  case Token::ADD: {
    result = ast.getLhs()->accept(*this) + ast.getRhs()->accept(*this);
    break;
  }
  case Token::AND: {
    result = ast.getLhs()->accept(*this) & ast.getRhs()->accept(*this);
    break;
  }
  case Token::MUL: {
    result = ast.getLhs()->accept(*this) * ast.getRhs()->accept(*this);
    break;
  }
  case Token::ASSIGMENT: {
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

  for (m_valuePosition = 0; m_valuePosition < m_valuesCount;
       m_valuePosition++) {
    auto mapIterator = m_values.begin();
    std::cout << "|\t" << mapIterator->second[m_valuePosition];
    mapIterator++;
    std::cout << "\t|\t" << mapIterator->second[m_valuePosition];

    TBoolean result = ast.getBody()->accept(*this);
    std::cout << "\t|\t" << (int)result << "\t|" << std::endl;
  }

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