#include "LexicalAnalyzer.hpp"

#include <iostream>

using namespace thl;

LexicalAnalyzer::LexicalAnalyzer()
    : m_lineCount(0), m_lexemTable(std::make_unique<LexemeTable>()),
      m_constTable(std::make_unique<ConstTable>()),
      m_identTable(std::make_unique<IdentTable>()) {}

LexicalAnalyzer::~LexicalAnalyzer() {}

std::unique_ptr<LexemeTable> thl::LexicalAnalyzer::getLexemeTable() {
  return std::move(m_lexemTable);
std::unique_ptr<TokenTable> thl::LexicalAnalyzer::getTokenTable() {
  return std::move(m_tokenTable);
}

std::unique_ptr<ConstTable> thl::LexicalAnalyzer::getConstTable() {
  return std::move(m_constTable);
}

std::unique_ptr<IdentTable> thl::LexicalAnalyzer::getIdentTable() {
  return std::move(m_identTable);
}

void thl::LexicalAnalyzer::parse(std::string &line) {
  m_lineCount++;

  if (m_lexemTable.get() == nullptr) {
    m_lexemTable = std::make_unique<LexemeTable>();
  } else {
    m_lexemTable->clear();
  }
  if (m_constTable.get() == nullptr) {
    m_constTable = std::make_unique<ConstTable>();
  } else {
    m_constTable->clear();
  }
  if (m_identTable.get() == nullptr) {
    m_identTable = std::make_unique<IdentTable>();
  } else {
    m_identTable->clear();
  }

  getTokens(line);
}

void thl::LexicalAnalyzer::getTokens(std::string &line) {
  bool skipLine = false;
  std::istringstream istream(line);

  int m_lastChar = istream.get();

  while (!istream.eof()) {
    // identifier: [a-z][_a-zA-Z0-9]*
    if (isspace(m_lastChar)) {
      m_lastChar = istream.get();
      continue;
    } else if (isalpha(m_lastChar)) {
      std::string identifierStr;
      identifierStr += m_lastChar;

      m_lastChar = istream.get();
      while (isalnum(m_lastChar) || m_lastChar == '_') {
        identifierStr += m_lastChar;
        m_lastChar = istream.get();
      }

      m_tokenTable->push_back(
          Token(TokenType::IDENTIFIER, (int)m_identTable->size()));
      m_identTable->push_back(identifierStr);

      continue;
    } else if (m_lastChar == '$' || m_lastChar == '0' || m_lastChar == '1') {
      m_tokenTable->push_back(Token(TokenType::NUMBER, (int)m_constTable->size()));

      switch (m_lastChar) {
      case '$':
        m_constTable->push_back(-1);
        break;
      case '0':
        m_constTable->push_back(0);
        break;
      default:
        m_constTable->push_back(1);
        break;
      }
    } else if (m_lastChar == '(') {
      m_tokenTable->push_back(Token(TokenType::OPEN_BRACKET, -1));
    } else if (m_lastChar == ')') {
      m_tokenTable->push_back(Token(TokenType::CLOSE_BRACKET, -1));
    } else if (m_lastChar == ',') {
      m_tokenTable->push_back(Token(TokenType::DELIMITER, -1));
    } else if (m_lastChar == '\n') {
      m_tokenTable->push_back(Token(TokenType::NEW_LINE, -1));
    } else if (m_lastChar == ':') {
      m_lastChar = istream.get();
      if (m_lastChar == '=') {
        m_tokenTable->push_back(Token(TokenType::ASSIGMENT, -1));
      } else {
        throw ParseException("(" + std::to_string(m_lineCount) + "," +
                             std::to_string(istream.tellg()) +
                             ") Error: " + "Unknown identifier");
      }
    } else if (m_lastChar == '-') {
      m_lastChar = istream.get();

      if (m_lastChar == '-') {
        m_tokenTable->push_back(Token(TokenType::DECREMENT, -1));
      } else if (m_lastChar == '>') {
        m_tokenTable->push_back(Token(TokenType::IMPLICATION, -1));
      } else {
        m_tokenTable->push_back(Token(TokenType::SUB, -1));
        continue;
      }
    } else if (m_lastChar == '+') {
      m_lastChar = istream.get();

      if (m_lastChar == '+') {
        m_tokenTable->push_back(Token(TokenType::INCREMENT, -1));
      } else if (m_lastChar == '>') {
        m_tokenTable->push_back(Token(TokenType::IMPLICATIONB, -1));
      } else {
        m_tokenTable->push_back(Token(TokenType::ADD, -1));
        continue;
      }
    } else if (m_lastChar == '~') {
      m_tokenTable->push_back(Token(TokenType::NOT, -1));
    } else if (m_lastChar == '*') {
      m_tokenTable->push_back(Token(TokenType::MUL, -1));
    } else if (m_lastChar == '&') {
      m_tokenTable->push_back(Token(TokenType::AND, -1));
    } else if (m_lastChar == '|') {
      m_tokenTable->push_back(Token(TokenType::OR, -1));
    } else if (m_lastChar == '#') {
      m_tokenTable->push_back(Token(TokenType::XOR, -1));
    } else if (m_lastChar == '/') {
      m_lastChar = istream.get();
      if (m_lastChar == '/') {
        skipLine = true;
        break;
      }
    } else {
      throw ParseException("(" + std::to_string(m_lineCount) + "," +
                           std::to_string(istream.tellg()) +
                           ") Error: " + "Unknown identifier");
    }

    m_lastChar = istream.get();
  }

  if (!skipLine) {
    std::cout << line << std::endl;
    m_tokenTable->push_back(Token(TokenType::NEW_LINE, -1));
  }
}
