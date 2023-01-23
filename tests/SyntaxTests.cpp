#include "LexicalAnalyzer.hpp"
#include "SyntaxAnalyzer.hpp"
#include "Token.hpp"

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/assign.hpp>
#include <boost/test/tools/old/interface.hpp>
#include <boost/test/unit_test.hpp>
#include <memory>
#include <string>
#include <utility>

#define BOOST_TEST_MODULE TestSyntax

std::shared_ptr<thl::TokenTable> tokenTable =
    std::make_unique<thl::TokenTable>();
std::shared_ptr<thl::ConstTable> constTable =
    std::make_unique<thl::ConstTable>();
std::shared_ptr<thl::IdentTable> identTable =
    std::make_unique<thl::IdentTable>();

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

  lexical.setTokenTable(tokenTable);
  lexical.setConstTable(constTable);
  lexical.setIdentTable(identTable);

  lexical.parse(testString);
  lexical.printResult();

  SyntaxAnalyzer syntax;

  syntax.setTokenTable(tokenTable);
  syntax.setConstTable(constTable);
  syntax.setIdentTable(identTable);

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

BOOST_AUTO_TEST_CASE(ThreeOperations_1) {
  parseData("f(x, y) := x -> y -> 0");
}

BOOST_AUTO_TEST_CASE(ThreeOperations_2) {
  parseData("f(x, y) := x -> y -> 0");
}

BOOST_AUTO_TEST_CASE(ThreeOperations_3) {
  parseData("f(x, y) := x -> y -> 0");
}

BOOST_AUTO_TEST_CASE(ConstsWithoutParams) {
  parseData("f() := 0 & 1 -> $");
}

BOOST_AUTO_TEST_CASE(VariableWithoutParams) {
  std::string message;

  try {
    parseData("f() := x -> y | z");
  } catch (thl::ParseException &exception) {
    message = exception.getError();
  }
  
  BOOST_CHECK(message.find("Undeclarated identifier"));
}

BOOST_AUTO_TEST_SUITE_END()
