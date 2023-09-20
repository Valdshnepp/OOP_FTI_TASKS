#include "pch.h"

#include "../Range/Range.h"

#include <vector>

#include <algorithm>
#include <iostream>
#include <ostream>
#include <iterator>

constexpr double EPS = 10e-6;

TEST(Range, intRange) {
	std::vector<int> sample{0,1,2,3,4,5 };
	std::vector<int> result{};
	for (auto i : Range<int>(6)) {
		result.push_back(i);
	}
	EXPECT_EQ(true, sample == result);

	std::vector<int> sample2{5,4,3,2,1};
	std::vector<int> result2{};
	for (auto i : Range<int>(5,0,-1)) {
		result2.push_back(i);
	}
	EXPECT_EQ(true, sample2 == result2);

	std::vector<int> sample3{ 10,8,6,4,2};
	std::vector<int> result3{};
	for (auto i : Range<int>(10, 0, -2)) {
		result3.push_back(i);
	}
	EXPECT_EQ(true, sample3 == result3);
}

TEST(Range, doubleRange) {
	std::vector<double> sample{ 0,0.1,0.2,0.3,0.4,0.5 };
	std::vector<double> result{};
	for (auto i : Range<double>(0.0,0.6,0.1)) {
		result.push_back(i);
	}
	std::for_each(sample.begin(), sample.end(), [&result](auto a) {
		static int index = 0;
	EXPECT_NEAR(a, result.at(index++),EPS);
		});
	

	std::vector<double> sample2{0.5,0.4,0.3,0.2,0.1 };
	std::vector<double> result2{};
	for (auto i : Range<double>(0.5, 0.0, -0.1)) {
		result2.push_back(i);
	}
	std::for_each(sample.begin(), sample.end(), [&result](auto a) {
		static int index = 0;
	EXPECT_NEAR(a, result.at(index++), EPS);
		});

	std::vector<double> sample3{ 0.10,0.8,0.6,0.4,0.2 };
	std::vector<double> result3{};
	for (auto i : Range<double>(0.10, 0.0, -0.2)) {
		result3.push_back(i);
	}
	std::for_each(sample.begin(), sample.end(), [&result](auto a) {
		static int index = 0;
	EXPECT_NEAR(a, result.at(index++), EPS);
		});
}