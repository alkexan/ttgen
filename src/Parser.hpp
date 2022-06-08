#pragma once

#include "CodeGenerator.hpp"
#include "LexicalAnalyzer.hpp"
#include "SyntaxAnalyzer.hpp"
#include <string>

using namespace thl;

class Parser {
public:
  Parser();
  Parser(const std::string &parseData, bool isFile);

  void setParseData(const std::string &parseData, bool isFile);
  void parse();

private:
  bool m_isFile;

  std::string m_parseData;

  LexicalAnalyzer m_lexical;
  SyntaxAnalyzer m_syntax;
  CodeGenerator m_codeGenerator;

  void parseFile(std::string &fileName);
  void parseLine(std::string &line);
};
