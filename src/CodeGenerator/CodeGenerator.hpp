#pragma once

#include <llvm/IR/Value.h>

#include "AbstractSyntaxTree.hpp"
#include "ParseException.hpp"
#include "Util.hpp"

namespace thl
{
	using namespace llvm;

	class CodeGenerator : public Visitor
	{
	public:
		Value* visit(NumberExprAST& ast) override;

		Value* visit(VariableExprAST& ast) override;

		Value* visit(UnaryExprAST& ast) override;

		Value* visit(BinaryExprAST& ast) override;

		Value* visit(PrototypeAST& ast) override;

		Value* visit(FunctionAST& ast) override;

		Value* visit(CallExprAST& ast) override;

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
