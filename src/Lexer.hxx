#pragma once
#include <vector>
#include "Token.hxx"

namespace GDN{
	class Lexer {
	public:
		std::vector<Token> lex(const std::string & json);
	private:
		//throws a LexError
		void error(const std::string msg);

		//keeps advancing until a second " is found
		void string();
		
		//keeps advancing until a decimal number (float and int) is complete
		bool numDec();
		
		//needs a 0x (lex() takes about for the 0) prefix
		//keeps advancing until a non-hex character is found 
		bool numHex();
		
		//needs a 0b (lex() takes about for the 0) prefix
		//keeps advancing until a non-hex character is found
		bool numBin();

		//advances until a non-alpha character is found
		void keyword();

		//advances if a xyz character ist found
		//numeric (0-9)
		bool matchNumeric();
		//hex (0-f)
		bool matchHex();
		//bin (0-1)
		bool matchBin();
		//alpha (a...z,A...z);
		bool matchAlpha();
		//alpha or numeric 
		bool matchAlphaNumeric();
		
		//consumes one character
		char advance();

		//returns the current character
		char peek() const;

		//consumes the current character if it matches with "char chr"
		bool match(char chr);

		//return true if current reached the end of the string
		bool hasFinished() const;

		//returns the previuous character
		char previous() const;

		//add a new token
		void addToken(const std::string & str, Token::Type type);

		//creates a substring between start and current
		std::string getLexeme() const;

		std::string str;
		std::size_t start;
		std::size_t current;
		std::size_t line;
		std::vector<Token> tokens;
	};
}