#pragma once
#include <thread>
#include <future>
#include "Policies.h"

namespace {
	template <class Iter, class Incr>
	void safe_advance(Iter& curr, Iter& end, Incr n) {
		size_t remaining(std::distance(curr, end));
		if (remaining < n)
		{
			n = remaining;
		}
		std::advance(curr, n);
	}

	bool isSimple(int num) {
		if (num <= 0) {
			return false;
		}
		for (int i = 2; i <= std::sqrt(num); i++) {
			if (num % i == 0) {
				return false;
			}
		}
		// может тогда return true? //fixed
		return true;
	}

	template <typename Iter>
	int subcontainerSimpleFind(Iter begin, Iter end, int initIndex, int threadCount) {
		int threadRes = 0;
		Iter it = begin;
		safe_advance(it, end, initIndex);
		for (;it < end;) {
			if (isSimple(*it)) {
				threadRes++;
			}
			safe_advance(it, end, threadCount);
		}
		return threadRes;
	}
}

namespace SimpleNumberFinder {
	template<typename RandomAccessIterator>
	typename std::enable_if_t<std::is_same<typename std::iterator_traits<RandomAccessIterator>::iterator_category, std::random_access_iterator_tag>::value,
		int> simpleNumberCount_NoMultithread(RandomAccessIterator begin, RandomAccessIterator end) {
		int res = 0;
		//const auto& /can`t iterate with const
		for (auto& it = begin; it != end; it++) {
			if (isSimple(*it)) {
				res++;
			}
		}
		return res;
	}

	template<typename RandomAccessIterator>
	typename std::enable_if_t<std::is_same<typename std::iterator_traits<RandomAccessIterator>::iterator_category, std::random_access_iterator_tag>::value,
		bool> hasSimpleNumber_NoMultithread(RandomAccessIterator begin, RandomAccessIterator end) {
		for (; begin != end; begin++) {
			if (isSimple(*begin)) {
				return true;
			}
		}
		return false;
	}

	template<typename RandomAccessIterator>
	typename std::enable_if_t<std::is_same<typename std::iterator_traits<RandomAccessIterator>::iterator_category, std::random_access_iterator_tag>::value,
		int> simpleNumberCount_Multithread(RandomAccessIterator begin, RandomAccessIterator end, const Policy& policy = MaxThreadsPolicy{}) {
		std::vector <std::future<int>> threads;
		int threadCount = policy.getNumberOfThreads();
		if (threadCount == 0) {
			threadCount = 4;
		}
		for (int i = 0; i < threadCount && i < std::distance(begin, end); i++) {
			// Слишком большую функцию занес в лямбду, так никто не делает. Сделай декомпозицию. //fixed
			threads.push_back(std::async(std::launch::async, subcontainerSimpleFind<RandomAccessIterator>, begin, end , i , threadCount));
		}
		int res = 0;

		// сначала в одном цикле делаешь каждой фиче wait, потом получаешь get. Иначе у тебя undefined behaviour. //fixed 
		// а почему UB? видел множество примеров, где сразу используют get. get же также ждет окончания работы как и wait. так в каком тогда случае это UB
		for (auto it = threads.begin(); it != threads.end(); it++) {
			(*it).wait();
		}
		for (auto it = threads.begin(); it != threads.end(); it++) {
			res = res + (*it).get();
		}
		return res;
	}

	template<typename RandomAccessIterator>
	typename std::enable_if_t<std::is_same<typename std::iterator_traits<RandomAccessIterator>::iterator_category, std::random_access_iterator_tag>::value,
		bool> hasSimpleNumber_Multithread(RandomAccessIterator begin, RandomAccessIterator end, const Policy& policy = MaxThreadsPolicy{}) {
		return simpleNumberCount_Multithread(begin, end, policy);
	}
}
