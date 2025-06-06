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
     * @tparam T Floating-point type.
     * @param a First value.
     * @param b Second value.
     * @param alpha Interpolation factor (0.0 ~ 1.0).
     * @return Weighted average of a and b.
     */
    template <typename T, std::floating_point FP>
    T lerp(const T a, const T b, const FP alpha) {
        if (alpha < FP(0) || alpha > FP(1)) {
            throw std::invalid_argument(
                "The alpha must be ranged from 0 to 1, but given value is " + std::to_string(alpha)
            );
        }

        return a * (FP(1) - alpha) + b * alpha;
    }
} // namespace mathod::util.
