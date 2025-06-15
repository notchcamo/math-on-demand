// By notchcamo.

#pragma once

#include <format>
#include <string>

#include "exception.h"
#include "util.h"

/**
 * @brief Namespace for <b>math</b>-<b>o</b>n-<b>d</b>emand.
 */
namespace mathod {
    /**
     * @brief 3D vector class.
     * @tparam T Type of the components. Must be a floating-point type.
     */
    template <std::floating_point T>
    class Vector3 {
    private:
        T x, y, z;

    public:
        // Constructors.

        Vector3() = default;
        explicit Vector3(const T value) noexcept : x(value), y(value), z(value) {}
        Vector3(const T x, const T y, const T z) noexcept : x(x), y(y), z(z) {}
        Vector3(const Vector3& other) noexcept : x(other.x), y(other.y), z(other.z) {}
        Vector3(Vector3&& other) noexcept : x(std::move(other.x)), y(std::move(other.y)), z(std::move(other.z)) {}

        ~Vector3() noexcept = default;

        // Operator Overloadings.

        Vector3& operator=(const Vector3& rhs) noexcept {
            if (*this != rhs) {
                x = rhs.x;
                y = rhs.y;
                z = rhs.z;
            }

            return *this;
        }
        Vector3& operator=(Vector3&& rhs) noexcept
        {
            if (*this != rhs)
            {
                x = std::move(rhs.x);
                y = std::move(rhs.y);
                z = std::move(rhs.z);
            }

            return *this;
        }
        Vector3 operator+(const Vector3& rhs) const noexcept {
            return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
        }
        Vector3 operator-(const Vector3& rhs) const noexcept {
            return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
        }
        Vector3 operator*(const T scalar) const noexcept {
            return Vector3(x * scalar, y * scalar, z * scalar);
        }
        Vector3 operator/(const T scalar) const {
            if (util::isZero(scalar)) {
                throw exception::DivisionByZero();
            }

            const T inv_scalar{static_cast<T>(1.0) / scalar};
            return Vector3(x * inv_scalar, y * inv_scalar, z * inv_scalar);
        }
        Vector3& operator+=(const Vector3& rhs) noexcept {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }
        Vector3 operator-=(const Vector3& rhs) noexcept {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }
        Vector3& operator*=(const T scalar) noexcept {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }
        Vector3& operator/=(const T scalar) {
            if (util::isZero(scalar)) {
                throw exception::DivisionByZero();
            }

            const T inv_scalar{static_cast<T>(1.0) / scalar};
            x *= inv_scalar;
            y *= inv_scalar;
            z *= inv_scalar;
            return *this;
        }
        bool operator==(const Vector3& rhs) const {
            return util::isEqual(x, rhs.x) &&
                util::isEqual(y, rhs.y) &&
                util::isEqual(z, rhs.z);
        }

        // Getters & Setters

        T getX() const noexcept { return x; }
        T getY() const noexcept { return y; }
        T getZ() const noexcept { return z; }

        void setX(const T value) noexcept { x = value; }
        void setY(const T value) noexcept { y = value; }
        void setZ(const T value) noexcept { z = value; }

        // Other methods.

        /**
         * @return String formatted as "[x, y, z]".
         */
        std::string toString() const {
            return std::format("[{:f}, {:f}, {:f}]", x, y, z);
        }

        /**
         * Use the @ref getMagnitudeSquared "squared version" if you only need relative comparison
         * to avoid the expensive square root operation.
         * @return Magnitude(length) of the vector.
         */
        T getMagnitude() const {
            return std::sqrt(x * x + y * y + z * z);
        }

        /**
         * @return Squared magnitude(length) of the vector.
         */
        T getMagnitudeSquared() const noexcept {
            return x * x + y * y + z * z;
        }

        /**
         * Changes the vector's magnitude to 1.
         */
        void normalize() {
            const T magnitude{getMagnitude()};
            if (util::isZero(magnitude)) {
                return;
            }

            const T inv_magnitude{static_cast<T>(1.0) / magnitude};
            x *= inv_magnitude;
            y *= inv_magnitude;
            z *= inv_magnitude;
        }

        /**
         * @return Normalized vector.
         */
        Vector3 getNormalized() const {
            return Vector3(x, y, z).normalize();
        }

        /**
         * @return Dot product of two vectors.
         */
        T dot(const Vector3& rhs) const noexcept {
            return x * rhs.x + y * rhs.y + z * rhs.z;
        }

        /**
         * @return Cross product of two vectors.
         */
        Vector3 cross(const Vector3& rhs) const noexcept {
            return Vector3(y * rhs.z - z *rhs.y,
                z * rhs.x - x * rhs.z,
                x * rhs.y - y * rhs.x);
        }

        // Static members.

        /**
         * Zero vector.
         */
        inline static const Vector3 ZERO{0, 0, 0};
    };

    // Type aliases.

    /**
     * Type alias for Vector3 with single precision.
     */
    using Vector3f = Vector3<float>;

    /**
     * Type alias for Vector3 with double precision.
     */
    using Vector3d = Vector3<double>;

    /**
     * Type alias for Vector3 with long double precision.
     */
    using Vector3L = Vector3<long double>;
} // namespace mathod.
