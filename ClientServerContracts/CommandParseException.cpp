#include <stdexcept>

class CommandParseException : public std::runtime_error {
public:	
	CommandParseException(const char *what) : runtime_error(what) {}
};