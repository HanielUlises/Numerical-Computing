#pragma once
#include "utils.h"

namespace nonlinear_solver {

inline std::optional<SolverResult> bisection(std::function<double(double)> f, double a, double b,
    const SolverOptions& opt = {}) {
        
    double fa = f(a), fb = f(b);
    if (fa * fb >= 0.0) return std::nullopt;

    double c = a, fc = fa;

    for (int iter = 1; iter <= opt.max_iter; ++iter) {
        c = 0.5 * (a + b);
        fc = f(c);

        if (fc == 0.0 || (b - a) * 0.5 <= opt.tol_abs)
            return SolverResult{c, iter, true, std::abs(fc)};

        (fa * fc < 0.0) ? (b = c, fb = fc) : (a = c, fa = fc);
    }
    return SolverResult{c, opt.max_iter, false, std::abs(fc)};
}

}  // namespace nonlinear_solver