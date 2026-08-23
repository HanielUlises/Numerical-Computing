#pragma once
#include <concepts>
#include <functional>
#include <cstddef>

namespace numeric::integrate {

template<typename F, typename T>
concept IntegrableFunction =
    std::regular_invocable<F, T> &&
    std::convertible_to<std::invoke_result_t<F, T>, T>;

template<std::floating_point T>
struct TrapState {
    T value;
    std::size_t evaluations;
};

template<std::floating_point T, typename F>
requires IntegrableFunction<F, T>
TrapState<T> trapezoidal_refine(
    F&& f,
    T a,
    T b,
    std::size_t k,
    TrapState<T> prev
) noexcept
{
    const std::size_t n = std::size_t{1} << (k - 1);
    const T h = (b - a) / T(std::size_t{1} << k);

    T sum = T(0);
    for (std::size_t i = 0; i < n; ++i) {
        sum += std::invoke(f, a + (T(2 * i + 1) * h));
    }

    return {
        prev.value * T(0.5) + h * sum,
        prev.evaluations + n
    };
}

}
