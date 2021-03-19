#include <stdexcept>
namespace GDN{
	class LexError : public std::runtime_error {
	public:
		LexError(const std::string & str) : std::runtime_error(str) {}
	};
}