#include <iostream>
#include <cmath>
#include "finite_difference.hpp"

int main() {
    auto f = [](double x) { return std::sin(x); };
    double x = M_PI / 4;
    double h = 1e-3;

    using FD = FiniteDifference<Scheme::Centered, 1, 1>;
    double derivative = FD::differentiate(f, x, h);

    std::cout << "Approximate f'(x): " << derivative << "\n";
    std::cout << "Exact      f'(x): " << std::cos(x) << "\n";
}
