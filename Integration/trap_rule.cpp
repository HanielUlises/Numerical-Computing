#include <concepts>
#include <ranges>
#include <functional>
#include <cstddef>

template<typename F, typename T>
concept IntegrableFunction =
    std::regular_invocable<F, T> &&
    std::convertible_to<std::invoke_result_t<F, T>, T>;

template<typename T>
struct TrapezoidalResult {
    T value;
    std::size_t evaluations;
};

template<
    std::floating_point T,
    typename F,
    std::ranges::input_range R
>
requires IntegrableFunction<F, T>
TrapezoidalResult<T> integrate_trapezoidal(
    F&& f,
    R&& x_points
) noexcept
{
    using std::ranges::begin, std::ranges::end;

    auto first = begin(x_points);
    auto last  = end(x_points);

    if (first == last)
        return { T(0), 0 };

    auto it = first;
    T a = *it;
    ++it;

    if (it == last)
        return { T(0), 0 };

    T integral = T(0);
    std::size_t evals = 0;

    T fa = std::invoke(f, a);
    ++evals;

    for (; it != last; ++it) {
        T b  = *it;
        T fb = std::invoke(f, b);
        ++evals;

        T h = b - a;
        integral += h * (fa + fb) * T(0.5);

        a  = b;
        fa = fb;
    }

    return { integral, evals };
}
