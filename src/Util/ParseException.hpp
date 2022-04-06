#ifndef SRC__PARSE_EXCEPTION__HPP
#define SRC__PARSE_EXCEPTION__HPP
#include <string>

class ParseException {
private:
  std::string m_error;

public:
  ParseException(std::string error) : m_error(error) {}

  std::string getError() const { return m_error; }
};

#endif // SRC__PARSE_EXCEPTION__HPP
