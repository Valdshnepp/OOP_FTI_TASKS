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
		for (int i = 2; i <= std::sqrt(num); i++) {
			if (num % i == 0) {
				return false;
			}
		}
		return num;
	}
}

namespace SimpleNumberFinder {
	template<typename RandomAccessIterator>
	typename std::enable_if_t<std::is_same<typename std::iterator_traits<RandomAccessIterator>::iterator_category, std::random_access_iterator_tag>::value,
		int> simpleNumberCount_NoMultithread(RandomAccessIterator begin, RandomAccessIterator end) {
		int res = 0;
		for (auto it = begin; it != end; it++) {
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
			threads.push_back(std::async([=]() {
				int threadRes = 0;
			RandomAccessIterator it = begin;
			RandomAccessIterator end1 = end;

			safe_advance(it, end1, i);
			for (; it < end;) {
				if (isSimple(*it)) {
					threadRes++;
				}
				safe_advance(it, end1, threadCount);
			}
			return threadRes;
				}));
		}
		int res = 0;
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
