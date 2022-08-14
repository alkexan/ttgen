#include "SyntaxAnalyzer.hpp"

using namespace thl;

SyntaxAnalyzer::SyntaxAnalyzer() {}

SyntaxAnalyzer::~SyntaxAnalyzer() {}

void thl::SyntaxAnalyzer::setLexemeTable(
    std::unique_ptr<TokenTable> lexemTable) {
  m_tokenTable = std::move(lexemTable);
}

void thl::SyntaxAnalyzer::setConstTable(
    std::unique_ptr<ConstTable> constTable) {
  m_constTable = std::move(constTable);
}

void thl::SyntaxAnalyzer::setIdentTable(
    std::unique_ptr<IdentTable> identTable) {
  m_identTable = std::move(identTable);
}

std::unique_ptr<TokenTable> thl::SyntaxAnalyzer::getLexemeTable() {
  return std::move(m_tokenTable);
}

std::unique_ptr<ConstTable> thl::SyntaxAnalyzer::getConstTable() {
  return std::move(m_constTable);
}

std::unique_ptr<IdentTable> thl::SyntaxAnalyzer::getIdentTable() {
  return std::move(m_identTable);
}

std::vector<std::unique_ptr<FunctionAST>> thl::SyntaxAnalyzer::getProgramAst() {
  return std::move(m_programAst);
}

void thl::SyntaxAnalyzer::parse() {
  m_programAst.clear();
  m_lexIterator = m_tokenTable->begin();
  Token token = getToken();

  while (token.getType() != TokenType::ENDF) {
    if (token.getType() == TokenType::ENDL) {
      // empty body
    } else {
      auto function = std::move(parseFunction(token));
      if (function) {
        m_programAst.push_back(std::move(function));
      } else {
        token = getToken();
      }
    }

    token = getToken();
  }
}

std::unique_ptr<FunctionAST> thl::SyntaxAnalyzer::parseFunction(Token token) {
  std::unique_ptr<FunctionAST> result = nullptr;

  // create Function Prototype Ast
  auto prototype = std::move(parsePrototype(token));
  if (prototype) {
    // create Expression Ast
    token = getToken();
    if (token.getType() == TokenType::ASSIGMENT) {
      token = getToken();
      auto exp = std::move(parseExpression(token));
      if (exp) {
        // create Function Ast
        result =
            std::make_unique<FunctionAST>(std::move(prototype), std::move(exp));
      }
    } else {
      throw ParseException("Exepted exeption");
    }
  }
  return std::move(result);
}

std::unique_ptr<PrototypeAST> thl::SyntaxAnalyzer::parsePrototype(Token token) {
  std::unique_ptr<PrototypeAST> result = nullptr;

  if (token.getType() != TokenType::IDENTIFIER) {
    throw ParseException("Expected function name in prototype");
  } else {
    std::string functionName = (*m_identTable)[token.getAttribute()];

    token = getToken();
    if (token.getType() == TokenType::OPEN_BRACKET) {
      std::vector<std::string> args;

      do {
        token = getToken();

        if (token.getType() == TokenType::CLOSE_BRACKET) {
          break;
        } else if (token.getType() == TokenType::IDENTIFIER) {
          args.push_back((*m_identTable)[token.getAttribute()]);
          token = getToken();
        }

        if (token.getType() != TokenType::DELIMITER &&
            token.getType() != TokenType::CLOSE_BRACKET) {
          throw ParseException("Expected ')' or ',' in argument list");
          break;
        }
      } while (token.getType() == TokenType::DELIMITER);

      if (token.getType() == TokenType::CLOSE_BRACKET) {
        // success.
        result = std::make_unique<PrototypeAST>(functionName, args);
      }
    } else {
      throw ParseException("Expected '(' in prototype");
    }
  }

  return std::move(result);
}

std::unique_ptr<ExpressionAst>
thl::SyntaxAnalyzer::parseExpression(Token token) {
  std::unique_ptr<ExpressionAst> result = nullptr;

  auto lhs = std::move(parseImplExpression(token));
  if (lhs) {
    token = getToken();
    TokenType tokenType = token.getType();
    if ((tokenType == TokenType::IMPLICATION) ||
        (tokenType == TokenType::IMPLICATIONB)) {
      token = getToken();
      auto rhs = std::move(parseImplExpression(token));
      if (rhs) {
        result = std::make_unique<BinaryExprAST>(tokenType, std::move(lhs),
                                                 std::move(rhs));
      }
    } else if (token.getType() != TokenType::ENDF) {
      result = std::move(lhs);
      token = getToken(1);
    } else {
      result = std::move(lhs);
    }
  }

  return std::move(result);
}

