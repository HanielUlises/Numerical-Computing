#pragma once

#include <complex>
#include <vector>
#include <functional>
#include <memory>
#include <string>

class ComplexSeries {
public:
    using Complex = std::complex<double>;
    using CoefficientFunction = std::function<Complex(size_t)>;

    ComplexSeries(CoefficientFunction coeff_gen, size_t terms, Complex center = 0.0);
    
    Complex evaluate(const Complex& z) const;
    Complex partial_sum(const Complex& z, size_t n_terms) const;
    double radius_of_convergence() const;
    std::string series_to_string(size_t max_terms = 10) const;

private:
    CoefficientFunction a_n;
    size_t max_terms;
    Complex center;

    std::vector<Complex> cached_coeffs;
    void compute_coefficients();
};
