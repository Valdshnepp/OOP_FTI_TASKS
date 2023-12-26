#include <iostream>
#include <chrono>
#include <random>
#include <array>
#include "SimpleNumberFinder.h"

constexpr int NUMVALUERANGE = 1'000'000;
constexpr int STEPMULTIPLYER = 10;
constexpr long MINVECNUMCOUNT = 1'000;
constexpr long MAXVECNUMCOUNT = 100'000'000;

template <typename T>
void functionTime(int(*func)(T, T, const Policy&), T begin, T end, const Policy& pol, std::string comment) {
	std::chrono::steady_clock::time_point starttime;
	std::chrono::steady_clock::time_point endtime;
	std::chrono::milliseconds timeDelta;
	starttime = std::chrono::steady_clock::now();
	int currentRes = func(begin, end, pol);
	endtime = std::chrono::steady_clock::now();
	timeDelta = std::chrono::duration_cast<std::chrono::milliseconds>(endtime - starttime);
	std::cout << comment << currentRes << ". Time : " << timeDelta.count() << " milliseconds" << std::endl;
}

template <typename T>
void functionTime(int(*func)(T, T), T begin, T end, std::string comment) {
	std::chrono::steady_clock::time_point starttime;
	std::chrono::steady_clock::time_point endtime;
	std::chrono::milliseconds timeDelta;
	starttime = std::chrono::steady_clock::now();
	int currentRes = func(begin, end);
	endtime = std::chrono::steady_clock::now();
	timeDelta = std::chrono::duration_cast<std::chrono::milliseconds>(endtime - starttime);
	std::cout << comment << currentRes << ". Time : " << timeDelta.count() << " milliseconds" << std::endl;
}

int main() {

	std::srand(std::time(NULL));

	int currentRes = 0;
	for (long i = MINVECNUMCOUNT; i <= MAXVECNUMCOUNT; i *= STEPMULTIPLYER) {
		std::vector<int> testVector;
		for (int j = 0; j < i; j++) {
			testVector.push_back(rand() % NUMVALUERANGE);
		}

		std::cout << "container size is " << i << std::endl;

		functionTime(SimpleNumberFinder::simpleNumberCount_Multithread, testVector.begin(), testVector.end(), SuitablePolicy{ static_cast<size_t>(testVector.size()) },
			std::string{ "SuitableThreadPolicy.\t Result: " });
		functionTime(SimpleNumberFinder::simpleNumberCount_Multithread, testVector.begin(), testVector.end(), MaxThreadsPolicy{},
			std::string{ "MaxThreadPolicy.\t Result: " });
		functionTime(SimpleNumberFinder::simpleNumberCount_Multithread, testVector.begin(), testVector.end(), OneThreadPolicy{},
			std::string{ "OneThreadPolicy.\t Result: " });
		functionTime(SimpleNumberFinder::simpleNumberCount_NoMultithread, testVector.begin(), testVector.end(),
			std::string{ "singlethread.   \t Result: " });

		std::cout << std::endl;

		//used for finding suitable numbers for sizes
		/*for (size_t k = 4; k < 33; k += 4) {
			starttime = std::chrono::steady_clock::now();
			currentRes = simpleNumberCount_multithread(testVector.begin(), testVector.end(), NThreadPolicy{ k });
			endtime = std::chrono::steady_clock::now();
			timeDelta = std::chrono::duration_cast<std::chrono::nanoseconds>(endtime - starttime);
			std::cout<<"Amount:"<<i<<" Thread count:" <<k<< "Result: " << currentRes << ".Time : " << timeDelta.count() << " milliseconds" << std::endl;
		}
		std::cout << std::endl;*/
	}
	return 0;
}