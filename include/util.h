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
} // namespace mathod::util.
