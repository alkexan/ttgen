#include "Parser.hpp"
#include <fstream>
#include <iostream>

Parser::Parser() : m_isFile(false), m_parseData("") {}
Parser::Parser(const std::string &parseData, bool isFile) : m_isFile(isFile), m_parseData(parseData) {}

void Parser::setParseData(const std::string &parseData, bool isFile) {
  m_isFile = isFile;
  m_parseData = parseData;
}

void Parser::parse() {
  if (m_isFile) {
    parseFile(m_parseData);
  } else {
    parseLine(m_parseData);
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
    m_lexical.parse(line);

    m_syntax.setLexemeTable(std::move(m_lexical.getLexemeTable()));
    m_syntax.setConstTable(std::move(m_lexical.getConstTable()));
    m_syntax.setIdentTable(std::move(m_lexical.getIdentTable()));
    m_syntax.parse();

    auto lexemeTable = std::move(m_syntax.getLexemeTable());
    auto programAst = std::move(m_syntax.getProgramAst());

    for (int i = 0; i < programAst.size(); i++) {
    m_codeGenerator.visit(*programAst[i]);
    std::cout << "\n";
    }
  } catch (ParseException &exception) {
    std::cerr << exception.getError() << std::endl;
  }
}
