#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

#include "LexicalAnalyzer.hpp"
#include "SyntaxAnalyzer.hpp"
#include "CodeGenerator.hpp"

using namespace thl;

namespace fs = std::filesystem;

LexicalAnalyzer lexical;
SyntaxAnalyzer syntax;
CodeGenerator codeGenerator;

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

			auto lexemeTable = std::move(syntax.getLexemeTable());
			auto programAst = std::move(syntax.getProgramAst());

			for (int i = 0 ; i < programAst.size(); i++)
			{
				codeGenerator.visit(*programAst[i]);
				std::cout << "\n";
			}

		} catch (ParseException &exception)
		{
			std::cerr << exception.getError();
		}
	}

	return 0;
}
