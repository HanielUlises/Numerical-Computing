#pragma once
#include "trapezoidal_refine.hpp"

namespace numeric::integrate {

template<std::floating_point T>
struct SimpsonResult {
    T value;
    std::size_t evaluations;
};

template<std::floating_point T, typename F>
requires IntegrableFunction<F, T>
SimpsonResult<T> integrate_simpson(
    F&& f,
    T a,
    T b
) noexcept
{
    TrapState<T> T0 {
        (b - a) * (std::invoke(f, a) + std::invoke(f, b)) * T(0.5),
        2
    };

    TrapState<T> T1 = trapezoidal_refine(f, a, b, 1, T0);

    T S = (T(4) * T1.value - T0.value) / T(3);

    return { S, T1.evaluations };
}

}
