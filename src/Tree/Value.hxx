#pragma once
#include "Node.hxx"
#include <string>
#include <variant>
#include <optional>
#include <memory>
namespace GDN {
class Object;
class Array;
class Value : public Node {
public:
	// dummy class for null
	enum class IntFormat : std::uint8_t { DEC, BIN, HEX };
	struct Nil {};
	struct IntPack {long val; IntFormat format;};

	Value(long val, IntFormat format = IntFormat::DEC);
	Value(double val);
	Value(bool val);
	Value(std::string val);
	Value(const char * val);
	Value(Object val);
	Value(Array val);
	Value();
	
	//used for e.g. printing
	virtual void accept(Visitor & visit) override;

	//returns value or empty optional
	std::optional<double> getFloat() const;
	std::optional<IntPack> getInt() const;
	std::optional<std::string> getString() const;
	std::optional<bool> getBool() const;
	std::optional<Nil> getNull() const;
	//return shared_ptr to object if successful 
	//return nullptr if not
	std::shared_ptr<Object> getObject()const;
	std::shared_ptr<Array> getArray()const;
private:
	std::variant<
			IntPack,
			double,
			bool,
			std::string,
			Nil,						// Nil: dummy class for null nan and inf
			std::shared_ptr<Object>,
			std::shared_ptr<Array>
		> value;
};
}
