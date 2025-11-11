#include "jacobi_solver.hpp"
#include <vector>

int main() {
    using namespace linear_solver;

    std::vector<std::vector<double>> A = {
        {2, 1, -1, 1},
        {-1, 2, 2, -1},
        {3, 2, -3, 4},
        {1, -1, 1, -2}
    };
    std::vector<double> b = {3, 8, 2, -1};
    std::vector<double> x0 = {3, 3, 3, 3};

    try {
        auto x = jacobi(A, b, x0, 1e-6, 25);
        std::cout << "Solution:\n";
        print_solution(x);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
}