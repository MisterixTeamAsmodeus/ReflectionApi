#pragma once

#include "ReflectionApi/reflectionapi_global.h"

#include <initializer_list>
#include <tuple>

// https://www.fluentcpp.com/2019/03/08/stl-algorithms-on-tuples/

namespace ReflectionApi {
namespace Helper {

namespace Impl {
template<class Tuple, class F, std::size_t... I>
constexpr F REFLECTIONAPI_EXPORT for_each_impl(Tuple&& t, F&& f, std::index_sequence<I...>)
{
    return (void)std::initializer_list<int> { (std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))), 0)... }, f;
}
} // namespace Impl

template<class Tuple, class F>
constexpr F REFLECTIONAPI_EXPORT for_each(Tuple&& t, F&& f)
{
    return Impl::for_each_impl(std::forward<Tuple>(t), std::forward<F>(f),
        std::make_index_sequence<std::tuple_size<std::remove_reference_t<Tuple>>::value> {});
}

template<typename Tuple, typename Predicate, typename Action>
constexpr void REFLECTIONAPI_EXPORT perform_if(Tuple&& tuple, Predicate&& predicate, Action&& action)
{
    for_each(tuple, [&predicate, &action](auto&& value) {
        if(predicate(std::forward<decltype(value)>(value)))
            action(std::forward<decltype(value)>(value));
    });
}

} // namespace Helper
} // namespace ReflectionApi
