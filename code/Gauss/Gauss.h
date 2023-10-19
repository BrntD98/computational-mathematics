// Gauss.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <cmath>
#include <iostream>
#include <iomanip>
#include <type_traits>
#include <array>


template<typename A>
struct ArgumentGetter;

template<typename R, typename Arg>
struct ArgumentGetter<R(Arg)> {
    using Argument = Arg;
};

template<typename T>
using Dif = decltype(std::declval<T>() - std::declval<T>());

template<std::size_t N>
struct GaussLegendreQuadrature {
    static constexpr std::array<double, N> x = { -0.5773502692, 0.5773502692 };
    static constexpr std::array<double, N> w = { 1, 1 };
};

template<std::size_t N>
struct GaussKronrodQuadrature {
    static constexpr std::array<double, N> x = { -0.9061798459, -0.5384693101, 0, 0.5384693101, 0.9061798459 };
    static constexpr std::array<double, N> w = { 0.2369268851, 0.4786286705, 0.5688888889, 0.4786286705, 0.2369268851 };
};

template<typename Callable, typename RealType, std::size_t N>
decltype(auto) integrate(
    const Callable& func,
    const typename ArgumentGetter<Callable>::Argument& start,
    const typename ArgumentGetter<Callable>::Argument& end
) {
    RealType sum = 0;
    for (std::size_t i = 0; i < N; ++i) {
        const RealType x = 0.5 * (end - start) * GaussLegendreQuadrature<N>::x[i] + 0.5 * (end + start);
        sum += GaussLegendreQuadrature<N>::w[i] * func(x);
    }
    return 0.5 * (end - start) * sum;
}

template<typename Callable, typename RealType, std::size_t N>
decltype(auto) integrate(
    const Callable& func,
    const typename ArgumentGetter<Callable>::Argument& start,
    const typename ArgumentGetter<Callable>::Argument& end,
    const Dif<typename ArgumentGetter<Callable>::Argument>& dx
) {
    RealType sum = 0;
    for (typename ArgumentGetter<Callable>::Argument x = start; x < end; x += dx) {
        const typename ArgumentGetter<Callable>::Argument x1 = x;
        const typename ArgumentGetter<Callable>::Argument x2 = x + dx;
        sum += integrate<Callable, RealType, N>(func, x1, x2);
    }
    return sum;
}

// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.
