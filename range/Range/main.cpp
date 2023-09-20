#include "Range.h"

#include "iostream"
#include <string>

int main() {
	
	try {
		for (auto a : Range<int>(1,23,4)) {
			std::cout << (a) << std::endl;
		}
	}
	catch (badRange& a) {
		std::cout<<a.what()<<std::endl;
	}

	return 0;
}