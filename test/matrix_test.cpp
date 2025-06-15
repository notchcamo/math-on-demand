// By notchcamo.

#include "gtest/gtest.h"
#include "mathod/mathod.h"

using namespace mathod;

TEST(Matrix, operator_array)
{
    Matrix3d mat1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    EXPECT_EQ(mat1[0][0], 1);
    EXPECT_EQ(mat1[1][1], 5);
    EXPECT_EQ(mat1[2][2], 9);

    EXPECT_THROW(
        {
            mat1[5];
        },
        std::out_of_range
    );
    EXPECT_NO_THROW(
        {
            mat1[2];
        }
    );
}

TEST(Matrix, addition)
{
    Matrix4d mat1 = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    const Matrix4d mat2 = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    const Matrix4d answer = {
        {2, 4, 6, 8},
        {10, 12, 14, 16},
        {18, 20, 22, 24},
        {26, 28, 30, 32}
    };

    EXPECT_EQ(mat1 + mat2, answer);

    mat1 += mat2;

    EXPECT_EQ(mat1, answer);
}

TEST(Matrix, subtraction)
{
    Matrix4d mat1{
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    const Matrix4d mat2{
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    const Matrix4d answer{};

    EXPECT_EQ(mat1 - mat2, answer);

    mat1 -= mat2;

    EXPECT_EQ(mat1, answer);
}
