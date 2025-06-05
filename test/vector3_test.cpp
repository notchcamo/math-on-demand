// By notchcamo.

#include "gtest/gtest.h"
#include "mathod/mathod.h"

TEST(Vector3Test, Normalize) {
    mathod::Vector3f v1(-1.344f, 999.0f, 9.11f);
    v1.normalize();
    EXPECT_EQ(mathod::util::isEqual(v1.getMagnitude(), 1.0f), true);
}

TEST(Vector3Test, CrossProduct) {
    // The cross product of the x-axis vector and the y-axis vector is the z-axis vector.
    mathod::Vector3f v1(1.0f, 0.0f, 0.0f);
    mathod::Vector3f v2(0.0f, 1.0f, 0.0f);
    mathod::Vector3f cross = v1.cross(v2);
    EXPECT_FLOAT_EQ(cross.getX(), 0.0f);
    EXPECT_FLOAT_EQ(cross.getY(), 0.0f);
    EXPECT_FLOAT_EQ(cross.getZ(), 1.0f);

    // The cross product of the y-axis vector and the x-axis vector is the - z-axis vector.
    mathod::Vector3f cross2 = v2.cross(v1);
    EXPECT_FLOAT_EQ(cross2.getX(), 0.0f);
    EXPECT_FLOAT_EQ(cross2.getY(), 0.0f);
    EXPECT_FLOAT_EQ(cross2.getZ(), -1.0f);

    // The cross product of any vector and the zero vector is the zero vector.
    mathod::Vector3f zero(0.0f, 0.0f, 0.0f);
    mathod::Vector3f cross3 = v1.cross(zero);
    EXPECT_FLOAT_EQ(cross3.getX(), 0.0f);
    EXPECT_FLOAT_EQ(cross3.getY(), 0.0f);
    EXPECT_FLOAT_EQ(cross3.getZ(), 0.0f);

    // The cross product of two parallel vectors is the zero vector.
    mathod::Vector3f v3(2.0f, 0.0f, 0.0f); // v1과 방향이 같음
    mathod::Vector3f cross4 = v1.cross(v3);
    EXPECT_FLOAT_EQ(cross4.getX(), 0.0f);
    EXPECT_FLOAT_EQ(cross4.getY(), 0.0f);
    EXPECT_FLOAT_EQ(cross4.getZ(), 0.0f);

    // The cross product of two vectors is orthogonal to both of them.
    mathod::Vector3f a(1.0f, 2.0f, 3.0f);
    mathod::Vector3f b(4.0f, 5.0f, 6.0f);
    mathod::Vector3f cross5 = a.cross(b);
    EXPECT_EQ(mathod::util::isEqual(cross5.dot(a),0.0f), true);
    EXPECT_EQ(mathod::util::isEqual(cross5.dot(b),0.0f), true);
}

TEST(Vector3Test, DivisionByZero) {
    EXPECT_THROW({
        mathod::Vector3f v1(1.0f, 1.0f, 1.0f);
        v1 /= 0.0f;
    },
        mathod::exception::DivisionByZeroException
    ) << "operator/= test failed.";

    EXPECT_THROW({
        mathod::Vector3f v1(1.0f, 1.0f, 1.0f);
        mathod::Vector3f v2 = v1 / 0.0f;
    },
        mathod::exception::DivisionByZeroException
    ) << "operator/ test failed.";
}
