#pragma once
#include <string>
namespace GDN{
	class FileIO {
	public:
		//reads entire file into string 
		//throws a FileError if the file is not available
		static std::string read(const std::string & fileName);

		//writes string into a file
		//throws a FileError if the file is not available
		static void write(const std::string & fileName, const std::string & content);
	};
}