#include <fstream>
#include <iostream>
#include <vector>

#include <boost/program_options.hpp>

#include "CodeGenerator.hpp"
#include "LexicalAnalyzer.hpp"
#include "SyntaxAnalyzer.hpp"

using namespace thl;

namespace po = boost::program_options;

LexicalAnalyzer lexical;
SyntaxAnalyzer syntax;
CodeGenerator codeGenerator;

std::string sourceNameOption(const po::variables_map &vm);

void parceSource(const std::string &sourceName);

int main(int argc, char *argv[]) {
  po::options_description desc("General options");
  std::string task_type;
  desc.add_options()("help,h", "Show help")(
      "source,S", po::value<std::string>(), "Source file");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << "\n";
  } else if (vm.count("source")) {
    std::string sourceName = vm["source"].as<std::string>();
    if (sourceName.size() == 0) {
      std::cout << "The source file is not set. Use --help for more information"
                << std::endl;
    } else {
      parceSource(sourceName);
    }
  } else {
    std::cout << desc << std::endl;
  }

  return 0;
}

void parceSource(const std::string &sourceName) {
  std::ifstream ifstream(sourceName);
  bool isContinue = ifstream.is_open();
  if (!isContinue) {
    std::cerr << "failed to open \n";
  } else {
    try {
      lexical.parse(ifstream);

      syntax.setLexemeTable(std::move(lexical.getLexemeTable()));
      syntax.setConstTable(std::move(lexical.getConstTable()));
      syntax.setIdentTable(std::move(lexical.getIdentTable()));

      syntax.parse();

      auto lexemeTable = std::move(syntax.getLexemeTable());
      auto programAst = std::move(syntax.getProgramAst());

      for (int i = 0; i < programAst.size(); i++) {
        codeGenerator.visit(*programAst[i]);
        std::cout << "\n";
      }

    } catch (ParseException &exception) {
      std::cerr << exception.getError();
    }
  }
}
