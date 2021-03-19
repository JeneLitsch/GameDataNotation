#include "Token.hxx"
#include <stdexcept>
#include "StringTools.hxx"
namespace GDN{

	Token::Token(Type type, const std::string & lexeme, std::size_t line){
		this->lexeme = lexeme;
		this->type = type;
		this->line = line;
	}

	Token::Type Token::getType() const{
		return this->type;
	}

	std::string Token::getString() const{
		if(type != Type::STRING){
			throw std::runtime_error("Not a string type: " + this->lexeme);
		}
		return StringTools::strip(this->lexeme);
	}

	const std::string & Token::getLexeme() const{
		return this->lexeme;
	}


	double Token::getFloat() const{
		if(type != Type::FLOAT && type != Type::INT){
			throw std::runtime_error("Not a float type: " + this->lexeme);
		}
		return std::stod(this->lexeme);
	}

	long Token::getInteger() const{
		if(type == Type::INT){
			return std::stol(this->lexeme);
		}
		if(type == Type::HEX){
			return StringTools::fromHex(this->lexeme.substr(2));
		}
		if(type == Type::BIN){
			return StringTools::fromBin(this->lexeme.substr(2));
		}
		else{
			throw std::runtime_error("Not a integer type: " + this->lexeme);
		}
	}

	long Token::getBool() const{
		if(type == Type::TRUE) {
			return true;
		}
		else if (type == Type::FALSE) {
			return false;
		}
		else {
			throw std::runtime_error("Not a bool type: " + this->lexeme);
		}
	}

	std::size_t Token::getLine() const{
		return this->line;
	}


}