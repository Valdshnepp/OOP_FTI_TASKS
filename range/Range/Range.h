#pragma once

#include "RangeIterator.h"
#include "rangeExceptions.h"

#include <cmath>
#include <type_traits>

template <typename T,typename = std::is_arithmetic<T>>
class Range {
	T m_begin,m_end,m_step;

public:
	Range(T stop) :Range(0, stop, 1) {
	}

	Range(T begin, T stop) :
		Range(begin, stop, 0) {};
	

	Range(T begin, T stop, T step) {
		if ((begin < stop && step < 0) || (begin > stop && step > 0) || step == 0) {
			throw badRange();
		}
		m_begin = begin;
		m_end = stop;
		m_step = step;
	}

	RangeIterator<T> begin() { return RangeIterator<T>(m_begin,m_end,m_step,0); }

	RangeIterator<T> end() {
		return RangeIterator<T>(m_begin, m_end, m_step,
			(int)std::ceil ((m_end - m_begin) / m_step));
	}
};
