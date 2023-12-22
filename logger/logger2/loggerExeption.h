#pragma once

#include <exception>

class badfile final: std::exception {
	char* what() {
		char msg[] = "bad file";
		return msg;
	};
};