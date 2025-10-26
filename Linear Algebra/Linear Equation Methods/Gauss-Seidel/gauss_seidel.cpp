#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

using Matrix = std::vector<std::vector<double>>;
using Vector = std::vector<double>;

// Solves Ax = b using the Gauss-Seidel method
// A: coefficient matrix (nxn), b: right-hand side (n), x: initial guess/solution (n)
// tol: tolerance for convergence, max_iter: maximum iterations
Vector gaussSeidel(const Matrix& A, const Vector& b, const Vector& x0, double tol = 1e-6, int max_iter = 1000) {
    size_t n = A.size();
    if (n != A[0].size() || n != b.size() || n != x0.size()) {
        throw std::invalid_argument("Matrix and vector dimensions must match.");
    }

    Vector x = x0; 
    Vector x_new = x0; 

    for (int iter = 0; iter < max_iter; ++iter) {
        double max_error = 0.0;

        for (size_t i = 0; i < n; ++i) {
            double sum1 = 0.0; // Sum of A[i][j] * x_new[j] for j < i
            double sum2 = 0.0; // Sum of A[i][j] * x[j] for j > i

            for (size_t j = 0; j < n; ++j) {
                if (j < i) {
                    sum1 += A[i][j] * x_new[j];
                } else if (j > i) {
                    sum2 += A[i][j] * x[j];
                }
            }

            if (std::abs(A[i][i]) < 1e-10) {
                throw std::runtime_error("Zero or near-zero diagonal element encountered.");
            }

            x_new[i] = (b[i] - sum1 - sum2) / A[i][i];

            // Track maximum error
            max_error = std::max(max_error, std::abs(x_new[i] - x[i]));
        }

        x = x_new; // Update solution

        // Check convergence
        if (max_error < tol) {
            std::cout << "Converged after " << iter + 1 << " iterations.\n";
            return x;
        }
    }

    throw std::runtime_error("Gauss-Seidel did not converge within max iterations.");
}

int main() {
    // 4x1 + x2 = 7, x1 + 3x2 = 4
    Matrix A = {{4.0, 1.0}, {1.0, 3.0}};
    Vector b = {7.0, 4.0};
    // Initial guess
    Vector x0 = {0.0, 0.0}; 

    try {
        Vector solution = gaussSeidel(A, b, x0);
        std::cout << "Solution:\n";
        for (size_t i = 0; i < solution.size(); ++i) {
            std::cout << "x[" << i << "] = " << solution[i] << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}