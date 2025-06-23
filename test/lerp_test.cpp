// By nothcamo.

#include "gtest/gtest.h"
#include "soo/soo.h"

using namespace soo;

TEST(LERP, function_float) {
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

TEST(LERP, function_vector) {
    const auto testFunc = []<std::floating_point T>() {
        const Vector3<T> a(1, 2, 3);
        const Vector3<T> b(4, 5, 6);

        EXPECT_EQ(util::lerp(a, b, T(0)), a);
        EXPECT_EQ(util::lerp(a, b, T(1)), b);
        EXPECT_EQ(util::lerp(a, b, T(0.5)), Vector3<T>(2.5, 3.5, 4.5));
    };

    testFunc.operator()<float>();
    testFunc.operator()<double>();
    testFunc.operator()<long double>();
}

TEST(LERP, invalid_argument) {
    EXPECT_THROW(util::lerp(0.0f, 1.0f, 1.1f), std::invalid_argument);
    EXPECT_THROW(util::lerp(0.0f, 1.0f, -0.5f), std::invalid_argument);
    EXPECT_NO_THROW(util::lerp(0.0f, 1.0f, 0.5f));
}
