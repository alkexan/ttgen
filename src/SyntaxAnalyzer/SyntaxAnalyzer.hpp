#ifndef SRC__SYNTAX_ANALYZER__HPP
#define SRC__SYNTAX_ANALYZER__HPP

#include <iostream>
#include <memory>

#include "Util.hpp"
#include "AbstractSyntaxTree.hpp"

namespace thl
{

    class SyntaxAnalyzer
    {
    public:
        SyntaxAnalyzer();
        ~SyntaxAnalyzer();

        void setLexemeTable(std::unique_ptr < LexemeTable > lexemTable);
        void setConstTable(std::unique_ptr < ConstTable > constTable);
        void setIdentTable(std::unique_ptr < IdentTable > identTable);

        // <program> :: = <function> { '\n' < function > }
        void parse();

    private:
        //Lexeme m_currentLexeme;

        std::unique_ptr < LexemeTable > m_lexemTable;
        std::unique_ptr < ConstTable > m_constTable;
        std::unique_ptr < IdentTable > m_identTable;

        // <function> ::=  <prototype> ":=" <exp>
        std::unique_ptr<FunctionAST> parseFunction(Lexeme lexeme);

        // <prototype> ::= <ident> "(" <ident> ["," <ident>]")"
        std::unique_ptr<PrototypeAST> parsePrototype(Lexeme lexeme);

        // <exp> ::= <implexp> {<impl> <implexp>}
        std::unique_ptr<ExprAST> parseExpression(Lexeme lexeme);

        // <implexp> ::= <term> {<sum> <term>}
        std::unique_ptr<ExprAST> parseImplExpression(Lexeme lexeme);

        // <term> ::= <factor> {<mul> <factor>}
        std::unique_ptr<ExprAST> parseTerm(Lexeme lexeme);

        // <factor> ::= <unary> |
        //              <paren> | 
        //              <name> |
        //              <number>
        std::unique_ptr<ExprAST> parseFactor(Lexeme lexeme);

        // <unary> ::= "~" <factor> | 
        //             "++" < factor > |
        //             "--" < factor >
        std::unique_ptr<ExprAST> parseUnary(Lexeme lexeme);

        // parenexpr ::= '(' expression ')'
        std::unique_ptr<ExprAST> parseParenExpr(Lexeme lexeme);

        // <name> ::= <ident> "(" <ident> {"," <ident>} ")" |
        //            <ident>
        // <ident> ::= "[a-z][_a-zA-Z0-9]*"
        std::unique_ptr<ExprAST> parseName(Lexeme lexeme);

        // <number> ::= "$" | "1" | "0"
        std::unique_ptr<ExprAST> parseNumber(Lexeme lexeme);


        inline Lexeme getLexeme(bool previous = 0)
        {
            static auto lexemIt = m_lexemTable->begin();
            static int couner = 0;
            Lexeme result;

            if (previous)
            {
                if (lexemIt != m_lexemTable->begin())
                {
                    result = *(--lexemIt);
                    couner --;
                }
                else
                {
                    result = Lexeme(Token::NEW_LINE, -1);
                }
            }
            else
            {
                if (lexemIt != m_lexemTable->end())
                {
                    result = *(lexemIt++);
                    couner++;
                }
                else
                {
                    result = Lexeme(Token::ENDF, -1);
                }
            }

            return result;
        }

        inline std::unique_ptr<ExprAST> error(const char* str)
        {
            std::cerr << "Error:" << str << std::endl; 
            return nullptr;
        }
        inline std::unique_ptr<PrototypeAST> errorPrototype(const char* Str)
        {
            error(Str); 
            return nullptr;
        }
        inline std::unique_ptr<FunctionAST> errorFunction(const char* Str)
        {
            error(Str); 
            return nullptr;
        }
    };

}

#endif // SRC__SYNTAX_ANALYZER__HPP
