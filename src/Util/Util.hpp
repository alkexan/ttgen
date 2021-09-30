#ifndef SRC__UTIL__HPP
#define SRC__UTIL__HPP

#include <array>
#include <vector>
#include <string>
#include <utility>

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
        ASSIGMENT,

        IMPLICATION,
        IMPLICATIONB,
        DECREMENT,
        INCREMENT,
        SUB,
        ADD,

        NOT,

        AND,
        MUL,
        OR,
        XOR,
    };

    class Lexeme
    {
    public:
        Lexeme(Token token, int attr) : m_token(token), m_attr(attr),
            m_textPos(std::make_pair(0, 0))
        {}
        Lexeme(std::pair<Token, int> tokenPair) : m_token(tokenPair.first), m_attr(tokenPair.second),
            m_textPos(std::make_pair(0, 0))
        {}

        inline Token token() const
        {
            return m_token;
        }

        inline int attr() const
        {
            return m_attr;
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
        int m_attr;
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
}

#endif // SRC__LEXICAL_ANALYZER__HPP
