#include <iostream>
#include "CodeGenerator.hpp"

using namespace thl;

Value* CodeGenerator::visit(NumberExprAST& ast)
{
	//return ConstantInt::get(*m_theContext, APInt(8, ast.getValue(), true));

	std::cout << ast.getValue();
	return nullptr;
}

Value* CodeGenerator::visit(VariableExprAST& ast)
{
	//Value* V = m_namedValues[ast.getName()];
	//if (!V)
	//{
	//	throw ParseException("Unknown variable name");
	//}

	//return V;

	std::cout << ast.getName();
	return nullptr;
}

Value* CodeGenerator::visit(UnaryExprAST& ast)
{
	//Value* result = nullptr;
	//Function* callee = nullptr;

	//switch (ast.getOperator())
	//{
	//	case Token::NOT:
	//	{
	//		Function* callee = m_theModule->getFunction("operator~");
	//		break;
	//	}
	//	case Token::DECREMENT:
	//	{
	//		Function* callee = m_theModule->getFunction("operator--");
	//		break;
	//	}
	//	case Token::INCREMENT:
	//	{
	//		Function* callee = m_theModule->getFunction("operator++");
	//		break;
	//	}
	//	default:
	//	{
	//		throw ParseException("Invalid unary operator");
	//		break;
	//	}
	//}

	//if (!callee)
	//{
	//	throw ParseException("Unknown function referenced");
	//}
	//else if (callee->arg_size() != 1)
	//{
	//	throw ParseException("Incorrect # arguments passed");
	//}
	//else
	//{
	//	Value* arg = ast.getRhs()->accept(*this);

	//	result = m_builder->CreateCall(callee, arg, "calltmp");
	//}

	//return result;

	switch (ast.getOperator())
	{
		case Token::NOT:
		{
			std::cout << "~";
			break;
		}
		case Token::DECREMENT:
		{
			std::cout << "--";
			break;
		}
		case Token::INCREMENT:
		{
			std::cout << "++";
			break;
		}
		default:
		{
			throw ParseException("Invalid unary operator");
			break;
		}
	}
	ast.getRhs()->accept(*this);
	
	return nullptr;
}

Value* CodeGenerator::visit(BinaryExprAST& ast)
{
	ast.getLhs()->accept(*this);

	switch (ast.getOperator())
	{
		case Token::ASSIGMENT:
		{
			std::cout << ":=";
			break;
		}
		case Token::IMPLICATION:
		{
			std::cout << "->";
			break;
		}
		case Token::IMPLICATIONB:
		{
			std::cout << "+>";
			break;
		}
		case Token::OR:
		{
			std::cout << "|";
			break;
		}
		case Token::XOR:
		{
			std::cout << "#";
			break;
		}
		case Token::SUB:
		{
			std::cout << "-";
			break;
		}
		case Token::ADD:
		{
			std::cout << "+";
			break;
		}
		case Token::AND:
		{
			std::cout << "&";
			break;
		}
		case Token::MUL:
		{
			std::cout << "*";
			break;
		}
		default:
		{
			throw ParseException("Invalid binary operator");
			break;
		}
	}
	ast.getRhs()->accept(*this);

	return nullptr;
}

Value* CodeGenerator::visit(PrototypeAST& ast)
{
	std::cout << ast.getName() << "(";
	auto args = ast.getArgs();
	for (int i = 0; i < args.size(); i++)
	{
		std::cout << args[i];
		if (i == args.size() - 1)
		{
			std::cout << ")";
		}
		else
		{
			std::cout << ", ";
		}
	}
	return nullptr;
}

Value* CodeGenerator::visit(FunctionAST& ast)
{
	ast.getPrototype()->accept(*this);
	std::cout << ":=";
	ast.getBody()->accept(*this);

	return nullptr;
}

Value* CodeGenerator::visit(CallExprAST& ast)
{
	std::cout << ast.getName() << "(";

	auto args = ast.getArgs();
	for (int i = 0; i < args.size(); i++)
	{
		args[i]->accept(*this);
		if (i == args.size() - 1)
		{
			std::cout << ")";
		}
		else
		{
			std::cout << ", ";
		}
	}
	return nullptr;
}