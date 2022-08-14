#include "Parser.hpp"
#include <fstream>
#include <iostream>

Parser::Parser() {
    m_lexemTable = std::make_unique<TokenTable>();
    m_constTable = std::make_unique<ConstTable>();
    m_identTable = std::make_unique<IdentTable>();
}

void Parser::parse(std::string &parseData, bool isFile) {
  m_lexemTable->clear();
  m_constTable->clear();
  m_identTable->clear();

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
    m_lexical.setTokenTable(std::move(m_lexemTable));
    m_lexical.setConstTable(std::move(m_constTable));
    m_lexical.setIdentTable(std::move(m_identTable));
    m_lexical.parse(line);

    m_syntax.setLexemeTable(std::move(m_lexical.getTokenTable()));
    m_syntax.setConstTable(std::move(m_lexical.getConstTable()));
    m_syntax.setIdentTable(std::move(m_lexical.getIdentTable()));
    m_syntax.parse();

    m_lexemTable = std::move(m_syntax.getLexemeTable());
    m_programAst = std::move(m_syntax.getProgramAst());

    for (int i = 0; i < m_programAst.size(); i++) {
      m_codeGenerator.visit(*m_programAst[i]);
      std::cout << "\n";
    }
  } catch (ParseException &exception) {
    std::cerr << exception.getError() << std::endl;
  }
}
