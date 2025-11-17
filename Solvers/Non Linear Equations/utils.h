#pragma once
#include <functional>
#include <optional>
#include <cmath>
#include <limits>

namespace nonlinear_solver {

struct SolverResult {
    double root{};
    int    iterations{};
    bool   converged{};
    double residual{};
};

struct SolverOptions {
    double tol_abs  = 1e-12;
    double tol_rel  = 1e-10;
    int    max_iter = 100;
};

inline bool is_converged(double x_old, double x_new, const SolverOptions& opt)
{
    return std::abs(x_new - x_old) <= opt.tol_abs + opt.tol_rel * std::abs(x_new);
}

}  