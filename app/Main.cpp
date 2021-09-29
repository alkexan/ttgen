#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>

#include "LexicalAnalyzer.hpp"

using namespace thl;

namespace fs = std::filesystem;

LexicalAnalyzer lexical;

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
		size_t lineCount = 0;
		while (!ifstream.eof())
		{
			lineCount++;
			std::string line;
			std::getline(ifstream, line);

			if (lexical.parse(std::istringstream(line)))
			{
				std::unique_ptr < TokenTable > m_tokenTable = lexical.getTokenTable();

				std::cout << line << std::endl;

				for (auto i = m_tokenTable->begin(); i < m_tokenTable->end(); i++)
				{
					std::cout << tokenToString(i->token()) << ":";
				}
			}
			else
			{
				std::cout << lineCount << ","
					<< lexical.getError().getPos() << ":"
					<< lexical.getError().getMsg();
			}
			
		}
	}

	return 0;
}
