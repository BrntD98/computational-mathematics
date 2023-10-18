// Derivative.cpp: определяет точку входа для приложения.
//

#include "Derivative.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

double exponential(double x) {
    return std::exp(x);
}

double numericalDerivative(double x, double h, unsigned int N) {
    std::array<double, 5> points = { x - 3*h, x - 2*h, x -  h, x +  h , x + 2*h};
    DerivativeCoef<double, 5> coef = calcDerivativeCoef(points);
    return coef.centralCoef / (2.0 * h);
}

int main() {
    double x = 1.0;
    double h = 1.0;
    double maxH = 1e-15;
     unsigned int N = 5;
    

    std::vector<double> logH, logError;

    while (h >= maxH) {
        double exactDerivative = exponential(x);
        double approxDerivative = numericalDerivative(x, h, N);

        double error = std::abs(exactDerivative - approxDerivative);
        double logErr = std::log10(error);

        logH.push_back(std::log10(h));
        logError.push_back(logErr);

        h /= 10.0;
    }

    std::cout << "Log Error vs. Log H:" << std::endl;
    std::cout << std::setw(10) << "Log H" << std::setw(15) << "Log Error" << std::endl;
    for (size_t i = 0; i < logH.size(); ++i) {
        std::cout << std::setw(10) << logH[i] << std::setw(15) << logError[i] << std::endl;
    }

    return 0;
}