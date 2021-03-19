#include "Parser.hxx"
#include "Object.hxx"
#include "Array.hxx"
#include "ParseError.hxx"
namespace GDN{
	Value Parser::parse(const std::vector<Token> & tokens){
		this->tokens = tokens;
		this->current = 0;
		return this->value();
	}

	Object Parser::object(){
		if(this->match(Token::Type::BRACE_L)){
			Object object;
			while(true){
				if(this->match(Token::Type::BRACE_R)){
					break;
				}
				else if(this->match(Token::Type::STRING)){
					std::string key;
					key = prev().getString();
					if(this->match(Token::Type::COLON)){
						Value value = this->value();
						object.set(key, value);


						//either a comma or a closing } must follow a value 
						if(this->match(Token::Type::COMMA));
						else if (this->match(Token::Type::BRACE_R)){
							break;
						}
						else {
							this->error("Expected , or } after object value");
						}
					}
					else this->error("Expexted :");
				}
				else this->error("Expected key in at: " + peek().getLexeme());
			}
			return object;
		}
		else this->error("Expected { object");
		return Object();
	}

	Array Parser::array(){
		if(this->match(Token::Type::BRACKET_L)){
			Array array;
			while(true){

				if(this->match(Token::Type::BRACKET_R)){
					break;
				}
				else {
					array.add(this->value());
					if(this->match(Token::Type::COMMA));
					else if (this->match(Token::Type::BRACKET_R)){
						break;
					}
					else {
						this->error("Expected , or ] after array value");
					}
				}
			}
			return array;
		}
		this->error("Expected [");
		return Array();
	}

	Value Parser::value(){
		Token token = peek();
		Token::Type type = token.getType();
		switch (type)
		{
		case Token::Type::NIL:
			this->advance();
			return Value();
			break;

		case Token::Type::STRING:
			this->advance();
			return Value(token.getString());
			break;

		case Token::Type::INT:
			this->advance();
			return Value(token.getInteger(), Value::IntFormat::DEC);
			break;
		

		case Token::Type::BIN:
			this->advance();
			return Value(token.getInteger(), Value::IntFormat::BIN);
			break;
		

		case Token::Type::HEX:
			this->advance();
			return Value(token.getInteger(), Value::IntFormat::HEX);
			break;
		

		case Token::Type::FLOAT:
			this->advance();
			return Value(token.getFloat());
			break;
		

		case Token::Type::TRUE:
			this->advance();
			return Value(true);
			break;
		

		case Token::Type::FALSE:
			this->advance();
			return Value(false);
			break;
		

		case Token::Type::BRACE_L:
			return Value(this->object());
			break;
		

		case  Token::Type::BRACKET_L:
			return Value(this->array());
			break;
		
		default:
			this->error("Unexpected value: " + token.getLexeme());
			return Value();
			break;
		}

		




	}

	bool Parser::match(Token::Type type){
		if(this->peek().getType() == type){
			this->current++;
			return true;
		}
		else{
			return false;
		}
	}


	Token Parser::advance(){
		if(!this->atEnd()) current++;
		return this->prev();
	}


	const Token &  Parser::peek() const{
		return this->tokens[this->current];
	}
	
	const Token &  Parser::prev() const{
		return this->tokens[this->current - 1];
	}

	bool Parser::atEnd() const{
		return this->peek().getType() == Token::Type::___EOF___;
	}

	void Parser::error(const std::string & msg){
		throw ParseError("In line " + std::to_string(this->peek().getLine()) + " : " + msg);

	}

}

