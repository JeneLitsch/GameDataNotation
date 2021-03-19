#include "Array.hxx"

namespace GDN {
	std::size_t Array::size() const{
		return this->values.size();
	}
	Value Array::get(std::size_t idx) const{
		return this->values[idx];
	}
	void Array::add(Value val){
		this->values.push_back(val);
	}

	void Array::accept(Visitor & visitor) {
		visitor.visitArray(*this);
	}

}