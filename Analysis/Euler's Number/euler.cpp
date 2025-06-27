#include "euler.h"

// Recursive approach
double infiniteSeriesRecursive(int number){
    if (number == 0){
        return 1.0; // Special case for the first term in the series
    } else {
        return 1.0 / number * infiniteSeriesRecursive(number - 1);
    }
}

// For loop approach
double infiniteSeriesForLoop(int number) {
    if (number == 0) {
        return 1.0; // Special case for the first term in the series
    } else {
        // The general term for the series is 1/n!
        double term = 1.0;
        for (int i = 1; i <= number; i++) {
            term /= i;
        }
        return term;
    }
}

double approach(int number) {
    double e = 0.0;
    int option;

    do {
        std::cout<<"======= Select an option ======= "<<std::endl;
        std::cout << "1. Calculate 'e' using the for loop approach" << std::endl;
        std::cout << "2. Calculate 'e' using the recursive approach" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> option;
        std::cout<<std::endl;

        switch (option) {
            case 1:
                std::cout <<"\n";
                for (int i = 0; i <= number; i++) {
                    e += infiniteSeriesForLoop(i);
                }
                std::cout << "e calculated using the for loop approach: " << e << std::endl;
                option = 0;
                break;

            case 2:
                for (int i = 0; i <= number; i++) {
                    e += infiniteSeriesRecursive(i);
                }
                std::cout << "e calculated using the recursive approach: " << e << std::endl;
                option = 0;
                break;

            case 0:
                std::cout << "Exiting the program." << std::endl;
                break;

            default:
                std::cout << "Invalid option. Please choose again." << std::endl;
                break;
        }

    } while (option != 0);
    
    return e;
}