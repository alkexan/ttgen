#include "Parser.hpp"
#include "Token.hpp"
#include <fstream>
#include <iostream>
#include <memory>

using namespace thl;

Parser::Parser()
    : m_tokenTable(std::make_shared<thl::TokenTable>()),
      m_constTable(std::make_shared<thl::ConstTable>()),
      m_identTable(std::make_shared<thl::IdentTable>()) {

  m_lexical.setTokenTable(m_tokenTable);
  m_lexical.setConstTable(m_constTable);
  m_lexical.setIdentTable(m_identTable);

  m_syntax.setTokenTable(m_tokenTable);
  m_syntax.setConstTable(m_constTable);
  m_syntax.setIdentTable(m_identTable);
}

bool Parser::parse(std::ifstream &ifstream) {
  bool res = false;

  if (!ifstream.is_open()) {
    std::cerr << "failed to open \n";
  } else {
    while (!ifstream.eof()) {
      std::string line;
      std::getline(ifstream, line);

      std::cout << line << std::endl;

      if (parse(line)) {
        m_codeGenerator.printTable();
      }
    }
  }

  return res;
}

bool Parser::parse(std::string &line) {
  bool res = true;
  try {
    m_tokenTable->clear();
    m_constTable->clear();
    m_identTable->clear();

    m_lexical.parse(line);

    m_syntax.parse();

    m_programAst = std::move(m_syntax.getProgramAst());

    if (m_programAst.size() > 0) {
      m_codeGenerator.visit(*m_programAst[0]);
      m_results = m_codeGenerator.getResults();
    } else {
      res = false;
    }
  } catch (ParseException &exception) {
    std::cerr << exception.getError() << std::endl;
    res = false;
  }

  return res;
}
