#ifndef SRC__LEXICAL_ANALYZER__HPP
#define SRC__LEXICAL_ANALYZER__HPP

#include <memory>
#include <sstream>

#include "Util.hpp"
#include "ParseException.hpp"

namespace thl
{
	class LexicalAnalyzer
	{
	public:
		LexicalAnalyzer();
		~LexicalAnalyzer();

		std::unique_ptr < LexemeTable > getLexemeTable();
		std::unique_ptr < ConstTable > getConstTable();
		std::unique_ptr < IdentTable > getIdentTable();

		void parse(std::istream& istream);

	private:
		size_t m_lineCount;

		std::unique_ptr < LexemeTable > m_lexemTable;
		std::unique_ptr < ConstTable > m_constTable;
		std::unique_ptr < IdentTable > m_identTable;

		void parseLine(std::istringstream& istream);
	};
}

#endif // SRC__LEXICAL_ANALYZER__HPP
