#ifndef SRC__LEXICAL_ANALYZER__HPP
#define SRC__LEXICAL_ANALYZER__HPP

#include <istream>
#include <memory>

#include "Util.hpp"
#include "LexicalError.hpp"

namespace thl
{
	class LexicalAnalyzer
	{
	public:
		LexicalAnalyzer();
		~LexicalAnalyzer();

		std::unique_ptr < TokenTable > getTokenTable();
		std::unique_ptr < ConstTable > getConstTable();
		std::unique_ptr < IdentTable > getIdentTable();

		LexicalError getError() const;

		bool parse(std::istream& istream);

	private:
		std::unique_ptr < TokenTable > m_tokenTable;
		std::unique_ptr < ConstTable > m_constTable;
		std::unique_ptr < IdentTable > m_identTable;

		LexicalError m_error;
	};
}

#endif // SRC__LEXICAL_ANALYZER__HPP
