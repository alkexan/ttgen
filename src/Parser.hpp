#pragma once

#include "CodeGenerator.hpp"
#include "LexicalAnalyzer.hpp"
#include "SyntaxAnalyzer.hpp"

using namespace thl;

class Parser {
public:
  Parser(const std::string &sourceName);
  void setFile(const std::string &sourceName);
  void parse();

private:
  std::string m_fileName;

  LexicalAnalyzer m_lexical;
  SyntaxAnalyzer m_syntax;
  CodeGenerator m_codeGenerator;
};
