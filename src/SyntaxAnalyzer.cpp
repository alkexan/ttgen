#include "SyntaxAnalyzer.hpp"
#include <algorithm>
#include <string>

using namespace thl;

SyntaxAnalyzer::SyntaxAnalyzer() {}

SyntaxAnalyzer::~SyntaxAnalyzer() {}

void thl::SyntaxAnalyzer::setTokenTable(
    std::shared_ptr<TokenTable> lexemTable) {
  m_tokenTable = lexemTable;
}

void thl::SyntaxAnalyzer::setConstTable(
    std::shared_ptr<ConstTable> constTable) {
  m_constTable = constTable;
}

void thl::SyntaxAnalyzer::setIdentTable(
    std::shared_ptr<IdentTable> identTable) {
  m_identTable = identTable;
}

std::vector<std::unique_ptr<FunctionAST>> thl::SyntaxAnalyzer::getProgramAst() {
  return std::move(m_programAst);
}

void thl::SyntaxAnalyzer::parse() {
  m_programAst.clear();
  m_lexIterator = m_tokenTable->begin();
  Token token = readToken();

  while (token.getType() != TokenType::ENDF) {
    if (token.getType() == TokenType::ENDL) {
      // empty body
    } else {
      auto function = std::move(parseFunction(token));
      if (function) {
        m_programAst.push_back(std::move(function));
      } else {
        token = readToken();
      }
    }

    token = readToken();
  }
}

std::unique_ptr<FunctionAST> thl::SyntaxAnalyzer::parseFunction(Token token) {
  std::unique_ptr<FunctionAST> result = nullptr;

  // create Function Prototype Ast
  auto prototype = std::move(parsePrototype(token));
  if (prototype) {
    // create Expression Ast
    token = readToken();
    if (token.getType() == TokenType::ASSIGMENT) {
      token = readToken();
      auto exp = std::move(parseStatement(token));
      if (exp) {
        // create Function Ast
        result =
            std::make_unique<FunctionAST>(std::move(prototype), std::move(exp));
      }
    } else {
      auto textPos = token.getTextPosition();
      throw ParseException("[" + std::to_string(textPos.first) + "," +
                           std::to_string(textPos.second) +
                           "] Error: " + "Exepted exeption");
    }
  }
  return std::move(result);
}

std::unique_ptr<PrototypeAST> thl::SyntaxAnalyzer::parsePrototype(Token token) {
  std::unique_ptr<PrototypeAST> result = nullptr;

  if (token.getType() != TokenType::IDENTIFIER) {
    auto textPos = token.getTextPosition();
    throw ParseException("[" + std::to_string(textPos.first) + "," +
                         std::to_string(textPos.second) +
                         "] Error: " + "Expected function name in prototype");
  } else {
    std::string functionName = (*m_identTable)[token.getAttribute()];

    token = readToken();
    if (token.getType() == TokenType::OPEN_BRACKET) {
      m_prototypeArgs.clear();

      do {
        token = readToken();

        if (token.getType() == TokenType::CLOSE_BRACKET) {
          break;
        } else if (token.getType() == TokenType::IDENTIFIER) {
          m_prototypeArgs.push_back((*m_identTable)[token.getAttribute()]);
          token = readToken();
        }

        if (token.getType() != TokenType::DELIMITER &&
            token.getType() != TokenType::CLOSE_BRACKET) {
          auto textPos = token.getTextPosition();
          throw ParseException("[" + std::to_string(textPos.first) + "," +
                               std::to_string(textPos.second) + "] Error: " +
                               "Expected ')' or ',' in argument list");
          break;
        }
      } while (token.getType() == TokenType::DELIMITER);

      if (token.getType() == TokenType::CLOSE_BRACKET) {
        // success.
        result = std::make_unique<PrototypeAST>(functionName, m_prototypeArgs);
      }
    } else {
      auto textPos = token.getTextPosition();
      throw ParseException("[" + std::to_string(textPos.first) + "," +
                           std::to_string(textPos.second) +
                           "] Error: " + "Expected '(' in prototype");
    }
  }

  return std::move(result);
}

std::unique_ptr<ExpressionAst>
thl::SyntaxAnalyzer::parseStatement(Token token) {
  auto lhs = std::move(parseExpression(token));
  if (lhs) {
    token = readToken();
    TokenType tokenType = token.getType();
    while ((tokenType == TokenType::IMPLICATION) ||
           (tokenType == TokenType::IMPLICATIONB)) {
      token = readToken();
      auto rhs = std::move(parseExpression(token));
      if (rhs) {
        lhs = std::make_unique<BinaryExprAST>(tokenType, std::move(lhs),
                                              std::move(rhs));
        token = readToken();
      }
      tokenType = token.getType();
    }

    if (token.getType() != TokenType::ENDF) {
      token = readToken(1);
    }
  }

  return std::move(lhs);
}

std::unique_ptr<ExpressionAst>
thl::SyntaxAnalyzer::parseExpression(Token token) {
  auto lhs = std::move(parseTerm(token));
  if (lhs) {
    token = readToken();
    TokenType tokenType = token.getType();
    while ((tokenType == TokenType::ADD) || (tokenType == TokenType::SUB) ||
           (tokenType == TokenType::OR) || (tokenType == TokenType::XOR)) {
      token = readToken();
      auto rhs = std::move(parseTerm(token));
      if (rhs) {
        lhs = std::make_unique<BinaryExprAST>(tokenType, std::move(lhs),
                                              std::move(rhs));
        token = readToken();
      }
      tokenType = token.getType();
    }

    if (token.getType() != TokenType::ENDF) {
      token = readToken(1);
    }
  }

  return std::move(lhs);
}

