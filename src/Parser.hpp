#pragma once

#include "CodeGenerator.hpp"
#include "LexicalAnalyzer.hpp"
#include "SyntaxAnalyzer.hpp"
#include <memory>
#include <string>

namespace thl {

class Parser {
public:
  Parser();

  bool parse(std::string &line);
  bool parse(std::ifstream &ifstream);

  std::vector<TBoolean> getResults() {
    return m_results;
  }

  void printTable() {
    m_codeGenerator.printTable();
  }

private:

  std::shared_ptr<TokenTable> m_tokenTable;
  std::shared_ptr<ConstTable> m_constTable;
  std::shared_ptr<IdentTable> m_identTable;

  std::vector<std::unique_ptr<FunctionAST>> m_programAst;

  std::vector<TBoolean> m_results;

  LexicalAnalyzer m_lexical;
  SyntaxAnalyzer m_syntax;
  CodeGenerator m_codeGenerator;
};

}