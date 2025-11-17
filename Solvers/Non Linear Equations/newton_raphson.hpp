#pragma once
#include "utils.h"

namespace nonlinear_solver {

inline std::optional<SolverResult> newton_raphson(std::function<double(double)> f, std::function<double(double)> df,
    double x0,
    const SolverOptions& opt = {}){
        
    double x = x0;
    double fx = f(x);
    int iter = 0;

    while (std::abs(fx) > opt.tol_abs && iter < opt.max_iter) {
        double dx = df(x);
        if (std::abs(dx) < 1e-14) return std::nullopt;

        double step = fx / dx;
        x -= step;
        fx = f(x);
        ++iter;

        if (std::abs(step) <= opt.tol_abs + opt.tol_rel * std::abs(x))
            return SolverResult{x, iter, true, std::abs(fx)};
    }
    return SolverResult{x, iter, std::abs(fx) <= opt.tol_abs, std::abs(fx)};
}

}  // namespace nonlinear_solver