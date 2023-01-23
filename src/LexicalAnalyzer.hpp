#ifndef SRC__LEXICAL_ANALYZER__HPP
#define SRC__LEXICAL_ANALYZER__HPP

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "ParseException.hpp"
#include "Token.hpp"

namespace thl {
  /**
   * @brief Lexical Analyzer class
   * 
   */
class LexicalAnalyzer {
public:
  LexicalAnalyzer();
  ~LexicalAnalyzer();

  void setTokenTable(std::shared_ptr<TokenTable> lexemTable);
  void setConstTable(std::shared_ptr<ConstTable> constTable);
  void setIdentTable(std::shared_ptr<IdentTable> identTable);

  void parse(std::string &line);

  inline void printResult();

private:
  std::pair<int, int> m_textPos;

  std::shared_ptr<TokenTable> m_tokenTable;
  std::shared_ptr<ConstTable> m_constTable;
  std::shared_ptr<IdentTable> m_identTable;

  inline void tokenPushBack(TokenType tokenType, int attr,
                            std::pair<int, int> textPos);
  void getTokens(std::string &line);

  inline std::string getTokenAttr(Token token);
};

/*
[pos] <token>: attr
*/

inline void LexicalAnalyzer::tokenPushBack(TokenType tokenType, int attr,
                                           std::pair<int, int> textPos) {
  Token token(tokenType, attr, m_textPos);
  m_tokenTable->push_back(token);
}

inline void LexicalAnalyzer::printResult() {
  for (Token token : *m_tokenTable) {
    std::cout << "[" << token.getTextPosition().first << ", "
              << token.getTextPosition().second << "] " << token.toString()
              << getTokenAttr(token) << std::endl;
  }
}

inline std::string LexicalAnalyzer::getTokenAttr(Token token) {
  std::string result = "";

  switch (token.getType()) {
  case TokenType::IDENTIFIER:
    result = ": " + (*m_identTable)[token.getAttribute()];
    break;
  case TokenType::NUMBER: {
    auto attr = (*m_constTable)[token.getAttribute()];
    result = ": " + std::to_string(attr);
    break;
  }
  default:
    break;
  }

  return result;
}

} // namespace thl

#endif // SRC__LEXICAL_ANALYZER__HPP
