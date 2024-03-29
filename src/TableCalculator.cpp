#include "TableCalculator.hpp"
#include "Token.hpp"

#include <iostream>
#include <math.h>

using namespace thl;

TBoolean TableCalculator::visit(NumberExprAST &ast) { return ast.getValue(); }

TBoolean TableCalculator::visit(VariableExprAST &ast) {
  return m_values[ast.getName()][m_valuePosition];
}

TBoolean TableCalculator::visit(UnaryExprAST &ast) {
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

TBoolean TableCalculator::visit(BinaryExprAST &ast) {
  TBoolean result = 0;
  switch (ast.getOperator()) {
  case TokenType::IMPL: {
    result = ast.getLhs()->accept(*this).impl(ast.getRhs()->accept(*this));
    break;
  }
  case TokenType::IMPLB: {
    result = ast.getLhs()->accept(*this).implb(ast.getRhs()->accept(*this));
    break;
  }
  case TokenType::LIMPL: {
    result = ast.getLhs()->accept(*this).limpl(ast.getRhs()->accept(*this));
    break;
  }
  case TokenType::IMPLM: {
    result = ast.getLhs()->accept(*this).implm(ast.getRhs()->accept(*this));
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
  case TokenType::DIF: {
    result = ast.getLhs()->accept(*this) / ast.getRhs()->accept(*this);
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

TBoolean TableCalculator::visit(PrototypeAST &ast) {
  m_values.clear();
  m_valuePosition = 0;
  m_valuesCount = 0;

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

TBoolean TableCalculator::visit(FunctionAST &ast) {
  ast.getPrototype()->accept(*this);

  m_valuePosition = 0;
  m_results.clear();
  do {
    TBoolean result = ast.getBody()->accept(*this);
    m_results.push_back(result);
    m_valuePosition++;
  } while (m_valuePosition < m_valuesCount);
  return 0;
}

TBoolean TableCalculator::visit(CallExprAST &ast) {

  auto args = ast.getArgs();
  for (int i = 0; i < args.size(); i++) {
    args[i]->accept(*this);
  }

  return 0;
}

void TableCalculator::printTable() {
  std::cout << "|\t";
  for (auto i = m_values.begin(); i != m_values.end(); i++) {
    std::cout << i->first << "\t|\t";
  }
  std::cout << "f\t|\n";

  m_valuePosition = 0;
  do {
    std::cout << "|\t";
    for (auto mapIterator = m_values.begin(); mapIterator != m_values.end();
         mapIterator++) {
      std::cout << mapIterator->second[m_valuePosition] << "\t|\t";
    }

    std::cout << (int)m_results[m_valuePosition] << "\t|\n";
    m_valuePosition++;
  } while (m_valuePosition < m_valuesCount);

  std::cout << std::endl;
}