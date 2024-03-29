#ifndef SRC__SYNTAX_ANALYZER__HPP
#define SRC__SYNTAX_ANALYZER__HPP

#include <functional>
#include <iostream>
#include <memory>
#include <utility>

#include "AbstractSyntaxTree.hpp"
#include "ParseException.hpp"
#include "Token.hpp"

namespace thl {

/**
 * @brief Syntax Analyzer class
 * 
 */
class SyntaxAnalyzer {
public:
  SyntaxAnalyzer();
  ~SyntaxAnalyzer();

  void setTokenTable(std::shared_ptr<TokenTable> lexemTable);
  void setConstTable(std::shared_ptr<ConstTable> constTable);
  void setIdentTable(std::shared_ptr<IdentTable> identTable);

  std::vector<std::unique_ptr<FunctionAST>> getProgramAst();

  // <program> :: = <function> { '\n' < function > }
  void parse();

private:
  std::shared_ptr<TokenTable> m_tokenTable;
  std::shared_ptr<ConstTable> m_constTable;
  std::shared_ptr<IdentTable> m_identTable;

  std::vector<std::string> m_prototypeArgs;

  std::vector<thl::Token>::iterator m_lexIterator;

  std::vector<std::unique_ptr<FunctionAST>> m_programAst;

  // typedef std::unique_ptr<ExpressionAst> (SyntaxAnalyzer::*parse_cb)(Token lexeme);

  // <function> ::=  <prototype> ":=" <exp>
  std::unique_ptr<FunctionAST> parseFunction(Token lexeme);

  // <prototype> ::= <ident> "(" <ident> ["," <ident>]")"
  std::unique_ptr<PrototypeAST> parsePrototype(Token lexeme);

  // <exp> ::= <implexp> {<impl> <implexp>}
  std::unique_ptr<ExpressionAst> parseStatement(Token lexeme);

  // <implexp> ::= <term> {<sum> <term>}
  std::unique_ptr<ExpressionAst> parseExpression(Token lexeme);

  // <term> ::= <factor> {<mul> <factor>}
  std::unique_ptr<ExpressionAst> parseTerm(Token lexeme);

  // <factor> ::= <unary> |
  //              <paren> |
  //              <name> |
  //              <number>
  std::unique_ptr<ExpressionAst> parseFactor(Token lexeme);

  // <unary> ::= "~" <factor> |
  //             "++" < factor > |
  //             "--" < factor >
  std::unique_ptr<ExpressionAst> parseUnary(Token lexeme);

  // parenexpr ::= '(' expression ')'
  std::unique_ptr<ExpressionAst> parseParenExpr(Token lexeme);

  // <name> ::= <ident> "(" <ident> {"," <ident>} ")" |
  //            <ident>
  // <ident> ::= "[a-z][_a-zA-Z0-9]*"
  std::unique_ptr<ExpressionAst> parseName(Token lexeme);

  // <number> ::= "$" | "1" | "0"
  std::unique_ptr<ExpressionAst> parseNumber(Token lexeme);

  inline Token readToken(bool previous = 0);
};

inline Token SyntaxAnalyzer::readToken(bool previous) {
  using namespace std;
  Token result;

  if (previous) {
    if (m_lexIterator != m_tokenTable->begin()) {
      result = *(--m_lexIterator);
    } else {
      result.setAttributes(TokenType::ENDL, -1, make_pair(0, 0));
    }
  } else {
    if (m_lexIterator != m_tokenTable->end()) {
      result = *(m_lexIterator++);
    } else {
      result.setAttributes(TokenType::ENDF, -1, make_pair(0, 0));
    }
  }

  return result;
}

} // namespace thl

#endif // SRC__SYNTAX_ANALYZER__HPP
