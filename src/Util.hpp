#ifndef SRC__UTIL__HPP
#define SRC__UTIL__HPP

#include <array>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace thl {
enum class TokenType {
  ENDF = -1,
  // primary
  IDENTIFIER,
  NUMBER,
  // operators
  OPEN_BRACKET,
  CLOSE_BRACKET,
  DELIMITER,
  ENDL,
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
  DIF,
};

static std::map<std::string, TokenType> operators = {
    {"(", TokenType::OPEN_BRACKET},
    {")", TokenType::CLOSE_BRACKET},
    {",", TokenType::DELIMITER},
    {"/n", TokenType::ENDL},
    {":=", TokenType::ASSIGMENT},
    {"->", TokenType::IMPLICATION},
    {"+>", TokenType::IMPLICATIONB},
    {"~", TokenType::NOT},
    {"--", TokenType::DECREMENT},
    {"++", TokenType::INCREMENT},
    {"|", TokenType::OR},
    {"#", TokenType::XOR},
    {"-", TokenType::SUB},
    {"+", TokenType::ADD},
    {"&", TokenType::AND},
    {"*", TokenType::MUL},
    {"*", TokenType::DIF},
};

class Token {
public:
  Token()
      : m_type(TokenType::ENDF), m_attribute(-1),
        m_textPos(std::make_pair(0, 0)) {}

  Token(TokenType TokenType, int attr, std::pair<int, int> textPos)
      : m_type(TokenType), m_attribute(attr), m_textPos(textPos) {}

  inline TokenType getType() const { return m_type; }

  inline int getAttribute() const { return m_attribute; }

  inline void setAttributes(TokenType TokenType, int attr,
                            std::pair<int, int> textPos) {
    m_type = TokenType;
    m_attribute = attr;
    m_textPos = textPos;
  }

  inline std::string toString();

  inline std::pair<int, int> getTextPosition() const { return m_textPos; }

private:
  TokenType m_type;
  int m_attribute;
  std::pair<int, int> m_textPos;
};

typedef std::vector<Token> TokenTable;
typedef std::vector<std::string> IdentTable;
typedef std::vector<int> ConstTable;

inline std::string Token::toString() {
  std::string result = "";
  switch (m_type) {
  case thl::TokenType::ENDF:
    result = "ENDF";
    break;
  case thl::TokenType::IDENTIFIER:
    result = "IDENTIFIER";
    break;
  case thl::TokenType::NUMBER:
    result = "NUMBER";
    break;
  case thl::TokenType::OPEN_BRACKET:
    result = "OPEN_BRACKET";
    break;
  case thl::TokenType::CLOSE_BRACKET:
    result = "CLOSE_BRACKET";
    break;
  case thl::TokenType::DELIMITER:
    result = "DELIMITER";
    break;
  case thl::TokenType::ENDL:
    result = "ENDL";
    break;
  case thl::TokenType::ASSIGMENT:
    result = "ASSIGMENT";
    break;
  case thl::TokenType::IMPLICATION:
    result = "IMPLICATION";
    break;
  case thl::TokenType::IMPLICATIONB:
    result = "IMPLICATIONB";
    break;
  case thl::TokenType::DECREMENT:
    result = "DECREMENT";
    break;
  case thl::TokenType::INCREMENT:
    result = "INCREMENT";
    break;
  case thl::TokenType::SUB:
    result = "SUB";
    break;
  case thl::TokenType::ADD:
    result = "ADD";
    break;
  case thl::TokenType::NOT:
    result = "NOT";
    break;
  case thl::TokenType::AND:
    result = "AND";
    break;
  case thl::TokenType::MUL:
    result = "MUL";
    break;
  case thl::TokenType::OR:
    result = "OR";
    break;
  case thl::TokenType::XOR:
    result = "XOR";
    break;
  case thl::TokenType::DIF:
    result = "DIF";
  default:
    result = "";
    break;
  }
  return result;
}

template <typename Base, typename T> inline bool instanceof (const T *) {
  return std::is_base_of<Base, T>::value;
}
} // namespace thl

#endif // SRC__LEXICAL_ANALYZER__HPP
