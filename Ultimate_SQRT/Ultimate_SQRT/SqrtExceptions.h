#pragma once
#include <string>
#include <exception>

class badTypeEx :std::exception {
	std::string msg{ "bad Type" };
public:
	const char* what() {
		return msg.c_str();
	}
};

class negValueEx :std::exception {
	std::string msg{ "sqrt of negative value" };
public:
	const char* what() {
		return msg.c_str();
	}
};