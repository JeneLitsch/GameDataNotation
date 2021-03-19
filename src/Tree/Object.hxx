#pragma once
#include "Node.hxx"
#include "Value.hxx"
#include <map>
namespace GDN{
	class Object : public Node {
	public:
		Object(){}
		std::optional<Value> get(const std::string & key);
		void set(const std::string & key, Value val);
		virtual void accept(Visitor & visitor) override;
		std::string keys() const;

	private:
		std::map<std::string, Value> values;
	
	public:
		std::map<std::string, Value>::iterator begin(){
			return this->values.begin();
		}
		std::map<std::string, Value>::const_iterator begin() const{
			return this->values.begin();
		}
		std::map<std::string, Value>::const_iterator cbegin() const{
			return this->values.cbegin();
		}

		std::map<std::string, Value>::iterator end(){
			return this->values.end();
		}
		std::map<std::string, Value>::const_iterator end() const{
			return this->values.end();
		}
		std::map<std::string, Value>::const_iterator cend() const{
			return this->values.cend();
		}
	};
}
