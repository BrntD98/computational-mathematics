// Derivative.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once
#include <iostream>
#include <array>
#include <cmath>
using namespace std;

#include <array>

template<typename RealType, unsigned int N>
struct DerivativeCoef {
    RealType centralCoef;
    std::array<RealType, N> otherCoefs;
};

template<typename RealType, unsigned int N>
DerivativeCoef<RealType, N> calcDerivativeCoef(const std::array<RealType, N>& points) noexcept {
    DerivativeCoef<RealType, N> result;

    result.centralCoef = 0;
    for (size_t i = 0; i < N; ++i) {
        result.centralCoef += points[i] * (i - (N - 1) / 2.0);
        result.otherCoefs[i] = (i - (N - 1) / 2.0);
    }

    return result;
}

// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.
