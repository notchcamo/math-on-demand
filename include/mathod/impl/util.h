// By notchcamo.

#pragma once

#include <limits>

/**
 * @brief Namespace for utility functions.
 */
namespace mathod::util {
    /**
     * @tparam T Arithmetic types only.
     * @return True if the given values are nearly equal.
     */
    template <typename T>
    requires std::is_arithmetic_v<T>
    bool isEqual(const T a, const T b, const T tolerance = std::numeric_limits<T>::epsilon()) {
        return std::abs(a - b) < tolerance;
    }

    /**
     * @tparam T Arithmetic types only.
     * @return True if the given value is nearly zero.
     */
    template <typename T>
    requires std::is_arithmetic_v<T>
    bool isZero(const T num, const T tolerance = std::numeric_limits<T>::epsilon()) {
        return isEqual(num, static_cast<T>(0), tolerance);
    }

    /**
     * Linear interpolation between two values.
     * @param a First value.
     * @param b Second value.
     * @param alpha Interpolation factor (0.0 ~ 1.0).
     * @tparam T Floating-point type.
     * @return Weighted average of a and b.
     */
    template <std::floating_point T>
    T lerp(const T a, const T b, const T alpha) {
        return (static_cast<T>(1.0) - alpha) * a + alpha * b;
    }
} // namespace mathod::util.
