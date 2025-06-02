// By notchcamo.

#ifndef UTIL_H
#define UTIL_H

#include <cstdlib>
#include <limits>

namespace mod {
    /**
     * @brief Returns true if the given value is nearly zero.
     */
    template <typename T>
    bool is_zero(const T value, const T tolerance = std::numeric_limits<T>::epsilon()) {
        return std::abs(value) < tolerance;
    }
} // namespace mod.

#endif //UTIL_H
