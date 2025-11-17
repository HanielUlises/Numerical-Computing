#pragma once
#include "../utils.h"

namespace nonlinear_solver {

// Classical regula falsi: linear interpolation on [a,b] with
// f(a) f(b) < 0. Guarantees that each iterate remains bracketed.
// Convergence is linear and often slow; stagnation occurs if one
// endpoint becomes "sticky" (the Illinois modification corrects this).

static std::optional<SolverResult>
regula_falsi(std::function<double(double)> f,
             double a, double b,
             const SolverOptions& opt = {})
{
    double fa = f(a);
    double fb = f(b);
    if (fa * fb >= 0.0) return std::nullopt;

    double c = a;
    double fc = fa;

    for (int iter = 1; iter <= opt.max_iter; ++iter) {

        // Secant step while keeping bracket
        c = (fa * b - fb * a) / (fa - fb);
        fc = f(c);

        if (is_converged(b, c, opt) || std::abs(fc) <= opt.tol_abs)
            return SolverResult{c, iter, true, std::abs(fc)};

        // Keep the root inside bracket
        if (fa * fc < 0.0) {
            b = c; fb = fc;
        } else {
            a = c; fa = fc;
        }
    }

    return SolverResult{c, opt.max_iter, false, std::abs(fc)};
}

} // namespace nonlinear_solver
