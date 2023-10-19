// Spline.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <type_traits>

// класс для работы с трехдиагональной матрицей /
template<typename Type>
class ThreeDiagonalMatrix {
    std::vector<Type> m_upper;
    std::vector<Type> m_main;
    std::vector<Type> m_lower;

public:
    ThreeDiagonalMatrix(std::size_t size) :
        m_upper(size - 1), m_main(size), m_lower(size - 1) {}

    Type& upper(std::size_t i) { return m_upper[i]; }
    Type& main(std::size_t i) { return m_main[i]; }
    Type& lower(std::size_t i) { return m_lower[i]; }

    const Type& upper(std::size_t i) const { return m_upper[i]; }
    const Type& main(std::size_t i) const { return m_main[i]; }
    const Type& lower(std::size_t i) const { return m_lower[i]; }

    std::size_t size() const { return m_main.size(); }
};

template<typename numeratorType, typename denominatorType>
using DivisType = decltype(std::declval<numeratorType>() / std::declval<denominatorType>());

// Функция для решения метода прогонки 
template<typename mType, typename cType>
std::vector<DivisType<cType, mType>> solve(const ThreeDiagonalMatrix<mType>& matrix,
    const std::vector<cType>& column)
{
    std::size_t n = matrix.size();

    std::vector<DivisType<cType, mType>> alpha(n);
    std::vector<DivisType<cType, mType>> beta(n);

    alpha[0] = 0;
    beta[0] = 0;

    for (std::size_t i = 1; i < n; ++i) {
        DivisType<mType, mType> a = matrix.lower(i - 1);
        DivisType<mType, mType> b = matrix.main(i - 1);
        DivisType<mType, mType> c = matrix.upper(i - 1);
        DivisType<cType, mType> f = column[i - 1];

        DivisType<mType, mType> m = b - a * alpha[i - 1];
        alpha[i] = c / m;
        beta[i] = (a * beta[i - 1] + f) / m;
    }

    std::vector<DivisType<cType, mType>> x(n);
    x[n - 1] = beta[n - 1];

    for (std::size_t i = n - 2; i != static_cast<std::size_t>(-1); --i) {
        x[i] = alpha[i + 1] * x[i + 1] + beta[i + 1];
    }

    return x;
}

/**
* xType - тип аргумента x.
* yType - тип значения функции y
*/
template<typename xType, typename yType>
class CubicSpline {
    std::vector<xType> m_points; // Значения x
    std::vector<yType> m_values; // значения y

    std::vector<DivisType<yType, xType>> m_a; // коэффициенты a в уравнениях сплайнов
    std::vector<DivisType<yType, xType>> m_b; // коэффициенты b в уравнениях сплайнов
    std::vector<DivisType<yType, xType>> m_c; // коэффициенты c в уравнениях сплайнов
    std::vector<DivisType<yType, xType>> m_d; // коэффициенты d в уравнениях сплайнов

public:
    CubicSpline(const std::vector<xType>& points, const std::vector<yType>& values) :
        m_points(points), m_values(values)
    {
        std::size_t n = points.size();

        ThreeDiagonalMatrix<DivisType<yType, xType>> matrix(n);
        std::vector<DivisType<yType, xType>> column(n);

        // Заполняем матрицу и столбец правых частей
        for (std::size_t i = 1; i < n - 1; ++i) {
            DivisType<yType, xType> h1 = points[i] - points[i - 1];
            DivisType<yType, xType> h2 = points[i + 1] - points[i];
            DivisType<yType, xType> f1 = (values[i] - values[i - 1]) / h1;
            DivisType<yType, xType> f2 = (values[i + 1] - values[i]) / h2;

            matrix.lower(i - 1) = h1;
            matrix.main(i) = 2 * (h1 + h2);
            matrix.upper(i) = h2;
            column[i] = 3 * (f1 * h2 + f2 * h1);
        }

        // Решаем систему методом прогонки
        std::vector<DivisType<yType, xType>> m = solve(matrix, column);

        // Вычисляем коэффициенты сплайнов
        m_a.resize(n - 1);
        m_b.resize(n - 1);
        m_c.resize(n - 1);
        m_d.resize(n - 1);

        for (std::size_t i = 0; i < n - 1; ++i) {
            DivisType<yType, xType> h = points[i + 1] - points[i];

            m_a[i] = values[i];
            m_b[i] = (values[i + 1] - values[i]) / h - h * (m[i + 1] + 2 * m[i]) / 3;
            m_c[i] = m[i];
            m_d[i] = (m[i + 1] - m[i]) / (3 * h);
        }
    }

    yType interpolate(const xType& x) const noexcept {
        std::size_t n = m_points.size();

        if (x <= m_points.front()) {
            return m_values.front();
        }
        else if (x >= m_points.back()) {
            return m_values.back();
        }
        else {
            std::size_t i = 0;
            while (i < n - 1 && x > m_points[i + 1]) {
                ++i;
            }

            DivisType<yType, xType> h = x - m_points[i];

            return m_a[i] + m_b[i] * h + m_c[i] * h * h + m_d[i] * h * h * h;
        }
    }
};

