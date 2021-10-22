#ifndef SRC__ABSTRACT_SYNTAX_TREE__HPP
#define SRC__ABSTRACT_SYNTAX_TREE__HPP

#include "Util.hpp"
#include "Visitor.hpp"

namespace thl
{
	/**
	 * @brief Базовый класс для всех узлов выражений.
	*/
	class ExpressionAst
	{
	public:
		virtual ~ExpressionAst() = default;
		virtual void accept(Visitor& visitor) = 0;
	};

	/**
	 * @brief Класс узла выражения числовых литералов (Например {-1, 0, 1}).
	*/
	class NumberExprAST : public ExpressionAst
	{
	public:
		NumberExprAST(int val) : m_val(val)
		{}

		void accept(Visitor& visitor) override
		{
			visitor.visit(*this);
		}

		inline int getValue() const
		{
			return m_val;
		}

	private:
		int m_val;

	};

	/**
	 * @brief Класс узла выражения переменных.
	*/
	class VariableExprAST : public ExpressionAst
	{
	public:
		VariableExprAST(const std::string& name) : m_name(name)
		{}

		void accept(Visitor & visitor) override
		{
			visitor.visit(*this);
		}

		inline std::string getName() const
		{
			return m_name;
		}

	private:
		std::string m_name;

	};

	/**
	 * @brief Класс узла выражения унарных операторов.
	*/
	class UnaryExprAST : public ExpressionAst
	{
	public:
		UnaryExprAST(Token op, std::unique_ptr<ExpressionAst> rhs)
			: m_op(op), m_rhs(std::move(rhs))
		{}

		void accept(Visitor & visitor) override
		{
			visitor.visit(*this);
		}

	private:
		Token m_op;
		std::unique_ptr<ExpressionAst> m_rhs;

	};

	/**
	 * @brief Класс узла выражения бинарных операторов.
	*/
	class BinaryExprAST : public ExpressionAst
	{
	public:
		BinaryExprAST(Token op, std::unique_ptr<ExpressionAst> lhs, std::unique_ptr<ExpressionAst> rhs)
			: m_op(op), m_lhs(std::move(lhs)), m_rhs(std::move(rhs))
		{}

		void accept(Visitor & visitor) override
		{
			visitor.visit(*this);
		}

	private:
		Token m_op;
		std::unique_ptr<ExpressionAst> m_lhs;
		std::unique_ptr<ExpressionAst> m_rhs;

	};

	/**
	 * @brief Класс "прототипа" функции, который хранит её имя и 
	 * имена аргументов.
	*/
	class PrototypeAST : public ExpressionAst
	{
	public:
		PrototypeAST(const std::string& name, const std::vector<std::string>& args)
			: m_name(name), m_args(args)
		{}

		void accept(Visitor & visitor) override
		{
			visitor.visit(*this);
		}

	private:
		std::string m_name;
		std::vector<std::string> m_args;

	};

	/**
	 * @brief Класс определения самой функции
	*/
	class FunctionAST : public ExpressionAst
	{
	public:
		FunctionAST(std::unique_ptr<PrototypeAST> prototype, std::unique_ptr<ExpressionAst> body)
			: m_prototype(std::move(prototype)), m_body(std::move(body))
		{}

		void accept(Visitor & visitor) override
		{
			visitor.visit(*this);
		}

	private:
		std::unique_ptr<PrototypeAST> m_prototype;
		std::unique_ptr<ExpressionAst> m_body;
	};

	/**
	 * @brief Класс узла выражения вызова функции.
	*/
	class CallExprAST : public ExpressionAst
	{
	public:
		CallExprAST(const std::string& callee, std::vector<std::unique_ptr<ExpressionAst>>& args)
			: m_callee(callee), m_args(std::move(args))
		{}

		void accept(Visitor & visitor) override
		{
			visitor.visit(*this);
		}

	private:
		std::string m_callee;
		std::vector<std::unique_ptr<ExpressionAst>> m_args;

	};
}

#endif // SRC__ABSTRACT_SYNTAX_TREE__HPP
