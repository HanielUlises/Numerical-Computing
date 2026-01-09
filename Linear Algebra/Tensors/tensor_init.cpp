#include <iostream>
#include <unsupported/Eigen/CXX11/Tensor>

int main() {
    // 1. Default construction (uninitialized)
    Eigen::Tensor<float, 3> t1(2, 3, 4);
    
    // 2. Zero initialization
    Eigen::Tensor<float, 2> t2(3, 4);
    t2.setZero();
    
    // 3. Constant initialization
    Eigen::Tensor<double, 3> t3(2, 3, 4);
    t3.setConstant(5.0);
    
    // 4. Random initialization
    Eigen::Tensor<float, 2> t4(3, 3);
    t4.setRandom();
    
    // 5. Initialize from array/pointer
    float data[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    Eigen::TensorMap<Eigen::Tensor<float, 2>> t5(data, 3, 4);
    
    // 6. Initialize with values using TensorMap
    Eigen::Tensor<int, 2> t6(2, 3);
    int vals[] = {1, 2, 3, 4, 5, 6};
    Eigen::TensorMap<Eigen::Tensor<int, 2>> temp(vals, 2, 3);
    t6 = temp;
    
    // 7. Copy construction
    Eigen::Tensor<float, 2> t7 = t2;
    
    // 8. Initialize using lambda/coefficient-wise
    Eigen::Tensor<float, 2> t8(3, 3);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            t8(i, j) = i * 3 + j;
        }
    }
    
    // 9. Initialize from expression
    Eigen::Tensor<float, 2> t9(3, 3);
    t9 = t4 * 2.0f + 1.0f;
    
    // 10. Identity-like initialization (diagonal)
    Eigen::Tensor<float, 2> t10(4, 4);
    t10.setZero();
    for (int i = 0; i < 4; ++i) {
        t10(i, i) = 1.0f;
    }
    
    // Print examples
    std::cout << "Constant tensor (5.0):\n";
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << t3(i, j, 0) << " ";
        }
        std::cout << "\n";
    }
    
    std::cout << "\nTensor from array:\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << t5(i, j) << " ";
        }
        std::cout << "\n";
    }
    
    std::cout << "\nCoefficient-wise initialized:\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << t8(i, j) << " ";
        }
        std::cout << "\n";
    }
    
    return 0;
}