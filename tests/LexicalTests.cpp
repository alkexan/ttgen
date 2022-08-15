#include "LexicalAnalyzer.hpp"
#include "Util.hpp"

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/assign.hpp>
#include <boost/test/tools/old/interface.hpp>
#include <boost/test/unit_test.hpp>
#include <memory>
#include <string>
#include <utility>

#define BOOST_TEST_MODULE TestLexical

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

  tokenTable = std::move(lexical.getTokenTable());
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

BOOST_AUTO_TEST_SUITE_END()
