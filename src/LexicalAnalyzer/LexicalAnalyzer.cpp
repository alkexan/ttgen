#include "LexicalAnalyzer.hpp"

#include <iostream>
#include <cctype>

using namespace thl;

LexicalAnalyzer::LexicalAnalyzer() :
	m_lineCount(0),
	m_lexemTable(std::make_unique<LexemeTable>()),
	m_constTable(std::make_unique<ConstTable>()),
	m_identTable(std::make_unique<IdentTable>())
{}

LexicalAnalyzer::~LexicalAnalyzer()
{}

std::unique_ptr<LexemeTable> thl::LexicalAnalyzer::getLexemeTable()
{
	return std::move(m_lexemTable);
}

std::unique_ptr<ConstTable> thl::LexicalAnalyzer::getConstTable()
{
	return std::move(m_constTable);
}

std::unique_ptr<IdentTable> thl::LexicalAnalyzer::getIdentTable()
{
	return std::move(m_identTable);
}

void thl::LexicalAnalyzer::parse(std::istream& istream)
{
	if (m_lexemTable.get() == nullptr)
	{
		m_lexemTable = std::make_unique<LexemeTable>();
	}
	else
	{
		m_lexemTable->clear();
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

	m_lineCount = 0;

	while (!istream.eof())
	{
		m_lexemTable->push_back(Lexeme(Token::NEW_LINE, -1));

		m_lineCount++;
		std::string line;
		std::getline(istream, line);
		std::istringstream istream(line);
		parseLine(istream);
	}
}

void thl::LexicalAnalyzer::parseLine(std::istringstream& istream)
{
	std::string line;
	int m_lastChar = istream.get();

	while (m_lastChar != -1)
	{
		// identifier: [a-z][_a-zA-Z0-9]*
		if (isspace(m_lastChar))
		{
			m_lastChar = istream.get();
			continue;
		}
		else if (isalpha(m_lastChar))
		{
			std::string identifierStr;
			identifierStr += m_lastChar;

			m_lastChar = istream.get();
			while (isalnum(m_lastChar) || m_lastChar == '_')
			{
				identifierStr += m_lastChar;
				m_lastChar = istream.get();
			}

			m_lexemTable->push_back(Lexeme(Token::IDENTIFIER, (int)m_identTable->size()));
			m_identTable->push_back(identifierStr);

			continue;
		}
		else if (m_lastChar == '$' || m_lastChar == '0' || m_lastChar == '1')
		{
			m_lexemTable->push_back(Lexeme(Token::NUMBER, (int)m_constTable->size()));

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
		else if (m_lastChar == '(')
		{
			m_lexemTable->push_back(Lexeme(Token::OPEN_BRACKET, -1));
		}
		else if (m_lastChar == ')')
		{
			m_lexemTable->push_back(Lexeme(Token::CLOSE_BRACKET, -1));
		}
		else if (m_lastChar == ',')
		{
			m_lexemTable->push_back(Lexeme(Token::DELIMITER, -1));
		}
		else if (m_lastChar == '\n')
		{
			m_lexemTable->push_back(Lexeme(Token::NEW_LINE, -1));
		}
		else if (m_lastChar == ':')
		{
			m_lastChar = istream.get();
			if (m_lastChar == '=')
			{
				m_lexemTable->push_back(Lexeme(Token::ASSIGMENT, -1));
			}
			else
			{
				throw ParseException("(" + std::to_string(m_lineCount) + "," + 
					std::to_string(istream.tellg()) + ") Error: " + 
					"Unknown identifier");
			}
		}
		else if (m_lastChar == '-')
		{
			m_lastChar = istream.get();

			if (m_lastChar == '-')
			{
				m_lexemTable->push_back(Lexeme(Token::DECREMENT, -1));
			}
			else if (m_lastChar == '>')
			{
				m_lexemTable->push_back(Lexeme(Token::IMPLICATION, -1));
			}
			else
			{
				m_lexemTable->push_back(Lexeme(Token::SUB, -1));
				continue;
			}
		}
		else if (m_lastChar == '+')
		{
			m_lastChar = istream.get();

			if (m_lastChar == '+')
			{
				m_lexemTable->push_back(Lexeme(Token::INCREMENT, -1));
			}
			else if (m_lastChar == '>')
			{
				m_lexemTable->push_back(Lexeme(Token::IMPLICATIONB, -1));
			}
			else
			{
				m_lexemTable->push_back(Lexeme(Token::ADD, -1));
				continue;
			}
		}
		else if (m_lastChar == '~')
		{
			m_lexemTable->push_back(Lexeme(Token::NOT, -1));
		}
		else if (m_lastChar == '*')
		{
			m_lexemTable->push_back(Lexeme(Token::MUL, -1));
		}
		else if (m_lastChar == '&')
		{
			m_lexemTable->push_back(Lexeme(Token::AND, -1));
		}
		else if (m_lastChar == '|')
		{
			m_lexemTable->push_back(Lexeme(Token::OR, -1));
		}
		else if (m_lastChar == '#')
		{
			m_lexemTable->push_back(Lexeme(Token::XOR, -1));
		}
		else if (m_lastChar == '/')
		{
			m_lastChar = istream.get();
			// ����������� �� ����� ������.
			if (m_lastChar == '/')
			{
				break;
			}
		}
		else if (m_lastChar == EOF)
		{
			m_lexemTable->push_back(Lexeme(Token::ENDF, -1));
		}
		else
		{
			throw ParseException("(" + std::to_string(m_lineCount) + "," +
				std::to_string(istream.tellg()) + ") Error: " +
				"Unknown identifier");

		}

		m_lastChar = istream.get();
	}
}