std::unique_ptr<ExpressionAst> thl::SyntaxAnalyzer::parseTerm(Token token) {
  auto lhs = std::move(parseFactor(token));
  if (lhs) {
    token = readToken();
    TokenType tokenType = token.getType();
    while ((tokenType == TokenType::MUL) || (tokenType == TokenType::AND)) {
      token = readToken();
      auto rhs = std::move(parseFactor(token));
      if (rhs) {
        lhs = std::make_unique<BinaryExprAST>(tokenType, std::move(lhs),
                                              std::move(rhs));
        token = readToken();
      }
      tokenType = token.getType();
    }

    if (token.getType() != TokenType::ENDF) {
      token = readToken(1);
    }
  }

  return std::move(lhs);
}

std::unique_ptr<ExpressionAst> thl::SyntaxAnalyzer::parseFactor(Token token) {
  std::unique_ptr<ExpressionAst> result = nullptr;

  switch (token.getType()) {
  case TokenType::IDENTIFIER: {
    result = std::move(parseName(token));
    break;
  }
  case TokenType::NUMBER: {
    result = std::move(parseNumber(token));
    break;
  }
  case TokenType::OPEN_BRACKET: {
    result = std::move(parseParenExpr(token));
    break;
  }
  default: {
    result = std::move(parseUnary(token));
    break;
  }
  }
  return std::move(result);
}

std::unique_ptr<ExpressionAst> thl::SyntaxAnalyzer::parseUnary(Token token) {
  std::unique_ptr<ExpressionAst> result = nullptr;

  switch (token.getType()) {
  case TokenType::INCREMENT: // No Body
  case TokenType::DECREMENT: // No Body
  case TokenType::NOT: {
    TokenType unary = token.getType();
    token = readToken();
    auto rhs = std::move(parseFactor(token));

    result = std::make_unique<UnaryExprAST>(unary, std::move(rhs));
    break;
  }
  default: {
    auto textPos = token.getTextPosition();
    throw ParseException("[" + std::to_string(textPos.first) + "," +
                         std::to_string(textPos.second) + "] Error: " +
                         "Unknown TokenType when expecting an expression");
    break;
  }
  }

  return std::move(result);
}

std::unique_ptr<ExpressionAst>
thl::SyntaxAnalyzer::parseParenExpr(Token token) {
  std::unique_ptr<ExpressionAst> result = nullptr;

  token = readToken();
  auto expression = std::move(parseStatement(token));
  if (expression) {
    token = readToken();
    if (token.getType() == TokenType::CLOSE_BRACKET) {
      result = std::move(expression);
    } else {
      auto textPos = token.getTextPosition();
      throw ParseException("[" + std::to_string(textPos.first) + "," +
                           std::to_string(textPos.second) +
                           "] Error: " + "Expected ')'");
    }
  }

  return std::move(result);
}

std::unique_ptr<ExpressionAst> thl::SyntaxAnalyzer::parseName(Token token) {
  std::unique_ptr<ExpressionAst> result = nullptr;

  std::string idName = (*m_identTable)[token.getAttribute()];

  token = readToken();
  if (token.getType() == TokenType::OPEN_BRACKET) {
    // Callable
    std::vector<std::unique_ptr<ExpressionAst>> args;

    do {
      token = readToken();

      if (token.getType() == TokenType::CLOSE_BRACKET) {
        break;
      } else if (token.getType() == TokenType::IDENTIFIER) {
        auto arg = std::move(parseStatement(token));
        if (arg) {
          args.push_back(std::move(arg));
          token = readToken();
        }
      }

      if (token.getType() != TokenType::DELIMITER &&
          token.getType() != TokenType::CLOSE_BRACKET) {
        auto textPos = token.getTextPosition();
        throw ParseException("[" + std::to_string(textPos.first) + "," +
                             std::to_string(textPos.second) + "] Error: " +
                             "Expected ')' or ',' in argument list");
        break;
      }

    } while (token.getType() == TokenType::DELIMITER);

    if (token.getType() == TokenType::CLOSE_BRACKET) {
      // success.
      result = std::make_unique<CallExprAST>(idName, std::move(args));
    }
  } else {
    // Variable
    auto contains = std::find(m_prototypeArgs.begin(), m_prototypeArgs.end(), idName);
    if (contains == m_prototypeArgs.end()) {
      auto textPos = token.getTextPosition();
      throw ParseException("[" + std::to_string(textPos.first) + "," +
                           std::to_string(textPos.second) +
                           "] Error: Error: Undeclarated identifier \"" +
                           idName + "\"");
    } else {
      result = std::make_unique<VariableExprAST>(idName);
      token = readToken(1);
    }
  }

  return std::move(result);
}

std::unique_ptr<ExpressionAst> thl::SyntaxAnalyzer::parseNumber(Token token) {
  auto result =
      std::make_unique<NumberExprAST>((*m_constTable)[token.getAttribute()]);
  return std::move(result);
}
