#include "SyntaxAnalyzer.hpp"

using namespace thl;

SyntaxAnalyzer::SyntaxAnalyzer()
{}

SyntaxAnalyzer::~SyntaxAnalyzer()
{}

void thl::SyntaxAnalyzer::setLexemeTable(std::unique_ptr<LexemeTable> lexemTable)
{
	m_lexemTable = std::move(lexemTable);
}

void thl::SyntaxAnalyzer::setConstTable(std::unique_ptr<ConstTable> constTable)
{
	m_constTable = std::move(constTable);
}

void thl::SyntaxAnalyzer::setIdentTable(std::unique_ptr<IdentTable> identTable)
{
	m_identTable = std::move(identTable);
}

std::vector<std::unique_ptr<FunctionAST>> thl::SyntaxAnalyzer::getProgramAst()
{
	return std::move(m_programAst);
}

void thl::SyntaxAnalyzer::parse()
{
	m_programAst.clear();
	Lexeme lexeme = getLexeme();

	while (lexeme.token() != Token::ENDF)
	{
		if (lexeme.token() == Token::NEW_LINE)
		{
			// empty body
		}
		else
		{
			auto function = std::move(parseFunction(lexeme));
			if (function)
			{
				m_programAst.push_back(std::move(function));
			}
			else
			{
				// Пропускаем токен для восстановления после ошибки.
				lexeme = getLexeme();
			}
		}

		lexeme = getLexeme();
	}
}

std::unique_ptr<FunctionAST> thl::SyntaxAnalyzer::parseFunction(Lexeme lexeme)
{
	std::unique_ptr<FunctionAST> result = nullptr;

	// create Function Prototype Ast
	auto prototype = std::move(parsePrototype(lexeme));
	if (prototype)
	{
		// create Expression Ast
		lexeme = getLexeme();
		if (lexeme.token() == Token::ASSIGMENT)
		{
			lexeme = getLexeme();
			auto exp = std::move(parseExpression(lexeme));
			if (exp)
			{
				// create Function Ast
				result = std::make_unique<FunctionAST>(std::move(prototype), std::move(exp));
			}
		}
		else
		{
			errorFunction("Exepted exeption");
		}
	}
	return std::move(result);
}

std::unique_ptr<PrototypeAST> thl::SyntaxAnalyzer::parsePrototype(Lexeme lexeme)
{
	std::unique_ptr<PrototypeAST> result = nullptr;

	if (lexeme.token() != Token::IDENTIFIER)
	{
		errorPrototype("Expected function name in prototype");
	}
	else
	{
		std::string functionName = (*m_identTable)[lexeme.attr()];

		lexeme = getLexeme();
		if (lexeme.token() == Token::OPEN_BRACKET)
		{
			std::vector<std::string> args;

			do
			{
				lexeme = getLexeme();

				if (lexeme.token() == Token::CLOSE_BRACKET)
				{
					break;
				}
				else if (lexeme.token() == Token::IDENTIFIER)
				{
					args.push_back((*m_identTable)[lexeme.attr()]);
					lexeme = getLexeme();
				}

				if (lexeme.token() != Token::DELIMITER && lexeme.token() != Token::CLOSE_BRACKET)
				{
					errorPrototype("Expected ')' or ',' in argument list");
					break;
				}
			} while (lexeme.token() == Token::DELIMITER);

			if (lexeme.token() == Token::CLOSE_BRACKET)
			{
				// success.
				result = std::make_unique<PrototypeAST>(functionName, args);
			}
		}
		else
		{
			errorPrototype("Expected '(' in prototype");
		}
	}

	return std::move(result);
}

std::unique_ptr<ExprAST> thl::SyntaxAnalyzer::parseExpression(Lexeme lexeme)
{
	std::unique_ptr<ExprAST> result = nullptr;

	auto lhs = std::move(parseImplExpression(lexeme));
	if (lhs)
	{
		lexeme = getLexeme();
		Token token = lexeme.token();
		if ((token == Token::IMPLICATION) || (token == Token::IMPLICATIONB))
		{
			lexeme = getLexeme();
			auto rhs = std::move(parseImplExpression(lexeme));
			if (rhs)
			{
				result = std::make_unique<BinaryExprAST>(token, std::move(lhs), std::move(rhs));
			}
		}
		else if (lexeme.token() != Token::ENDF)
		{
			result = std::move(lhs);
			lexeme = getLexeme(1);
		}
		else
		{
			result = std::move(lhs);
		}
	}

	return std::move(result);
}

