#pragma once
#include <thread>
#include <map>

class Policy{
public:
	Policy() = default;
	virtual size_t getNumberOfThreads() const = 0;
};

class OneThreadPolicy final : public Policy{
public:
	OneThreadPolicy() = default;
	size_t getNumberOfThreads() const override{
		return 1;
	}
};

class MaxThreadsPolicy final : public Policy{
public:
	MaxThreadsPolicy() = default;
	size_t getNumberOfThreads() const override{
		return std::thread::hardware_concurrency();
	}
};

class SuitablePolicy final : public Policy{
private:
	size_t m_size;
	std::map<size_t, size_t> suitableAmount{
		{1, 1},
		{26, 2},
		{100, 4},
		{10'000, 8},
		{100'000, 12},
		{1'000'000, 16},
	};
public:
	SuitablePolicy(size_t ContSize) :m_size{ ContSize } {};
	size_t getNumberOfThreads() const override{
		auto mapIterator = suitableAmount.lower_bound(m_size);
		if (mapIterator == suitableAmount.end()){
			return 1;
		}
		return mapIterator->second - 1;
	}
};

class NThreadPolicy final : public Policy {
	size_t m_ThreadCount;
public:
	NThreadPolicy(size_t ThreadCount) :m_ThreadCount{ ThreadCount } {};
	size_t getNumberOfThreads() const override {
		return m_ThreadCount;
	}
};