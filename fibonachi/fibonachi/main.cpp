
#include <iostream>
#include <chrono>

template<int N>
class Fib {
	public:
	static const int val= Fib<N - 1>::val+ Fib < N - 2 >::val;
};

template<>
class Fib<0> {
	public:
	static const int val = 0;
};

template<>
class Fib<1> {
	public:
	static const int val = 1;
};

// Сделай еще кое-что. Реализуй алгоритм чисел Фиббоначи, которые в рантайме вычисляются и сравни время исполнения. Остальное обсудим на семинаре. 
int main() {
	auto starttime = std::chrono::high_resolution_clock::now();
	std::cout << Fib<0>::val << std::endl;
	std::cout << Fib<1>::val << std::endl;
	std::cout << Fib<2>::val << std::endl;
	std::cout << Fib<3>::val << std::endl;
	std::cout << Fib<4>::val << std::endl;
	std::cout << Fib<5>::val << std::endl;
	std::cout << Fib<6>::val << std::endl;
	std::cout << Fib<20>::val << std::endl;
	std::cout << Fib<40>::val << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()- starttime).count() << std::endl;
	return 0;

}
