#include "objectPool.h"
#include <iostream>

class test {
public:
	test() {
		std::cout << "test created" << std::endl;
	}
	~test() {
		std::cout << "test died" << std::endl;
	}

	test(const test& rhs) {
		std::cout << "copy constructor worked" << std::endl;
	}
};

int main() {

	try {
		objectPool<test> p(2);
		test& first = p.alloc();
		test& second = p.alloc();
		p.free(second);
		test& third = p.alloc();

		objectPool q = p;
	}
	catch (std::out_of_range& a) {
		std::cout << a.what() << std::endl;
	}

	return 0;
}