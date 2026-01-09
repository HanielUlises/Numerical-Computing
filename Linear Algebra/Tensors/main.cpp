#include "tensor_class.hpp"
#include <iostream>

int main() {
    std::cout << "Eigen Tensor Mid-Basic Examples\n\n";

    TensorDemo::run3DTensorDemo();

    TensorDemo::runContractionDemo();

    return 0;
}