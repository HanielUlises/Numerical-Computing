#include <concepts>
#include <ranges>
#include <functional>
#include <cstddef>
#include <stdexcept>

template<typename F, typename T>
concept IntegrableFunction =
    std::regular_invocable<F, T> &&
    std::convertible_to<std::invoke_result_t<F, T>, T>;

template<typename T>
struct SimpsonResult {
    T value;
    std::size_t evaluations;
};

template<
    std::floating_point T,
    typename F,
    std::ranges::random_access_range R
>
requires IntegrableFunction<F, T>
SimpsonResult<T> integrate_simpson(
    F&& f,
    R&& x_points
)
{
    using std::ranges::size;

    const std::size_t n = size(x_points);
    if (n < 3)
        return { T(0), 0 };

    const std::size_t intervals = n - 1;
    if (intervals % 2 != 0)
        throw std::invalid_argument("Simpson rule requires an even number of subintervals");

    T h = x_points[1] - x_points[0];

    T integral = std::invoke(f, x_points[0]) +
                 std::invoke(f, x_points[n - 1]);

    std::size_t evals = 2;

    for (std::size_t i = 1; i < n - 1; ++i) {
        T fx = std::invoke(f, x_points[i]);
        evals += 1;

        integral += (i % 2 == 0 ? T(2) : T(4)) * fx;
    }

    integral *= h / T(3);

    return { integral, evals };
}
