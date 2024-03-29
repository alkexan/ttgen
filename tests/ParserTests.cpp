#include "Parser.hpp"
#include "Token.hpp"
#include <iostream>

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/assign.hpp>
#include <boost/test/tools/old/interface.hpp>
#include <boost/test/unit_test.hpp>
#include <memory>
#include <string>
#include <fstream>
#include <utility>

#define BOOST_TEST_MODULE TestLexical

void parseData(std::string testString) {
  using namespace thl;

  Parser parser;
  std::cout << testString << std::endl;
  if (parser.parse(testString)) {
    parser.printTable();
  }
}

BOOST_AUTO_TEST_SUITE(TestLexical)

BOOST_AUTO_TEST_CASE(Simple) { parseData("f(x):=x"); }

BOOST_AUTO_TEST_CASE(SimpleWithSpaces) { parseData("f(x) := x"); }

BOOST_AUTO_TEST_CASE(TwoParams) { parseData("f(x,y):=x&y"); }

BOOST_AUTO_TEST_CASE(TwoParamsWithSpaces) { parseData("f(x, y) := x & y"); }

BOOST_AUTO_TEST_CASE(NoOpen) {
  using namespace thl;

  std::string fileName = "./example/noopen_example.txt";
  std::ifstream ifstream(fileName);

  Parser parser;
  parser.parse(ifstream);
}

BOOST_AUTO_TEST_CASE(Example) {
  using namespace thl;

  std::string fileName = "./example/example.txt";
  std::ifstream ifstream(fileName);

  Parser parser;
  parser.parse(ifstream);
}

BOOST_AUTO_TEST_CASE(Example2) {
  using namespace thl;

  std::string fileName = "./example/example2.txt";
  std::ifstream ifstream(fileName);

  Parser parser;
  parser.parse(ifstream);
}

BOOST_AUTO_TEST_CASE(Callable) {
  using namespace thl;

  std::string fileName = "./example/example_call.txt";
  std::ifstream ifstream(fileName);

  Parser parser;
  parser.parse(ifstream);
}

BOOST_AUTO_TEST_CASE(ThreeOperations_1) { parseData("f(x, y) := x -> y -> 0"); }

BOOST_AUTO_TEST_CASE(ThreeOperations_2) { parseData("f(x, y) := x -> y -> 0"); }

BOOST_AUTO_TEST_CASE(ThreeOperations_3) { parseData("f(x, y) := x -> y -> 0"); }

BOOST_AUTO_TEST_CASE(ConstsWithoutParams) { parseData("f() := 0 & 1 -> $"); }

BOOST_AUTO_TEST_CASE(VariableWithoutParams) { parseData("f() := x -> y | z"); }

BOOST_AUTO_TEST_CASE(ConstAsParams) { parseData("f(0, $) := 0 & 1 | $"); }

BOOST_AUTO_TEST_SUITE_END()
