#include "Parser.hpp"
#include <fstream>
#include <iostream>

Parser::Parser(const std::string &sourceName) : m_fileName(sourceName) {}

void Parser::setFile(const std::string &sourceName) { m_fileName = sourceName; }

void Parser::parse() {
  std::ifstream ifstream(m_fileName);
  bool isContinue = ifstream.is_open();
  if (!isContinue) {
    std::cerr << "failed to open \n";
  } else {
    try {
      while (!ifstream.eof()) {
        std::string line;
        std::getline(ifstream, line);

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
      }
    } catch (ParseException &exception) {
      std::cerr << exception.getError() << std::endl;
    }
  }
}
