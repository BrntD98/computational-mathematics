// Spline.cpp: определяет точку входа для приложения.
//

#include "Spline.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <type_traits>


int main() {
    const double PI = std::acos(-1);

    std::vector<double> x(1000);
    std::vector<double> y(1000);

    for (std::size_t n = 5; n <= 160; n *= 2) {
        CubicSpline<double, double> spline;

        std::vector<double> points(n);
        std::vector<double> values(n);

        for (std::size_t i = 0; i < n; ++i) {
            points[i] = 10.0 * i / (n - 1);
            values[i] = std::exp(points[i]);
        }

        spline = CubicSpline<double, double>(points, values);

        double max_error = 0;

        for (std::size_t i = 0; i < 1000; ++i) {
            x[i] = 10.0 * i / 999;
            y[i] = std::abs(std::exp(x[i]) - spline.interpolate(x[i]));

            if (y[i] > max_error) {
                max_error = y[i];
            }
        }

        double log_n = std::log(n) / std::log(2);
        double log_error = std::log(max_error);

        std::cout << "n = " << n << ", log(error) = " << log_error << std::endl;

        if (n == 5 || n == 40) {
            std::cout << "x\texp(x)\tinterpolant" << std::endl;

            for (std::size_t i = 0; i < 1000; ++i) {
                std::cout << x[i] << "\t" << std::exp(x[i]) << "\t" << spline.interpolate(x[i]) << std::endl;
            }
        }
    }

    return 0;
}

