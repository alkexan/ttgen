#include "LexicalError.hpp"

thl::LexicalError::LexicalError(int pos, std::string msg) :
	m_pos (pos),
	m_msg (msg)
{}

thl::LexicalError::~LexicalError()
{}

int thl::LexicalError::getPos() const
{
	return m_pos;
}

std::string thl::LexicalError::getMsg() const
{
	return m_msg;
}
