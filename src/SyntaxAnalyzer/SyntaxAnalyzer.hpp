#ifndef SRC__SYNTAX_ANALYZER__HPP
#define SRC__SYNTAX_ANALYZER__HPP

#include "Util.hpp"
#include "AbstractSyntaxTree.hpp"

namespace thl
{

    class SyntaxAnalyzer
    {
    public:
        SyntaxAnalyzer();
        ~SyntaxAnalyzer();

        /// Error* - Это небольшие вспомогательные функции для обработки ошибок.
        ExprAST* Error(const char* Str)
        {
            fprintf(stderr, "Error: %s\n", Str); return 0;
        }
        PrototypeAST* ErrorP(const char* Str)
        {
            Error(Str); return 0;
        }
        FunctionAST* ErrorF(const char* Str)
        {
            Error(Str); return 0;
        }

        int GetTokPrecedence();

        Token getNextToken();
        
        ExprAST* ParseNumberExpr();
        ExprAST* ParseParenExpr();
        ExprAST* ParseIdentifierExpr();
        ExprAST* ParsePrimary();
        ExprAST* ParseExpression();
        ExprAST* ParseBinOpRHS(int ExprPrec, ExprAST* LHS);

        PrototypeAST* ParsePrototype();

        FunctionAST* ParseDefinition();

        PrototypeAST* ParseExtern();

        FunctionAST* ParseTopLevelExpr();


    private:
        Token m_currentToken;

    };

}

#endif // SRC__SYNTAX_ANALYZER__HPP
