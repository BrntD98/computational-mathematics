// Gauss.cpp: определяет точку входа для приложения.
//

#include "Gauss.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <type_traits>

int main() {
    // Функция для интегрирования - sin(x)
    auto func = [](double x) { return std::sin(x); };

    double start = 0.0;
    double end = 10.0;

    std::cout << std::left << std::setw(10) << "Step" << std::setw(15) << "Error" << std::endl;

    for (double dx = 0.1; dx >= 1e-6; dx /= 10) {
        double numericalIntegral = integrate<decltype(func), double, 2>(func, start, end, dx);

        // Истинное значение интеграла cos(x) на отрезке [0, 10] = cos(10) - cos(0) = -1 - 1 = -2
        double trueIntegral = -2.0;

        double error = std::abs(numericalIntegral - trueIntegral);

        std::cout << std::left << std::setw(10) << dx << std::setw(15) << error << std::endl;
    }

    return 0;
}