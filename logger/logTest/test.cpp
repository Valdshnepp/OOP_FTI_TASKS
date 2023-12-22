#include "pch.h"

#include "../logger2/logger.h"
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>

bool compareFiles(const std::string& p1, const std::string& p2) {
	std::ifstream f1(p1, std::ifstream::binary | std::ifstream::ate);
	std::ifstream f2(p2, std::ifstream::binary | std::ifstream::ate);

	if (f1.fail() || f2.fail()) {
		return false; //file problem
	}

	if (f1.tellg() != f2.tellg()) {
		return false; //size mismatch
	}

	//seek back to beginning and use std::equal to compare contents
	f1.seekg(0, std::ifstream::beg);
	f2.seekg(0, std::ifstream::beg);
	return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
		std::istreambuf_iterator<char>(),
		std::istreambuf_iterator<char>(f2.rdbuf()));
}

const std::string outPath{ "../logTest/output/" };
const std::string examplePath{ "../logTest/example/" };

TEST(exceptionTest, TestName) {
	EXPECT_ANY_THROW(logger::getInstance() << "test";);
}

TEST(OutTest1, TestName) {
	std::string testOutPath = outPath;
	std::string testExamplePath = examplePath;
	testOutPath.append("Test1.txt");
	testExamplePath.append("Test1.txt");
	logger::setLogFile(testOutPath, std::ios::out);

	logger::getInstance() << "string ";
	logger::getInstance() << "1";
	logger::getInstance() << std::endl;
	logger::getInstance() << "string 2" << std::endl;

	EXPECT_EQ(compareFiles(testOutPath, testExamplePath), true);
}

TEST(OutTest2, TestName) {
	std::string testOutPath = outPath;
	std::string testExamplePath = examplePath;
	testOutPath.append("Test2.txt");
	testExamplePath.append("Test2.txt");
	logger::setLogFile(testOutPath, std::ios::out);

	logger::getInstance() << "string 1" << std::endl;
	logger::logstream("pref: ");
	logger::getInstance() << "string 2" << std::endl;
	logger::getInstance() << "string 3" << std::endl;
	logger::logstream();
	logger::getInstance() << "string 4" << std::endl;
	EXPECT_EQ(compareFiles(testOutPath, testExamplePath), true);
}


TEST(OutTest3, TestName) {
	std::string testOutPath = outPath;
	std::string testExamplePath = examplePath;
	testOutPath.append("Test3.1.txt");
	testExamplePath.append("Test3.1.txt");
	logger::getInstance().setLogFile(testOutPath, std::ios::out);

	logger::getInstance() << "string 1" << std::endl;
	logger::logstream("pref: ");
	logger::getInstance() << "string 2" << std::endl;
	logger::getInstance() << "string 3" << std::endl;
	logger::logstream();
	logger::getInstance() << "string 4" << std::endl;

	std::string testOutPath2 = outPath;
	std::string testExamplePath2 = examplePath;
	testOutPath2.append("Test3.2.txt");
	testExamplePath2.append("Test3.2.txt");
	logger::setLogFile(testOutPath2, std::ios::out);

	logger::getInstance() << "string 1" << std::endl;
	logger::logstream("pref: ");
	logger::getInstance() << "string 2" << std::endl;
	logger::getInstance() << "string 3" << std::endl;
	logger::logstream();
	logger::getInstance() << "string 4" << std::endl;
	EXPECT_EQ(compareFiles(testOutPath, testExamplePath), true);
	EXPECT_EQ(compareFiles(testOutPath2, testExamplePath2), true);
}