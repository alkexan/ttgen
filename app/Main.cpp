﻿#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include <boost/program_options.hpp>

#include "Parser.hpp"

#include "version.h"

namespace po = boost::program_options;

static Parser parser;
static std::string parseSource;

int main(int argc, char *argv[]) {
  po::options_description desc("General options");
  std::string task_type;
  desc.add_options()("help,h", "Show help")("version,v", "Show version")(
      "source,S", po::value<std::string>(), "Source file");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << "\n";
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
      std::cin >> parseSource;

      if (parseSource == "!q") {
        break;
      } else {
        parser.parse(parseSource);
      }
    }
  }

  return 0;
}
