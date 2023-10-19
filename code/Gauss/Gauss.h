// Gauss.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <cmath>
#include <iostream>
#include <iomanip>
#include <type_traits>

template<typename A>
struct ArgumentGetter;

template<typename R, typename Arg>
struct ArgumentGetter<R(Arg)> {
    using Argument = Arg;
};

template<typename T>
using Dif = decltype(std::declval<T>() - std::declval<T>());

// Квадратура Гаусса с 2 узлами
template<typename RealType>
struct GaussQuadrature2 {
    static constexpr std::array<RealType, 2> nodes = { -0.57735026919, 0.57735026919 };
    static constexpr std::array<RealType, 2> weights = { 1.0, 1.0 };
};

// Квадратура Гаусса с 4 узлами
template<typename RealType>
struct GaussQuadrature4 {
    static constexpr std::array<RealType, 4> nodes = { -0.8611363116, -0.3399810436, 0.3399810436, 0.8611363116 };
    static constexpr std::array<RealType, 4> weights = { 0.3478548451, 0.6521451549, 0.6521451549, 0.3478548451 };
};

// Функция производит интегрирование на одном отрезке с использованием квадратур Гаусса
template<typename Callable, typename RealType, std::size_t N>
decltype(auto) integrate(const Callable& func,
    const typename ArgumentGetter<Callable>::Argument& start,
    const typename ArgumentGetter<Callable>::Argument& end) {

    std::array<RealType, N> nodes;
    std::array<RealType, N> weights;

    // Выбираем квадратуру Гаусса с N узлами
    if constexpr (N == 2) {
        nodes = GaussQuadrature2<RealType>::nodes;
        weights = GaussQuadrature2<RealType>::weights;
    }
    else if constexpr (N == 4) {
        nodes = GaussQuadrature4<RealType>::nodes;
        weights = GaussQuadrature4<RealType>::weights;
    }

    RealType integral = 0.0;

    for (std::size_t i = 0; i < N; ++i) {
        RealType x = ((end - start) * nodes[i] + (end + start)) / 2.0;
        integral += weights[i] * func(x);
    }

    return integral * (end - start) / 2.0;
}

// Функция производит интегрирование, разбивая отрезок на подотрезки длиной не более dx
template<typename Callable, typename RealType, std::size_t N>
decltype(auto) integrate(const Callable& func,
    const typename ArgumentGetter<Callable>::Argument& start,
    const typename ArgumentGetter<Callable>::Argument& end,
    const Dif<typename ArgumentGetter<Callable>::Argument>& dx) {

    RealType result = 0.0;
    typename ArgumentGetter<Callable>::Argument left = start;
    typename ArgumentGetter<Callable>::Argument right = start + dx;

    while (right <= end) {
        result += integrate<Callable, RealType, N>(func, left, right);
        left = right;
        right += dx;
    }

    // Рассмотрим последний подотрезок, длина которого может быть меньше dx
    if (right > end && left < end) {
        result += integrate<Callable, RealType, N>(func, left, end);
    }

    return result;
}


// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.
