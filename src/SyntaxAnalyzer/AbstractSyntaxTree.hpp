#ifndef SRC__ABSTRACT_SYNTAX_TREE__HPP
#define SRC__ABSTRACT_SYNTAX_TREE__HPP

#include "Util.hpp"

namespace thl
{
	/// ExprAST - ������� ����� ��� ���� ����� ���������.
	class ExprAST
	{
	public:
		virtual ~ExprAST() = default;
	};

	/// NumberExprAST - ����� ���� ��������� ��� �������� ��������� (�������� {-1, 0, 1}).
	class NumberExprAST : public ExprAST
	{
	public:
		NumberExprAST(int val) : m_val(val)
		{}

	private:
		int m_val;

	};

	/// VariableExprAST - ����� ���� ��������� ��� ���������� (��������, "a").
	class VariableExprAST : public ExprAST
	{
	public:
		VariableExprAST(const std::string& name) : m_name(name)
		{}

	private:
		std::string m_name;

	};

	/// BinaryExprAST - ����� ���� ��������� ��� �������� ����������.
	class UnaryExprAST : public ExprAST
	{
	public:
		UnaryExprAST(Token op, std::unique_ptr<ExprAST> rhs)
			: m_op(op), m_rhs(std::move(rhs))
		{}

	private:
		Token m_op;
		std::unique_ptr<ExprAST> m_rhs;

	};

	/// UnaryExprAST - ����� ���� ��������� ��� �������� ����������.
	class BinaryExprAST : public ExprAST
	{
	public:
		BinaryExprAST(Token op, std::unique_ptr<ExprAST> lhs, std::unique_ptr<ExprAST> rhs)
			: m_op(op), m_lhs(std::move(lhs)), m_rhs(std::move(rhs))
		{}

	private:
		Token m_op;
		std::unique_ptr<ExprAST> m_lhs;
		std::unique_ptr<ExprAST> m_rhs;

	};

	/// PrototypeAST - ���� ����� ������������ "��������" ��� �������,
	/// ������� ������ � ��� � ����� ���������� (�, ����� �������, 
	/// ������ �������� ����� ����������).
	class PrototypeAST
	{
	public:
		PrototypeAST(const std::string& name, const std::vector<std::string>& args)
			: m_name(name), m_args(args)
		{}

	private:
		std::string m_name;
		std::vector<std::string> m_args;

	};

	/// FunctionAST - ������������ ����������� ����� �������
	class FunctionAST
	{
	public:
		FunctionAST(std::unique_ptr<PrototypeAST> prototype, std::unique_ptr<ExprAST> body)
			: m_prototype(std::move(prototype)), m_body(std::move(body))
		{}

	private:
		std::unique_ptr<PrototypeAST> m_prototype;
		std::unique_ptr<ExprAST> m_body;
	};

	/// CallExprAST - ����� ���� ��������� ��� ������ �������.
	class CallExprAST : public ExprAST
	{
	public:
		CallExprAST(const std::string& callee, std::vector<std::unique_ptr<ExprAST>>& args)
			: m_callee(callee), m_args(std::move(args))
		{}

	private:
		std::string m_callee;
		std::vector<std::unique_ptr<ExprAST>> m_args;

	};
}

#endif // SRC__ABSTRACT_SYNTAX_TREE__HPP
