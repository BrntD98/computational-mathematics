#include "pch.h"


#include <gtest/gtest.h>
#include "your_code.h"

TEST(DerivativeTest, Test1) {
    double result = calculateDerivative(3, 0.1);
    EXPECT_NEAR(result, std::exp(1), 0.001);
}

TEST(DerivativeTest, Test2) {
    double result = calculateDerivative(3, 0.01);
    EXPECT_NEAR(result, std::exp(1), 0.0001);
}

TEST(DerivativeTest, Test3) {
    double result = calculateDerivative(5, 0.1);
    EXPECT_NEAR(result, std::exp(1), 0.001);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}