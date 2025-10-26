#include "Matrix.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>


int main() {
    // Test 1: Default Constructor and Basic Operations
    std::cout << "Test 1: Default Constructor\n";
    Matrix<double> m1;
    assert(m1.get_num_rows() == 1 && m1.get_num_cols() == 1);
    assert(m1.get_element(0, 0) == 0.0);
    std::cout << "Default constructor passed\n\n";

    // Test 2: Constructor with specified dimensions
    std::cout << "Test 2: Constructor with dimensions\n";
    Matrix<double> m2(2, 3);
    assert(m2.get_num_rows() == 2 && m2.get_num_cols() == 3);
    assert(m2.get_element(1, 2) == 0.0);
    std::cout << "Constructor with dimensions passed\n\n";

    // Test 3: Constructor with input data
    std::cout << "Test 3: Constructor with input data\n";
    double data[] = {1.0, 2.0, 3.0, 4.0};
    Matrix<double> m3(2, 2, data);
    assert(m3.get_element(0, 0) == 1.0 && m3.get_element(1, 1) == 4.0);
    std::cout << "Constructor with input data passed\n\n";

    // Test 4: Copy Constructor
    std::cout << "Test 4: Copy Constructor\n";
    Matrix<double> m4(m3);
    assert(m4 == m3);
    std::cout << "Copy constructor passed\n\n";

    // Test 5: Matrix Addition
    std::cout << "Test 5: Matrix Addition\n";
    Matrix<double> m5(2, 2, data);
    auto sum = m3 + m5;
    assert(sum.get_element(0, 0) == 2.0 && sum.get_element(1, 1) == 8.0);
    std::cout << "Matrix addition passed\n\n";

    // Test 6: Scalar Operations
    std::cout << "Test 6: Scalar Operations\n";
    auto scalar_mult = 2.0 * m3;
    assert(scalar_mult.get_element(0, 0) == 2.0 && scalar_mult.get_element(1, 1) == 8.0);
    auto scalar_add = m3 + 1.0;
    assert(scalar_add.get_element(0, 0) == 2.0 && scalar_add.get_element(1, 1) == 5.0);
    std::cout << "Scalar operations passed\n\n";

    // Test 7: Matrix Multiplication
    std::cout << "Test 7: Matrix Multiplication\n";
    double data2[] = {1.0, 0.0, 0.0, 1.0};
    Matrix<double> m6(2, 2, data2);
    auto prod = m3 * m6;
    assert(prod == m3); // Should be identity multiplication
    std::cout << "Matrix multiplication passed\n\n";

    // Test 8: Transpose
    std::cout << "Test 8: Transpose\n";
    auto trans = m3.transpose();
    assert(trans.get_element(0, 1) == m3.get_element(1, 0));
    std::cout << "Transpose passed\n\n";

    // Test 9: Determinant
    std::cout << "Test 9: Determinant\n";
    double det = m3.determinant();
    assert(std::abs(det - (1.0 * 4.0 - 2.0 * 3.0)) < 1e-10); // det = ad - bc
    std::cout << "Determinant passed\n\n";

    // Test 10: Inverse
    std::cout << "Test 10: Inverse\n";
    auto inv = m3.inverse();
    auto identity = m3 * inv;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            double expected = (i == j) ? 1.0 : 0.0;
            assert(std::abs(identity.get_element(i, j) - expected) < 1e-10);
        }
    }
    std::cout << "Inverse passed\n\n";

    // Test 11: Trace
    std::cout << "Test 11: Trace\n";
    double trace = m3.trace();
    assert(std::abs(trace - 5.0) < 1e-10); // 1.0 + 4.0
    std::cout << "Trace passed\n\n";

    // Test 12: Static Matrix Creation
    std::cout << "Test 12: Static Matrix Creation\n";
    auto zero = Matrix<double>::zero_matrix(2, 2);
    assert(zero.get_element(0, 0) == 0.0 && zero.get_num_rows() == 2);
    auto ident = Matrix<double>::identity_matrix(2);
    assert(ident.get_element(0, 0) == 1.0 && ident.get_element(0, 1) == 0.0);
    std::vector<double> diag = {2.0, 3.0};
    auto diag_mat = Matrix<double>::diagonal_matrix(diag);
    assert(diag_mat.get_element(0, 0) == 2.0 && diag_mat.get_element(1, 1) == 3.0);
    std::cout << "Static matrix creation passed\n\n";

    // Test 13: QR Decomposition
    std::cout << "Test 13: QR Decomposition\n";
    Matrix<double> Q, R;
    m3.QRDecomposition(Q, R);
    auto qr_product = Q * R;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            assert(std::abs(qr_product.get_element(i, j) - m3.get_element(i, j)) < 1e-10);
        }
    }
    std::cout << "QR Decomposition passed\n\n";

    // Test 14: Eigenvalues
    std::cout << "Test 14: Eigenvalues\n";
    auto eigenvals = m3.eigenvalues();
    // For a 2x2 matrix, verify sum of eigenvalues equals trace
    assert(std::abs(eigenvals[0] + eigenvals[1] - m3.trace()) < 1e-10);
    std::cout << "Eigenvalues passed\n\n";

    // Test 15: Cholesky Decomposition
    std::cout << "Test 15: Cholesky Decomposition\n";
    double sym_data[] = {4.0, 1.0, 1.0, 3.0}; // Symmetric positive definite
    Matrix<double> sym_mat(2, 2, sym_data);
    auto L = sym_mat.CholeskyDecomposition();
    auto LLt = L * L.transpose();
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            assert(std::abs(LLt.get_element(i, j) - sym_mat.get_element(i, j)) < 1e-10);
        }
    }
    std::cout << "Cholesky Decomposition passed\n\n";

    // Test 16: Matrix Power
    std::cout << "Test 16: Matrix Power\n";
    auto pow = m3.power(2);
    auto expected_pow = m3 * m3;
    assert(pow == expected_pow);
    std::cout << "Matrix power passed\n\n";

    // Test 17: Hadamard Product
    std::cout << "Test 17: Hadamard Product\n";
    auto hadamard = m3.hadamard_product(m3);
    assert(hadamard.get_element(0, 0) == 1.0 && hadamard.get_element(1, 1) == 16.0);
    std::cout << "Hadamard product passed\n\n";

    std::cout << "All tests passed successfully!\n";
    return 0;
}