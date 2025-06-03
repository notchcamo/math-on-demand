// By notchcamo.

#pragma once

#include <limits>

/**
 * @brief Namespace for utility functions.
 */
namespace mathod::util {
    /**
     * @brief Returns true if the given value is nearly zero.
     * @tparam T Floating-point type.
     */
    template <std::floating_point T>
    bool is_zero(const T value, const T tolerance = std::numeric_limits<T>::epsilon()) {
        return std::abs(value) < tolerance;
    }
} // namespace mathod.
