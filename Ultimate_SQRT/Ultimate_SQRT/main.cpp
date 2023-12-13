#include "Sqrt.h"
#include <iostream>

#include <iostream>
#include <algorithm>

#include "Sqrt.h"


int main() { 

	try {
		Sqrt(1);
		Sqrt(std::string{ "12_" });

		std::cout << std::string{ "succes!" }<<std::endl;
	}
	catch (negValueEx& a) {
		std::cout << "ERROR!" << std::endl;
		std::cout<<a.what() << std::endl;
	}
	catch (badTypeEx& a) {
		std::cout << "ERROR!" << std::endl;
		std::cout << a.what() << std::endl;
	}
	return 0;
}