#include "Parser.hpp"
#include "Util.hpp"
#include <fstream>
#include <iostream>
#include <memory>

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

bool Parser::parse(std::string &parseData, bool isFile) {
  bool res = false;

  m_tokenTable->clear();
  m_constTable->clear();
  m_identTable->clear();

  if (isFile) {
    res = parseFile(parseData);
  } else {
    res = parseLine(parseData);
  }

  return res;
}

bool Parser::parseFile(std::string &fileName) {
  bool res = false;

  std::ifstream ifstream(fileName);
  if (!ifstream.is_open()) {
    std::cerr << "failed to open \n";
  } else {
    while (!ifstream.eof()) {
      std::string line;
      std::getline(ifstream, line);

      res = parseLine(line);
    }
  }

  return res;
}

bool Parser::parseLine(std::string &line) {
  bool res = true;
  try {
    m_lexical.parse(line);

    m_syntax.parse();

    m_programAst = std::move(m_syntax.getProgramAst());

    m_codeGenerator.visit(*m_programAst[0]);
    m_results = m_codeGenerator.getResults();
  } catch (ParseException &exception) {
    std::cerr << exception.getError() << std::endl;
    res = false;
  }

  return res;
}
