#include "euler.h"

int main() {
    int number;
    std::cout << "Enter the number of terms in the series: ";
    std::cin >> number;
    std::cout<<std::endl;

    double e_approximation = approach(number);
    std::cout << "Approximation of e after " << number << " terms: " << e_approximation << std::endl;

    return 0;
}