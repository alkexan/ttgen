#include "LexicalAnalyzer.hpp"

#include <iostream>
#include <cctype>

using namespace thl;

LexicalAnalyzer::LexicalAnalyzer() :
	m_tokenTable(std::make_unique<TokenTable>()),
	m_constTable(std::make_unique<ConstTable>()),
	m_identTable(std::make_unique<IdentTable>()),
	m_error(0, "")
{}

LexicalAnalyzer::~LexicalAnalyzer()
{}

std::unique_ptr<TokenTable> thl::LexicalAnalyzer::getTokenTable()
{
	return std::move(m_tokenTable);
}

std::unique_ptr<ConstTable> thl::LexicalAnalyzer::getConstTable()
{
	return std::move(m_constTable);
}

std::unique_ptr<IdentTable> thl::LexicalAnalyzer::getIdentTable()
{
	return std::move(m_identTable);
}

LexicalError thl::LexicalAnalyzer::getError() const
{
	return m_error;
}

bool thl::LexicalAnalyzer::parse(std::istream& istream)
{
	if (m_tokenTable.get() == nullptr)
	{
		m_tokenTable = std::make_unique<TokenTable>();
	}
	else
	{
		m_tokenTable->clear();
	}
	if (m_constTable.get() == nullptr)
	{
		m_constTable = std::make_unique<ConstTable>();
	}
	else
	{
		m_constTable->clear();
	}
	if (m_identTable.get() == nullptr)
	{
		m_identTable = std::make_unique<IdentTable>();
	}
	else
	{
		m_identTable->clear();
	}

	bool result = true;
	std::string line;
	int m_lastChar = istream.get();

	while (m_lastChar != -1 && result == true)
	{
		// identifier: [a-z][_a-zA-Z0-9]*
		if (isalpha(m_lastChar))
		{
			std::string identifierStr;
			identifierStr += m_lastChar;

			m_lastChar = istream.get();
			while (isalnum(m_lastChar) || m_lastChar == '_')
			{
				identifierStr += m_lastChar;
				m_lastChar = istream.get();
			}

			m_tokenTable->push_back(TokenCell(Token::IDENTIFIER, m_identTable->size()));
			m_identTable->push_back(identifierStr);

			continue;
		}
		else if (m_lastChar == '(')
		{
			m_tokenTable->push_back(TokenCell(Token::OPEN_BRACKET, -1));
		}
		else if (m_lastChar == ',')
		{
			m_tokenTable->push_back(TokenCell(Token::DELIMITER, -1));
		}
		else if (m_lastChar == ')')
		{
			m_tokenTable->push_back(TokenCell(Token::CLOSE_BRACKET, -1));
		}
		else if (m_lastChar == '=')
		{
			m_tokenTable->push_back(TokenCell(Token::ASSIGMENT, -1));
		}
		else if (m_lastChar == '$' || m_lastChar == '0' || m_lastChar == '1')
		{
			m_tokenTable->push_back(TokenCell(Token::NUMBER, m_constTable->size()));

			switch (m_lastChar)
			{
				case '$':
					m_constTable->push_back(-1);
					break;
				case '0':
					m_constTable->push_back(0);
					break;
				default:
					m_constTable->push_back(1);
					break;
			}
		}
		else if (m_lastChar == '-')
		{
			m_lastChar = istream.get();

			if (m_lastChar == '-')
			{
				m_tokenTable->push_back(TokenCell(Token::DECREMENT, -1));
			}
			else if (m_lastChar == '>')
			{
				m_tokenTable->push_back(TokenCell(Token::IMPLICATION, -1));
			}
			else
			{
				m_tokenTable->push_back(TokenCell(Token::SUB, -1));
				continue;
			}
		}
		else if (m_lastChar == '+')
		{
			m_lastChar = istream.get();

			if (m_lastChar == '+')
			{
				m_tokenTable->push_back(TokenCell(Token::INCREMENT, -1));
			}
			else if (m_lastChar == '>')
			{
				m_tokenTable->push_back(TokenCell(Token::IMPLICATIONB, -1));
			}
			else
			{
				m_tokenTable->push_back(TokenCell(Token::ADD, -1));
				continue;
			}
		}
		else if (m_lastChar == '~')
		{
			m_tokenTable->push_back(TokenCell(Token::NOT, -1));
		}
		else if (m_lastChar == '*')
		{
			m_tokenTable->push_back(TokenCell(Token::MUL, -1));
		}
		else if (m_lastChar == '&')
		{
			m_tokenTable->push_back(TokenCell(Token::AND, -1));
		}
		else if (m_lastChar == '|')
		{
			m_tokenTable->push_back(TokenCell(Token::OR, -1));
		}
		else if (m_lastChar == '#')
		{
			m_tokenTable->push_back(TokenCell(Token::XOR, -1));
		}
		else if (m_lastChar == ' ')
		{
			m_tokenTable->push_back(TokenCell(Token::SPACE, -1));
		}
		else if (m_lastChar == '\n')
		{
			m_tokenTable->push_back(TokenCell(Token::ENDL, -1));
		}
		else if (m_lastChar == EOF)
		{
			m_tokenTable->push_back(TokenCell(Token::ENDF, -1));
		}
		else
		{
			m_error = LexicalError(istream.tellg(), "Unknown identifier");
			result = false;
		}

		m_lastChar = istream.get();
	}

	return result;
}
