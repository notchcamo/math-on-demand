// By notchcamo.

#pragma once

#include <format>
#include <string>

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
        Vector3(const T x, const T y, const T z) : x(x), y(y), z(z) {}
        Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z) {}

        ~Vector3() = default;

        // Operator Overloadings.

        Vector3 operator+(const Vector3& rhs) const {
            return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
        }
        Vector3 operator-(const Vector3& rhs) const {
            return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
        }
        Vector3 operator*(const T scalar) const {
            return Vector3(x * scalar, y * scalar, z * scalar);
        }
        Vector3 operator/(const T scalar) const {
            const T inv_scalar{static_cast<T>(1.0) / scalar};
            return Vector3(x * inv_scalar, y * inv_scalar, z * inv_scalar);
        }
        Vector3& operator+=(const Vector3& rhs) {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }
        Vector3 operator-=(const Vector3& rhs) {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }
        Vector3& operator*=(const T scalar) {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }
        Vector3& operator/=(const T scalar) {
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

        T getX() const { return x; }
        T getY() const { return y; }
        T getZ() const { return z; }

        void setX(const T value) { x = value; }
        void setY(const T value) { y = value; }
        void setZ(const T value) { z = value; }

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
        T getMagnitudeSquared() const {
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
        T dot(const Vector3& rhs) const {
            return x * rhs.x + y * rhs.y + z * rhs.z;
        }

        /**
         * @return Cross product of two vectors.
         */
        Vector3 cross(const Vector3& rhs) const {
            return Vector3(y * rhs.z - z *rhs.y,
                z * rhs.x - x * rhs.z,
                x * rhs.y - y * rhs.x);
        }
    };

    using Vector3f = Vector3<float>;
    using Vector3d = Vector3<double>;
} // namespace mathod.
