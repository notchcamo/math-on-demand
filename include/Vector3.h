// By notchcamo.

#ifndef VECTOR3_H
#define VECTOR3_H

#include <format>
#include <string>

#include "Util.h"

namespace mod {
    /**
     * @brief 3D vector class.
     * @tparam T Type of the components.
     */
    template <typename T>
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
            return Vector3(x / scalar, y / scalar, z / scalar);
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
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }
        bool operator==(const Vector3& rhs) const {
            return mod::is_zero(x - rhs.x) &&
                mod::is_zero(y - rhs.y) &&
                mod::is_zero(z, rhs.z);
        }

        // Getters & Setters

        T get_x() const { return x; }
        T get_y() const { return y; }
        T get_z() const { return z; }

        void set_x(const T value) { x = value; }
        void set_y(const T value) { y = value; }
        void set_z(const T value) { z = value; }

        // Other methods.

        /**
         * @brief Returns the string formatted as "[x, y, z]".
         */
        std::string to_string() const {
            return std::format("[{:f}, {:f}, {:f}]", x, y, z);
        }

        /**
         * @brief Returns magnitude(length) of the vector.
         */
        T get_magnitude() const {
            return std::sqrt(x * x + y * y + z * z);
        }

        /**
         * @brief Returns squared magnitude(length) of the vector.
         */
        T get_magnitude_squared() const {
            return x * x + y * y + z * z;
        }

        /**
         * @brief Changes the vector's magnitude to 1.
         */
        void normalize() {
            const T magnitude = get_magnitude();
            if (is_zero(magnitude)) {
                return;
            }

            const T inv_magnitude = 1.0f / magnitude;
            x *= inv_magnitude;
            y *= inv_magnitude;
            z *= inv_magnitude;
        }

        /**
         * @brief Returns normalized vector.
         */
        Vector3 get_normalized() const {
            return Vector3(x, y, z).normalize();
        }

        /**
         * @brief Returns the dot product of two vectors.
         */
        T dot(const Vector3& rhs) const {
            return x * rhs.x + y * rhs.y + z * rhs.z;
        }

        /**
         * @brief Returns the cross product of two vectors.
         */
        Vector3 cross(const Vector3& rhs) const {
            return Vector3(y * rhs.z - z *rhs.y,
                z * rhs.x - x * rhs.z,
                x * rhs.y - y * rhs.x);
        }
    };

    using Vector3f = Vector3<float>;
    using Vector3d = Vector3<double>;
} // namespace mod.

#endif //VECTOR3_H
