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

  std::unique_ptr<LexemeTable> getLexemeTable();
  std::unique_ptr<ConstTable> getConstTable();
  std::unique_ptr<IdentTable> getIdentTable();

  void parse(std::string &line);

private:
  size_t m_lineCount;

  std::unique_ptr<LexemeTable> m_lexemTable;
  std::unique_ptr<ConstTable> m_constTable;
  std::unique_ptr<IdentTable> m_identTable;

  void parseLine(std::istringstream &istream);
};
} // namespace thl

#endif // SRC__LEXICAL_ANALYZER__HPP
