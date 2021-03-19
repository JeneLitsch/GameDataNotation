#pragma once
#include <string>
namespace GDN {
	class Token{
	public:
		enum class Type {
			STRING = 0x08, FLOAT = 0x01, INT = 0x02, NIL = 0x03, TRUE = 0x04, FALSE = 0x05, HEX = 0x06, BIN = 0x07,
			BRACE_L = 0x10, BRACE_R = 0x11,
			BRACKET_L = 0x12, BRACKET_R = 0x13,
			COLON = 0x20, COMMA = 0x21,

			___EOF___ = -1,
		};

		Token(Type type, const std::string & lexeme, std::size_t line);

		//retuns raw lexeme != getString()
		const std::string & getLexeme() const;

		Type getType() const;
		std::size_t getLine() const;

		//conversion methods
		//throw std::runtime_error if types don't matches
		std::string getString() const;
		double getFloat() const;
		long getInteger() const;
		long getBool() const;


	private:
		Type type;
		std::string lexeme;
		std::size_t line;
	};
}