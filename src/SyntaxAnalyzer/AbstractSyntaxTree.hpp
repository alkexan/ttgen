#ifndef SRC__ABSTRACT_SYNTAX_TREE__HPP
#define SRC__ABSTRACT_SYNTAX_TREE__HPP

#include "Util.hpp"

namespace thl
{
	/// ExprAST - ������� ����� ��� ���� ����� ���������.
	class ExprAST
	{
	public:
		virtual ~ExprAST()
		{}
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
	class BinaryExprAST : public ExprAST
	{
	public:
		BinaryExprAST(Token op, ExprAST* rhs)
			: m_op(op), m_rhs(rhs)
		{}

	private:
		Token m_op;
		ExprAST* m_rhs;

	};

	/// UnaryExprAST - ����� ���� ��������� ��� �������� ����������.
	class UnaryExprAST : public ExprAST
	{
	public:
		UnaryExprAST(Token op, ExprAST* lhs, ExprAST* rhs)
			: m_op(op), m_lhs(lhs), m_rhs(rhs)
		{}

	private:
		Token m_op;
		ExprAST* m_lhs;
		ExprAST* m_rhs;

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
		FunctionAST(PrototypeAST* proto, ExprAST* body)
			: m_proto(proto), m_body(body)
		{}

	private:
		PrototypeAST* m_proto;
		ExprAST* m_body;
	};

	/// CallExprAST - ����� ���� ��������� ��� ������ �������.
	class CallExprAST : public ExprAST
	{
	public:
		CallExprAST(const std::string& callee, std::vector<ExprAST*>& args)
			: m_callee(callee), m_args(args)
		{}

	private:
		std::string m_callee;
		std::vector<ExprAST*> m_args;

	};
}

#endif // SRC__ABSTRACT_SYNTAX_TREE__HPP
