#include "pch.h"


#include <gtest/gtest.h>
#include "cubic_spline.hpp"

TEST(CubicSplineTest, InterpolationTest) {
    std::vector<double> x = { 0.0, 1.0, 2.0, 3.0 };
    std::vector<double> y = { 0.0, 1.0, 4.0, 9.0 };
    CubicSpline<double> spline(x, y);

    EXPECT_DOUBLE_EQ(spline.interpolate(1.5), 3.5);
    EXPECT_DOUBLE_EQ(spline.interpolate(2.5), 6.5);
}

TEST(CubicSplineTest, ExtrapolationTest) {
    std::vector<double> x = { 0.0, 1.0, 2.0, 3.0 };
    std::vector<double> y = { 0.0, 1.0, 4.0, 9.0 };
    CubicSpline<double> spline(x, y);

    EXPECT_DOUBLE_EQ(spline.interpolate(-1.0), -2.0);
    EXPECT_DOUBLE_EQ(spline.interpolate(4.0), 16.0);
}

TEST(CubicSplineTest, EdgeCasesTest) {
    std::vector<double> x = { 0.0, 1.0, 2.0, 3.0 };
    std::vector<double> y = { 0.0, 1.0, 4.0, 9.0 };
    CubicSpline<double> spline(x, y);

    EXPECT_DOUBLE_EQ(spline.interpolate(0.0), 0.0);
    EXPECT_DOUBLE_EQ(spline.interpolate(3.0), 9.0);
}

TEST(CubicSplineTest, EmptyVectorsTest) {
    std::vector<double> x = {};
    std::vector<double> y = {};
    EXPECT_THROW(CubicSpline<double> spline(x, y), std::invalid_argument);
}

TEST(CubicSplineTest, DifferentLengthVectorsTest) {
    std::vector<double> x = { 0.0, 1.0, 2.0, 3.0 };
    std::vector<double> y = { 0.0, 1.0, 4.0 };
    EXPECT_THROW(CubicSpline<double> spline(x, y), std::invalid_argument);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}