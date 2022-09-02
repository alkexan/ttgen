#include "Parser.hpp"
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

void parseData(std::string testString) {
  using namespace thl;

  Parser parser;
  parser.parse(testString);
}

BOOST_AUTO_TEST_SUITE(TestLexical)

BOOST_AUTO_TEST_CASE(Simple) {
  parseData("f(x):=x");
}

BOOST_AUTO_TEST_CASE(SimpleWithSpaces) {
  parseData("f(x) := x");
}

BOOST_AUTO_TEST_CASE(TwoParams) {
  parseData("f(x,y):=x&y");
}

BOOST_AUTO_TEST_CASE(TwoParamsWithSpaces) {
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
  parseData("f() := x -> y | z");
}

BOOST_AUTO_TEST_CASE(ConstAsParams) {
  parseData("f(0, $) := 0 & 1 | $");
}

BOOST_AUTO_TEST_SUITE_END()
