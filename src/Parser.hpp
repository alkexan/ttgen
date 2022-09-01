#pragma once

#include "CodeGenerator.hpp"
#include "LexicalAnalyzer.hpp"
#include "SyntaxAnalyzer.hpp"
#include <memory>
#include <string>

using namespace thl;

class Parser {
public:
  Parser();

  void parse(std::string &parseData, bool isFile = false);

  std::vector<TBoolean> getResults() {
    return m_results;
  }

  void printTable() {
    m_codeGenerator.printTable();
  }

private:

  std::unique_ptr<TokenTable> m_tokenTable;
  std::unique_ptr<ConstTable> m_constTable;
  std::unique_ptr<IdentTable> m_identTable;

  std::vector<std::unique_ptr<FunctionAST>> m_programAst;

  std::vector<TBoolean> m_results;

  LexicalAnalyzer m_lexical;
  SyntaxAnalyzer m_syntax;
  CodeGenerator m_codeGenerator;

  void parseFile(std::string &fileName);
  void parseLine(std::string &line);
};
