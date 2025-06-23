// By notchcamo.

#pragma once

#include <concepts>
#include <array>
#include <string>
#include "soo/impl/vector3.h"

namespace soo
{
    /**
     * @brief Matrix class.
     * @tparam T Type of the entries. Must be a floating-point type.
     * @tparam Row The number of rows.
     * @tparam Col The number of columns.
     */
    template <std::floating_point T, size_t Row, size_t Col>
    requires (Row > 0 && Col > 0)
    class Matrix
    {
    private:
        using ColArray = std::array<T, Col>;
        std::array<ColArray, Row> entries;

    public:
        // Constructors.

        Matrix() : entries{0} {}
        Matrix(const std::initializer_list<std::initializer_list<T>>& list)
        {
            if (list.size() != Row)
            {
                throw std::invalid_argument("Number of rows must be " + std::to_string(Row));
            }

            size_t row = 0;
            for (auto rowIt = std::cbegin(list); rowIt != std::cend(list); ++rowIt, ++row)
            {
                if (rowIt->size() != Col)
                {
                    throw std::invalid_argument("Number of columns must be " + std::to_string(Col));
                }

                size_t col = 0;
                for (auto colIt = std::cbegin(*rowIt); colIt != std::cend(*rowIt); ++colIt, ++col)
                {
                    entries[row][col] = *colIt;
                }
            }
        }

        Matrix(const Matrix& rhs) noexcept : entries(rhs.entries) {}
        Matrix(Matrix&& rhs) noexcept : entries(std::move(rhs.entries)) {}

        ~Matrix() noexcept = default;

        // Operators.

        Matrix& operator=(const Matrix& rhs) noexcept
        {
            if (*this != rhs)
            {
                entries = rhs.entries;
            }

            return *this;
        }

        Matrix& operator=(Matrix&& rhs) noexcept
        {
            if (*this != rhs)
            {
                entries = std::move(rhs.entries);
            }

            return *this;
        }

        ColArray& operator[](const size_t row) noexcept(false)
        {
            if (row >= Row)
            {
                throw std::out_of_range("Max row is " + std::to_string(Row));
            }

            return entries[row];
        }

        const ColArray& operator[](const size_t row) const noexcept(false)
        {
            if (row >= Row)
            {
                throw std::out_of_range("Max row is " + std::to_string(Row));
            }

            return entries[row];
        }

        bool operator==(const Matrix& rhs) const noexcept
        {
            for (int row = 0; row < Row; ++row)
            {
                if (!util::isEqual(entries[row], rhs.entries[row]))
                {
                    return false;
                }
            }

            return true;
        }

        Matrix operator+(const Matrix& rhs) const noexcept
        {
            Matrix newMatrix{};

            newMatrix.forEachEntry([this, &rhs](T& entry, const size_t row, const size_t col)
            {
                entry = entries[row][col] + rhs.entries[row][col];
            });

            return newMatrix;
        }

        Matrix operator-(const Matrix& rhs) const noexcept
        {
            Matrix newMatrix{};

            newMatrix.forEachEntry([this, &rhs](T& entry, const size_t row, const size_t col)
            {
                entry = entries[row][col] - rhs.entries[row][col];
            });

            return newMatrix;
        }

        /**
         * Matrix multiplication.
         * @tparam R RHS matrix's row size
         * @tparam C RHS matrix's column size
         */
        template <size_t R, size_t C>
        Matrix<T, Row, C> operator*(const Matrix<T, R, C>& rhs) const noexcept(false)
        {
            if (Col != R)
            {
                throw std::invalid_argument("The number of rows must be " + std::to_string(Col));
            }

            Matrix<T, Row, C> newMatrix{};

            newMatrix.forEachEntry([this, &rhs](T& entry, const size_t row, const size_t col)
            {
                for (size_t c = 0; c < Col; ++c)
                {
                    entry += entries[row][c] * rhs[c][col];
                }
            });

            return newMatrix;
        }

        /**
         * Scalar multiplication.
         */
        Matrix operator*(const T val) const noexcept
        {
            Matrix newMatrix{};

            newMatrix.forEachEntry([this, val](T& entry, const size_t row, const size_t col)
            {
                entry = entries[row][col] * val;
            });

            return newMatrix;
        }

        /**
         * Vector multiplication.
         */
        Vector3<T> operator*(const Vector3<T>& rhs) const requires (Row == 4 && Col == 4)
        {
            const T a = entries[0][0], b = entries[0][1], c = entries[0][2], d = entries[0][3];
            const T e = entries[1][0], f = entries[1][1], g = entries[1][2], h = entries[1][3];
            const T i = entries[2][0], j = entries[2][1], k = entries[2][2], l = entries[2][3];
            const T m = entries[3][0], n = entries[3][1], o = entries[3][2], p = entries[3][3];

            const T divisor = m*rhs.x + n*rhs.y + o*rhs.z + p;

            return {
                (a*rhs.x + b*rhs.y + c*rhs.z + d) / divisor,
                (e*rhs.x + f*rhs.y + g*rhs.z + h) / divisor,
                (i*rhs.x + j*rhs.y + k*rhs.z + l) / divisor,
            };
        }

        Matrix& operator+=(const Matrix& rhs) noexcept
        {
            forEachEntry([&rhs](T& entry, const size_t row, const size_t col)
            {
                entry += rhs.entries[row][col];
            });

            return *this;
        }

        Matrix& operator-=(const Matrix& rhs) noexcept
        {
            forEachEntry([&rhs](T& entry, const size_t row, const size_t col)
            {
               entry -= rhs.entries[row][col];
            });

            return *this;
        }

