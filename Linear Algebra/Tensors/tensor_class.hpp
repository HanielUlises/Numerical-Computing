#ifndef TENSOR_CLASS_HPP
#define TENSOR_CLASS_HPP

#include <unsupported/Eigen/CXX11/Tensor>
#include <iostream>
#include <array>

class TensorDemo {
public:
    static void run3DTensorDemo() {
        std::cout << "=== 3D Tensor Demo (2x3x4 float tensor) ===\n";

        Eigen::Tensor<float, 3> tensor(2, 3, 4);  // Dimensions: batch=2, height=3, width=4

        // Initialize with constant value
        tensor.setConstant(1.0f);

        // Set some specific values manually
        tensor(0, 1, 2) = 5.5f;
        tensor(1, 2, 3) = 10.0f;

        // Print the whole tensor
        std::cout << "Tensor contents:\n" << tensor << "\n\n";

        // Element-wise operations
        Eigen::Tensor<float, 3> doubled = tensor * 2.0f;
        std::cout << "Doubled tensor:\n" << doubled << "\n\n";

        // Reduction: sum over the width dimension (dim 2)
        Eigen::array<int, 1> reduce_dims = {2};
        Eigen::Tensor<float, 2> sum_width = tensor.sum(reduce_dims);
        std::cout << "Sum over width (result 2x3):\n" << sum_width << "\n\n";

        // Slicing: extract the first (batch 0)
        Eigen::array<Eigen::Index, 3> offsets = {0, 0, 0};
        Eigen::array<Eigen::Index, 3> extents = {1, 3, 4};
        Eigen::Tensor<float, 3> slice = tensor.slice(offsets, extents);
        std::array<Eigen::Index, 2> reshape_shape = {3, 4};
        Eigen::Tensor<float, 2> first_image = slice.reshape(reshape_shape);
        std::cout << "First image (3x4 matrix):\n" << first_image << "\n\n";
    }

    // Tensor contraction (like matrix multiplication but for higher ranks)
    static void runContractionDemo() {
        std::cout << "=== Tensor Contraction Demo (Matrix Multiplication via Tensors) ===\n";

        Eigen::Tensor<float, 2> A(2, 3);
        Eigen::Tensor<float, 2> B(3, 2);

        A.setValues({{1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}});
        B.setValues({{0.0f, 1.0f}, {1.0f, 1.0f}, {2.0f, 1.0f}});

        std::cout << "Matrix A (2x3):\n" << A << "\n\n";
        std::cout << "Matrix B (3x2):\n" << B << "\n\n";

        // Contract along dimension 1 of A and dimension 0 of B
        Eigen::array<Eigen::IndexPair<int>, 1> contract_dims = {Eigen::IndexPair<int>(1, 0)};
        Eigen::Tensor<float, 2> C = A.contract(B, contract_dims);

        std::cout << "A * B (2x2):\n" << C << "\n\n";
    }
};

#endif // TENSOR_CLASS_HPP