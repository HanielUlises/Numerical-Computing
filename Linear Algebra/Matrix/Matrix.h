#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm> 
#include <vector>
#include <stdexcept>
#include <complex>

// Ontological definition
// I've always wanted to write this into a .h file (sob)
template <class T>
class Matrix{
    public:
    // Constructors
    Matrix();
    Matrix(int rows, int columns);
    Matrix(int rows, int columns, const T* input_data);
    Matrix(const Matrix<T>& input_Matrix);

    ~Matrix();
    // Succesful or not succesful resizing of matrix
    bool resize (int nRows, int nColumns);
    
    // Access methods
    T get_element (int row, int column);
    bool set_element (int row, int column, T element_value);
    int get_num_rows();
    int get_num_cols();

    // Operations
    // Equality
    bool operator== (const Matrix<T> & rhs);

    // Sum of matrices
    template <class U> friend Matrix<U> operator+ (const Matrix<U>& lhs, const Matrix<U>& rhs);
    template <class U> friend Matrix<U> operator+ (const U& lhs, const Matrix<U>& rhs);
    template <class U> friend Matrix<U> operator+ (const Matrix<U>& lhs, const U& rhs);

    // Difference of matrices
    template <class U> friend Matrix<U> operator- (const Matrix<U>& lhs, const Matrix<U>& rhs);
    template <class U> friend Matrix<U> operator- (const U& lhs, const Matrix<U>& rhs);
    template <class U> friend Matrix<U> operator- (const Matrix<U>& lhs, const U& rhs);

    // Product of matrices
    template <class U> friend Matrix<U> operator* (const Matrix<U>& lhs, const Matrix<U>& rhs);
    template <class U> friend Matrix<U> operator* (const U& lhs, const Matrix<U>& rhs);
    template <class U> friend Matrix<U> operator* (const Matrix<U>& lhs, const U& rhs);

    Matrix<T> transpose() const;
    T determinant() const;
    Matrix<T> inverse() const;
    T trace() const;
    void fill(T value);

    static Matrix<T> zero_matrix(int n, int m);
    static Matrix<T> identity_matrix(int n);
    static Matrix<T> diagonal_matrix(const std::vector<T>& diag_elements);

    std::vector<T> eigenvalues() const;

    Matrix<T> CholeskyDecomposition() const;
    Matrix<T> power(int exponent) const;
    Matrix<T> hadamard_product(const Matrix<T>& other) const;
    Matrix<T> QRDecomposition(Matrix<T>& Q, Matrix<T>& R) const;


    private:
    int sub_to_index(int row, int col) const;

    private:
    int rows, columns, n_elements;
    T* matrix_data;
};

#endif // MATRIX_H