#include "symbolic_diff.h"
#include <iostream>

int main() {
    using namespace symbolic;

    auto x = make_variable("x");
    auto x_squared = x * x;
    auto sin_x = sin(x);
    auto expr = x_squared + sin_x;

    std::cout << "Expresión: " << expr->to_string() << std::endl;

    auto deriv = expr->derivative("x");
    std::cout << "Derivada: " << deriv->to_string() << std::endl;

    auto deriv_simp = deriv->simplify();
    std::cout << "Derivada simplificada: " << deriv_simp->to_string() << std::endl;

    return 0;
}