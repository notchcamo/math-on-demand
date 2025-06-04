// By notchcamo.

#pragma once

#include <limits>

/**
 * @brief Namespace for utility functions.
 */
namespace mathod::util {
    /**
     * @brief Returns true if the given values are nearly equal.
     * @tparam T Arithmetic types only.
     */
    template <typename T>
    requires std::is_arithmetic_v<T>
    bool isEqual(const T a, const T b, const T tolerance = std::numeric_limits<T>::epsilon()) {
        return std::abs(a - b) < tolerance;
    }
} // namespace mathod.
