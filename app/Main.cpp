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
		if (lexical.parse(ifstream))
		{
			std::unique_ptr < LexemeTable > m_lexemTable = lexical.getLexemeTable();

			for (auto i = m_lexemTable->begin(); i < m_lexemTable->end(); i++)
			{
				std::cout << tokenToString(i->token()) << ":";
			}

			syntax.setLexemeTable(std::move(m_lexemTable));
			syntax.setConstTable(std::move(lexical.getConstTable()));
			syntax.setIdentTable(std::move(lexical.getIdentTable()));
		}
	}

	return 0;
}
