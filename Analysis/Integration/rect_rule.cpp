#include <iostream>
#include <concepts>
#include <ranges>
#include <vector>
#include <cmath>
#include <numeric>
#include <functional>

template<typename F, typename T>
concept IntegrableFunction = std::regular_invocable<F, T> &&
                             std::convertible_to<std::invoke_result_t<F, T>, T>;


// Rectangle Rule Variants
enum class RectangleMethod { Left, Right, Midpoint };

template<typename T>
struct RectangleResult {
    T value;
    std::size_t evaluations;
};

template<
    std::floating_point T,
    IntegrableFunction<T> F,
    std::ranges::input_range R
>
constexpr RectangleResult<T> integrate_rectangle(
    F&& f,
    R&& x_points,  
    RectangleMethod method = RectangleMethod::Midpoint
) noexcept
{
    using std::ranges::begin, std::ranges::end;
    auto first = begin(x_points);
    auto last = end(x_points);

    if (first == last) return { T(0), 0 };

    auto it = first;
    T a = *it;
    ++it;
    if (it == last) return { T(0), 1 }; 

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
        evals += 1; 
        a = b;
    }

    if (method == RectangleMethod::Left || method == RectangleMethod::Right) {
        evals += 1; 
    }

    return { integral, evals };
}

// Helper: Generate uniform grid using ranges
auto uniform_grid = []<std::floating_point T>(T a, T b, std::size_t n) constexpr
    -> std::vector<T>
{
    if (n == 0) return {};
    if (n == 1) return {a};

    std::vector<T> points(n);
    T h = (b - a) / T(n - 1);
    std::ranges::generate(points, [a, h, i = 0]() mutable { return a + i++ * h; });
    return points;
};

int main()
{
    constexpr auto f = [](double x) constexpr noexcept -> double {
        return std::sin(x);
    };

    constexpr auto grid = uniform_grid.template operator()<double>(0.0, 3.1415926535, 1000);
    constexpr auto result_mid = integrate_rectangle(f, grid, RectangleMethod::Midpoint);

    std::cout << "∫ sin(x) dx from 0 to π (Midpoint, n=1000)\n";
    std::cout << "Result: " << result_mid.value << " (evals: " << result_mid.evaluations << ")\n";
    std::cout << "Error:  " << std::abs(result_mid.value - 2.0) << "\n\n";

    auto test = [&](RectangleMethod m, const char* name) {
        auto res = integrate_rectangle(f, grid, m);
        std::cout << name << ": " << res.value
                  << " (error: " << std::abs(res.value - 2.0) << ")\n";
    };

    test(RectangleMethod::Left,      "Left     ");
    test(RectangleMethod::Right,     "Right    ");
    test(RectangleMethod::Midpoint, "Midpoint ");

    std::vector<double> custom_points = {0.0, 0.1, 0.5, 1.0, 2.0, 3.14159};
    auto res_custom = integrate_rectangle(f, custom_points, RectangleMethod::Midpoint);
    std::cout << "\nCustom grid result: " << res_custom.value << "\n";

    return 0;
}