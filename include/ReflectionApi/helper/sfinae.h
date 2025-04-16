#pragma once

#include <iostream>
#include <type_traits>
#include <utility>

namespace ReflectionApi {
namespace SFINAE {

// Структура для проверки наличия оператора <<
template<typename T, typename = void>
struct has_left_shift_operator : std::false_type
{
};

template<typename T>
struct has_left_shift_operator<T, std::void_t<decltype((std::declval<std::ostream&>() << std::declval<T>()))>>
    : std::true_type
{
};

template<typename T>
constexpr bool has_left_shift_operator_v = has_left_shift_operator<T>::value;

// Структура для проверки наличия оператора >>
template<typename T, typename = void>
struct has_right_shift_operator : std::false_type
{
};

template<typename T>
struct has_right_shift_operator<T, std::void_t<decltype((std::declval<std::istream&>() >> std::declval<T&>()))>>
    : std::true_type
{
};

template<typename T>
constexpr bool has_right_shift_operator_v = has_right_shift_operator<T>::value;



} // namespace SFINAE
} // namespace ReflectionApi