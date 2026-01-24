#include "ComplexSeries.hpp"
#include <cmath>
#include <sstream>
#include <fmt/core.h>

ComplexSeries::ComplexSeries(CoefficientFunction coeff_gen, size_t terms, Complex center)
    : a_n(std::move(coeff_gen)), max_terms(terms), center(center) {
    compute_coefficients();
}

void ComplexSeries::compute_coefficients() {
    cached_coeffs.resize(max_terms);
    for (size_t n = 0; n < max_terms; ++n)
        cached_coeffs[n] = a_n(n);
}

ComplexSeries::Complex ComplexSeries::evaluate(const Complex& z) const {
    Complex sum = 0;
    Complex dz = z - center;
    Complex power = 1.0;

    for (size_t n = 0; n < max_terms; ++n) {
        sum += cached_coeffs[n] * power;
        power *= dz;
    }

    return sum;
}

ComplexSeries::Complex ComplexSeries::partial_sum(const Complex& z, size_t n_terms) const {
    Complex sum = 0;
    Complex dz = z - center;
    Complex power = 1.0;

    for (size_t n = 0; n < std::min(n_terms, max_terms); ++n) {
        sum += cached_coeffs[n] * power;
        power *= dz;
    }

    return sum;
}

double ComplexSeries::radius_of_convergence() const {
    // Cauchy-Hadamard: R = 1 / limsup |a_n|^{1/n}
    double limsup = 0.0;
    for (size_t n = 1; n < max_terms; ++n) {
        double magnitude = std::abs(cached_coeffs[n]);
        limsup = std::max(limsup, std::pow(magnitude, 1.0 / n));
    }
    return (limsup == 0.0) ? std::numeric_limits<double>::infinity() : 1.0 / limsup;
}

std::string ComplexSeries::series_to_string(size_t max_display_terms) const {
    std::ostringstream oss;
    for (size_t n = 0; n < std::min(max_terms, max_display_terms); ++n) {
        oss << fmt::format("({})*(z - z0)^{}\n", cached_coeffs[n], n);
    }
    return oss.str();
}
