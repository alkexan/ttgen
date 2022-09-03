#include "LexicalAnalyzer.hpp"
#include "Util.hpp"

#include <iostream>
#include <utility>

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

void thl::LexicalAnalyzer::parse(std::istream &dataStream) {
  m_textPos.first++;
  m_textPos.second = 0;
  getTokens(dataStream);
}

void thl::LexicalAnalyzer::getTokens(std::istream &dataStream) {
  Token token;

  std::streampos marker;

  size_t count = 0;

  for (;;) {
    m_textPos.second++;

    /*!re2c
    re2c:api:style = free-form;

    re2c:define:YYPEEK       = "dataStream.peek()";
    re2c:define:YYSKIP       = "dataStream.ignore();";
    re2c:define:YYBACKUP     = "marker = dataStream.tellg();";
    re2c:define:YYRESTORE    = "dataStream.seekg(marker);";
    re2c:define:YYLESSTHAN   = "YYLIMIT - dataStream.tellg() < @@{len}";

    re2c:define:YYCTYPE = "char";
    re2c:yyfill:enable = 0;
    
    nul = "\000";
    varname = [a-zA-Z][_a-zA-Z0-9]*;
    
    [ ]+        { 
      continue; 
    }
    
    [ ]*"//"[^\000\n]*"\n" { 
      break; 
    }
    nul         { 
      tokenPushBack(TokenType::ENDL, -1, m_textPos); 
      break; 
    }

    [a-zA-Z]    {
      readIdent(dataStream);
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

void thl::LexicalAnalyzer::readIdent(std::istream &dataStream) {
  std::streampos marker;

  dataStream.unget();

  /*!re2c
    re2c:define:YYSKIP       = "m_ident += yych; dataStream.ignore();";
    
    varname     {
      tokenPushBack(TokenType::IDENTIFIER,
        (int)m_identTable->size(), m_textPos);

      m_identTable->push_back(m_ident);
      m_textPos.second += m_ident.size();

      std::cout << m_ident << std::endl;
      m_ident.clear();
      return;
    }
  */
}
