// By notchcamo.

#include "gtest/gtest.h"
#include "vector3.h"
#include "util.h"

TEST(Vector3Test, CrossProduct) {
    // The cross product of the x-axis vector and the y-axis vector is the z-axis vector.
    mathod::Vector3f v1(1.0f, 0.0f, 0.0f);
    mathod::Vector3f v2(0.0f, 1.0f, 0.0f);
    mathod::Vector3f cross = v1.cross(v2);
    EXPECT_FLOAT_EQ(cross.get_x(), 0.0f);
    EXPECT_FLOAT_EQ(cross.get_y(), 0.0f);
    EXPECT_FLOAT_EQ(cross.get_z(), 1.0f);

    // The cross product of the y-axis vector and the x-axis vector is the - z-axis vector.
    mathod::Vector3f cross2 = v2.cross(v1);
    EXPECT_FLOAT_EQ(cross2.get_x(), 0.0f);
    EXPECT_FLOAT_EQ(cross2.get_y(), 0.0f);
    EXPECT_FLOAT_EQ(cross2.get_z(), -1.0f);

    // The cross product of any vector and the zero vector is the zero vector.
    mathod::Vector3f zero(0.0f, 0.0f, 0.0f);
    mathod::Vector3f cross3 = v1.cross(zero);
    EXPECT_FLOAT_EQ(cross3.get_x(), 0.0f);
    EXPECT_FLOAT_EQ(cross3.get_y(), 0.0f);
    EXPECT_FLOAT_EQ(cross3.get_z(), 0.0f);

    // The cross product of two parallel vectors is the zero vector.
    mathod::Vector3f v3(2.0f, 0.0f, 0.0f); // v1과 방향이 같음
    mathod::Vector3f cross4 = v1.cross(v3);
    EXPECT_FLOAT_EQ(cross4.get_x(), 0.0f);
    EXPECT_FLOAT_EQ(cross4.get_y(), 0.0f);
    EXPECT_FLOAT_EQ(cross4.get_z(), 0.0f);

    // The cross product of two vectors is orthogonal to both of them.
    mathod::Vector3f a(1.0f, 2.0f, 3.0f);
    mathod::Vector3f b(4.0f, 5.0f, 6.0f);
    mathod::Vector3f cross5 = a.cross(b);
    EXPECT_EQ(mathod::util::is_zero(cross5.dot(a)), true);
    EXPECT_EQ(mathod::util::is_zero(cross5.dot(b)), true);
}
