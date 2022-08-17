#include "LexicalAnalyzer.hpp"

#include <iostream>

using namespace thl;

LexicalAnalyzer::LexicalAnalyzer()
    : m_lineCount(0) {}

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
  m_lineCount++;
  getTokens(line);
}

void thl::LexicalAnalyzer::getTokens(std::string &line) {
  bool skipLine = false;

  const char* p = line.c_str();
  const char* q;
  const char* start;
  size_t count = 0;

  for (size_t count = 0; count <= line.size(); ++count) {
    start = p;

    /*!re2c
    re2c:define:YYCTYPE = "char";
    re2c:define:YYCURSOR = p;
    re2c:define:YYMARKER = q;
    re2c:yyfill:enable = 0;
    
    nul = "\000";
    varname = [a-zA-Z][_a-zA-Z0-9]*;
    
    [ ]*"#"[^\000\n]*"\n" { continue; }
    [ ]*"\r\n" { m_tokenTable->push_back(Token(TokenType::ENDL, -1)); continue; }
    [ ]*"\n"   { m_tokenTable->push_back(Token(TokenType::ENDL, -1)); continue; }
    nul        { m_tokenTable->push_back(Token(TokenType::ENDL, -1)); continue; }

    varname       {
      m_tokenTable->push_back(Token(TokenType::IDENTIFIER,
        (int)m_identTable->size()));
      std::string s;
      s.assign(start, p - start);
      m_identTable->push_back(s);
      continue;
    }

    ":="       { m_tokenTable->push_back(Token(TokenType::ASSIGMENT, -1)); continue;}
    "("        { m_tokenTable->push_back(Token(TokenType::OPEN_BRACKET, -1)); continue;}
    ")"        { m_tokenTable->push_back(Token(TokenType::CLOSE_BRACKET, -1)); continue;}
    ","        { m_tokenTable->push_back(Token(TokenType::DELIMITER, -1)); continue;}

    "--"       { m_tokenTable->push_back(Token(TokenType::DECREMENT, -1)); continue;}
    "->"       { m_tokenTable->push_back(Token(TokenType::IMPLICATION, -1)); continue;}
    "-"        { m_tokenTable->push_back(Token(TokenType::SUB, -1)); continue;}

    "++"       { m_tokenTable->push_back(Token(TokenType::INCREMENT, -1)); continue;}
    "+>"       { m_tokenTable->push_back(Token(TokenType::IMPLICATIONB, -1)); continue;}
    "+"        { m_tokenTable->push_back(Token(TokenType::ADD, -1)); continue;}

    "~"        { m_tokenTable->push_back(Token(TokenType::NOT, -1)); continue;}
    "*"        { m_tokenTable->push_back(Token(TokenType::MUL, -1)); continue;}
    "&"        { m_tokenTable->push_back(Token(TokenType::AND, -1)); continue;}
    "|"        { m_tokenTable->push_back(Token(TokenType::OR, -1)); continue;}
    "#"        { m_tokenTable->push_back(Token(TokenType::XOR, -1)); continue;}

    "$"        {
      m_tokenTable->push_back(Token(TokenType::NUMBER, (int)m_constTable->size()));
      m_constTable->push_back(-1);
      continue;
    }
    "0"       {
      m_tokenTable->push_back(Token(TokenType::NUMBER, (int)m_constTable->size()));
      m_constTable->push_back(0);
      continue;
    }
    "1"        {
      m_tokenTable->push_back(Token(TokenType::NUMBER, (int)m_constTable->size()));
      m_constTable->push_back(1);
      continue;
    }

    "//"       { skipLine = true; break; }

    [^]        {
      throw ParseException("(" + std::to_string(m_lineCount) + "," +
                           std::to_string(count) +
                           ") Error: Unknown identifier");
      break;
    }
    */
  }

  if (!skipLine) {
    std::cout << line << std::endl;
    m_tokenTable->push_back(Token(TokenType::ENDL, -1));
  }

}
