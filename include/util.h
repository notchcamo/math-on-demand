// By notchcamo.

#ifndef UTIL_H
#define UTIL_H

#include <limits>

/**
 * @brief Namespace for utility functions.
 */
namespace mathod::util {
    /**
     * @brief Returns true if the given value is nearly zero.
     */
    template <typename T>
    bool is_zero(const T value, const T tolerance = std::numeric_limits<T>::epsilon()) {
        return std::abs(value) < tolerance;
    }
} // namespace mathod.

#endif //UTIL_H
