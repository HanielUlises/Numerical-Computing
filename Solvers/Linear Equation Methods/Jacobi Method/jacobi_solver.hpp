#pragma once

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace linear_solver {

inline std::vector<double> jacobi(
    const std::vector<std::vector<double>>& A,
    const std::vector<double>& b,
    const std::vector<double>& x0,
    double tol = 1e-6,
    int max_iter = 1000)
{
    const std::size_t n = A.size();
    if (n == 0 || n != A[0].size() || n != b.size() || n != x0.size()) {
        throw std::invalid_argument("Matrix and vector dimensions must match.");
    }

    auto x = x0;
    auto x_new = std::vector<double>(n, 0.0);

    for (int iter = 0; iter < max_iter; ++iter) {
        double max_error = 0.0;

        for (std::size_t i = 0; i < n; ++i) {
            if (std::abs(A[i][i]) < 1e-10) {
                throw std::runtime_error("Zero or near-zero diagonal element at row " +
                                         std::to_string(i));
            }

            double sum = 0.0;
            for (std::size_t j = 0; j < n; ++j) {
                if (i != j) {
                    sum += A[i][j] * x[j];
                }
            }
            x_new[i] = (b[i] - sum) / A[i][i];
            max_error = std::max(max_error, std::abs(x_new[i] - x[i]));
        }

        x = x_new;

        if (max_error < tol) {
            std::cout << "Jacobi converged after " << iter + 1 << " iterations.\n";
            return x;
        }
    }

    throw std::runtime_error("Jacobi did not converge within " + std::to_string(max_iter) + " iterations.");
}

inline void print_solution(const std::vector<double>& x)
{
    std::cout << std::fixed << std::setprecision(10);
    for (std::size_t i = 0; i < x.size(); ++i) {
        std::cout << "x" << i + 1 << " = " << x[i] << '\n';
    }
}

} 