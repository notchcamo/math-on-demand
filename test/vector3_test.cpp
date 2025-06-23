// By notchcamo.

#include "gtest/gtest.h"
#include "soo/soo.h"

using namespace soo;

TEST(Vector3, normalize_non_zero) {
    const auto testFunc = []<std::floating_point T>(){
        Vector3<T> v(3.0, 4.0, 0.0);
        v.normalize();

        const auto tolerance = std::numeric_limits<T>::epsilon();

        EXPECT_NEAR(v.getMagnitude(), T(1), tolerance);
        EXPECT_NEAR(v.getX(), T(0.6), tolerance);
        EXPECT_NEAR(v.getY(), T(0.8), tolerance);
        EXPECT_NEAR(v.getZ(), T(0), tolerance);
    };

    testFunc.operator()<float>();
    testFunc.operator()<double>();
    testFunc.operator()<long double>();
}

TEST(Vector3, cross_product) {
    const auto testFunc = []<std::floating_point T>() {
        Vector3<T> v1(1, 0, 0);
        Vector3<T> v2(0, 1, 0);
        Vector3<T> v3(0, 0, 1);
        Vector3<T> v4(1, 2, 3);
        Vector3<T> v5(4, 5, 6);

        const auto tolerance = std::numeric_limits<T>::epsilon();

        // x X y = z
        Vector3<T> result = v1.cross(v2);
        EXPECT_NEAR(result.getX(), T(0), tolerance);
        EXPECT_NEAR(result.getY(), T(0), tolerance);
        EXPECT_NEAR(result.getZ(), T(1), tolerance);

        // y X z = x
        result = v2.cross(v3);
        EXPECT_NEAR(result.getX(), T(1), tolerance);
        EXPECT_NEAR(result.getY(), T(0), tolerance);
        EXPECT_NEAR(result.getZ(), T(0), tolerance);

        // z X x = y
        result = v3.cross(v1);
        EXPECT_NEAR(result.getX(), T(0), tolerance);
        EXPECT_NEAR(result.getY(), T(1), tolerance);
        EXPECT_NEAR(result.getZ(), T(0), tolerance);

        // Normal case.
        result = v4.cross(v5);
        EXPECT_NEAR(result.getX(), T(2*6 - 3*5), tolerance);
        EXPECT_NEAR(result.getY(), T(3*4 - 1*6), tolerance);
        EXPECT_NEAR(result.getZ(), T(1*5 - 2*4), tolerance);

        // Cross product with itself is a zero vector.
        result = v1.cross(v1);
        EXPECT_EQ(result, Vector3<T>::ZERO);
    };

    testFunc.operator()<float>();
    testFunc.operator()<double>();
    testFunc.operator()<long double>();
}

TEST(Vector3, dot_product) {
    const auto testFunc = []<std::floating_point T>() {
        Vector3<T> v1(1.0, 2.0, 3.0);
        Vector3<T> v2(4.0, 5.0, 6.0);
        Vector3<T> v3(0.0, 0.0, 0.0);
        Vector3<T> v4(-1.0, -2.0, -3.0);
        const auto tolerance = std::numeric_limits<T>::epsilon();

        // Normal case.
        EXPECT_NEAR(v1.dot(v2), T(1*4 + 2*5 + 3*6), tolerance);

        // Dot product with itself.
        EXPECT_NEAR(v1.dot(v1), T(1*1 + 2*2 + 3*3), tolerance);

        // Dot product with zero.
        EXPECT_NEAR(v1.dot(Vector3<T>::ZERO), T(0), tolerance);

        // Dot product with minus vector.
        EXPECT_NEAR(v1.dot(v4), T(1*-1 + 2*-2 + 3*-3), tolerance);
    };

    testFunc.operator()<float>();
    testFunc.operator()<double>();
    testFunc.operator()<long double>();
}

TEST(Vector3, division_by_zero) {
    EXPECT_THROW(
        {
            Vector3f v1(1.0f, 1.0f, 1.0f);
            v1 /= 0.0f;
        },
        exception::DivisionByZero
    ) << "operator/= test failed.";

    EXPECT_THROW(
        {
            Vector3f v1(1.0f, 1.0f, 1.0f);
            Vector3f v2 = v1 / 0.0f;
        },
        exception::DivisionByZero
    ) << "operator/ test failed.";
}
