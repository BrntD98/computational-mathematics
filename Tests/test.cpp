#include "pch.h"

#include <gtest/gtest.h>
#include "newton_interpolator.h"

TEST(NewtonInterpolatorTest, InterpolateTest) {
    std::vector<double> x = { 0.0, 1.0, 2.0, 3.0 };
    std::vector<double> y = { 1.0, 2.0, 1.0, 4.0 };
    NewtonInterpolator interpolator(x, y);
    EXPECT_DOUBLE_EQ(interpolator.interpolate(1.5), 1.5);
    EXPECT_DOUBLE_EQ(interpolator.interpolate(2.5), 2.25);
    EXPECT_DOUBLE_EQ(interpolator.interpolate(0.5), 1.75);
}