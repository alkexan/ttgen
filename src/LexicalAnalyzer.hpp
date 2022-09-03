#ifndef SRC__LEXICAL_ANALYZER__HPP
#define SRC__LEXICAL_ANALYZER__HPP

#include <iostream>
#include <istream>
#include <memory>
#include <sstream>
#include <string>

#include "ParseException.hpp"
#include "Util.hpp"

namespace thl {
class LexicalAnalyzer {
public:
  LexicalAnalyzer();
  ~LexicalAnalyzer();

  void setTokenTable(std::unique_ptr<TokenTable> lexemTable);
  void setConstTable(std::unique_ptr<ConstTable> constTable);
  void setIdentTable(std::unique_ptr<IdentTable> identTable);

  std::unique_ptr<TokenTable> getTokenTable();
  std::unique_ptr<ConstTable> getConstTable();
  std::unique_ptr<IdentTable> getIdentTable();

  void parse(std::istream &dataStream);

  inline void printResult();

private:
  std::pair<int, int> m_textPos;
  std::string m_ident;

  std::unique_ptr<TokenTable> m_tokenTable;
  std::unique_ptr<ConstTable> m_constTable;
  std::unique_ptr<IdentTable> m_identTable;

  void getTokens(std::istream &dataStream);

  void readIdent(std::istream &dataStream);
 
  inline void tokenPushBack(TokenType tokenType, int attr,
                            std::pair<int, int> textPos);

  inline std::string getTokenAttr(Token token);
};

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
