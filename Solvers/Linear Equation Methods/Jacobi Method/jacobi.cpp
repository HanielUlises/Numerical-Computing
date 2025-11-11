#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <iomanip>

using Matrix = std::vector<std::vector<double>>;
using Vector = std::vector<double>;

// Generalized Jacobi method for solving Ax = b
// A: coefficient matrix (nxn), b: right-hand side (n), x0: initial guess (n)
// tol: tolerance for convergence, max_iter: maximum iterations
Vector jacobi(const Matrix& A, const Vector& b, const Vector& x0, double tol = 1e-6, int max_iter = 1000) {
    size_t n = A.size();
    
    if (n == 0 || n != A[0].size() || n != b.size() || n != x0.size()) {
        throw std::invalid_argument("Matrix and vector dimensions must match.");
    }

    Vector x = x0; 
    Vector x_new(n, 0.0);

    for (int iter = 0; iter < max_iter; ++iter) {
        double max_error = 0.0;

        for (size_t i = 0; i < n; ++i) {
            if (std::abs(A[i][i]) < 1e-10) {
                throw std::runtime_error("Zero or near-zero diagonal element at row " + std::to_string(i));
            }

            double sum = 0.0;
            for (size_t j = 0; j < n; ++j) {
                if (i != j) {
                    sum += A[i][j] * x[j];
                }
            }
            x_new[i] = (b[i] - sum) / A[i][i];

            // Track maximum error
            max_error = std::max(max_error, std::abs(x_new[i] - x[i]));
        }

        x = x_new; 

        // Check convergence
        if (max_error < tol) {
            std::cout << "Jacobi converged after " << iter + 1 << " iterations.\n";
            return x;
        }
    }

    throw std::runtime_error("Jacobi did not converge within " + std::to_string(max_iter) + " iterations.");
}

void print_(const Vector& x) {
    std::cout << std::fixed << std::setprecision(10);
    for (size_t i = 0; i < x.size(); ++i) {
        std::cout << "x" << i + 1 << " = " << x[i] << "\n";
    }
}

int main() {
    Matrix A = {
        {2, 1, -1, 1},
        {-1, 2, 2, -1},
        {3, 2, -3, 4},
        {1, -1, 1, -2}
    };
    Vector b = {3, 8, 2, -1};
    Vector x0 = {3, 3, 3, 3};
    double tol = 1e-6;
    int max_iter = 25;

    try {
        Vector x = jacobi(A, b, x0, tol, max_iter);
        std::cout << "Solution:\n";
        print_(x);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}