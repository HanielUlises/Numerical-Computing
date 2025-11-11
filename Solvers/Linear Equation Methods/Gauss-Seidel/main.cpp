#include "gauss_seidel.hpp"
#include <vector>

int main()
{
    using namespace linear_solver;

    std::vector<std::vector<double>> A = {{4.0, 1.0}, {1.0, 3.0}};
    std::vector<double> b = {7.0, 4.0};
    std::vector<double> x0 = {0.0, 0.0};

    try {
        auto solution = gauss_seidel(A, b, x0, 1e-6, 25);
        std::cout << "Solution:\n";
        print_solution(solution);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
}