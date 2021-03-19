#include "Value.hxx"
#include "Array.hxx"
#include "Object.hxx"
namespace GDN {
	
	void Value::accept(Visitor & visitor) {
		visitor.visitValue(*this);
	}

	// constructors

	Value::Value(Object val){
		this->value = std::make_shared<Object>(val);
	}

	Value::Value(Array val){
		this->value = std::make_shared<Array>(val);
	}

	Value::Value(long val, IntFormat format){
		this->value = IntPack{val, format};
	}

	Value::Value(double val){
		this->value = val;
	}

	Value::Value(bool val){
		this->value = val;
	}

	Value::Value(std::string val){
		this->value = val;
	}

	Value::Value(const char * val) : Value(std::string(val)){
		// only delegating
	}

	Value::Value(){
		this->value = Nil();
	}


	// read functions

	std::optional<double> Value::getFloat() const{
		if(auto val = std::get_if<double>(&this->value)){
			return *val;
		}
		//automatic conversion from int(long) to float(double)
		//every int can also be read as float
		else if (auto val = this->getInt()){
			return static_cast<double>(val->val);
		}
		else{
			return std::optional<double>();
		}
	}

	std::optional<Value::IntPack> Value::getInt() const{
		if(auto val = std::get_if<IntPack>(&this->value)){
			return *val;
		}
		else{
			return std::optional<IntPack>();
		}
	}

	std::optional<std::string> Value::getString() const{
		if(auto val = std::get_if<std::string>(&this->value)){
			return *val;
		}
		else{
			return std::optional<std::string>();
		}
	}

	std::optional<bool> Value::getBool() const {
		if(auto val = std::get_if<bool>(&this->value)){
			return *val;
		}
		else{
			return std::optional<bool>();
		}
	}

	std::optional<Value::Nil> Value::getNull() const{
		if(auto val = std::get_if<Nil>(&this->value)){
			return *val;
		}
		else{
			return std::optional<Nil>();
		}
	}

	std::shared_ptr<Object> Value::getObject()const{
		if(auto val = std::get_if<std::shared_ptr<Object>>(&this->value)){
			return *val;
		}
		else{
			return nullptr;
		}
	}

	std::shared_ptr<Array> Value::getArray()const{
		if(auto val = std::get_if<std::shared_ptr<Array>>(&this->value)){
			return *val;
		}
		else{
			return nullptr;
		}
	}


}