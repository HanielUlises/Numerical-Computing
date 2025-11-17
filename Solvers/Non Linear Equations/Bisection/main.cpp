#include <iostream>
#include <optional>
#include "bisection.hpp"
#include "utils.h" 

int main() {
    auto f1 = [](double x) {
        return x*x - 2.0;
    };

    nonlinear_solver::SolverOptions opt;
    opt.tol_abs = 1e-12;
    opt.max_iter = 100;

    auto result1 = nonlinear_solver::bisection(f1, 0.0, 2.0, opt);

    if (result1 && result1->converged) {
        std::cout << "=== Test 1 ===\n";
        std::cout << "Root:       " << result1->root << "\n";
        std::cout << "Iterations: " << result1->iterations << "\n";
        std::cout << "Residual:   " << result1->residual << "\n\n";
    } else {
        std::cout << "Bisection failed for test 1.\n";
    }

    auto f2 = [](double x) {
        return std::cos(x) - x;  
    };

    auto result2 = nonlinear_solver::bisection(f2, 0.0, 1.0, opt);

    if (result2 && result2->converged) {
        std::cout << "=== Test 2 ===\n";
        std::cout << "Root:       " << result2->root << "\n";
        std::cout << "Iterations: " << result2->iterations << "\n";
        std::cout << "Residual:   " << result2->residual << "\n";
    } else {
        std::cout << "Bisection failed for test 2.\n";
    }

    return 0;
}
