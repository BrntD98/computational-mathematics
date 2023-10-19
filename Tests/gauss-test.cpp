#include "pch.h"
#include <gtest/gtest.h>

#include "gauss_quadrature.hpp"

double sin_func(double x) {
    return std::sin(x);
}

TEST(GaussQuadratureTest, GaussLegendreQuadrature) {
    const double expected = 0.4596976941;
    const double result = integrate<decltype(sin_func), double, 2>(sin_func, 0, 10);
    const double error = std::abs(expected - result);
    EXPECT_LE(error, 1e-6);
}

TEST(GaussQuadratureTest, GaussKronrodQuadrature) {
    const double expected = 0.4596976941;
    const double result = integrate<decltype(sin_func), double, 5>(sin_func, 0, 10);
    const double error = std::abs(expected - result);
    EXPECT_LE(error, 1e-12);
}

TEST(GaussQuadratureTest, GaussLegendreQuadratureWithStep) {
    const double expected = 0.4596976941;
    const double result = integrate<decltype(sin_func), double, 2>(sin_func, 0, 10, 0.01);
    const double error = std::abs(expected - result);
    EXPECT_LE(error, 1e-3);
}

TEST(GaussQuadratureTest, GaussKronrodQuadratureWithStep) {
    const double expected = 0.4596976941;
    const double result = integrate<decltype(sin_func), double, 5>(sin_func, 0, 10, 0.01);
    const double error = std::abs(expected - result);
    EXPECT_LE(error, 1e-12);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
