#ifndef SRC__LEXICAL_ANALYZER__HPP
#define SRC__LEXICAL_ANALYZER__HPP

#include <memory>
#include <sstream>

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

  void parse(std::string &line);

private:
  size_t m_lineCount;

  std::unique_ptr<TokenTable> m_tokenTable;
  std::unique_ptr<ConstTable> m_constTable;
  std::unique_ptr<IdentTable> m_identTable;

  void getTokens(std::string &line);
};
} // namespace thl

#endif // SRC__LEXICAL_ANALYZER__HPP
