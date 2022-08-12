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

  const char* p = line.c_str();
  const char* q;
  const char* start;
  size_t count = 0;

  for (;;) {
    count++;
    start = p;

    /*!re2c
    re2c:define:YYCTYPE = "char";
    re2c:define:YYCURSOR = p;
    re2c:define:YYMARKER = q;
    re2c:yyfill:enable = 0;
    nul = "\000";
    varname = [a-zA-Z0-9_-]+;
    [ ]*"#"[^\000\n]*"\n" { continue; }
    [ ]*"\r\n" { m_lexemTable->push_back(Lexeme(Token::NEW_LINE, -1)); break; }
    [ ]*"\n"   { m_lexemTable->push_back(Lexeme(Token::NEW_LINE, -1)); break; }
    nul        { m_lexemTable->push_back(Lexeme(Token::NEW_LINE, -1)); break; }

    [ ]+       {
      m_lexemTable->push_back(Lexeme(Token::IDENTIFIER,
        (int)m_identTable->size()));
      std::string s;
      s.assign(start, p - start);
      m_identTable->push_back(s);
      break;
    }

    ":="       { m_lexemTable->push_back(Lexeme(Token::ASSIGMENT, -1)); break; }
    "("        { m_lexemTable->push_back(Lexeme(Token::OPEN_BRACKET, -1)); break; }
    ")"        { m_lexemTable->push_back(Lexeme(Token::CLOSE_BRACKET, -1)); break; }
    ","        { m_lexemTable->push_back(Lexeme(Token::DELIMITER, -1)); break; }

    "--"       { m_lexemTable->push_back(Lexeme(Token::DECREMENT, -1)); break; }
    "->"       { m_lexemTable->push_back(Lexeme(Token::IMPLICATION, -1)); break; }
    "-"        { m_lexemTable->push_back(Lexeme(Token::SUB, -1)); break; }

    "++"       { m_lexemTable->push_back(Lexeme(Token::DECREMENT, -1)); break; }
    "+>"       { m_lexemTable->push_back(Lexeme(Token::IMPLICATION, -1)); break; }
    "+"        { m_lexemTable->push_back(Lexeme(Token::SUB, -1)); break; }

    "~"        { m_lexemTable->push_back(Lexeme(Token::NOT, -1)); break; }
    "*"        { m_lexemTable->push_back(Lexeme(Token::MUL, -1)); break; }
    "&"        { m_lexemTable->push_back(Lexeme(Token::AND, -1)); break; }
    "|"        { m_lexemTable->push_back(Lexeme(Token::OR, -1)); break; }
    "#"        { m_lexemTable->push_back(Lexeme(Token::XOR, -1)); break; }

    "$"        {
      m_lexemTable->push_back(Lexeme(Token::NUMBER, (int)m_constTable->size()));
      m_constTable->push_back(-1);
      break;
    }
    "0>"       {
      m_lexemTable->push_back(Lexeme(Token::NUMBER, (int)m_constTable->size()));
      m_constTable->push_back(0);
      break;
    }
    "1"        {
      m_lexemTable->push_back(Lexeme(Token::NUMBER, (int)m_constTable->size()));
      m_constTable->push_back(1);
      break;
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
    m_lexemTable->push_back(Lexeme(Token::NEW_LINE, -1));
  }

}
