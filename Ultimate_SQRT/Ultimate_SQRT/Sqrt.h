#pragma once

#include <cmath>
#include <algorithm>
#include <iterator>

#include <vector>
#include <list>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

#include <type_traits>

#include "SqrtExceptions.h"

// попытка 1:
// 
// 1. Слишком много перегрузок. Можно уложиться всего в три.
// 2. Нет проверки на то, что инстанцировался тип, который является числом.
// 3. Как-то бы надо проверить, что корень от неотрицательного числа берешь что ли :)
// 4. Приходи на семинар, поговорим как и что надо сделать 

// попытка 2:
// Со SFINAE вроде как разобрались.
// Нехорошо наследоваться от stl. В предыдущем семестре должны были про это сказать. Сделай все без наследования от std::false_type. Есть альтернатива с композициейю
// В перегрузке std::forward_list какие-то перевороты зачем-то... Попробуй сделать проще. 

//check if pair
template <typename T>
struct is_pair {
	static constexpr bool value = false;
};

template <typename T, typename U>
struct is_pair<std::pair<T, U>> {
	static constexpr bool value = true;
};

template <typename T>
constexpr bool is_pair_v = is_pair<T>::value;

//check if map
template<typename, typename = void>
struct is_mapping {
	static constexpr bool value = false;
};

template <typename Container>
struct is_mapping<Container, std::enable_if_t<is_pair_v<typename  std::iterator_traits<typename Container::iterator>::value_type>>>{
	static constexpr bool value = true;
};

template <typename T>
constexpr bool is_mapping_v = is_mapping<T>::value;

//sqrt implementation

//for int,double...
template <typename T>
typename std::enable_if_t<!is_mapping_v<T> && !std::is_class<T>::value, T> Sqrt(const T& val) {
	if (!std::is_arithmetic<T>::value) {
		throw badTypeEx();
	}
	if (val < 0) {
		throw negValueEx();
	}
	return (static_cast<T>(std::sqrt(val)));
}

//for maps
template <typename T>
typename std::enable_if_t<is_mapping_v<T>, T> Sqrt(const T& in) {
	T res{};
	std::transform(in.begin(), in.end(), std::inserter(res, res.begin()), [](auto a) {
		a.second = Sqrt(a.second);
		return a; });
	return res;
}

//for vector,set,list...
template <typename T>
typename std::enable_if_t<!is_mapping_v<T> && std::is_class<T>::value , T> Sqrt(const T& in) {
	T res{};
		std::transform(in.begin(), in.end(), std::inserter(res, res.begin()), [](auto a) {return Sqrt(a); });
	return res;
}

template <typename T>
std::forward_list<T> Sqrt(const std::forward_list<T>& in) {
	std::forward_list<T> res{};
	std::for_each(in.begin(), in.end(), [&res](T a) {res.push_front( Sqrt(a)); });
	res.reverse();
	return res;
}
