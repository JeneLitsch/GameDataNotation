#include "Lexer.hxx"
#include "StringTools.hxx"
#include "LexError.hxx"
namespace GDN{

	char Lexer::advance(){
		this->current++;
		return previous();
	}

	char Lexer::peek() const {
		if(this->hasFinished()) return '\0';
		return this->str[this->current];
	}

	bool Lexer::match(char chr){
		if(!this->hasFinished() && this->peek() == chr){
			this->advance();
			return true;
		}
		else {
			return false;
		}
	}

	char Lexer::previous() const{
		return this->str[this->current -1];
	}

	bool Lexer::hasFinished() const{
		return this->current >= this->str.size();
	}

	void Lexer::addToken(const std::string & str, Token::Type type){
		this->tokens.push_back(Token(type, str, this->line));
	}

	std::string Lexer::getLexeme() const{
		return this->str.substr(this->start, this->current - this->start);
	}


	void Lexer::string(){
		while(this->advance() != '"'){
			//handles unterminated string
			//if current reaches the end without finding a matching "
			if(this->hasFinished()){
				this->error("Unterminated string");
			}
			//escape a single character
			if(previous() == '\\'){
				this->advance();
			}
		}
		this->addToken(this->getLexeme(), Token::Type::STRING);
	}


	bool Lexer::numDec(){

		bool flt = false;
		match('-');

		//match integer part
		if(match('0')){
			//catches leading 0
			if(matchNumeric()){
				this->error("Leading 0 not allowed in number: "  + this->getLexeme());
			}
		}
		else if(matchNumeric()){
			while(this->matchNumeric());
		}
		//match fraction
		if(match('.')){
			flt = true;
			while(this->matchNumeric());
		}

		//match exponent
		if(match('e') || match('E')){
			flt = true;
			//+ and - are mutual exclusive in the exponent
			if(!match('+')){
				match('-');
			}
			if(!this->matchNumeric()){
				this->error("Illformed exponent in floating point number: "  + this->getLexeme());
			}
			//TODO add error handling
			while(this->matchNumeric());
		}

		if(flt){
			this->addToken(this->getLexeme(), Token::Type::FLOAT);
		}
		else{
			this->addToken(this->getLexeme(), Token::Type::INT);
		}
		return true;
	}



	bool Lexer::numHex(){
		//check for the 0x prefix
		if(this->match('x')){
			//needs a least one digit to be valid
			if(this->matchHex()){
				while(this->matchHex());
			}
			else{
				this->error("No Hex digits found");
			}
			this->addToken(this->getLexeme(), Token::Type::HEX);
			return true;
		}
		return false;
	}

	bool Lexer::numBin(){
		//check for the 0b prefix
		if(this->match('b')){
			//needs a least one digit to be valid
			if(this->matchBin()){
				while(this->matchBin());
			}
			else{
				this->error("No Binary digits found");
			}
			this->addToken(this->getLexeme(), Token::Type::BIN);
			return true;
		}
		return false;
	}

	void Lexer::keyword(){
		while(this->matchAlpha());
		const std::string name = this->getLexeme();
		if(name == "null") this->addToken(name, Token::Type::NIL);
		else if(name == "true") this->addToken(name, Token::Type::TRUE);
		else if(name == "false") this->addToken(name, Token::Type::FALSE);
		else {
			this->error("Unknown keyword :" + name);
		}
	}


	bool Lexer::matchNumeric(){
		if(StringTools::isNumeric(this->peek())){
			this->advance();
			return true;
		}
		else {
			return false;
		}
	}

	bool Lexer::matchAlpha(){
		if(StringTools::isAlpha(this->peek())){
			this->advance();
			return true;
		}
		else {
			return false;
		}
	}

	bool Lexer::matchAlphaNumeric(){
		return this->matchAlpha() || this->matchNumeric();
	}

	bool Lexer::matchHex(){
		if(StringTools::isHex(this->peek())){
			this->advance();
			return true;
		}
		else {
			return false;
		}
	}

	bool Lexer::matchBin(){
		if(StringTools::isBin(this->peek())){
			this->advance();
			return true;
		}
		else {
			return false;
		}
	}



	void Lexer::error(const std::string msg){
		throw(LexError("Error in line " + std::to_string(this->line) + " : " + msg));
	}


	std::vector<Token> Lexer::lex(const std::string & json){
		this->start = 0;
		this->current = 0;
		this->line = 0;
		this->str = json;
		this->tokens.clear();

		while(!this->hasFinished()){
			char chr = this->advance();
			switch (chr){
			
			case '{':
				this->addToken("{", Token::Type::BRACE_L);
				break;
			
			case '}':
				this->addToken("}", Token::Type::BRACE_R);
				break;
			
			case '[':
				this->addToken("[", Token::Type::BRACKET_L); 
				break;
			
			case ']':
				this->addToken("]", Token::Type::BRACKET_R);
				break;

			case ':':
				this->addToken(":", Token::Type::COLON); 
				break;
			
			case ',':
				this->addToken(",", Token::Type::COMMA); 
				break;

			case '\n': 
				this->line++;
				break;
			
			case '\t':
			case '\r': 
			case ' ': 
				break;
				
			case '"' : this->string(); break;

			//hex, bin and 0.something decimal numbers 
			case '0':
				if (this->numBin());
				else if (this->numHex());
				else if (this->numDec());
				else this->error("Invalid Number");
				break;

			default:
				//non-zero-starting and negative decimal numbers 
				if(StringTools::isNumeric(chr) || chr == '-'){
					this->numDec();
				}

				//keyworld: true, false, null
				else if(StringTools::isAlpha(chr)){
					this->keyword();
				}
				
				else{
					this->error(std::string() + "Invalid Token \"" + chr + "\"");
				}
				break;
			}
			this->start = this->current;
		}

		this->addToken("___EOF___", Token::Type::___EOF___);
		return this->tokens;
	}

}