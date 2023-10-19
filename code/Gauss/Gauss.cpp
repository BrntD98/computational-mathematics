// Gauss.cpp: определяет точку входа для приложения.
//

#include "Gauss.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <type_traits>

int main() {
    const double ex
    pected = 0.4596976941;
    for (double dx = 1; dx >= 1e-6; dx /= 10) {
        const double result = integrate<decltype(sin_func), double, 5>(sin_func, 0, 10, dx);
        const double error = std::abs(expected - result);
        std::cout << dx << " " << error << std::endl;
    }
    return 0;
}

