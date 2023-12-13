#pragma once
#include <memory>
#include <utility> 
#include <vector>
#include <stdexcept>

template <typename T>
class objectPool final {
private:
	std::unique_ptr<uint8_t[]> m_data;
	size_t m_count;
	std::vector<bool> m_isLocked;
public:
	objectPool() = delete;

	objectPool(size_t count) : m_data(std::make_unique<uint8_t[]>(count * sizeof(T))),
		m_count(count),
		m_isLocked(count, false) {};

	~objectPool() {
		for (size_t i = 0; i < m_count; i++) {
			if (m_isLocked[i]) {
				reinterpret_cast<T*>(m_data.get() + sizeof(T) * i)->~T();
			}
		}
	}

	objectPool(const objectPool& rhs) :objectPool(rhs.m_count) {
		for (size_t i = 0; i < rhs.m_count; i++) {
			if (rhs.m_isLocked[i]) {
				this->alloc(*reinterpret_cast<T*>(rhs.m_data.get() + i * sizeof(T)));
			}
		}
	}

	objectPool(objectPool&& rhs) noexcept {
		std::swap(rhs.m_data, m_data);
		m_isLocked = rhs.m_isLocked;
		m_count = rhs.m_count;
	}

	objectPool& operator=(const objectPool& rhs) {
		if (this == &rhs) {
			return *this;
		}
		for (size_t i = 0; i < m_count; i++) {
			if (m_isLocked[i]) {
				m_isLocked[i] = 0;
				reinterpret_cast<T*>(m_data.get() + sizeof(T) * i)->~T();
			}
		}
		m_data=std::make_unique<uint8_t[]>(rhs.m_count * sizeof(T));
		for (size_t i = 0; i < rhs.m_count; i++) {
			if (rhs.m_isLocked[i]) {
				this->alloc(*reinterpret_cast<T*>(rhs.m_data.get() + i * sizeof(T)));
			}
		}
		m_isLocked = rhs.m_isLocked;
		m_count = rhs.m_count;
		return *this;
	}

	objectPool& operator=(objectPool&& rhs) {
		if (this == &rhs) {
			return *this;
		}
		for (size_t i = 0; i < m_count; i++) {
			if (m_isLocked[i]) {
				m_isLocked[i] = 0;
				reinterpret_cast<T*>(m_data.get() + sizeof(T) * i)->~T();
			}
		}
		std::swap(m_data, rhs.m_data);
		m_isLocked = rhs.m_isLocked;
		m_count = rhs.m_count;
		return *this;
	}

	template <typename ... Args>
	T& alloc(Args&& ... args) {
		for (size_t i = 0; i < m_count; i++) {
			if (m_isLocked[i]) {
				continue;
			}
			m_isLocked[i] = true;

			return *new(m_data.get() + sizeof(T) * i)T{ std::forward<Args>(args)... };;
		}
		throw std::out_of_range("no more space");
	}

	void free(T& obj) {
		for (size_t i = 0; i < m_count; i++) {
			uint8_t* a = m_data.get() + sizeof(T) * i;
			uint8_t* b = reinterpret_cast<uint8_t*>(&obj);
			if (m_isLocked[i] && (m_data.get() + sizeof(T) * i) == reinterpret_cast<uint8_t*>(&obj)) {
				if (std::is_standard_layout<T>()) {
					obj.~T();
				}
				m_isLocked[i] = false;
			}
		}
	}

	T& firstInPool() {
		for (size_t i = 0; i < m_count; i++) {
			if (m_isLocked[i]) {
				return *reinterpret_cast<T*>(m_data.get() + i * sizeof(T));
			}
		}
		throw std::out_of_range("no elements");
	}

	const T& firstInPool() const {
		for (size_t i = 0; i < m_count; i++) {
			if (m_isLocked[i]) {
				return *reinterpret_cast<T*>(m_data.get() + i * sizeof(T));
			}
		}
		throw std::out_of_range("no elements");
	}
};