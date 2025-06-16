// By notchcamo.

#pragma once

#include <concepts>
#include <array>
#include <string>

namespace mathod
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
                entries = std::move(entries);
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

        Matrix operator*(const T val) const noexcept
        {
            Matrix newMatrix{};

            newMatrix.forEachEntry([this, val](T& entry, const size_t row, const size_t col)
            {
                entry = entries[row][col] * val;
            });

            return newMatrix;
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
    };

    // Type aliases.

    using Matrix3f = Matrix<float, 3, 3>;
    using Matrix3d = Matrix<double, 3, 3>;
    using Matrix3L = Matrix<long double, 3, 3>;
    using Matrix4f = Matrix<float, 4, 4>;
    using Matrix4d = Matrix<double, 4, 4>;
    using Matrix4L = Matrix<long double, 4, 4>;
} // namespace mathod.
