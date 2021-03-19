#pragma once
#include <stdexcept>
namespace GDN{
class FileError : public std::runtime_error {
public:
	FileError(const std::string & str) : std::runtime_error(str) {}
};
}