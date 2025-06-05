// By nothcamo.

#include "gtest/gtest.h"
#include "mathod/mathod.h"

using namespace mathod;

TEST(LERP, function) {
    const auto testFunc = []<std::floating_point T>() {
        const auto tolerance = std::numeric_limits<T>::epsilon();
        const T a(0);
        const T b(10);

        EXPECT_NEAR(util::lerp(a, b, T(0)), a, tolerance);
        EXPECT_NEAR(util::lerp(a, b, T(1)), b, tolerance);
        EXPECT_NEAR(util::lerp(a, b, T(0.5)), T(5), tolerance);
        EXPECT_NEAR(util::lerp(a, b, T(0.3)), T(3), tolerance);
    };

    testFunc.operator()<float>();
    testFunc.operator()<double>();
    testFunc.operator()<long double>();
}
