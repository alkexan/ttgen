#include "LexicalAnalyzer.hpp"
#include "Util.hpp"

#include <iostream>
#include <utility>

using namespace thl;

LexicalAnalyzer::LexicalAnalyzer()
    : m_textPos(std::make_pair(0, 0)) {}

LexicalAnalyzer::~LexicalAnalyzer() {}

void thl::LexicalAnalyzer::setTokenTable(
    std::shared_ptr<TokenTable> lexemTable) {
  m_tokenTable = lexemTable;
}

void thl::LexicalAnalyzer::setConstTable(
    std::shared_ptr<ConstTable> constTable) {
  m_constTable = constTable;
}

void thl::LexicalAnalyzer::setIdentTable(
    std::shared_ptr<IdentTable> identTable) {
  m_identTable = identTable;
}

void thl::LexicalAnalyzer::parse(std::string &line) {
  m_textPos.first++;
  m_textPos.second = 0;
  getTokens(line);
}

void thl::LexicalAnalyzer::getTokens(std::string &line) {
  Token token;

  const char* p = line.c_str();
  const char* q;
  const char* start;
  size_t count = 0;

  for (;;) {
    m_textPos.second++;
    start = p;

    /*!re2c
    re2c:define:YYCTYPE = "char";
    re2c:define:YYCURSOR = p;
    re2c:define:YYMARKER = q;
    re2c:yyfill:enable = 0;
    
    nul = "\000";
    varname = [a-zA-Z][_a-zA-Z0-9]*;
    
    [ ]+        { continue; }
    [ ]*"//"[^\000\n]* { break; }

    [ ]*"\r\n" { 
      tokenPushBack(TokenType::ENDL, -1, m_textPos); 
      break; 
    }
    [ ]*"\n"   { 
      tokenPushBack(TokenType::ENDL, -1, m_textPos); 
      break; 
    }

    nul         { 
      tokenPushBack(TokenType::ENDL, -1, m_textPos); 
      break; 
    }

    varname     {
      tokenPushBack(TokenType::IDENTIFIER,
        (int)m_identTable->size(), m_textPos);

      std::string s;
      s.assign(start, p - start);
      m_identTable->push_back(s);
      continue;
    }

    ":="        { 
      tokenPushBack(TokenType::ASSIGMENT, -1, m_textPos);
      continue;
    }
    "("         { 
      tokenPushBack(TokenType::OPEN_BRACKET, -1, m_textPos);
      continue;
    }
    ")"         { 
      tokenPushBack(TokenType::CLOSE_BRACKET, -1, m_textPos);
      continue;
    }
    ","         { 
      tokenPushBack(TokenType::DELIMITER, -1, m_textPos);
      continue;
    }

    "--"        { 
      tokenPushBack(TokenType::DECREMENT, -1, m_textPos);
      continue;
    }
    "->"        { 
      tokenPushBack(TokenType::IMPLICATION, -1, m_textPos);
      continue;
    }
    "-"         { 
      tokenPushBack(TokenType::SUB, -1, m_textPos);
      continue;
    }

    "++"        { 
      tokenPushBack(TokenType::INCREMENT, -1, m_textPos);
      continue;
    }
    "+>"        { 
      tokenPushBack(TokenType::IMPLICATIONB, -1, m_textPos);
      continue;
    }
    "+"         { 
      tokenPushBack(TokenType::ADD, -1, m_textPos);
      continue;
    }

    "~"         { 
      tokenPushBack(TokenType::NOT, -1, m_textPos);
      continue;
    }
    "*"         { 
      tokenPushBack(TokenType::MUL, -1, m_textPos);
      continue;
    }
    "&"         { 
      tokenPushBack(TokenType::AND, -1, m_textPos);
      continue;
    }
    "|"         { 
      tokenPushBack(TokenType::OR, -1, m_textPos);
      continue;
    }
    "#"         { 
      tokenPushBack(TokenType::XOR, -1, m_textPos);
      continue;
    }

    "$"         {
      tokenPushBack(TokenType::NUMBER, (int)m_constTable->size(), m_textPos);
      m_constTable->push_back(-1);
      continue;
    }
    "0"         {
      tokenPushBack(TokenType::NUMBER, (int)m_constTable->size(), m_textPos);
      m_constTable->push_back(0);
      continue;
    }
    "1"         {
      tokenPushBack(TokenType::NUMBER, (int)m_constTable->size(), m_textPos);
      m_constTable->push_back(1);
      continue;
    }

    [^]         {
      std::string err = "(" + std::to_string(m_textPos.first) + "," +
                           std::to_string(m_textPos.second) +
                           ") Error: Unknown identifier";
      throw ParseException(err);
      break;
    }
    */
  }
}
