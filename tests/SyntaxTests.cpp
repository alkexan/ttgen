#include "LexicalAnalyzer.hpp"
#include "SyntaxAnalyzer.hpp"
#include "Util.hpp"

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/assign.hpp>
#include <boost/test/tools/old/interface.hpp>
#include <boost/test/unit_test.hpp>
#include <memory>
#include <string>
#include <utility>

#define BOOST_TEST_MODULE TestSyntax

std::unique_ptr<thl::TokenTable> tokenTable;
std::unique_ptr<thl::ConstTable> constTable;
std::unique_ptr<thl::IdentTable> identTable;

void parseData(std::string testString) {
  using namespace thl;

  LexicalAnalyzer lexical;

  if (!tokenTable) {
    tokenTable = std::make_unique<thl::TokenTable>();
  } else {
    tokenTable->clear();
  }

  if (!constTable) {
    constTable = std::make_unique<thl::ConstTable>();
  } else {
    constTable->clear();
  }

  if (!identTable) {
    identTable = std::make_unique<thl::IdentTable>();
  } else {
    identTable->clear();
  }

  lexical.setTokenTable(std::move(tokenTable));
  lexical.setConstTable(std::move(constTable));
  lexical.setIdentTable(std::move(identTable));

  lexical.parse(testString);
  lexical.printResult();

  SyntaxAnalyzer syntax;

  syntax.setTokenTable(std::move(lexical.getTokenTable()));
  syntax.setConstTable(std::move(lexical.getConstTable()));
  syntax.setIdentTable(std::move(lexical.getIdentTable()));

  syntax.parse();
}

BOOST_AUTO_TEST_SUITE(TestSyntax)

BOOST_AUTO_TEST_CASE(SyntaxSimple) {
  parseData("f(x):=x");
}

BOOST_AUTO_TEST_CASE(SyntaxSimpleWithSpaces) {
  parseData("f(x) := x");
}

BOOST_AUTO_TEST_CASE(TwoParamsSimple) {
  parseData("f(x,y):=x&y");
}

BOOST_AUTO_TEST_CASE(TwoParamsSimpleWithSpaces) {
  parseData("f(x, y) := x & y");
}

BOOST_AUTO_TEST_CASE(ThreeOperations) {
  parseData("f(x, y) := x | y | 0");
}

BOOST_AUTO_TEST_SUITE_END()
