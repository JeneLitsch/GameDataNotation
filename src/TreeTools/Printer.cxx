#include "Printer.hxx"
#include <iostream>
#include "Object.hxx"
#include "Array.hxx"
#include "StringTools.hxx"
namespace GDN {

	Printer::Printer(bool pretty){
		this->pretty = pretty;
	}



	void Printer::visitValue(Value & val){
		

		//add int to str
		if(auto content = val.getInt()){
			if(content->format == Value::IntFormat::DEC) {
				this->add(std::to_string(content->val));
			}
			else if(content->format == Value::IntFormat::BIN) {
				this->add("0b" + StringTools::toBin(static_cast<std::uint64_t>(content->val)));
			}
			else if(content->format == Value::IntFormat::HEX) {
				this->add("0x" + StringTools::toHex(static_cast<std::uint64_t>(content->val)));
			}
		}

		//TODO handle inf und nan
		//add float without exponent to str
		else if(auto content = val.getFloat()){
			this->add(std::to_string(*content));
		}

		//add string with "" to str
		else if(auto content = val.getString()){
			this->add("\"" + *content + "\"");
		}

		//add boolean to str
		else if(auto content = val.getBool()){
			this->add(((*content)?"true":"false"));
		}

		//add object to str
		else if(auto content = val.getObject()){
			content->accept(*this);
		}

		//add array to str
		else if(auto content = val.getArray()){
			content->accept(*this);
		}

		// TODO add hex and bin

		//automatic conversion of unknown data to null
		else {
			this->add("null");
		}
	}



	void Printer::visitObject(Object & obj){
		this->add("{");
		this->depth++;
		bool firstLine = true;
		for(auto & el : obj){
			//comma for previous line
			this->comma(firstLine);

			//for pretty printing
			this->add(newline());
			this->add(this->indent());

			//key
			this->add("\"" + el.first + "\" : ");

			//process child object
			el.second.accept(*this);
		}
		this->add(newline());
		this->depth--;
		this->add(this->indent());
		this->add("}");
	}



	void Printer::visitArray(Array & arr){
		this->add("[");
		this->depth++;
		bool firstLine = true;
		for(auto & el : arr){
			//comma for previous line
			this->comma(firstLine);
			
			//for pretty printing
			this->add(newline());
			this->add(this->indent());

			//process child object
			el.accept(*this);
		}
		this->add(newline());
		this->depth--;
		this->add(this->indent());
		this->add("]");
	}



	//returns a couple tabs if pretty is acivated
	std::string Printer::indent(){
		if(pretty){
			return std::string(static_cast<unsigned long>(4*depth), ' ');
		}
		else {
			return "";
		}
	}


	// returns a new line if pretty printing is activated
	std::string Printer::newline(){
		if(pretty){
			return "\n";
		}
		else {
			return "";
		}
	}



	//add "," to previous line
	//its only done if the current line is not te first
	//to prevent trailing ","s
	void Printer::comma(bool & firstLine){
		if(firstLine){
			firstLine = false;
		}
		else{
			this->add(",");
		}
	}



	void Printer::clear(){
		this->str = "";
	}



	std::string Printer::get() const{
		return this->str;
	}



	void Printer::add(const std::string & str){
		this->str += str;
	}

}