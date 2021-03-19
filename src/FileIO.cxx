#include "FileIO.hxx"
#include <fstream>
#include <stdexcept>

#include "FileError.hxx"
namespace GDN{

	std::string FileIO::read(const std::string & fileName){
		std::ifstream file(fileName);
		
		//check file
		if(file.bad()){
			throw(FileError("Cannot read file :" + fileName));
		}

		//copy content
		std::string str;
		str.assign(
			std::istreambuf_iterator<char>(file),
			std::istreambuf_iterator<char>()
		);
		file.close();
		return str;
	}

	void FileIO::write(const std::string & fileName, const std::string & content){
		std::ofstream file(fileName);
		
		//check file
		if(file.bad()){
			throw(FileError("Cannot write to file: " + fileName));
		}
		//write content
		file << content;
		file.close();
	}

}