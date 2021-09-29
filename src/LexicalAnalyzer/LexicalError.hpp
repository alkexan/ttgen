#ifndef SRC__LEXICAL_ERROR__HPP
#define SRC__LEXICAL_ERROR__HPP

#include <string>

namespace thl
{
	class LexicalError
	{
	public:
		LexicalError(int pos, std::string msg);
		~LexicalError();

		int getPos() const;
		std::string getMsg() const;

	private:
		int m_pos;
		std::string m_msg;
	};
}

#endif // SRC__LEXICAL_ERROR__HPP
