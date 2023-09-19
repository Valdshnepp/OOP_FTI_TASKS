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


// 1. Слишком много перегрузок. Можно уложиться всего в три.
// 2. Нет проверки на то, что инстанцировался тип, который является числом.
// 3. Как-то бы надо проверить, что корень от неотрицательного числа берешь что ли :)
// 4. Приходи на семинар, поговорим как и что надо сделать 

template<typename T>
T Sqrt(const T& val) {
	return (static_cast<T>(std::sqrt(val)));
}

template <typename T>
std::vector<T> Sqrt(const std::vector<T>& in) {
	std::vector<T> res{};
	std::transform(in.begin(), in.end(), std::back_inserter(res), [](T a) {return Sqrt(a); });
	return res;
}

template <typename T>
std::list<T> Sqrt(const std::list<T>& in) {
	std::list<T> res{};
	std::transform(in.begin(), in.end(), std::back_inserter(res), [](T a) {return Sqrt(a); });
	return res;
}

template <typename T>
std::forward_list<T> Sqrt(const std::forward_list<T>& in) {
	std::forward_list<T> resReversed{};
	std::forward_list<T> res{};
	std::for_each(in.begin(), in.end(), [&resReversed](T a) {resReversed.push_front( Sqrt(a)); });
	std::for_each(resReversed.begin(), resReversed.end(), [&res](T a) {res.push_front(a); });

	return res;
}

template <typename T>
std::set<T> Sqrt(const std::set<T>& in) {
	std::set<T> res{};
	std::transform(in.begin(), in.end(), std::inserter(res,res.begin()), [](T a) {return Sqrt(a); });
	return res;
}

template <typename T>
std::unordered_set<T> Sqrt(const std::unordered_set<T>& in) {
	std::unordered_set<T> res{};
	std::transform(in.begin(), in.end(), std::inserter(res, res.begin()), [](T a) {return Sqrt(a); });
	return res;
}

template <typename K,typename V>
std::unordered_map<K,V> Sqrt(const std::unordered_map<K, V>& in) {
	std::unordered_map<K, V> res{};
	std::transform(in.begin(), in.end(), std::inserter(res, res.begin()), [](auto a) {
		a.second = Sqrt(a.second);
		return a; });
	return res;
}

template <typename K, typename V>
std::map<K, V> Sqrt(const std::map<K, V>& in) {
	std::map<K, V> res{};
	std::transform(in.begin(), in.end(), std::inserter(res, res.begin()), [](auto a) {
		a.second = Sqrt(a.second);
	return a; });
	return res;
}
