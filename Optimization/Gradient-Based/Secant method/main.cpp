// main.cpp

#include "secant.h"
#include <iostream>

int main() {
    std::cout << "Testing with f(x) = x³ - 4x - 9:\n";
    secantMethod(cubic, 2.0f, 3.0f, 10, 0.0001f);

    std::cout << "\nTesting with f(x) = x² - 2:\n";
    secantMethod([](float x) { return x * x - 2; }, 1.0f, 2.0f, 10, 0.0001f);

    std::cout << "\nTesting with static iteration limit (5 iterations):\n";
    SecantMethodStatic<5, decltype(cubic), float>::apply(cubic, 2.0f, 3.0f, 0.0001f);

    return 0;
}