        Matrix& operator*=(const T val) noexcept
        {
            forEachEntry([val](T& entry, const size_t, const size_t)
            {
                entry *= val;
            });

            return *this;
        }

        // Methods.

        constexpr static size_t getRowSize() noexcept { return Row; }
        constexpr static size_t getColSize() noexcept { return Col; }

        constexpr static Matrix createIdentity() noexcept requires (Row == Col)
        {
            Matrix identity{};

            for (size_t i = 0; i < Row; ++i)
            {
                identity[i][i] = T(1);
            }

            return identity;
        }

        /**
         * Do an action for each entry.
         * @tparam Func Params must be (T& entry, const size_t row, const size_t col)
         * @param action Callable that will be invoked for each entry
         */
        template <typename Func>
        requires std::invocable<Func, T&, const size_t, const size_t>
        void forEachEntry(const Func& action)
        {
            for (size_t row = 0; row < Row; ++row)
            {
                for (size_t col = 0; col < Col; ++col)
                {
                    action(entries[row][col], row, col);
                }
            }
        }

        /**
         * @return Transposed matrix of this
         */
        Matrix<T, Col, Row> transpose() const noexcept
        {
            Matrix<T, Col, Row> transposed{};

            transposed.forEachEntry([this](T& entry, const size_t row, const size_t col)
            {
                entry = entries[col][row];
            });

            return transposed;
        }

        /**
         * Only callable on 2 x 2 matrix
         * @return Inverse matrix
         */
        Matrix inverse2x2() const noexcept(false) requires (Row == Col && Row == 2)
        {
            const T a = entries[0][0], b = entries[0][1];
            const T c = entries[1][0], d = entries[1][1];

            const T det = a * d - b * c;

            if (util::isZero(det))
            {
                throw std::domain_error("Matrix is not invertible");
            }

            const T invDet = T(1) / det;

            return {
                {d * invDet, -b * invDet},
                {-c * invDet, a * invDet}
            };
        }

        /**
         * Only callable on 3 x 3 matrix
         * @return Inverse matrix
         */
        Matrix inverse3x3() const noexcept(false) requires (Row == Col && Row == 3)
        {
            const T a = entries[0][0], b = entries[0][1], c = entries[0][2];
            const T d = entries[1][0], e = entries[1][1], f = entries[1][2];
            const T g = entries[2][0], h = entries[2][1], i = entries[2][2];

            const T det = a*(e*i - f*h) - b*(d*i - f*g) + c*(d*h - e*g);

            if (util::isZero(det))
            {
                throw std::domain_error("Matrix is not invertible");
            }

            const T invDet = T(1) / det;

            return {
                {(e*i - f*h) * invDet, (c*h - b*i) * invDet, (b*f - c*e) * invDet},
                {(f*g - d*i) * invDet, (a*i - c*g) * invDet, (c*d - a*f) * invDet},
                {(d*h - e*g) * invDet, (b*g - a*h) * invDet, (a*e - b*d) * invDet},
            };
        }

        /**
         * Using Gauss-Jordan Elimination to get the inverse matrix.
         * inverse2x2 or inverse3x3 functions are recommended for 2x2 or 3x3 matrices.
         * @return Inverse matrix
         */
        Matrix inverseNxN() const noexcept(false) requires (Row == Col)
        {
            const Matrix identity = Matrix::createIdentity();
            std::array<std::array<T, Row*2>, Row> augmented{};

            for (int r = 0; r < Row; ++r)
            {
                for (int c = 0; c < Row; ++c)
                {
                    augmented[r][c] = entries[r][c];
                    augmented[r][c + Row] = identity[r][c];
                }
            }

            for (int i = 0; i < Row; ++i)
            {
                if (util::isZero(augmented[i][i]))
                {
                    bool swapped = false;

                    for (int k = i + 1; k < Row; ++k)
                    {
                        if (!util::isZero(augmented[k][i]))
                        {
                            std::swap(augmented[i], augmented[k]);
                            swapped = true;
                            break;
                        }
                    }

                    if (!swapped)
                    {
                        throw std::domain_error("Matrix is not invertible");
                    }
                }

                const T invPivot = T(1) / augmented[i][i];

                for (int j = i; j < Row * 2; ++j)
                {
                    augmented[i][j] *= invPivot;
                }

                for (int k = 0; k < Row; ++k)
                {
                    if (k != i && !util::isZero(augmented[k][i]))
                    {
                        const T factor = augmented[k][i];

                        for (int j = i; j < Row * 2; ++j)
                        {
                            augmented[k][j] -= factor * augmented[i][j];
                        }
                    }
                }
            }

            Matrix inversed{};

            for (int r = 0; r < Row; ++r)
            {
                for (int c = Row; c < 2 * Row; ++c)
                {
                    inversed[r][c-Row] = augmented[r][c];
                }
            }

            return inversed;
        }
    };

    // Type aliases.

    using Matrix2f = Matrix<float, 2, 2>;
    using Matrix2d = Matrix<double, 2, 2>;
    using Matrix2L = Matrix<long double, 2, 2>;
    using Matrix3f = Matrix<float, 3, 3>;
    using Matrix3d = Matrix<double, 3, 3>;
    using Matrix3L = Matrix<long double, 3, 3>;
    using Matrix4f = Matrix<float, 4, 4>;
    using Matrix4d = Matrix<double, 4, 4>;
    using Matrix4L = Matrix<long double, 4, 4>;
} // namespace soo.
