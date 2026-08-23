#include <iostream>
#include <fstream>
#include <cmath>

// Funcion f(z) = e^(e^z)

// Derivada de f(z) = e^(e^z)
double df(double z) {
    return exp(exp(z)) * exp(z);
}

// Segunda derivada de f(z)
double d2f(double z) {
    return exp(exp(z)) * (exp(z) + exp(2 * z));
}

// Tercera derivada de f(z)
double d3f(double z) {
    return exp(3*z+exp(z)) + 3*(exp(2*z+exp(z))) + exp(z + exp(z));
}

int main() {
    // Se evalua cada derivada en z=0
    double f0 = exp(1);
    double f1 = df(0);
    double f2 = d2f(0);
    double f3 = d3f(0);

    double cf0 = f0 / exp(1);
    double cf1 = f1 / exp(1);
    double cf2 = f2 / exp(1);
    double cf3 = f3 / exp(1);

    std::cout << "f(0) = " << cf0 << "e" << std::endl;
    std::cout << "f'(0) = " << cf1 << "e" << std::endl;
    std::cout << "f''(0) = " << cf2 << "e" << std::endl;
    std::cout << "f'''(0) = " << cf3 << "e"  << std::endl;

    std::ofstream dataFile("data.txt");

    // Data for GNUPlot
    for(double z = -2; z <= 2; z += 0.01) {
        double val_f = exp(exp(z));
        double val_df = df(z);
        double val_d2f = d2f(z);
        double val_d3f = d3f(z);

        dataFile << z << " " << val_f << " " << val_df << " " << val_d2f << " " << val_d3f << std::endl;
    }

    dataFile.close();
    return 0;
}