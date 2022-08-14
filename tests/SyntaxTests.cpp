#include "SyntaxAnalyzer.hpp"
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

#define BOOST_TEST_MODULE TestSyntax

auto tokenTable = std::make_unique<thl::TokenTable>();
auto constTable = std::make_unique<thl::ConstTable>();
auto identTable = std::make_unique<thl::IdentTable>();

void prepareData() {
  using namespace thl;

  LexicalAnalyzer lexical;

  lexical.setTokenTable(std::move(tokenTable));
  lexical.setConstTable(std::move(constTable));
  lexical.setIdentTable(std::move(identTable));

  std::string testString = "f(x):=x";
  lexical.parse(testString);

  tokenTable = std::move(lexical.getTokenTable());
  constTable = std::move(lexical.getConstTable());
  identTable = std::move(lexical.getIdentTable());
}

BOOST_AUTO_TEST_CASE(TestSyntax) {
  using namespace thl;

  prepareData();

  SyntaxAnalyzer syntax;

  syntax.setTokenTable(std::move(tokenTable));
  syntax.setConstTable(std::move(constTable));
  syntax.setIdentTable(std::move(identTable));

  syntax.parse();
}
