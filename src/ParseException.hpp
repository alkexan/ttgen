#ifndef SRC__PARSE_EXCEPTION__HPP
#define SRC__PARSE_EXCEPTION__HPP
#include <string>

namespace thl {
/**
 * @brief Parse Exception class
 * 
 */
class ParseException {
public:
  ParseException(std::string error) : m_error(error) {}

  std::string getError() const { return m_error; }

private:
  std::string m_error;
};
}

#endif // SRC__PARSE_EXCEPTION__HPP
