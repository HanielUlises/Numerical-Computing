#include "ComplexSeries.hpp"
#include <iostream>
#include <complex>

int main() {
    using Complex = std::complex<double>;

    // Example: f(z) = Σ z^n / n!
    ComplexSeries series(
        [](size_t n) -> Complex {
            double fact = 1.0;
            for (size_t i = 1; i <= n; ++i)
                fact *= i;
            return 1.0 / fact;
        },
        50  // max terms
    );

    Complex z = 1.0;
    auto value = series.evaluate(z);
    auto r = series.radius_of_convergence();

    std::cout << "Series approximation of exp(z) at z=1: " << value << "\n";
    std::cout << "Radius of convergence: " << r << "\n";
    std::cout << "\nSeries (first few terms):\n" << series.series_to_string();
    
    return 0;
}
