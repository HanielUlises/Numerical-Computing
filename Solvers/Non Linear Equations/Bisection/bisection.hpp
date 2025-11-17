#pragma once
#include <concepts>
#include <optional>
#include <cmath>
#include "../utils.h"

namespace nonlinear_solver {

template<std::regular_invocable<double> Func>
    requires std::floating_point<std::invoke_result_t<Func,double>>
inline std::optional<SolverResult>
bisection(Func&& f, double a, double b, const SolverOptions& opt = {})
{
    using std::abs;

    double fa = std::invoke(f, a);
    double fb = std::invoke(f, b);

    // Must bracket a root
    if (fa * fb >= 0.0)
        return std::nullopt;

    double c = a;
    double fc = fa;

    for (int iter = 1; iter <= opt.max_iter; ++iter)
    {
        c = 0.5 * (a + b);
        fc = std::invoke(f, c);

        // Convergence test
        if (fc == 0.0 || 0.5 * (b - a) <= opt.tol_abs) {
            return SolverResult{
                c,
                iter,
                true,
                abs(fc)
            };
        }

        // Reduce interval
        if (fa * fc < 0.0) {
            b  = c;
            fb = fc;
        } else {
            a  = c;
            fa = fc;
        }
    }

    // Not converged
    return SolverResult{
        c,
        opt.max_iter,
        false,
        abs(fc)
    };
}

} // namespace nonlinear_solver
