#pragma once

#include <concepts>
#include <type_traits>

inline constexpr float epsilon = 0.000001f;

template<typename T>
concept floating_point = std::is_floating_point_v<T>;

template<floating_point T>
[[nodiscard]] constexpr bool nearly_equal(T a, T b, T eps = T(epsilon)) noexcept;

template<floating_point T>
[[nodiscard]] constexpr bool nearly_zero(T a, T eps = T(epsilon)) noexcept;

template<floating_point T>
[[nodiscard]] constexpr bool nearly_greater_or_equal(T a, T b, T eps = T(epsilon)) noexcept;

template<floating_point T>
[[nodiscard]] constexpr bool nearly_less_or_equal(T a, T b, T eps = T(epsilon)) noexcept;

template<std::equality_comparable T>
[[nodiscard]] constexpr bool is_equal(T a, T b) noexcept;

template<std::totally_ordered T>
[[nodiscard]] constexpr bool is_greater_or_equal(T a, T b) noexcept;

template<std::totally_ordered T>
[[nodiscard]] constexpr bool is_less_or_equal(T a, T b) noexcept;

[[nodiscard]] bool is_equal(float a, float b);                    // uses nearly_equal
[[nodiscard]] bool is_greater_than_or_equal(float a, float b);   // uses tolerance
[[nodiscard]] bool is_less_than_or_equal(float a, float b);      // uses tolerance

namespace float_compare {
    [[nodiscard]] constexpr bool equal              (float a, float b) noexcept;
    [[nodiscard]] constexpr bool greater_or_equal   (float a, float b) noexcept;
    [[nodiscard]] constexpr bool less_or_equal      (float a, float b) noexcept;
    [[nodiscard]] constexpr bool zero               (float a) noexcept;
}