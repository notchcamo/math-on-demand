// By notchcamo.

#include "gtest/gtest.h"
#include "mathod/mathod.h"

using namespace soo;

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

TEST(Matrix, matrix_multiplication)
{
    const Matrix<double, 2, 3> mat1{
        {1, 2, 3},
        {4, 5, 6}
    };

    const Matrix<double, 3, 2> mat2{
        {7, 8},
        {9, 10},
        {11, 12}
    };

    const Matrix<double, 2, 2> answer{
        {58, 64},
        {139, 154}
    };

    const auto result = mat1 * mat2;

    EXPECT_EQ(result, answer);
}

TEST(Matrix, scalar_multiplication)
{
    Matrix3d mat1{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    const Matrix3d answer{
        {2, 4, 6},
        {8, 10, 12},
        {14, 16, 18}
    };

    EXPECT_EQ(mat1 * 2, answer);

    mat1 *= 2;

    EXPECT_EQ(mat1, answer);
}

TEST(Matrix, vector_multiplication)
{
    const Matrix4d mat{
        {0, -1, 0, 10},
        {1, 0, 0, 20},
        {0, 0, 1, 30},
        {0, 0, 0, 1}
    };

    const Vector3d vec{1, 0, 0};
    const Vector3d answer{10, 21, 30};

    EXPECT_EQ(mat * vec, answer);
}

TEST(Matrix, transpose)
{
    const Matrix<float, 2, 3> mat{
        {1, 2, 3},
        {4, 5, 6}
    };

    const Matrix<float, 3, 2> answer{
        {1, 4},
        {2, 5},
        {3, 6}
    };

    const auto matT = mat.transpose();

    EXPECT_EQ(matT, answer);
}

TEST(Matrix, identity)
{
    const Matrix2d mat2x2{
        {1, 0},
        {0, 1}
    };
    const Matrix3f mat3x3{
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    EXPECT_EQ(mat2x2, Matrix2d::createIdentity());
    EXPECT_EQ(mat3x3, Matrix3f::createIdentity());

    const Matrix2L mat1{
        {1, 2},
        {3, 4}
    };

    EXPECT_EQ(mat1, mat1 * Matrix2L::createIdentity());
}

TEST(Matrix, inverse)
{
    // 2 x 2
    const Matrix2L mat1{
        {2, 1},
        {1, 3}
    };
    const Matrix2L ans1{
        {0.6, -0.2},
        {-0.2, 0.4}
    };

    EXPECT_EQ(mat1.inverse2x2(), ans1);
    EXPECT_EQ(mat1.inverseNxN(), ans1);
    EXPECT_EQ(Matrix2L::createIdentity().inverse2x2(), Matrix2L::createIdentity());
    EXPECT_EQ(Matrix2L::createIdentity().inverseNxN(), Matrix2L::createIdentity());

    // 3 x 3
    const Matrix3d mat2{
        {1, 2, 3},
        {0, 1, 4},
        {5, 6, 0}
    };
    const Matrix3d ans2{
        {-24, 18, 5},
        {20, -15, -4},
        {-5, 4, 1}
    };

    EXPECT_EQ(mat2.inverse3x3(), ans2);
    EXPECT_EQ(mat2.inverseNxN(), ans2);
    EXPECT_EQ(Matrix3d::createIdentity().inverse3x3(), Matrix3d::createIdentity());
    EXPECT_EQ(Matrix3d::createIdentity().inverseNxN(), Matrix3d::createIdentity());

    // 4 x 4
    Matrix4L mat3 = Matrix4L::createIdentity();
    EXPECT_EQ(mat3.inverseNxN(), mat3);

    mat3 = {
        {5, 6, 6, 8},
        {2, 2, 2, 8},
        {6, 6, 2, 8},
        {2, 3, 6, 7}
    };
    const Matrix4L ans3{
        {-17, -9, 12, 16},
        {17, 8.75, -11.75, -16},
        {-4, -2.25, 2.75, 4},
        {1, 0.75, -0.75, -1}
    };
    EXPECT_EQ(mat3.inverseNxN(), ans3);
}
