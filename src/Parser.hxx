#pragma once
#include "Value.hxx"
#include <vector>
#include "Token.hxx"
//Trailing commas are tolerated but not standard
//Please consider not using them
namespace GDN {
	class Parser {
	public:

		//returns a json tree if successful
		//may throw a ParseError
		Value parse(const std::vector<Token> & tokens);
	private:
		Object object();
		Array array();
		Value value();

		//sonsumes a token if types match
		bool match(Token::Type type);

		//consumes one token
		void consume();

		void error(const std::string & msg);

		//returns current token and inrements consumes it
		Token advance();

		//returns current toke
		const Token & peek() const;

		//returns last consumed token
		const Token & prev() const;

		bool atEnd() const;

		std::vector<Token> tokens;
		std::size_t current;
	};
}

