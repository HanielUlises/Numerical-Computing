#include <cmath>
#include <iostream>
#include <vector>

// Función1: x^2 - y + z - 3 = 0
double func1(double x, double y, double z) {
    return std::pow(x, 2) - y + z - 3;
}

// Función2: e^x + cos(y) - z - 4 = 0
double func2(double x, double y, double z) {
    return std::exp(x) + std::cos(y) - z - 4;
}

// Función3: tan(z) + xy - 1 = 0
double func3(double x, double y, double z) {
    return std::tan(z) + x * y - 1;
}

// Derivada de la función 1 con respecto a x
double dfunc1_dx(double x) {
    return 2 * x;
}

// Derivada de la función 1 con respecto a y
double dfunc1_dy() {
    return -1;
}

// Derivada de la función 1 con respecto a z
double dfunc1_dz() {
    return 1;
}

// Derivada de la función 2 con respecto a x
double dfunc2_dx(double x) {
    return std::exp(x);
}

// Derivada de la función 2 con respecto a y
double dfunc2_dy(double y) {
    return -std::sin(y);
}

// Derivada de la función 2con respecto a z
double dfunc2_dz() {
    return -1;
}

// Derivada de la función 3 con respecto a x
double dfunc3_dx(double y) {
    return y;
}

// Derivada de la función 3 con respecto a y
double dfunc3_dy(double x) {
    return x;
}

// Derivada de la función 3 con respecto a z
double dfunc3_dz(double z) {
    return std::pow(1.0 / std::cos(z), 2);
}

// Matriz Jacobiana
std::vector<std::vector<double>> jacobian(double x, double y, double z) {
    return {
        {dfunc1_dx(x), dfunc1_dy(), dfunc1_dz()},
        {dfunc2_dx(x), dfunc2_dy(y), dfunc2_dz()},
        {dfunc3_dx(y), dfunc3_dy(x), dfunc3_dz(z)}
    };
}

// Inversa de una matriz 3x3
std::vector<std::vector<double>> inverse(std::vector<std::vector<double>> matrix) {
    double a = matrix[0][0];
    double b = matrix[0][1];
    double c = matrix[0][2];
    double d = matrix[1][0];
    double e = matrix[1][1];
    double f = matrix[1][2];
    double g = matrix[2][0];
    double h = matrix[2][1];
    double i = matrix[2][2];

    double det = a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);

    return {
        {(e * i - f * h) / det, (c * h - b * i) / det, (b * f - c * e) / det},
        {(f * g - d * i) / det, (a * i - c * g) / det, (c * d - a * f) / det},
        {(d * h - e * g) / det, (b * g - a * h) / det, (a * e - b * d) / det}
    };
}

// Multiplicación de matrices
std::vector<double> multiply(std::vector<std::vector<double>> matrix, std::vector<double> vec) {
    return {
        matrix[0][0] * vec[0] + matrix[0][1] * vec[1] + matrix[0][2] * vec[2],
        matrix[1][0] * vec[0] + matrix[1][1] * vec[1] + matrix[1][2] * vec[2],
        matrix[2][0] * vec[0] + matrix[2][1] * vec[1] + matrix[2][2] * vec[2]
    };
}

// Método de Newton-Raphson
void newtonRaphson(double x, double y, double z) {
    int max_iter = 100;

    for (int i = 0; i < max_iter; i++) {
        std::vector<double> f = {-func1(x, y, z), -func2(x, y, z), -func3(x, y, z)};
        std::vector<std::vector<double>> J = jacobian(x, y, z);
        std::vector<std::vector<double>> inv_J = inverse(J);

        std::vector<double> delta = multiply(inv_J, f);

        x += delta[0];
        y += delta[1];
        z += delta[2];
    }

    std::cout << "Solución: x = " << x << ", y = " << y << ", z = " << z << std::endl;
}

// Función principal
int main() {
    // Valores iniciales de la suposición
    double x0 = 2.0;
    double y0 = 2.0;
    double z0 = 2.0;

    newtonRaphson(x0, y0, z0);

    return 0;
}
