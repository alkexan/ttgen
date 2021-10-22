#pragma once

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>

#include "AbstractSyntaxTree.hpp"


namespace thl
{
	using namespace llvm;

	class Visitor
	{
	public:
		virtual ~Visitor() = default;

		virtual Value* visit(NumberExprAST& ast) = 0;
		virtual Value* visit(VariableExprAST& ast) = 0;
		virtual Value* visit(UnaryExprAST& ast) = 0;
		virtual Value* visit(BinaryExprAST& ast) = 0;
		virtual Value* visit(PrototypeAST& ast) = 0;
		virtual Value* visit(FunctionAST& ast) = 0;
		virtual Value* visit(CallExprAST& ast) = 0;

	protected:
		std::unique_ptr<LLVMContext> TheContext;
		std::unique_ptr<Module> TheModule;
		std::unique_ptr<IRBuilder<>> Builder;
		std::map<std::string, Value*> NamedValues;
	};

	class CodeGenerator : public Visitor
	{
	public:
		Value* visit(NumberExprAST& ast) override
		{
			return ConstantInt::get(*TheContext, APInt(8, ast.getValue(), true));
		}

		Value* visit(VariableExprAST& ast) override
		{
			Value* V = NamedValues[ast.getName()];
			if (!V)
			{
				throw ParseException("Unknown variable name");
			}

			return V;
		}

		Value* visit(UnaryExprAST& ast) override
		{

		}

		Value* visit(BinaryExprAST& ast) override
		{

		}

		Value* visit(PrototypeAST& ast) override
		{

		}

		Value* visit(FunctionAST& ast) override
		{

		}

		Value* visit(CallExprAST& ast) override
		{

		}

	private:

	};

	class AssignOperator : public Visitor
	{
	public:

	private:

	};

	class ImplicationOperator : public Visitor
	{
	public:

	private:

	};

	class ImplicationbOperator : public Visitor
	{
	public:

	private:

	};

	class NotOperator : public Visitor
	{
	public:

	private:

	};

	class DecrementOperator : public Visitor
	{
	public:

	private:

	};

	class IncrementOperator : public Visitor
	{
	public:

	private:

	};

	class OrOperator : public Visitor
	{
	public:

	private:

	};

	class XorOperator : public Visitor
	{
	public:

	private:

	};

	class SubOperator : public Visitor
	{
	public:

	private:

	};

	class AddOperator : public Visitor
	{
	public:

	private:

	};

	class AndOperator : public Visitor
	{
	public:

	private:

	};

	class MulOperator : public Visitor
	{
	public:

	private:

	};

}
