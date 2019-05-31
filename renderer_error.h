#pragma once
#include <stdexcept>
#include <cstring>
#include <sstream>
class error : public std::runtime_error
{
private:
	std::string message; //error message
public:
	error(const char* error):runtime_error("renderer_error") {
		std::stringstream ss(message);
		ss << error;
		message = ss.str();
	}
	const char* what() const noexcept {
		return message.c_str();
	}
};

