#pragma once

#include "RangeIterator.h"
#include "rangeExceptions.h"

#include <cmath>
#include <type_traits>

//В целом молодец, идею уловил верно, но надо доработать.
//1. typename = std::is_arithmetic<T>. Не понял, что ты тут хотел сделать. То что здесь написано просто делает вторым параметром по умолчанию true или false, в зависимости от того, что std::is_arithmetic выплюнет. На SFINAE не оч похоже.
//2. Посмотри реализацию Range(T begin, T stop). Не знаю зачем ты сделал нулевой step, видимо чтоб никогда из цикла не выходить).
//3. Соответвсвенно в Range(T begin, T stop, T step) надо чтобы  step был не равен 0.
//4. Сделай так, чтобы дефолтный конструктор был недоступен.
//5. Хочу константые перегрузки begin и end.




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
