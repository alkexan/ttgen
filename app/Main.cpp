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
    std::string sourceName = vm["source"].as<std::string>();
    if (sourceName.size() == 0) {
      std::cout << "The source file is not set. Use --help for more information"
                << std::endl;
    } else {
      Parser parser = Parser(sourceName);
      parser.parse();
    }
  } else {
    std::cout << desc << std::endl;
  }

  return 0;
}
