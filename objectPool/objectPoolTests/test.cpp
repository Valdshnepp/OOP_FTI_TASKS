#include "pch.h"
#include "../objectPool2/objectPool.h"

class MemoryLeakDetector {
public:
	MemoryLeakDetector() {
		_CrtMemCheckpoint(&memState_);
	}

	~MemoryLeakDetector() {
		_CrtMemState stateNow, stateDiff;
		_CrtMemCheckpoint(&stateNow);
		int diffResult = _CrtMemDifference(&stateDiff, &memState_, &stateNow);
		if (diffResult)
			reportFailure(stateDiff.lSizes[1]);
	}
private:
	void reportFailure(unsigned int unfreedBytes) {
		FAIL() << "Memory leak of " << unfreedBytes << " byte(s) detected.";
	}
	_CrtMemState memState_;
};

struct foo final {
	int m_field1;
	char m_field2;
public:
	foo() = delete;
	foo(int f1, char f2) :m_field1(f1), m_field2(f2) {}
};

TEST(constructorTEST, Test1) {
	MemoryLeakDetector leakDetector;
	try {
		objectPool<foo> boo(0);
		EXPECT_THROW(boo.alloc(1, 'a'), std::out_of_range);
	}
	catch (...) { EXPECT_EQ(true, false); }
}

TEST(allocTEST, Test1) {
	MemoryLeakDetector leakDetector;
	try {
		objectPool<foo> boo(2);
		foo& qoo = boo.alloc(1, 'a');
		foo& zoo = boo.alloc(2, 'b');
		auto a = &zoo;
		EXPECT_THROW(boo.alloc(1, 'a'), std::out_of_range);
		EXPECT_EQ(qoo.m_field1, 1);
		EXPECT_EQ(qoo.m_field2, 'a');
		EXPECT_EQ(zoo.m_field1, 2);
		EXPECT_EQ(zoo.m_field2, 'b');
	}
	catch (...) { EXPECT_EQ(true, false); }
}

TEST(freeTEST, Test1) {
	MemoryLeakDetector leakDetector;
	try {
		objectPool<foo> boo(2);
		foo& qoo = boo.alloc(1, 'a');
		foo& zoo = boo.alloc(2, 'b');
		EXPECT_THROW(boo.alloc(1, 'a'), std::out_of_range);
		EXPECT_EQ(qoo.m_field1, 1);
		EXPECT_EQ(qoo.m_field2, 'a');
		EXPECT_EQ(zoo.m_field1, 2);
		EXPECT_EQ(zoo.m_field2, 'b');
		boo.free(qoo);
		EXPECT_EQ(zoo.m_field1, 2);
		EXPECT_EQ(zoo.m_field2, 'b');
		boo.free(zoo);
		qoo = boo.alloc(3, 'a');
		zoo = boo.alloc(4, 'b');
		EXPECT_EQ(qoo.m_field1, 3);
		EXPECT_EQ(zoo.m_field1, 4);
	}
	catch (...) { EXPECT_EQ(true, false); }
}

TEST(copyConstructor, Test1) {
	MemoryLeakDetector leakDetector;
	try {
		objectPool<foo> boo(2);
		foo& qoo = boo.alloc(1, 'a');
		foo& zoo = boo.alloc(2, 'b');
		objectPool<foo> too(boo);
		EXPECT_THROW(too.alloc(1, 'a'), std::out_of_range);
		too.free(zoo);
		EXPECT_THROW(too.alloc(1, 'a'), std::out_of_range);
		foo& qq = too.firstInPool();
		EXPECT_EQ(qq.m_field1, 1);
		EXPECT_EQ(qq.m_field2, 'a');
		too.free(qq);
		foo& ww = too.firstInPool();
		EXPECT_EQ(ww.m_field1, 2);
		EXPECT_EQ(ww.m_field2, 'b');
		too.free(ww);
		EXPECT_THROW(too.firstInPool(), std::out_of_range);
	}
	catch (...) { EXPECT_EQ(true, false); }
}

TEST(moveConstructor, Test1) {
	MemoryLeakDetector leakDetector;
	try {
		objectPool<foo> boo(2);
		foo& qoo = boo.alloc(1, 'a');
		foo& zoo = boo.alloc(2, 'b');
		objectPool<foo> too(std::move(boo));
		foo& qq = too.firstInPool();
		EXPECT_EQ(qq.m_field1, 1);
		EXPECT_EQ(qq.m_field2, 'a');
		too.free(qq);
		foo& ww = too.firstInPool();
		EXPECT_EQ(ww.m_field1, 2);
		EXPECT_EQ(ww.m_field2, 'b');
	}
	catch (...) { EXPECT_EQ(true, false); }
}

TEST(moveAssign, Test1) {
	MemoryLeakDetector leakDetector;
	try {
		objectPool<foo> boo(2);
		foo& qoo = boo.alloc(1, 'a');
		foo& zoo = boo.alloc(2, 'b');
		objectPool<foo> too(3);
		too.alloc(6, 'q');
		too = std::move(boo);

		foo& qq = too.firstInPool();
		EXPECT_EQ(qq.m_field1, 1);
		EXPECT_EQ(qq.m_field2, 'a');
		too.free(qq);
		foo& ww = too.firstInPool();
		EXPECT_EQ(ww.m_field1, 2);
		EXPECT_EQ(ww.m_field2, 'b');
	}
	catch (...) { EXPECT_EQ(true, false); }
}

TEST(copyAssign, Test1) {
	MemoryLeakDetector leakDetector;
	try {
		objectPool<foo> boo(2);
		foo& qoo = boo.alloc(1, 'a');
		foo& zoo = boo.alloc(2, 'b');
		objectPool<foo> too(3);
		too.alloc(6, 'q');
		too = boo;


		foo& qq = too.firstInPool();
		EXPECT_EQ(qq.m_field1, 1);
		EXPECT_EQ(qq.m_field2, 'a');
		too.free(qq);
		foo& ww = too.firstInPool();
		EXPECT_EQ(ww.m_field1, 2);
		EXPECT_EQ(ww.m_field2, 'b');
	}
	catch (...) { EXPECT_EQ(true, false); }
}