std::unique_ptr<ExprAST> thl::SyntaxAnalyzer::parseImplExpression(Lexeme lexeme)
{
	std::unique_ptr<ExprAST> result = nullptr;

	auto lhs = std::move(parseTerm(lexeme));
	if (lhs)
	{
		lexeme = getLexeme();
		Token token = lexeme.token();
		if ((token == Token::ADD) || (token == Token::SUB) || (token == Token::OR) || (token == Token::XOR))
		{
			lexeme = getLexeme();
			auto rhs = std::move(parseTerm(lexeme));
			if (rhs)
			{
				result = std::make_unique<BinaryExprAST>(token, std::move(lhs), std::move(rhs));
			}
		}
		else if (lexeme.token() != Token::ENDF)
		{
			result = std::move(lhs);
			lexeme = getLexeme(1);
		}
		else
		{
			result = std::move(lhs);
		}
	}

	return std::move(result);
}

std::unique_ptr<ExprAST> thl::SyntaxAnalyzer::parseTerm(Lexeme lexeme)
{
	std::unique_ptr<ExprAST> result = nullptr;

	auto lhs = std::move(parseFactor(lexeme));
	if (lhs)
	{
		lexeme = getLexeme();
		Token token = lexeme.token();
		if ((token == Token::MUL) || (token == Token::AND))
		{
			lexeme = getLexeme();
			auto rhs = std::move(parseFactor(lexeme));
			if (rhs)
			{
				result = std::make_unique<BinaryExprAST>(token, std::move(lhs), std::move(rhs));
			}
		}
		else if (lexeme.token() != Token::ENDF)
		{
			result = std::move(lhs);
			lexeme = getLexeme(1);
		}
		else
		{
			result = std::move(lhs);
		}
	}

	return std::move(result);
}

std::unique_ptr<ExprAST> thl::SyntaxAnalyzer::parseFactor(Lexeme lexeme)
{
	std::unique_ptr<ExprAST> result = nullptr;

	switch (lexeme.token())
	{
		case Token::IDENTIFIER:
		{
			result = std::move(parseName(lexeme));
			break;
		}
		case Token::NUMBER:
		{
			result = std::move(parseNumber(lexeme));
			break;
		}
		case Token::OPEN_BRACKET:
		{
			result = std::move(parseParenExpr(lexeme));
			break;
		}
		default:
		{
			result = std::move(parseUnary(lexeme));
			break;
		}
	}
	return std::move(result);
}

std::unique_ptr<ExprAST> thl::SyntaxAnalyzer::parseUnary(Lexeme lexeme)
{
	std::unique_ptr<ExprAST> result = nullptr;

	switch (lexeme.token())
	{
		case Token::INCREMENT: // No Body
		case Token::DECREMENT: // No Body
		case Token::NOT:
		{
			Token unary = lexeme.token();
			lexeme = getLexeme();
			auto rhs = std::move(parseFactor(lexeme));

			result = std::make_unique<UnaryExprAST>(unary, std::move(rhs));
			break;
		}
		default:
		{
			error("unknown token when expecting an expression");
			break;
		}
	}

	return std::move(result);
}

std::unique_ptr<ExprAST> thl::SyntaxAnalyzer::parseParenExpr(Lexeme lexeme)
{
	std::unique_ptr<ExprAST> result = nullptr;

	lexeme = getLexeme();
	auto expression = std::move(parseExpression(lexeme));
	if (expression)
	{
		lexeme = getLexeme();
		if (lexeme.token() == Token::CLOSE_BRACKET)
		{
			result = std::move(expression);
		}
		else
		{
			error("expected ')'");
		}
	}

	return std::move(result);
}

std::unique_ptr<ExprAST> thl::SyntaxAnalyzer::parseName(Lexeme lexeme)
{
	std::unique_ptr<ExprAST> result = nullptr;

	std::string idName = (*m_identTable)[lexeme.attr()];

	lexeme = getLexeme();
	if (lexeme.token() == Token::OPEN_BRACKET)
	{
		// Callable
		std::vector<std::unique_ptr<ExprAST>> args;

		do
		{
			lexeme = getLexeme();

			if (lexeme.token() == Token::CLOSE_BRACKET)
			{
				break;
			}
			else if (lexeme.token() == Token::IDENTIFIER)
			{
				auto arg = std::move(parseExpression(lexeme));
				if (arg)
				{
					args.push_back(std::move(arg));
					lexeme = getLexeme();
				}
			}

			if (lexeme.token() != Token::DELIMITER && lexeme.token() != Token::CLOSE_BRACKET)
			{
				error("Expected ')' or ',' in argument list");
				break;
			}

		} while (lexeme.token() == Token::DELIMITER);


		if (lexeme.token() == Token::CLOSE_BRACKET)
		{
			// success.
			result = std::make_unique<CallExprAST>(idName, std::move(args));
		}
	}
	else
	{
		// Variable
		result = std::make_unique<VariableExprAST>(idName);
		lexeme = getLexeme(1);
	}

	return std::move(result);
}

std::unique_ptr<ExprAST> thl::SyntaxAnalyzer::parseNumber(Lexeme lexeme)
{
	auto result = std::make_unique<NumberExprAST>((*m_constTable)[lexeme.attr()]);
	std::cout << (*m_constTable)[lexeme.attr()];
	return std::move(result);
}
