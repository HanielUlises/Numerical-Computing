#include "Matrix.h"
#include "newton_raphson.hpp"
#include <iostream>
#include <vector>
#include <functional>  

using MatrixD = Matrix<double>;

int main()
{
    std::vector<double> x0 = {3.0, 3.0};

    auto F_lambda = [&](const std::vector<double>& x) -> MatrixD {
        MatrixD res(2,1);
        res(0,0) = x[0]*x[0] - x[1] - 3.0;
        res(1,0) = std::exp(x[0]) + std::cos(x[1]) - 4.0;
        return res;
    };

    auto J_lambda = [&](const std::vector<double>& x) -> MatrixD {
        MatrixD jac(2,2);
        jac(0,0) = 2*x[0];     jac(0,1) = -1.0;
        jac(1,0) = std::exp(x[0]); jac(1,1) = -std::sin(x[1]);
        return jac;
    };

    std::function<MatrixD(const std::vector<double>&)> F = F_lambda;
    std::function<MatrixD(const std::vector<double>&)> J = J_lambda;

    auto result = newton_raphson(F, J, x0, 1e-12, 50, true);

    std::cout << "\n=== FINAL RESULT ===\n";
    if (result.converged) {
        std::cout << "CONVERGED in " << result.iterations << " iterations!\n";
        std::cout << "x = " << result.solution[0] << "\n";
        std::cout << "y = " << result.solution[1] << "\n";
    } else {
        std::cout << "Failed to converge.\n";
    }

    return 0;
}