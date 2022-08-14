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

BOOST_AUTO_TEST_CASE(TestLexical) {
  using namespace thl;

  LexicalAnalyzer lexical;

  auto tokenTable = std::make_unique<TokenTable>();
  auto constTable = std::make_unique<ConstTable>();
  auto identTable = std::make_unique<IdentTable>();

  lexical.setTokenTable(std::move(tokenTable));
  lexical.setConstTable(std::move(constTable));
  lexical.setIdentTable(std::move(identTable));

  std::string testString = "f(x):=x";
  lexical.parse(testString);
  
  lexical.printResult();

  tokenTable = std::move(lexical.getTokenTable());
  BOOST_CHECK((*tokenTable)[0].getToken() == TokenType::IDENTIFIER);
  BOOST_CHECK((*tokenTable)[1].getToken() == TokenType::OPEN_BRACKET);
  BOOST_CHECK((*tokenTable)[2].getToken() == TokenType::IDENTIFIER);
  BOOST_CHECK((*tokenTable)[3].getToken() == TokenType::CLOSE_BRACKET);
  BOOST_CHECK((*tokenTable)[4].getToken() == TokenType::ASSIGMENT);
  BOOST_CHECK((*tokenTable)[5].getToken() == TokenType::IDENTIFIER);
  BOOST_CHECK((*tokenTable)[6].getToken() == TokenType::ENDL);
}
