#pragma once
#include "../utils.h"

namespace nonlinear_solver {

// The secant iteration
//     x_{n+1} = x_n - f(x_n) (x_n - x_{n-1}) / (f(x_n) - f(x_{n-1}))
// arises by replacing f' in Newton’s method with a first-order divided
// difference. Convergence is superlinear (order ≈ 1.618) provided f is
// C^1 in a neighborhood of a simple root and the initial pair straddles
// no singular behavior. Failure modes: near-vanishing denominator or
// iteration entering a region where f loses regularity.
static std::optional<SolverResult>
secant(std::function<double(double)> f,
       double x0, double x1,
       const SolverOptions& opt = {})
{
    double f0 = f(x0);
    double f1 = f(x1);

    for (int iter = 1; iter <= opt.max_iter; ++iter) {

        if (std::abs(f1 - f0) < std::numeric_limits<double>::epsilon())
            return std::nullopt;

        // Secant update formula
        double x2 = x1 - f1 * (x1 - x0) / (f1 - f0);
        double f2 = f(x2);

        // Convergence criteria
        if (is_converged(x1, x2, opt) || std::abs(f2) <= opt.tol_abs)
            return SolverResult{x2, iter, true, std::abs(f2)};

        // Shift window
        x0 = x1; f0 = f1;
        x1 = x2; f1 = f2;
    }

    return SolverResult{x1, opt.max_iter, false, std::abs(f1)};
}

} // namespace nonlinear_solver
