#include "Parser.hpp"
#include "Util.hpp"
#include <fstream>
#include <iostream>

Parser::Parser() {}

void Parser::parse(std::string &parseData, bool isFile) {
  if (!m_tokenTable) {
    m_tokenTable = std::make_unique<thl::TokenTable>();
  } else {
    m_tokenTable->clear();
  }

  if (!m_constTable) {
    m_constTable = std::make_unique<thl::ConstTable>();
  } else {
    m_constTable->clear();
  }

  if (!m_identTable) {
    m_identTable = std::make_unique<thl::IdentTable>();
  } else {
    m_identTable->clear();
  }

  if (isFile) {
    parseFile(parseData);
  } else {
    parseLine(parseData);
  }
}

void Parser::parseFile(std::string &fileName) {
  std::ifstream ifstream(fileName);
  bool isContinue = ifstream.is_open();
  if (!isContinue) {
    std::cerr << "failed to open \n";
  } else {
    while (!ifstream.eof()) {
      std::string line;
      std::getline(ifstream, line);

      parseLine(line);
    }
  }
}

void Parser::parseLine(std::string &line) {
  try {
    m_lexical.setTokenTable(std::move(m_tokenTable));
    m_lexical.setConstTable(std::move(m_constTable));
    m_lexical.setIdentTable(std::move(m_identTable));
    m_lexical.parse(line);

    m_syntax.setTokenTable(std::move(m_lexical.getTokenTable()));
    m_syntax.setConstTable(std::move(m_lexical.getConstTable()));
    m_syntax.setIdentTable(std::move(m_lexical.getIdentTable()));
    m_syntax.parse();

    m_tokenTable = std::move(m_syntax.getTokenTable());
    m_programAst = std::move(m_syntax.getProgramAst());

    m_codeGenerator.visit(*m_programAst[0]);
    m_results = m_codeGenerator.getResults();
  } catch (ParseException &exception) {
    std::cerr << exception.getError() << std::endl;
  }
}
