#include <cmath>
#include <iostream>
#include <vector>

// Funcion1 : x^2 - y - 3 = 0
double func1(double x, double y) {
    return std::pow(x, 2) - y - 3;
}

// Funcion2 : e^x + cos(y) - 4 = 0
double func2(double x, double y) {
    return std::exp(x) + std::cos(y) - 4;
}

// Primera derivada de la funcion 1
double dfunc1_dx(double x) {
    return 2 * x;
}

// Primera derivada de la funcion 2
double dfunc1_dy() {
    return -1;
}

// Derivada de la funcion 2 con respecto a x
double dfunc2_dx(double x) {
    return std::exp(x);
}

// Derivada de la funcion 2 con respecto a y
double dfunc2_dy(double y) {
    return -std::sin(y);
}

// Jacobian matrix
std::vector<std::vector<double>> jacobian(double x, double y) {
    return {{dfunc1_dx(x), dfunc1_dy()}, {dfunc2_dx(x), dfunc2_dy(y)}};
}

// Inverse of 2x2 matrix
std::vector<std::vector<double>> inverse(std::vector<std::vector<double>> matrix) {
    double a = matrix[0][0];
    double b = matrix[0][1];
    double c = matrix[1][0];
    double d = matrix[1][1];

    double det = a * d - b * c;

    return {{d / det, -b / det}, {-c / det, a / det}};
}

// Matrix multiplication
std::vector<double> multiply(std::vector<std::vector<double>> matrix, std::vector<double> vec) {
    return {matrix[0][0] * vec[0] + matrix[0][1] * vec[1], matrix[1][0] * vec[0] + matrix[1][1] * vec[1]};
}

// Newton-Raphson method
void newtonRaphson(double x, double y) {
    int max_iter = 100;

    for (int i = 0; i < max_iter; i++) {
        std::vector<double> f = {-func1(x, y), -func2(x, y)};
        std::vector<std::vector<double>> J = jacobian(x, y);
        std::vector<std::vector<double>> inv_J = inverse(J);

        std::vector<double> delta = multiply(inv_J, f);

        x += delta[0];
        y += delta[1];
    }

    std::cout << "Solucion: x = " << x << ", y = " << y << std::endl;
}

int main() {
    double x0 = 3.0;
    double y0 = 3.0;

    newtonRaphson(x0, y0);

    return 0;
}