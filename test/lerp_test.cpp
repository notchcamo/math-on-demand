// By nothcamo.

#include "gtest/gtest.h"
#include "mathod/mathod.h"

using namespace mathod;

TEST(LERP, float_test) {
    constexpr auto tolerance = std::numeric_limits<float>::epsilon();
    constexpr float a = 0.0f;
    constexpr float b = 10.0f;

    EXPECT_NEAR(util::lerp(a, b, 0.0f), a, tolerance);
    EXPECT_NEAR(util::lerp(a, b, 1.0f), b, tolerance);
    EXPECT_NEAR(util::lerp(a, b, 0.5f), 5.0f, tolerance);
    EXPECT_NEAR(util::lerp(a, b, 0.3f), 3.0f, tolerance);
}

TEST(LERP, double_test) {
    constexpr auto tolerance = std::numeric_limits<double>::epsilon();
    constexpr double a = 0.0f;
    constexpr double b = 10.0f;

    EXPECT_NEAR(util::lerp(a, b, 0.0), a, tolerance);
    EXPECT_NEAR(util::lerp(a, b, 1.0), b, tolerance);
    EXPECT_NEAR(util::lerp(a, b, 0.5), 5.0, tolerance);
    EXPECT_NEAR(util::lerp(a, b, 0.3), 3.0, tolerance);
}

TEST(LERP, long_double_test) {
    constexpr auto tolerance = std::numeric_limits<long double>::epsilon();
    constexpr long double a = 0.0L;
    constexpr long double b = 10.0L;

    EXPECT_NEAR(util::lerp(a, b, 0.0L), a, tolerance);
    EXPECT_NEAR(util::lerp(a, b, 1.0L), b, tolerance);
    EXPECT_NEAR(util::lerp(a, b, 0.5L), 5.0L, tolerance);
    EXPECT_NEAR(util::lerp(a, b, 0.3L), 3.0L, tolerance);
}
