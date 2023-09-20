#pragma once
#include <string>
#include <exception>

class badRange :std::exception {
	const std::string msg{ "bad range" };
public:
	const char* what() {
		return msg.c_str();
	}
};