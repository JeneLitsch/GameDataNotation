#include "StringTools.hxx"
#include <sstream>
#include <iomanip>
#include <bitset>
namespace GDN
{	
	bool StringTools::isHex(char c){
		return std::isxdigit(static_cast<unsigned char>(c));
	}

	bool StringTools::isBin(char c){
		return (c == '0' || c == '1');
	}

	bool StringTools::isAlpha(char c) {
		return std::isalpha(static_cast<unsigned char>(c));
	}

	bool StringTools::isNumeric(char c) {
		return std::isdigit(static_cast<unsigned char>(c));
	}

	bool StringTools::isAlphaNumeric(char c) {
		return std::isalnum(static_cast<unsigned char>(c));
	}

	std::string StringTools::strip(const std::string & str){
		if(str.size() >= 2){
			return str.substr(1, str.size() -2);
		}
		else {
			return "";
		}
	}

	std::uint64_t StringTools::fromHex(const std::string & hex){
		std::uint64_t num;   
		std::stringstream stream;
		stream << std::hex << hex;
		stream >> num;
		return num;
	}

	std::string StringTools::toHex(std::uint64_t _int){
		std::string hex;
		std::stringstream stream;
		stream << std::setfill('0') <<  std::setw(sizeof(std::uint64_t) * 2) << std::hex << _int;
		stream >> hex;
		return hex;
	}



	std::uint64_t StringTools::fromBin(const std::string & bin){
		std::bitset<64> bitset(bin);
		return bitset.to_ullong();
	}
	
	std::string StringTools::toBin(std::uint64_t _int){
		std::bitset<64> bitset = _int;
		std::string bin = bitset.to_string();
		return bin;
	}


} // namespace GDN