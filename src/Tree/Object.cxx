#include "Object.hxx"
namespace GDN {
	std::optional<Value> Object::get(const std::string & key) const {
		if(this->values.contains(key)){
			return this->values.at(key);
		}
		else{
			return std::optional<Value>();
		}
	}
	void Object::set(const std::string & key, Value val){
		this->values[key] = val;
	}

	void Object::accept(Visitor & visitor) {
		visitor.visitObject(*this);
	}
}