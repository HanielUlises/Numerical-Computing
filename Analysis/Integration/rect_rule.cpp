#include <iostream>
#include <concepts>
#include <ranges>
#include <vector>
#include <cmath>
#include <functional>

/*
 * Concept enforcing that a callable F can be evaluated at T
 * and returns a value convertible to T.
 * For scalar-valued integrands.
 */
template<typename F, typename T>
concept IntegrableFunction =
    std::regular_invocable<F, T> &&
    std::convertible_to<std::invoke_result_t<F, T>, T>;

/*
 * Enumeration of supported rectangle-rule variants.
 */
enum class RectangleMethod {
    Left,       // f evaluated at left endpoint
    Right,      // f evaluated at right endpoint
    Midpoint    // f evaluated at subinterval midpoint
};

/*
 * Result type returned by numerical integration routines.
 * Stores the computed integral value and the number of
 * function evaluations performed.
 */
template<typename T>
struct RectangleResult {
    T value;
    std::size_t evaluations;
};

/*
 * Numerical integration using the rectangle rule on an arbitrary grid.
 *
 * The integration domain is defined implicitly by a monotone sequence
 * of sample points x_points. Each adjacent pair defines a subinterval.
 *
 * Requirements:
 *  - T must be a floating-point type
 *  - F must satisfy IntegrableFunction<F, T>
 *  - R must be an input range of values convertible to T
 *
 * The algorithm performs exactly one function evaluation per subinterval.
 */
template<
    std::floating_point T,
    typename F,
    std::ranges::input_range R
>
requires IntegrableFunction<F, T>
RectangleResult<T> integrate_rectangle(
    F&& f,
    R&& x_points,
    RectangleMethod method = RectangleMethod::Midpoint
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

    for (; it != last; ++it) {
        T b = *it;
        T h = b - a;
        T fx;

        switch (method) {
            case RectangleMethod::Left:
                fx = std::invoke(f, a);
                break;

            case RectangleMethod::Right:
                fx = std::invoke(f, b);
                break;

            case RectangleMethod::Midpoint:
            default:
                fx = std::invoke(f, (a + b) * T(0.5));
                break;
        }

        integral += h * fx;
        ++evals;
        a = b;
    }

    return { integral, evals };
}

/*
 * Utility function generating a uniformly spaced grid over [a, b].
 *
 * The grid contains n points, including both endpoints.
 * If n < 2, the result degenerates to a single-point grid.
 */
auto uniform_grid = []<std::floating_point T>(T a, T b, std::size_t n)
    -> std::vector<T>
{
    if (n == 0) return {};
    if (n == 1) return { a };

    std::vector<T> points(n);
    T h = (b - a) / T(n - 1);

    std::generate(points.begin(), points.end(),
              [a, h, i = std::size_t{0}]() mutable {
                  return a + T(i++) * h;
              });

    return points;
};

int main()
{

    auto f = [](double x) noexcept -> double {
        return std::sin(x);
    };

    
    // Integrate sin(x) over [0, π] using a uniform grid.
    auto grid = uniform_grid.template operator()<double>(
        0.0, 3.141592653589793, 1000
    );

    auto result_mid =
        integrate_rectangle<double>(f, grid, RectangleMethod::Midpoint);

    std::cout << "∫ sin(x) dx from 0 to π (Midpoint, n=1000)\n";
    std::cout << "Result: " << result_mid.value
              << " (evals: " << result_mid.evaluations << ")\n";
    std::cout << "Error:  " << std::abs(result_mid.value - 2.0) << "\n\n";

    // Rectangle-rule variants on the same grid.
    auto test = [&](RectangleMethod m, const char* name) {
        auto res = integrate_rectangle<double>(f, grid, m);
        std::cout << name << ": " << res.value
                  << " (error: " << std::abs(res.value - 2.0) << ")\n";
    };

    test(RectangleMethod::Left,     "Left     ");
    test(RectangleMethod::Right,    "Right    ");
    test(RectangleMethod::Midpoint, "Midpoint ");

    
    // Integration over a non-uniform, user-specified grid.
    std::vector<double> custom_points =
        { 0.0, 0.1, 0.5, 1.0, 2.0, 3.14159 };

    auto res_custom =
        integrate_rectangle<double>(f, custom_points, RectangleMethod::Midpoint);

    std::cout << "\nCustom grid result: " << res_custom.value << "\n";

    return 0;
}
