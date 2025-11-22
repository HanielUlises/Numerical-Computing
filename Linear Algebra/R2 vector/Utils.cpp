#include "Utils.h"
#include <cmath>

template<floating_point T>
constexpr bool nearly_equal(T a, T b, T eps) noexcept
{
    return std::abs(a - b) <= eps;
}

template<floating_point T>
constexpr bool nearly_zero(T a, T eps) noexcept
{
    return std::abs(a) <= eps;
}

template<floating_point T>
constexpr bool nearly_greater_or_equal(T a, T b, T eps) noexcept
{
    return a >= b - eps;
}

template<floating_point T>
constexpr bool nearly_less_or_equal(T a, T b, T eps) noexcept
{
    return a <= b + eps;
}

template<std::equality_comparable T>
constexpr bool is_equal(T a, T b) noexcept
{
    return a == b;
}

template<std::totally_ordered T>
constexpr bool is_greater_or_equal(T a, T b) noexcept
{
    return a >= b;
}

template<std::totally_ordered T>
constexpr bool is_less_or_equal(T a, T b) noexcept
{
    return a <= b;
}

bool is_equal(float a, float b)
{
    return nearly_equal(a, b);
}

bool is_greater_than_or_equal(float a, float b)
{
    return nearly_greater_or_equal(a, b);
}

bool is_less_than_or_equal(float a, float b)
{
    return nearly_less_or_equal(a, b);
}

namespace float_compare {

    constexpr bool equal(float a, float b) noexcept
    {
        return nearly_equal(a, b);
    }

    constexpr bool greater_or_equal(float a, float b) noexcept
    {
        return nearly_greater_or_equal(a, b);
    }

    constexpr bool less_or_equal(float a, float b) noexcept
    {
        return nearly_less_or_equal(a, b);
    }

    constexpr bool zero(float a) noexcept
    {
        return nearly_zero(a);
    }

} // namespace float_compare

template bool nearly_equal<float>(float, float, float) noexcept;
template bool nearly_equal<double>(double, double, double) noexcept;

template bool nearly_zero<float>(float, float) noexcept;
template bool nearly_zero<double>(double, double) noexcept;

template bool is_equal<int>(int, int) noexcept;
template bool is_equal<float>(float, float) noexcept;
template bool is_equal<double>(double, double) noexcept;