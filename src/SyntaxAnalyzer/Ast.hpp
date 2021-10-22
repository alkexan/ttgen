#pragma once

#include "Util.hpp"


namespace thl
{
    /**
     * @brief Класс для всех узлов выражений синтаксического дерева.
    */
    class Expression
    {
    public:
        Expression(const Lexeme& lexeme, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : m_operation(lexeme.getToken()), m_attribute(lexeme.getAttribute()), m_left(std::move(left)), m_right(std::move(right))
        {}

        inline Token getOperation() const
        {
            return m_operation;
        }

        inline int getAttribute() const
        {
            return m_attribute;
        }

    protected:
        Token m_operation;
        int m_attribute;

        std::unique_ptr<Expression> m_left;
        std::unique_ptr<Expression> m_right;
    };

}
