// interpolant.cpp: определяет точку входа для приложения.
//

#include "interpolant.h"
#include <vector>
#include <iostream>
#include <cmath>

int main() {
    // Генерация узлов интерполяции и значений функции
    std::vector<double> nodes = { 0, 0.03125, 0.0625 };
    std::vector<double> y_values = { 1, std::exp(0.03125), std::exp(0.0625) };

    // Создание объекта интерполянта Ньютона
    NewtonInterpolator interpolator(nodes, y_values);

    // Вычисление значения интерполяционного многочлена в точках отрезка [0,2]
    std::cout << "p(3) = " << interpolator.interpolate(0.0) << std::endl;
    std::cout << "p(4) = " << interpolator.interpolate(4.0) << std::endl;
    std::cout << "p(5) = " << interpolator.interpolate(5.0) << std::endl;

    // Нахождение максимального модуля разности между интерполянтом и функцией
    double max_err = max_error(interpolator);
    std::cout << "Max error: " << max_err << std::endl;




    const double PI = 3.141592653589793;

    // Генерация узлов интерполяции и значений функции для Чебышевского расположения узлов
    std::vector<double> nodes_chebyshev(3);
    for (int i = 0; i < nodes_chebyshev.size(); i++) {
        nodes_chebyshev[i] = 1 - std::cos((2 * i + 1) * PI / (2 * nodes_chebyshev.size()));
    }
    std::vector<double> y_values_chebyshev = { 1, std::exp(0.03125), std::exp(0.0625) };

    // Создание объекта интерполянта Ньютона
    NewtonInterpolator interpolator_chebyshev(nodes_chebyshev, y_values_chebyshev);

    // Вычисление значения интерполяционного многочлена в 3, 4, 5 точках отрезка [0,2]
    //std::cout << "p(3) = " << interpolator_chebyshev.interpolate(3.0) << std::endl;
    //std::cout << "p(4) = " << interpolator_chebyshev.interpolate(4.0) << std::endl;
    //std::cout << "p(5) = " << interpolator_chebyshev.interpolate(5.0) << std::endl;

    // Нахождение максимального модуля разности между интерполянтом и функцией
    double max_err_chebyshev = max_error(interpolator_chebyshev);
    std::cout << "Max error (Chebyshev nodes): " << max_err_chebyshev << std::endl;

    return 0;
}