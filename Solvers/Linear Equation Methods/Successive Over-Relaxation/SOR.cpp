#include <vector>
#include <cmath>
#include <stdexcept>

/*
    Perform one or more iterations of the SOR method to solve A x = b.

    A is given as a dense matrix in row-major form: A[i][j].
    x is the initial guess and is updated in-place.
    b is the right-hand side.
    
    ω (omega) is the relaxation parameter. 
    Classical theory requires 0 < ω < 2 for convergence on SPD matrices.
    
    maxIter is the maximum number of iterations to perform.
    tol is the residual tolerance on ||A x - b||.

    NOTE:
    - This implementation follows the standard component-wise SOR update:
    
        x_i^(k+1) = (1 - ω) x_i^(k)
                    + (ω / a_ii) [ b_i
                        - Σ_{j < i} a_ij x_j^(k+1)
                        - Σ_{j > i} a_ij x_j^(k)
                      ]
    
    - The lower triangular part uses updated values from iteration k+1.
    - The upper triangular part uses old values from iteration k.
*/

void SOR(
    const std::vector<std::vector<double>>& A,
    const std::vector<double>& b,
    std::vector<double>& x,
    double omega,
    int maxIter = 5000,
    double tol = 1e-10
) {
    int n = A.size();
    if (n == 0 || A[0].size() != n)
        throw std::invalid_argument("Matrix A must be square.");

    if (b.size() != n || x.size() != n)
        throw std::invalid_argument("Dimension mismatch.");

    if (omega <= 0.0 || omega >= 2.0)
        throw std::invalid_argument("Relaxation parameter ω must satisfy 0 < ω < 2.");

    std::vector<double> x_old(n);

    for (int iter = 0; iter < maxIter; ++iter) {
        x_old = x; // For upper-triangular evaluations

        // Full SOR sweep
        for (int i = 0; i < n; ++i) {
            double diag = A[i][i];
            if (std::abs(diag) < 1e-14)
                throw std::runtime_error("Zero diagonal entry encountered in SOR.");

            // Gauss–Seidel residual for row i using updated lower entries and old upper entries
            double sigma = 0.0;

            // Contribution from lower triangular part (j < i) — uses updated values x[j]
            for (int j = 0; j < i; ++j)
                sigma += A[i][j] * x[j];

            // Contribution from upper triangular part (j > i) — uses old values x_old[j]
            for (int j = i + 1; j < n; ++j)
                sigma += A[i][j] * x_old[j];

            // SOR update: convex combination of old iterate and Gauss–Seidel update
            x[i] = (1.0 - omega) * x_old[i]
                    + (omega / diag) * (b[i] - sigma);
        }

        // Check convergence using residual norm ||A x - b||
        double resid = 0.0;
        for (int i = 0; i < n; ++i) {
            double s = -b[i];
            for (int j = 0; j < n; ++j)
                s += A[i][j] * x[j];
            resid += s * s;
        }
        resid = std::sqrt(resid);

        if (resid < tol)
            return;
    }
}
