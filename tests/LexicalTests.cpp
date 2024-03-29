#include "LexicalAnalyzer.hpp"
#include "Token.hpp"

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/assign.hpp>
#include <boost/test/tools/old/interface.hpp>
#include <boost/test/unit_test.hpp>
#include <memory>
#include <string>
#include <utility>

#define BOOST_TEST_MODULE TestLexical

std::shared_ptr<thl::TokenTable> tokenTable =
    std::make_unique<thl::TokenTable>();
std::shared_ptr<thl::ConstTable> constTable =
    std::make_unique<thl::ConstTable>();
std::shared_ptr<thl::IdentTable> identTable =
    std::make_unique<thl::IdentTable>();

void parseData(std::string testString) {
  using namespace thl;

  LexicalAnalyzer lexical;

  tokenTable->clear();
  constTable->clear();
  identTable->clear();

  lexical.setTokenTable(tokenTable);
  lexical.setConstTable(constTable);
  lexical.setIdentTable(identTable);

  lexical.parse(testString);
  lexical.printResult();
}

BOOST_AUTO_TEST_SUITE(TestLexical)

BOOST_AUTO_TEST_CASE(Simple) {
  parseData("f(x):=x");

  using namespace thl;
  BOOST_CHECK((*tokenTable)[0].getType() == TokenType::IDENTIFIER);
  BOOST_CHECK((*tokenTable)[1].getType() == TokenType::OPEN_BRACKET);
  BOOST_CHECK((*tokenTable)[2].getType() == TokenType::IDENTIFIER);
  BOOST_CHECK((*tokenTable)[3].getType() == TokenType::CLOSE_BRACKET);
  BOOST_CHECK((*tokenTable)[4].getType() == TokenType::ASSIGMENT);
  BOOST_CHECK((*tokenTable)[5].getType() == TokenType::IDENTIFIER);
  BOOST_CHECK((*tokenTable)[6].getType() == TokenType::ENDL);
}

BOOST_AUTO_TEST_CASE(SimpleWithSpaces) {
  parseData("f(x) := x");

  using namespace thl;
  BOOST_CHECK((*tokenTable)[0].getType() == TokenType::IDENTIFIER);
  BOOST_CHECK((*tokenTable)[1].getType() == TokenType::OPEN_BRACKET);
  BOOST_CHECK((*tokenTable)[2].getType() == TokenType::IDENTIFIER);
  BOOST_CHECK((*tokenTable)[3].getType() == TokenType::CLOSE_BRACKET);
  BOOST_CHECK((*tokenTable)[4].getType() == TokenType::ASSIGMENT);
  BOOST_CHECK((*tokenTable)[5].getType() == TokenType::IDENTIFIER);
  BOOST_CHECK((*tokenTable)[6].getType() == TokenType::ENDL);
}

BOOST_AUTO_TEST_CASE(TwoParams) {
  parseData("f(x,y):=x&y");

  using namespace thl;
  BOOST_CHECK((*tokenTable)[0].getType() == TokenType::IDENTIFIER);
  BOOST_CHECK((*tokenTable)[1].getType() == TokenType::OPEN_BRACKET);
  BOOST_CHECK((*tokenTable)[2].getType() == TokenType::IDENTIFIER);
  BOOST_CHECK((*tokenTable)[3].getType() == TokenType::DELIMITER);
  BOOST_CHECK((*tokenTable)[4].getType() == TokenType::IDENTIFIER);
  BOOST_CHECK((*tokenTable)[5].getType() == TokenType::CLOSE_BRACKET);
  BOOST_CHECK((*tokenTable)[6].getType() == TokenType::ASSIGMENT);
  BOOST_CHECK((*tokenTable)[7].getType() == TokenType::IDENTIFIER);
  BOOST_CHECK((*tokenTable)[8].getType() == TokenType::AND);
  BOOST_CHECK((*tokenTable)[9].getType() == TokenType::IDENTIFIER);
  BOOST_CHECK((*tokenTable)[10].getType() == TokenType::ENDL);
}

BOOST_AUTO_TEST_CASE(TwoParamsWithSpaces) {
  parseData("f(x, y) := x & y");

  using namespace thl;
  BOOST_CHECK((*tokenTable)[0].getType() == TokenType::IDENTIFIER);
  BOOST_CHECK((*tokenTable)[1].getType() == TokenType::OPEN_BRACKET);
  BOOST_CHECK((*tokenTable)[2].getType() == TokenType::IDENTIFIER);
  BOOST_CHECK((*tokenTable)[3].getType() == TokenType::DELIMITER);
  BOOST_CHECK((*tokenTable)[4].getType() == TokenType::IDENTIFIER);
  BOOST_CHECK((*tokenTable)[5].getType() == TokenType::CLOSE_BRACKET);
  BOOST_CHECK((*tokenTable)[6].getType() == TokenType::ASSIGMENT);
  BOOST_CHECK((*tokenTable)[7].getType() == TokenType::IDENTIFIER);
  BOOST_CHECK((*tokenTable)[8].getType() == TokenType::AND);
  BOOST_CHECK((*tokenTable)[9].getType() == TokenType::IDENTIFIER);
  BOOST_CHECK((*tokenTable)[10].getType() == TokenType::ENDL);
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
  parseData("f() := x -> y | z");
}

BOOST_AUTO_TEST_CASE(ConstAsParams) {
  parseData("f(0, $) := 0 & 1 | $");
}

BOOST_AUTO_TEST_SUITE_END()
