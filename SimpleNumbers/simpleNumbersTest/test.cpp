#include "pch.h"

#include <vector>
#include "../simple/SimpleNumberFinder.h"
#include <random>

TEST(NoMultiThread, empty) {
	std::vector<int> testVec{};
	EXPECT_EQ(SimpleNumberFinder::simpleNumberCount_NoMultithread(testVec.begin(), testVec.end()), 0);
	EXPECT_EQ(SimpleNumberFinder::hasSimpleNumber_NoMultithread(testVec.begin(), testVec.end()), 0);
}

TEST(NoMultiThread, oneSimple) {
	std::vector<int> testVec{1};
	EXPECT_EQ(SimpleNumberFinder::simpleNumberCount_NoMultithread(testVec.begin(), testVec.end()), 1);
	EXPECT_EQ(SimpleNumberFinder::hasSimpleNumber_NoMultithread(testVec.begin(), testVec.end()), 1);
}

TEST(NoMultiThread, oneNonSimple) {
	std::vector<int> testVec{ 4};
	EXPECT_EQ(SimpleNumberFinder::simpleNumberCount_NoMultithread(testVec.begin(), testVec.end()), 0);
	EXPECT_EQ(SimpleNumberFinder::hasSimpleNumber_NoMultithread(testVec.begin(), testVec.end()), 0);
}

TEST(NoMultiThread, fromOneToTen) {
	std::vector<int> testVec{1,2,3,4,5,6,7,8,9,10};
	EXPECT_EQ(SimpleNumberFinder::simpleNumberCount_NoMultithread(testVec.begin(), testVec.end()), 5);
	EXPECT_EQ(SimpleNumberFinder::hasSimpleNumber_NoMultithread(testVec.begin(), testVec.end()), 1);
}

TEST(MultiThread, empty) {
	std::vector<int> testVec{};
	EXPECT_EQ(SimpleNumberFinder::simpleNumberCount_Multithread(testVec.begin(), testVec.end()), 0);
	EXPECT_EQ(SimpleNumberFinder::hasSimpleNumber_Multithread(testVec.begin(), testVec.end()), 0);
}

TEST(MultiThread, oneSimple) {
	std::vector<int> testVec{ 1 };
	EXPECT_EQ(SimpleNumberFinder::simpleNumberCount_Multithread(testVec.begin(), testVec.end()), 1);
	EXPECT_EQ(SimpleNumberFinder::hasSimpleNumber_Multithread(testVec.begin(), testVec.end()), 1);
}

TEST(MultiThread, oneNonSimple) {
	std::vector<int> testVec{ 4 };
	EXPECT_EQ(SimpleNumberFinder::simpleNumberCount_Multithread(testVec.begin(), testVec.end()), 0);
	EXPECT_EQ(SimpleNumberFinder::hasSimpleNumber_Multithread(testVec.begin(), testVec.end()), 0);
}

TEST(MultiThread, fromOneToTen) {
	std::vector<int> testVec{ 1,2,3,4,5,6,7,8,9,10 };
	EXPECT_EQ(SimpleNumberFinder::simpleNumberCount_Multithread(testVec.begin(), testVec.end()), 5);
	EXPECT_EQ(SimpleNumberFinder::hasSimpleNumber_Multithread(testVec.begin(), testVec.end()), 1);
}

TEST(MultiThread, randomVec1000) {
	std::srand(std::time(NULL));
	std::vector<int> testVec{};
	for (int i = 0; i < 1000; i++) {
		testVec.push_back(rand() % 100'000);
	}
	EXPECT_EQ(SimpleNumberFinder::simpleNumberCount_Multithread(testVec.begin(), testVec.end()),
		SimpleNumberFinder::simpleNumberCount_NoMultithread(testVec.begin(), testVec.end()) );
	EXPECT_EQ(SimpleNumberFinder::hasSimpleNumber_Multithread(testVec.begin(), testVec.end()),
		SimpleNumberFinder::hasSimpleNumber_NoMultithread(testVec.begin(), testVec.end()) );
}

TEST(MultiThread, randomVec100000) {
	std::srand(std::time(NULL));
	std::vector<int> testVec{};
	for (int i = 0; i < 100000; i++) {
		testVec.push_back(rand() % 100'000);
	}
	EXPECT_EQ(SimpleNumberFinder::simpleNumberCount_Multithread(testVec.begin(), testVec.end()),
		SimpleNumberFinder::simpleNumberCount_NoMultithread(testVec.begin(), testVec.end()));
	EXPECT_EQ(SimpleNumberFinder::hasSimpleNumber_Multithread(testVec.begin(), testVec.end()),
		SimpleNumberFinder::hasSimpleNumber_NoMultithread(testVec.begin(), testVec.end()));
}

TEST(MultiThread, randomVec1000000) {
	std::srand(std::time(NULL));
	std::vector<int> testVec{};
	for (int i = 0; i < 1000000; i++) {
		testVec.push_back(rand() % 100'000);
	}
	EXPECT_EQ(SimpleNumberFinder::simpleNumberCount_Multithread(testVec.begin(), testVec.end()),
		SimpleNumberFinder::simpleNumberCount_NoMultithread(testVec.begin(), testVec.end()));
	EXPECT_EQ(SimpleNumberFinder::hasSimpleNumber_Multithread(testVec.begin(), testVec.end()),
		SimpleNumberFinder::hasSimpleNumber_NoMultithread(testVec.begin(), testVec.end()));
}