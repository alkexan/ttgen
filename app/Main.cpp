#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

#include "LexicalAnalyzer.hpp"
#include "SyntaxAnalyzer.hpp"

using namespace thl;

namespace fs = std::filesystem;

LexicalAnalyzer lexical;
SyntaxAnalyzer syntax;

int main(int argc, char* argv[])
{
	fs::path filePath = "E:/Alkexan/Documents/MEGA/MEGAsync/software_workspace/ttgen/test/test";
	std::ifstream ifstream(filePath);
	bool isContinue = ifstream.is_open();
	if (!isContinue)
	{
		std::cout << "failed to open \n";
	}
	else
	{
		try
		{
			lexical.parse(ifstream);
			
			syntax.setLexemeTable(std::move(lexical.getLexemeTable()));
			syntax.setConstTable(std::move(lexical.getConstTable()));
			syntax.setIdentTable(std::move(lexical.getIdentTable()));

			syntax.parse();
		} catch (ParseException &exception)
		{
			std::cerr << exception.getError();
		}
	}

	return 0;
}
