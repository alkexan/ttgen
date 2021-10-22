#ifndef SRC__UTIL__HPP
#define SRC__UTIL__HPP

#include <array>
#include <vector>
#include <string>
#include <utility>
#include <map>

namespace thl
{
	enum class Token
	{
		ENDF = -1,
		// primary
		IDENTIFIER,
		NUMBER,
		// operators
		OPEN_BRACKET,
		CLOSE_BRACKET,
		DELIMITER,
		NEW_LINE,
		// not null operators
		ASSIGMENT,
		IMPLICATION,
		IMPLICATIONB,
		NOT,
		DECREMENT,
		INCREMENT,
		OR,
		XOR,
		SUB,
		ADD,
		AND,
		MUL,
	};

	static std::map <std::string, Token> operators = {
		{"(", Token::OPEN_BRACKET},
		{")", Token::CLOSE_BRACKET},
		{",", Token::DELIMITER},
		{"/n", Token::NEW_LINE},
		{":=", Token::ASSIGMENT},
		{"->", Token::IMPLICATION},
		{"+>", Token::IMPLICATIONB},
		{"~", Token::NOT},
		{"--", Token::DECREMENT},
		{"++", Token::INCREMENT},
		{"|", Token::OR},
		{"#", Token::XOR},
		{"-", Token::SUB},
		{"+", Token::ADD},
		{"&", Token::AND},
		{"*", Token::MUL},
	};

	class Lexeme
	{
	public:
		Lexeme() : m_token(Token::ENDF), m_attribute(-1),
			m_textPos(std::make_pair(0, 0))
		{}

		Lexeme(Token token, int attr) : m_token(token), m_attribute(attr),
			m_textPos(std::make_pair(0, 0))
		{}

		Lexeme(std::pair<Token, int> tokenPair) : m_token(tokenPair.first), m_attribute(tokenPair.second),
			m_textPos(std::make_pair(0, 0))
		{}

		inline Token getToken() const
		{
			return m_token;
		}

		inline int getAttribute() const
		{
			return m_attribute;
		}

		inline void setTextPosition(std::pair<int, int> textPos)
		{
			m_textPos = textPos;
		}

		inline std::pair<int, int> getTextPosition() const
		{
			return m_textPos;
		}

	private:
		Token m_token;
		int m_attribute;
		std::pair<int, int> m_textPos;
	};

	typedef std::vector<Lexeme> LexemeTable;
	typedef std::vector<std::string> IdentTable;
	typedef std::vector<int> ConstTable;

	inline std::string tokenToString(Token token)
	{
		std::string result = "";
		switch (token)
		{
			case thl::Token::ENDF:
				result = "ENDF";
				break;
			case thl::Token::IDENTIFIER:
				result = "IDENTIFIER";
				break;
			case thl::Token::NUMBER:
				result = "NUMBER";
				break;
			case thl::Token::OPEN_BRACKET:
				result = "OPEN_BRACKET";
				break;
			case thl::Token::CLOSE_BRACKET:
				result = "CLOSE_BRACKET";
				break;
			case thl::Token::DELIMITER:
				result = "DELIMITER";
				break;
			case thl::Token::NEW_LINE:
				result = "END_LINE";
				break;
			case thl::Token::ASSIGMENT:
				result = "ASSIGMENT";
				break;
			case thl::Token::IMPLICATION:
				result = "IMPLICATION";
				break;
			case thl::Token::IMPLICATIONB:
				result = "IMPLICATIONB";
				break;
			case thl::Token::DECREMENT:
				result = "DECREMENT";
				break;
			case thl::Token::INCREMENT:
				result = "INCREMENT";
				break;
			case thl::Token::SUB:
				result = "SUB";
				break;
			case thl::Token::ADD:
				result = "ADD";
				break;
			case thl::Token::NOT:
				result = "NOT";
				break;
			case thl::Token::AND:
				result = "AND";
				break;
			case thl::Token::MUL:
				result = "MUL";
				break;
			case thl::Token::OR:
				result = "OR";
				break;
			case thl::Token::XOR:
				result = "XOR";
				break;
			default:
				result = "";
				break;
		}
		return result;
	}

	template<typename Base, typename T>
	inline bool instanceof(const T*)
	{
		return std::is_base_of<Base, T>::value;
	}
}

#endif // SRC__LEXICAL_ANALYZER__HPP
