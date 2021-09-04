#pragma once
#include "Node.hxx"
#include <vector>
#include "Value.hxx"
namespace GDN {
	class Array : public Node {
	public:
		std::size_t size() const;
		const Value & get(std::size_t idx) const;
		void add(Value val);
		
		virtual void accept(Visitor & visitor) override;

	private:
		std::vector<Value> values;

	public:
		std::vector<Value>::iterator begin(){
			return this->values.begin();
		}
		std::vector<Value>::const_iterator begin() const{
			return this->values.begin();
		}
		std::vector<Value>::const_iterator cbegin() const{
			return this->values.cbegin();
		}

		std::vector<Value>::iterator end(){
			return this->values.end();
		}
		std::vector<Value>::const_iterator end() const{
			return this->values.end();
		}
		std::vector<Value>::const_iterator cend() const{
			return this->values.cend();
		}
	};
}