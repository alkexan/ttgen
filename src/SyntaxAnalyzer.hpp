#ifndef SRC__SYNTAX_ANALYZER__HPP
#define SRC__SYNTAX_ANALYZER__HPP

#include <iostream>
#include <memory>

#include "AbstractSyntaxTree.hpp"
#include "ParseException.hpp"
#include "Util.hpp"

namespace thl {

class SyntaxAnalyzer {
public:
  SyntaxAnalyzer();
  ~SyntaxAnalyzer();

  void setLexemeTable(std::unique_ptr<TokenTable> lexemTable);
  void setConstTable(std::unique_ptr<ConstTable> constTable);
  void setIdentTable(std::unique_ptr<IdentTable> identTable);

  std::unique_ptr<TokenTable> getLexemeTable();
  std::unique_ptr<ConstTable> getConstTable();
  std::unique_ptr<IdentTable> getIdentTable();

  std::vector<std::unique_ptr<FunctionAST>> getProgramAst();

  // <program> :: = <function> { '\n' < function > }
  void parse();

private:
  std::unique_ptr<TokenTable> m_lexemTable;
  std::unique_ptr<ConstTable> m_constTable;
  std::unique_ptr<IdentTable> m_identTable;

  std::vector<thl::Token>::iterator m_lexIterator;

  std::vector<std::unique_ptr<FunctionAST>> m_programAst;

  // <function> ::=  <prototype> ":=" <exp>
  std::unique_ptr<FunctionAST> parseFunction(Token lexeme);

  // <prototype> ::= <ident> "(" <ident> ["," <ident>]")"
  std::unique_ptr<PrototypeAST> parsePrototype(Token lexeme);

  // <exp> ::= <implexp> {<impl> <implexp>}
  std::unique_ptr<ExpressionAst> parseExpression(Token lexeme);

  // <implexp> ::= <term> {<sum> <term>}
  std::unique_ptr<ExpressionAst> parseImplExpression(Token lexeme);

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

  inline Token getLexeme(bool previous = 0) {
    Token result;

    if (previous) {
      if (m_lexIterator != m_lexemTable->begin()) {
        result = *(--m_lexIterator);
      } else {
        result = Token(TokenType::NEW_LINE, -1);
      }
    } else {
      if (m_lexIterator != m_lexemTable->end()) {
        result = *(m_lexIterator++);
      } else {
        result = Token(TokenType::ENDF, -1);
      }
    }

    return result;
  }
};

} // namespace thl

#endif // SRC__SYNTAX_ANALYZER__HPP
