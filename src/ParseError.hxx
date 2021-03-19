#pragma once
#include <stdexcept>
namespace GDN{
	class ParseError : public std::runtime_error{
	public:
		ParseError(const std::string & str) : std::runtime_error(str) {}
	};
}