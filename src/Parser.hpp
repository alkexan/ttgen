#pragma once

#include "CodeGenerator.hpp"
#include "LexicalAnalyzer.hpp"
#include "SyntaxAnalyzer.hpp"
#include <string>
#include <memory>

using namespace thl;

class Parser {
public:
  Parser();

  void parse(std::string &parseData, bool isFile);

private:
  std::unique_ptr<LexemeTable> m_lexemTable;
  std::unique_ptr<ConstTable> m_constTable;
  std::unique_ptr<IdentTable> m_identTable;

  std::vector<std::unique_ptr<FunctionAST>> m_programAst;

  LexicalAnalyzer m_lexical;
  SyntaxAnalyzer m_syntax;
  CodeGenerator m_codeGenerator;

  void parseFile(std::string &fileName);
  void parseLine(std::string &line);
};
