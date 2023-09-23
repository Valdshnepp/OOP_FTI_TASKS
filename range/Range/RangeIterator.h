#pragma once
//1. А зачем хранить m_end? Ты ж его вроде нигде не юзаешь...
//2. Что-то у тебя не так с сигнатурой оператора !=... Подумай и добавь туда кое-что.
//3. size_t m_index. Почему такой тип? Ты же его к int привел в Range. Подумай что там можно с типом сделать.



template<typename T>
class RangeIterator {
	const T& m_begin, m_end, m_step;
	size_t m_index{};
public:
	RangeIterator(const T& begin, const T& stop, const T& step, size_t index) :
		m_begin(begin), m_end(stop), m_step(step),m_index(index) {};

	RangeIterator& operator++() {
		m_index++;
		return *this;
	}

	bool operator!=(const RangeIterator& other) {
		return m_index != other.m_index;
	}

	T operator*() const{
		return m_begin + (m_step*m_index);
	}
};
