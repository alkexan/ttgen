#include "LexicalAnalyzer.hpp"

#include <iostream>

using namespace thl;

LexicalAnalyzer::LexicalAnalyzer()
    : m_textPos(std::make_pair(0, 0)) {}

LexicalAnalyzer::~LexicalAnalyzer() {}

void thl::LexicalAnalyzer::setTokenTable(
    std::unique_ptr<TokenTable> lexemTable) {
  m_tokenTable = std::move(lexemTable);
}

void thl::LexicalAnalyzer::setConstTable(
    std::unique_ptr<ConstTable> constTable) {
  m_constTable = std::move(constTable);
}

void thl::LexicalAnalyzer::setIdentTable(
    std::unique_ptr<IdentTable> identTable) {
  m_identTable = std::move(identTable);
}

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
  m_textPos.first++;
  m_textPos.second = 0;
  getTokens(line);
}

void thl::LexicalAnalyzer::getTokens(std::string &line) {
  bool skipLine = false;
  std::istringstream istream(line);

  int m_lastChar = istream.get();

  while (!istream.eof()) {
    m_textPos.second++;

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

      tokenPushBack(TokenType::IDENTIFIER, (int)m_identTable->size(),
                    m_textPos);
      m_identTable->push_back(identifierStr);

      continue;
    } else if (m_lastChar == '$' || m_lastChar == '0' || m_lastChar == '1') {
      tokenPushBack(TokenType::NUMBER, (int)m_constTable->size(), m_textPos);

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
      tokenPushBack(TokenType::OPEN_BRACKET, -1, m_textPos);
    } else if (m_lastChar == ')') {
      tokenPushBack(TokenType::CLOSE_BRACKET, -1, m_textPos);
    } else if (m_lastChar == ',') {
      tokenPushBack(TokenType::DELIMITER, -1, m_textPos);
    } else if (m_lastChar == '\n') {
      tokenPushBack(TokenType::ENDL, -1, m_textPos);
    } else if (m_lastChar == ':') {
      m_lastChar = istream.get();
      if (m_lastChar == '=') {
        tokenPushBack(TokenType::ASSIGMENT, -1, m_textPos);
      } else {
        throw ParseException("(" + std::to_string(m_textPos.first) + "," +
                             std::to_string(m_textPos.second) +
                             "] Error: " + "Unknown identifier");
      }
    } else if (m_lastChar == '-') {
      m_lastChar = istream.get();

      if (m_lastChar == '-') {
        tokenPushBack(TokenType::DECREMENT, -1, m_textPos);
      } else if (m_lastChar == '>') {
        tokenPushBack(TokenType::IMPLICATION, -1, m_textPos);
      } else {
        tokenPushBack(TokenType::SUB, -1, m_textPos);
        continue;
      }
    } else if (m_lastChar == '+') {
      m_lastChar = istream.get();

      if (m_lastChar == '+') {
        tokenPushBack(TokenType::INCREMENT, -1, m_textPos);
      } else if (m_lastChar == '>') {
        tokenPushBack(TokenType::IMPLICATIONB, -1, m_textPos);
      } else {
        tokenPushBack(TokenType::ADD, -1, m_textPos);
        continue;
      }
    } else if (m_lastChar == '~') {
      tokenPushBack(TokenType::NOT, -1, m_textPos);
    } else if (m_lastChar == '*') {
      tokenPushBack(TokenType::MUL, -1, m_textPos);
    } else if (m_lastChar == '&') {
      tokenPushBack(TokenType::AND, -1, m_textPos);
    } else if (m_lastChar == '|') {
      tokenPushBack(TokenType::OR, -1, m_textPos);
    } else if (m_lastChar == '#') {
      tokenPushBack(TokenType::XOR, -1, m_textPos);
    } else if (m_lastChar == '/') {
      m_lastChar = istream.get();
      if (m_lastChar == '/') {
        skipLine = true;
        break;
      }
    } else {
      throw ParseException("(" + std::to_string(m_textPos.first) + "," +
                           std::to_string(m_textPos.second) +
                           "] Error: " + "Unknown identifier");
    }

    m_lastChar = istream.get();
  }

  if (!skipLine) {
    std::cout << line << std::endl;
    tokenPushBack(TokenType::ENDL, -1, m_textPos);
  }
}
