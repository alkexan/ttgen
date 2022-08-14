#include "SyntaxAnalyzer.hpp"

using namespace thl;

SyntaxAnalyzer::SyntaxAnalyzer() {}

SyntaxAnalyzer::~SyntaxAnalyzer() {}

void thl::SyntaxAnalyzer::setLexemeTable(
    std::unique_ptr<TokenTable> lexemTable) {
  m_lexemTable = std::move(lexemTable);
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
  return std::move(m_lexemTable);
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
  m_lexIterator = m_lexemTable->begin();
  Token lexeme = getLexeme();

  while (lexeme.getToken() != TokenType::ENDF) {
    if (lexeme.getToken() == TokenType::NEW_LINE) {
      // empty body
    } else {
      auto function = std::move(parseFunction(lexeme));
      if (function) {
        m_programAst.push_back(std::move(function));
      } else {
        lexeme = getLexeme();
      }
    }

    lexeme = getLexeme();
  }
}

std::unique_ptr<FunctionAST> thl::SyntaxAnalyzer::parseFunction(Token lexeme) {
  std::unique_ptr<FunctionAST> result = nullptr;

  // create Function Prototype Ast
  auto prototype = std::move(parsePrototype(lexeme));
  if (prototype) {
    // create Expression Ast
    lexeme = getLexeme();
    if (lexeme.getToken() == TokenType::ASSIGMENT) {
      lexeme = getLexeme();
      auto exp = std::move(parseExpression(lexeme));
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

std::unique_ptr<PrototypeAST>
thl::SyntaxAnalyzer::parsePrototype(Token lexeme) {
  std::unique_ptr<PrototypeAST> result = nullptr;

  if (lexeme.getToken() != TokenType::IDENTIFIER) {
    throw ParseException("Expected function name in prototype");
  } else {
    std::string functionName = (*m_identTable)[lexeme.getAttribute()];

    lexeme = getLexeme();
    if (lexeme.getToken() == TokenType::OPEN_BRACKET) {
      std::vector<std::string> args;

      do {
        lexeme = getLexeme();

        if (lexeme.getToken() == TokenType::CLOSE_BRACKET) {
          break;
        } else if (lexeme.getToken() == TokenType::IDENTIFIER) {
          args.push_back((*m_identTable)[lexeme.getAttribute()]);
          lexeme = getLexeme();
        }

        if (lexeme.getToken() != TokenType::DELIMITER &&
            lexeme.getToken() != TokenType::CLOSE_BRACKET) {
          throw ParseException("Expected ')' or ',' in argument list");
          break;
        }
      } while (lexeme.getToken() == TokenType::DELIMITER);

      if (lexeme.getToken() == TokenType::CLOSE_BRACKET) {
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
thl::SyntaxAnalyzer::parseExpression(Token lexeme) {
  std::unique_ptr<ExpressionAst> result = nullptr;

  auto lhs = std::move(parseImplExpression(lexeme));
  if (lhs) {
    lexeme = getLexeme();
    TokenType getToken = lexeme.getToken();
    if ((getToken == TokenType::IMPLICATION) || (getToken == TokenType::IMPLICATIONB)) {
      lexeme = getLexeme();
      auto rhs = std::move(parseImplExpression(lexeme));
      if (rhs) {
        result = std::make_unique<BinaryExprAST>(getToken, std::move(lhs),
                                                 std::move(rhs));
      }
    } else if (lexeme.getToken() != TokenType::ENDF) {
      result = std::move(lhs);
      lexeme = getLexeme(1);
    } else {
      result = std::move(lhs);
    }
  }

  return std::move(result);
}

std::unique_ptr<ExpressionAst>
thl::SyntaxAnalyzer::parseImplExpression(Token lexeme) {
  std::unique_ptr<ExpressionAst> result = nullptr;

  auto lhs = std::move(parseTerm(lexeme));
  if (lhs) {
    lexeme = getLexeme();
    TokenType getToken = lexeme.getToken();
    if ((getToken == TokenType::ADD) || (getToken == TokenType::SUB) ||
        (getToken == TokenType::OR) || (getToken == TokenType::XOR)) {
      lexeme = getLexeme();
      auto rhs = std::move(parseTerm(lexeme));
      if (rhs) {
        result = std::make_unique<BinaryExprAST>(getToken, std::move(lhs),
                                                 std::move(rhs));
      }
    } else if (lexeme.getToken() != TokenType::ENDF) {
      result = std::move(lhs);
      lexeme = getLexeme(1);
    } else {
      result = std::move(lhs);
    }
  }

  return std::move(result);
}

std::unique_ptr<ExpressionAst> thl::SyntaxAnalyzer::parseTerm(Token lexeme) {
  std::unique_ptr<ExpressionAst> result = nullptr;

  auto lhs = std::move(parseFactor(lexeme));
  if (lhs) {
    lexeme = getLexeme();
    TokenType getToken = lexeme.getToken();
    if ((getToken == TokenType::MUL) || (getToken == TokenType::AND)) {
      lexeme = getLexeme();
      auto rhs = std::move(parseFactor(lexeme));
      if (rhs) {
        result = std::make_unique<BinaryExprAST>(getToken, std::move(lhs),
                                                 std::move(rhs));
      }
    } else if (lexeme.getToken() != TokenType::ENDF) {
      result = std::move(lhs);
      lexeme = getLexeme(1);
    } else {
      result = std::move(lhs);
    }
  }

  return std::move(result);
}

std::unique_ptr<ExpressionAst> thl::SyntaxAnalyzer::parseFactor(Token lexeme) {
  std::unique_ptr<ExpressionAst> result = nullptr;

  switch (lexeme.getToken()) {
  case TokenType::IDENTIFIER: {
    result = std::move(parseName(lexeme));
    break;
  }
  case TokenType::NUMBER: {
    result = std::move(parseNumber(lexeme));
    break;
  }
  case TokenType::OPEN_BRACKET: {
    result = std::move(parseParenExpr(lexeme));
    break;
  }
  default: {
    result = std::move(parseUnary(lexeme));
    break;
  }
  }
  return std::move(result);
}

std::unique_ptr<ExpressionAst> thl::SyntaxAnalyzer::parseUnary(Token lexeme) {
  std::unique_ptr<ExpressionAst> result = nullptr;

  switch (lexeme.getToken()) {
  case TokenType::INCREMENT: // No Body
  case TokenType::DECREMENT: // No Body
  case TokenType::NOT: {
    TokenType unary = lexeme.getToken();
    lexeme = getLexeme();
    auto rhs = std::move(parseFactor(lexeme));

    result = std::make_unique<UnaryExprAST>(unary, std::move(rhs));
    break;
  }
  default: {
    throw ParseException("unknown token when expecting an expression");
    break;
  }
  }

  return std::move(result);
}

std::unique_ptr<ExpressionAst>
thl::SyntaxAnalyzer::parseParenExpr(Token lexeme) {
  std::unique_ptr<ExpressionAst> result = nullptr;

  lexeme = getLexeme();
  auto expression = std::move(parseExpression(lexeme));
  if (expression) {
    lexeme = getLexeme();
    if (lexeme.getToken() == TokenType::CLOSE_BRACKET) {
      result = std::move(expression);
    } else {
      throw ParseException("expected ')'");
    }
  }

  return std::move(result);
}

std::unique_ptr<ExpressionAst> thl::SyntaxAnalyzer::parseName(Token lexeme) {
  std::unique_ptr<ExpressionAst> result = nullptr;

  std::string idName = (*m_identTable)[lexeme.getAttribute()];

  lexeme = getLexeme();
  if (lexeme.getToken() == TokenType::OPEN_BRACKET) {
    // Callable
    std::vector<std::unique_ptr<ExpressionAst>> args;

    do {
      lexeme = getLexeme();

      if (lexeme.getToken() == TokenType::CLOSE_BRACKET) {
        break;
      } else if (lexeme.getToken() == TokenType::IDENTIFIER) {
        auto arg = std::move(parseExpression(lexeme));
        if (arg) {
          args.push_back(std::move(arg));
          lexeme = getLexeme();
        }
      }

      if (lexeme.getToken() != TokenType::DELIMITER &&
          lexeme.getToken() != TokenType::CLOSE_BRACKET) {
        throw ParseException("Expected ')' or ',' in argument list");
        break;
      }

    } while (lexeme.getToken() == TokenType::DELIMITER);

    if (lexeme.getToken() == TokenType::CLOSE_BRACKET) {
      // success.
      result = std::make_unique<CallExprAST>(idName, std::move(args));
    }
  } else {
    // Variable
    result = std::make_unique<VariableExprAST>(idName);
    lexeme = getLexeme(1);
  }

  return std::move(result);
}

std::unique_ptr<ExpressionAst> thl::SyntaxAnalyzer::parseNumber(Token lexeme) {
  auto result =
      std::make_unique<NumberExprAST>((*m_constTable)[lexeme.getAttribute()]);
  std::cout << (*m_constTable)[lexeme.getAttribute()];
  return std::move(result);
}
