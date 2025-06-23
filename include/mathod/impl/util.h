// By notchcamo.

#pragma once

#include <limits>

/**
 * @brief Namespace for utility functions.
 */
namespace soo::util
{
    /**
     * Used as the default arguments in comparison functions.
     */
    constexpr double DEFAULT_TOLERANCE = 1e-8;

    /**
     * @tparam T Arithmetic types only.
     * @return True if the given values are nearly equal.
     */
    template <typename T>
    requires std::is_arithmetic_v<T>
    bool isEqual(const T a, const T b, const T tolerance = DEFAULT_TOLERANCE)
    {
        return std::abs(a - b) <= tolerance;
    }

    /**
     * Compares elements of two containers.
     * @tparam Range Elements' type must be arithmetic.
     * @return True if given containers' entries are identical.
     */
    template <std::ranges::range Range>
    requires std::is_arithmetic_v<std::ranges::range_value_t<Range>>
    bool isEqual(const Range& a, const Range& b, const std::ranges::range_value_t<Range> tolerance = DEFAULT_TOLERANCE)
    {
        const auto pred = [tolerance](const auto& aVal, const auto& bVal)
        {
            return isEqual(aVal, bVal, tolerance);
        };

        return std::ranges::equal(a, b, pred);
    }

    /**
     * @tparam T Arithmetic types only.
     * @return True if the given value is nearly zero.
     */
    template <typename T>
    requires std::is_arithmetic_v<T>
    bool isZero(const T num, const T tolerance = DEFAULT_TOLERANCE)
    {
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
    T lerp(const T a, const T b, const FP alpha)
    {
        if (alpha < FP(0) || alpha > FP(1))
        {
            throw std::invalid_argument(
                "The alpha must be ranged from 0 to 1, but given value is " + std::to_string(alpha)
            );
        }

        return a * (FP(1) - alpha) + b * alpha;
    }
} // namespace soo::util.
