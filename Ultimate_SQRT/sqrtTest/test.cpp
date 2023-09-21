#include "pch.h"
#include "../Ultimate_SQRT/Sqrt.h"

constexpr double EBS = 10e-6;

TEST(sqrt, intTest) {
	int a1 = 1;
	int a2 = 4;
	int a3 = 3;
	//int a4 = -1;
	
	EXPECT_EQ(Sqrt(a1), 1);
	EXPECT_EQ(Sqrt(a2), 2 );
	EXPECT_EQ(Sqrt(a3), 1);
	//EXPECT_EQ(Sqrt(a4), nan);
	EXPECT_TRUE(true);
}

TEST(sqrt, doubleTest) {
	double a1 = 1;
	double a2 = 4;
	double a3 = 3;
//	double a4 = -1;

	EXPECT_NEAR(Sqrt(a1), 1, EBS);
	EXPECT_NEAR(Sqrt(a2), 2, EBS);
	EXPECT_NEAR(Sqrt(a3), std::sqrt(3), EBS);
//	EXPECT_NEAR(Sqrt(a4), std::sqrt(-1), EBS);

	EXPECT_TRUE(true);
}

TEST(sqrt, vectorTest) {
	std::vector<double> a1{ 0,1,5,10,1344 };
	std::vector<double> r1{Sqrt(a1)};

	std::for_each(r1.begin(), r1.end(), [&a1 = std::as_const(a1)](const auto& r) {
		static int index = 0;
		EXPECT_NEAR(r, std::sqrt(a1[index++]), EBS); });

}

TEST(sqrt, listTest) {
	std::list<double> a1{ 0 ,1,5,10,1344 };
	std::list<double> r1{ Sqrt(a1) };

	std::for_each(r1.begin(), r1.end(), [&a1 = std::as_const(a1)](const auto& r) {
		static int index = 0;
		auto goalVal = a1.begin();
		std::advance(goalVal, index++);
	EXPECT_NEAR(r, std::sqrt(*goalVal), EBS); });

}

TEST(sqrt, forwardListTest) {
	std::forward_list<double> a1{ 0,4,10};
	std::forward_list<double> r1{ Sqrt(a1) };

	std::for_each(r1.begin(), r1.end(), [a1 = std::as_const(a1)](const auto& r) {
		static auto goalVal = a1.begin();
	EXPECT_NEAR(r, std::sqrt(*goalVal), EBS); 
	goalVal++; });
}

TEST(sqrt, setTest) {
	std::set<double> a1{ 0,1,5,10,1344 };
	std::set<double> r1{ Sqrt(a1) };

	std::for_each(r1.begin(), r1.end(), [&a1 = std::as_const(a1)](const auto& r) {
		static int index = 0;
	auto goalVal = a1.begin();
	std::advance(goalVal, index++);
	EXPECT_NEAR(r, std::sqrt(*goalVal), EBS); });
}

TEST(sqrt, unorderedSetTest) {
	std::unordered_set<double> a1{ 0,1,5,10,1344 };
	std::set<double> a2{};
	std::transform(a1.begin(), a1.begin(), std::inserter(a2,a2.begin()), [](double a) {return a; });
	
	std::unordered_set<double> r1{ Sqrt(a1) };
	std::set<double> r2{};
	std::transform(r1.begin(), r1.begin(), std::inserter(r2, r2.begin()), [](double a) {return a; });

	std::for_each(r2.begin(), r2.end(), [&a2 = std::as_const(a2)](const auto& r) {
		static int index = 0;
	auto goalVal = a2.begin();
	std::advance(goalVal, index++);
	EXPECT_NEAR(r, std::sqrt(*goalVal), EBS); });
}

TEST(sqrt, mapTest) {
	std::map<char, double> a1{ {'a',0},{'b',25},{'c',103}};
	std::map<char, double> r1 = Sqrt(a1);

	std::for_each(r1.begin(), r1.end(), [&a1 = std::as_const(a1)](const auto& r) {
		static auto goalVal = a1.begin();
	EXPECT_NEAR(r.second, std::sqrt((*goalVal++).second), EBS); });
}

TEST(sqrt, unorderedMapTest) {

	std::unordered_map<char, double> a1{ {'a',0},{'b',25},{'c',103} };
	std::map<char, double> a2{};
	std::transform(a1.begin(), a1.begin(), std::inserter(a2, a2.begin()), [](auto a) {return a; });

	std::unordered_map<char, double> r1{ Sqrt(a1) };
	std::map<char, double> r2{};
	std::transform(r1.begin(), r1.begin(), std::inserter(r2, r2.begin()), [](auto a) {return a; });

	std::for_each(r2.begin(), r2.end(), [&a2 = std::as_const(a2)](const auto& r) {
		static int index = 0;
	auto goalVal = a2.begin();
	std::advance(goalVal, index++);
	EXPECT_NEAR(r.second, std::sqrt((*goalVal).second), EBS); });

}

TEST(sqrt, setOfVectorsTest) {
	std::set<std::vector<double>> a1{ {1,4,9,16},{25,49},{1} };
	auto r1{ Sqrt(a1) };
	std::set<std::vector<double>> sample = { {1, 2, 3, 4}, { 5,7 }, { 1 } };
	EXPECT_EQ(r1, sample);

}