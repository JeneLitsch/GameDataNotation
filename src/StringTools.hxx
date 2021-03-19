#pragma once
#include <vector>
#include <string>
namespace GDN{
	class StringTools{
	public:
		static bool isAlpha(char c);
		static bool isNumeric(char c);
		static bool isHex(char c);
		static bool isBin(char c);
		static bool isAlphaNumeric(char c);
		static std::string strip(const std::string & str);

		//requires hex without 0x
		static std::uint64_t fromHex(const std::string & str);
		//returns hex without 0x
		static std::string toHex(unsigned long _int);

		//requires bin string without 0b
		static std::uint64_t fromBin(const std::string & str);
		//returns bin without 0b
		static std::string toBin(std::uint64_t _int);
	};
} // namespace GD
