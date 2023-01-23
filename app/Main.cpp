#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include <boost/program_options.hpp>

#include "Parser.hpp"

#include "version.h"

namespace po = boost::program_options;

static thl::Parser parser;
static std::string parseSource;

void printFunctions() {
  std::cout << "This program supported this logical funcions.\n"
            << "Not - \"~\" for use\n"
            << "|   x   |   f   |\n"
            << "|:-----:|:-----:|\n"
            << "|  -1   |   1   |\n"
            << "|   0   |   0   |\n"
            << "|   1   |  -1   |\n"
            << "\n\n\n"
            << "Decrement - \"--< x >\" for use\n"
            << "|   x   |   f   |\n"
            << "|:-----:|:-----:|\n"
            << "|  -1   |   1   |\n"
            << "|   0   |  -1   |\n"
            << "|   1   |   0   |\n"
            << "\n\n\n"
            << "Increment - \"++< x >\" for use\n"
            << "|   x   |   f   |\n"
            << "|:-----:|:-----:|\n"
            << "|  -1   |   0   |\n"
            << "|   0   |   1   |\n"
            << "|   1   |  -1   |\n"
            << "\n\n\n"
            << "Or - \"|\" for use\n"
            << "|   x   |   y   |   f   |\n"
            << "|:-----:|:-----:|:-----:|\n"
            << "|  -1   |  -1   |  -1   |\n"
            << "|  -1   |   0   |   0   |\n"
            << "|  -1   |   1   |   1   |\n"
            << "|   0   |  -1   |   0   |\n"
            << "|   0   |   0   |   0   |\n"
            << "|   0   |   1   |   1   |\n"
            << "|   1   |  -1   |   1   |\n"
            << "|   1   |   0   |   1   |\n"
            << "|   1   |   1   |   1   |\n"
            << "\n\n\n"
            << "And - \"&\" for use\n"
            << "|   x   |   y   |   f   |\n"
            << "|:-----:|:-----:|:-----:|\n"
            << "|  -1   |  -1   |  -1   |\n"
            << "|  -1   |   0   |  -1   |\n"
            << "|  -1   |   1   |  -1   |\n"
            << "|   0   |  -1   |  -1   |\n"
            << "|   0   |   0   |   0   |\n"
            << "|   0   |   1   |   0   |\n"
            << "|   1   |  -1   |  -1   |\n"
            << "|   1   |   0   |   0   |\n"
            << "|   1   |   1   |   1   |\n"
            << "\n\n\n"
            << "Diffirential - \"\\\" for use\n"
            << "|   x   |   y   |   f   |\n"
            << "|:-----:|:-----:|:-----:|\n"
            << "|  -1   |  -1   |  -1   |\n"
            << "|  -1   |   0   |   0   |\n"
            << "|  -1   |   1   |  -1   |\n"
            << "|   0   |  -1   |   0   |\n"
            << "|   0   |   0   |   0   |\n"
            << "|   0   |   1   |  -1   |\n"
            << "|   1   |  -1   |   1   |\n"
            << "|   1   |   0   |   0   |\n"
            << "|   1   |   1   |  -1   |\n"
            << "\n\n\n"
            << "XOR - \"#\" for use\n"
            << "|   x   |   y   |   f   |\n"
            << "|:-----:|:-----:|:-----:|\n"
            << "|  -1   |  -1   |  -1   |\n"
            << "|  -1   |   0   |   0   |\n"
            << "|  -1   |   1   |   1   |\n"
            << "|   0   |  -1   |   0   |\n"
            << "|   0   |   0   |   0   |\n"
            << "|   0   |   1   |   0   |\n"
            << "|   1   |  -1   |   1   |\n"
            << "|   1   |   0   |   0   |\n"
            << "|   1   |   1   |  -1   |\n"
            << "\n\n\n"
            << "Sum - \"+\" for use\n"
            << "|   x   |   y   |   f   |\n"
            << "|:-----:|:-----:|:-----:|\n"
            << "|  -1   |  -1   |  -1   |\n"
            << "|  -1   |   0   |  -1   |\n"
            << "|  -1   |   1   |   0   |\n"
            << "|   0   |  -1   |  -1   |\n"
            << "|   0   |   0   |   0   |\n"
            << "|   0   |   1   |   1   |\n"
            << "|   1   |  -1   |  -1   |\n"
            << "|   1   |   0   |   1   |\n"
            << "|   1   |   1   |   1   |\n"
            << "\n\n\n"
            << "Mul - \"*\" for use\n"
            << "|   x   |   y   |   f   |\n"
            << "|:-----:|:-----:|:-----:|\n"
            << "|  -1   |  -1   |   1   |\n"
            << "|  -1   |   0   |   0   |\n"
            << "|  -1   |   1   |  -1   |\n"
            << "|   0   |  -1   |   0   |\n"
            << "|   0   |   0   |   0   |\n"
            << "|   0   |   1   |   0   |\n"
            << "|   1   |  -1   |  -1   |\n"
            << "|   1   |   0   |   0   |\n"
            << "|   1   |   1   |   1   |\n"
            << "\n\n\n"
            << "Substract - \"-\" for use\n"
            << "|   x   |   y   |   f   |\n"
            << "|:-----:|:-----:|:-----:|\n"
            << "|  -1   |  -1   |   0   |\n"
            << "|  -1   |   0   |  -1   |\n"
            << "|  -1   |   1   |  -1   |\n"
            << "|   0   |  -1   |   1   |\n"
            << "|   0   |   0   |   0   |\n"
            << "|   0   |   1   |  -1   |\n"
            << "|   1   |  -1   |   1   |\n"
            << "|   1   |   0   |   1   |\n"
            << "|   1   |   1   |   0   |\n"
            << "\n\n\n"
            << "Implication - \"->\" for use\n"
            << "|   x   |   y   |   f   |\n"
            << "|:-----:|:-----:|:-----:|\n"
            << "|  -1   |  -1   |   1   |\n"
            << "|  -1   |   0   |   1   |\n"
            << "|  -1   |   1   |   1   |\n"
            << "|   0   |  -1   |   0   |\n"
            << "|   0   |   0   |   0   |\n"
            << "|   0   |   1   |   1   |\n"
            << "|   1   |  -1   |  -1   |\n"
            << "|   1   |   0   |   0   |\n"
            << "|   1   |   1   |   1   |\n"
            << "\n\n"
            << std::endl;
}

int main(int argc, char* argv[]) {
  po::options_description desc("General options");
  std::string task_type;
  desc.add_options()
    ("help,h", "Show help")
    ("functions", "Show a description of all supported logical functions")
    ("version,v", "Show version")
    ("source,S", po::value<std::string>(), "Source file");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << "\n";
  } else if (vm.count("functions")) {
    printFunctions();
  } else if (vm.count("version")) {
    std::cout << VERSION << std::endl;
  } else if (vm.count("source")) {
    parseSource = vm["source"].as<std::string>();
    if (parseSource.size() == 0) {
      std::cout << "The source file is not set. Use --help for more information"
                << std::endl;
    } else {
      parser.parse(parseSource, true);
    }
  } else {
    while (true) {
      std::cout << ">> ";
      std::getline(std::cin, parseSource);

      if (parseSource == "!q") {
        break;
      } else {
        if (parser.parse(parseSource)) {
          parser.printTable();
        }
      }
    }
  }

  return 0;
}
