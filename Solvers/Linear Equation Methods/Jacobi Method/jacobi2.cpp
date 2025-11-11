#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

std::vector<double> jacobi(const std::vector<std::vector<double>>& A, const std::vector<double>& b, std::vector<double> x, int max_iter) {
    int n = A.size();
    std::vector<double> prev_x(n, 0.0);
    std::vector<double> new_x(n, 0.0);
    
    for (int iter = 0; iter < max_iter; ++iter) {
        for (int i = 0; i < n; ++i) {
            prev_x[i] = x[i];
        }

        for (int i = 0; i < n; ++i) {
            double sum = 0.0;
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    sum += A[i][j] * prev_x[j];
                }
            }
            new_x[i] = (b[i] - sum) / A[i][i];
        }
        x = new_x;
    }

    return x;
}

int main() {
    std::vector<std::vector<double>> A = {
        {2, 1, -1, 1},
        {-1, 2, 2, -1},
        {3, 2, -3, 4},
        {1, -1, 1, -2}
    };
    std::vector<double> b = {3, 8, 2, -1};
    std::vector<double> x0 = {3, 3, 3, 3};
    int max_iter = 25;

    std::vector<double> x = jacobi(A, b, x0, max_iter);

    for (int i = 0; i < x.size(); ++i) {
        std::cout << "x" << i+1 << " = " << std::setprecision(10) << x[i] << std::endl;
    }

    return 0;
}