std::unique_ptr<ExpressionAst>
thl::SyntaxAnalyzer::parseImplExpression(Token token) {
  std::unique_ptr<ExpressionAst> result = nullptr;

  auto lhs = std::move(parseTerm(token));
  if (lhs) {
    token = getToken();
    TokenType tokenType = token.getType();
    if ((tokenType == TokenType::ADD) || (tokenType == TokenType::SUB) ||
        (tokenType == TokenType::OR) || (tokenType == TokenType::XOR)) {
      token = getToken();
      auto rhs = std::move(parseTerm(token));
      if (rhs) {
        result = std::make_unique<BinaryExprAST>(tokenType, std::move(lhs),
                                                 std::move(rhs));
      }
    } else if (token.getType() != TokenType::ENDF) {
      result = std::move(lhs);
      token = getToken(1);
    } else {
      result = std::move(lhs);
    }
  }

  return std::move(result);
}

std::unique_ptr<ExpressionAst> thl::SyntaxAnalyzer::parseTerm(Token token) {
  std::unique_ptr<ExpressionAst> result = nullptr;

  auto lhs = std::move(parseFactor(token));
  if (lhs) {
    token = getToken();
    TokenType tokenType = token.getType();
    if ((tokenType == TokenType::MUL) || (tokenType == TokenType::AND)) {
      token = getToken();
      auto rhs = std::move(parseFactor(token));
      if (rhs) {
        result = std::make_unique<BinaryExprAST>(tokenType, std::move(lhs),
                                                 std::move(rhs));
      }
    } else if (token.getType() != TokenType::ENDF) {
      result = std::move(lhs);
      token = getToken(1);
    } else {
      result = std::move(lhs);
    }
  }

  return std::move(result);
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
    token = getToken();
    auto rhs = std::move(parseFactor(token));

    result = std::make_unique<UnaryExprAST>(unary, std::move(rhs));
    break;
  }
  default: {
    throw ParseException("unknown TokenType when expecting an expression");
    break;
  }
  }

  return std::move(result);
}

std::unique_ptr<ExpressionAst>
thl::SyntaxAnalyzer::parseParenExpr(Token token) {
  std::unique_ptr<ExpressionAst> result = nullptr;

  token = getToken();
  auto expression = std::move(parseExpression(token));
  if (expression) {
    token = getToken();
    if (token.getType() == TokenType::CLOSE_BRACKET) {
      result = std::move(expression);
    } else {
      throw ParseException("expected ')'");
    }
  }

  return std::move(result);
}

std::unique_ptr<ExpressionAst> thl::SyntaxAnalyzer::parseName(Token token) {
  std::unique_ptr<ExpressionAst> result = nullptr;

  std::string idName = (*m_identTable)[token.getAttribute()];

  token = getToken();
  if (token.getType() == TokenType::OPEN_BRACKET) {
    // Callable
    std::vector<std::unique_ptr<ExpressionAst>> args;

    do {
      token = getToken();

      if (token.getType() == TokenType::CLOSE_BRACKET) {
        break;
      } else if (token.getType() == TokenType::IDENTIFIER) {
        auto arg = std::move(parseExpression(token));
        if (arg) {
          args.push_back(std::move(arg));
          token = getToken();
        }
      }

      if (token.getType() != TokenType::DELIMITER &&
          token.getType() != TokenType::CLOSE_BRACKET) {
        throw ParseException("Expected ')' or ',' in argument list");
        break;
      }

    } while (token.getType() == TokenType::DELIMITER);

    if (token.getType() == TokenType::CLOSE_BRACKET) {
      // success.
      result = std::make_unique<CallExprAST>(idName, std::move(args));
    }
  } else {
    // Variable
    result = std::make_unique<VariableExprAST>(idName);
    token = getToken(1);
  }

  return std::move(result);
}

std::unique_ptr<ExpressionAst> thl::SyntaxAnalyzer::parseNumber(Token token) {
  auto result =
      std::make_unique<NumberExprAST>((*m_constTable)[token.getAttribute()]);
  std::cout << (*m_constTable)[token.getAttribute()];
  return std::move(result);
}
