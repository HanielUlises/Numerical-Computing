#pragma once
#include <vector>
#include <cmath>
#include "trapezoidal_refine.hpp"

namespace numeric::integrate {

template<std::floating_point T>
struct RombergResult {
    T value;
    T error;
    std::size_t evaluations;
};

template<std::floating_point T, typename F>
requires IntegrableFunction<F, T>
RombergResult<T> integrate_romberg(
    F&& f,
    T a,
    T b,
    std::size_t max_levels = 6
)
{
    std::vector<std::vector<T>> R(max_levels);

    TrapState<T> state {
        (b - a) * (std::invoke(f, a) + std::invoke(f, b)) * T(0.5),
        2
    };

    R[0].push_back(state.value);

    for (std::size_t k = 1; k < max_levels; ++k) {
        state = trapezoidal_refine(f, a, b, k, state);
        R[k].push_back(state.value);

        for (std::size_t j = 1; j <= k; ++j) {
            T factor = std::pow(T(4), j);
            T value =
                R[k][j - 1] +
                (R[k][j - 1] - R[k - 1][j - 1]) / (factor - T(1));

            R[k].push_back(value);
        }

        T error = std::abs(R[k][k] - R[k - 1][k - 1]);
        if (error < T(1e-12)) {
            return { R[k][k], error, state.evaluations };
        }
    }

    return {
        R.back().back(),
        std::abs(R.back().back() - R[max_levels - 2].back()),
        state.evaluations
    };
}

}
