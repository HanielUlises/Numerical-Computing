#include <iostream>
#include <cmath>

double df (double z){
    return -2/std::pow(1+z,3);
}

double d2f (double z){
    return  6/std::pow(1+z,4);
}

double d3f (double z){
    return 24/std::pow(1+z,5);
}

// Funcion f(z) = 1/(1+z^2)

int main (){
    double f0 = 1/(std::pow(1, 2.0f));
    double f1 = df(0);
    double f2 = d2f(0);
    double f3 = d3f(0);

    std::cout<<"f(0) = "<< f0 <<std::endl;
    std::cout<<"f'(0) = "<< f1 <<std::endl;
    std::cout<<"f''(0) = "<< f2 <<std::endl;
}