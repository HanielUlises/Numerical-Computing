#include "Matrix.h"

// Default constructor
// New matrix with 0s
template <class T>
Matrix<T>::Matrix() {
    rows = 1;
    columns = 1;
    n_elements = 1;
    matrix_data = new T[n_elements];
    matrix_data[0] = 0.0;
}

// Constructor with specified rows and columns
template <class T>
Matrix<T>::Matrix(int rows, int columns) {
    this -> rows = rows;
    this -> columns = columns;
    n_elements = rows * columns;
    matrix_data = new T[n_elements];

    for(int i = 0; i < n_elements; i++){
        matrix_data[i] = 0.0;
    }
}

// Constructor with rows, columns, and data specified
template <class T>
Matrix<T>::Matrix(int rows, int columns, const T* input_data) {
    this -> rows = rows;
    this -> columns = columns;
    n_elements = rows * columns;
    matrix_data = new T[n_elements];

    for(int i = 0; i < n_elements; i++){
        matrix_data[i] = input_data[i];
    }
}

// Copy constructor
template <class T>
Matrix<T>::Matrix(const Matrix<T>& input_Matrix) {
    rows = input_Matrix.rows;
    columns = input_Matrix.columns;
    n_elements = input_Matrix.n_elements;
    matrix_data = new T[n_elements];

    for(int i = 0; i < n_elements; i++){
        matrix_data[i] = input_Matrix.matrix_data[i];
    }
}

// Destructor
template <class T>
Matrix<T>::~Matrix() {
    if(matrix_data != nullptr){
        delete[] matrix_data;
    }
}

template <class T>
int Matrix<T>::sub_to_index(int row, int col) const {
    return row * columns + col; 
}

// Resize the matrix
template <class T>
bool Matrix<T>::resize(int nRows, int nColumns) {
    rows = nRows;
    columns = nColumns;
    n_elements = (rows * columns);
    delete[] matrix_data;
    matrix_data = new T[n_elements];
    if(matrix_data != nullptr){
        for(int i = 0; i < n_elements; i++){
            matrix_data[i] = 0.0;
        }
        return true;
    }else{
        return false;
    }
}

template <class T>
T Matrix<T>::get_element(int row, int column) {
    if (row >= rows || column >= columns || row < 0 || column < 0) {
        throw std::out_of_range("Index out of range");
    }
    return matrix_data[sub_to_index(row, column)];
}


template <class T>
bool Matrix<T>::set_element(int row, int column, T element_value) {
    if (row >= rows || column >= columns || row < 0 || column < 0) {
        return false;
    }
    matrix_data[sub_to_index(row, column)] = element_value;
    return true;
}


template <class T>
int Matrix<T>::get_num_rows() {
    return rows;
}

template <class T>
int Matrix<T>::get_num_cols() {
    return columns;
}

template <class T>
bool Matrix<T>::operator==(const Matrix<T>& rhs) {
    if (rows != rhs.rows || columns != rhs.columns) {
        return false;
    }

    for (int i = 0; i < n_elements; ++i) {
        if (matrix_data[i] != rhs.matrix_data[i]) {
            return false;
        }
    }

    return true;
}

// Matrix + Matrix
template <class U>
Matrix<U> operator+(const Matrix<U>& lhs, const Matrix<U>& rhs) {
    if (lhs.rows != rhs.rows || lhs.columns != rhs.columns) {
        throw std::invalid_argument("Matrices must have the same dimensions for addition");
    }

    Matrix<U> result(lhs.rows, lhs.columns);
    for (int i = 0; i < lhs.n_elements; ++i) {
        result.matrix_data[i] = lhs.matrix_data[i] + rhs.matrix_data[i];
    }

    return result;
}

// Scalar + Matrix
template <class U>
Matrix<U> operator+(const U& lhs, const Matrix<U>& rhs) {
    Matrix<U> result(rhs.rows, rhs.columns);
    for (int i = 0; i < rhs.n_elements; ++i) {
        result.matrix_data[i] = lhs + rhs.matrix_data[i];
    }

    return result;
}

// Matrix + Scalar
template <class U>
Matrix<U> operator+(const Matrix<U>& lhs, const U& rhs) {
    return rhs + lhs;  // Reusing Scalar + Matrix implementation
}

// Matrix - Matrix
template <class U>
Matrix<U> operator-(const Matrix<U>& lhs, const Matrix<U>& rhs) {
    if (lhs.rows != rhs.rows || lhs.columns != rhs.columns) {
        throw std::invalid_argument("Matrices must have the same dimensions for subtraction");
    }

    Matrix<U> result(lhs.rows, lhs.columns);
    for (int i = 0; i < lhs.n_elements; ++i) {
        result.matrix_data[i] = lhs.matrix_data[i] - rhs.matrix_data[i];
    }

    return result;
}

// Scalar - Matrix
template <class U>
Matrix<U> operator-(const U& lhs, const Matrix<U>& rhs) {
    Matrix<U> result(rhs.rows, rhs.columns);
    for (int i = 0; i < rhs.n_elements; ++i) {
        result.matrix_data[i] = lhs - rhs.matrix_data[i];
    }

    return result;
}

// Matrix - Scalar
template <class U>
Matrix<U> operator-(const Matrix<U>& lhs, const U& rhs) {
    Matrix<U> result(lhs.rows, lhs.columns);
    for (int i = 0; i < lhs.n_elements; ++i) {
        result.matrix_data[i] = lhs.matrix_data[i] - rhs;
    }

    return result;
}

// Matrix * Matrix
template <class U>
Matrix<U> operator*(const Matrix<U>& lhs, const Matrix<U>& rhs) {
    if (lhs.columns != rhs.rows) {
        throw std::invalid_argument("Matrices must have appropriate dimensions for multiplication");
    }

    Matrix<U> result(lhs.rows, rhs.columns);
    for (int i = 0; i < lhs.rows; ++i) {
        for (int j = 0; j < rhs.columns; ++j) {
            U sum = 0;
            for (int k = 0; k < lhs.columns; ++k) {
                sum += lhs.get_element(i, k) * rhs.get_element(k, j);
            }
            result.set_element(i, j, sum);
        }
    }

    return result;
}

// Scalar * Matrix
template <class U>
Matrix<U> operator*(const U& lhs, const Matrix<U>& rhs) {
    Matrix<U> result(rhs.rows, rhs.columns);
    for (int i = 0; i < rhs.n_elements; ++i) {
        result.matrix_data[i] = lhs * rhs.matrix_data[i];
    }

    return result;
}

// Matrix * Scalar
template <class U>
Matrix<U> operator*(const Matrix<U>& lhs, const U& rhs) {
    return rhs * lhs; 
}

// Transpose Method
template <class T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> result(columns, rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            result.set_element(j, i, get_element(i, j));
        }
    }
    return result;
}

// Determinant Method
template <class T>
T Matrix<T>::determinant() const {
    if (rows != columns) {
        throw std::invalid_argument("Determinant can only be calculated for square matrices");
    }

    if (rows == 1) {
        return matrix_data[0];
    }

    if (rows == 2) {
        return matrix_data[0] * matrix_data[3] - matrix_data[1] * matrix_data[2];
    }

    T det = 0;
    for (int i = 0; i < columns; ++i) {
        Matrix<T> subMatrix(rows - 1, columns - 1);

        for (int subRow = 1; subRow < rows; ++subRow) {
            int subColIndex = 0;
            for (int subCol = 0; subCol < columns; ++subCol) {
                if (subCol == i) continue;
                subMatrix.set_element(subRow - 1, subColIndex, get_element(subRow, subCol));
                ++subColIndex;
            }
        }

        T subDet = subMatrix.determinant();
        det += (i % 2 == 0 ? 1 : -1) * matrix_data[i] * subDet;
    }
    return det;
}

// Inverse Method
template <class T>
Matrix<T> Matrix<T>::inverse() const {
    if (rows != columns) {
        throw std::invalid_argument("Inverse can only be calculated for square matrices");
    }

    T det = determinant();
    if (det == 0) {
        throw std::runtime_error("Matrix is singular and cannot be inverted");
    }

    Matrix<T> adjoint(rows, columns);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            Matrix<T> subMatrix(rows - 1, columns - 1);
            for (int subRow = 0; subRow < rows; ++subRow) {
                if (subRow == i) continue;
                int subColIndex = 0;
                for (int subCol = 0; subCol < columns; ++subCol) {
                    if (subCol == j) continue;
                    subMatrix.set_element(subRow < i ? subRow : subRow - 1, subColIndex, get_element(subRow, subCol));
                    ++subColIndex;
                }
            }
            adjoint.set_element(j, i, ((i + j) % 2 == 0 ? 1 : -1) * subMatrix.determinant());
        }
    }
    return (1 / det) * adjoint;
}

// Trace Method
template <class T>
T Matrix<T>::trace() const {
    if (rows != columns) {
        throw std::invalid_argument("Trace can only be calculated for square matrices");
    }

    T traceSum = 0;
    for (int i = 0; i < rows; ++i) {
        traceSum += get_element(i, i);
    }
    return traceSum;
}

// Fill Method
template <class T>
void Matrix<T>::fill(T value) {
    for (int i = 0; i < n_elements; ++i) {
        matrix_data[i] = value;
    }
}

// Create a Zero Matrix
template <class T>
Matrix<T> Matrix<T>::zero_matrix(int n, int m) {
    Matrix<T> result(n, m);
    result.fill(0);
    return result;
}

// Create an Identity Matrix
template <class T>
Matrix<T> Matrix<T>::identity_matrix(int n) {
    Matrix<T> result(n, n);
    for (int i = 0; i < n; ++i) {
        result.set_element(i, i, 1);
    }
    return result;
}

// Create a Diagonal Matrix
template <class T>
Matrix<T> Matrix<T>::diagonal_matrix(const std::vector<T>& diag_elements) {
    int n = diag_elements.size();
    Matrix<T> result(n, n);
    for (int i = 0; i < n; ++i) {
        result.set_element(i, i, diag_elements[i]);
    }
    return result;
}

// QR Decomposition
template <class T>
Matrix<T> Matrix<T>::QRDecomposition(Matrix<T>& Q, Matrix<T>& R) const {
    int n = rows;

    Q = Matrix<T>::identity_matrix(n);
    R = *this;

    for (int k = 0; k < n - 1; ++k) {
        T norm_x = 0;
        for (int i = k; i < n; ++i) {
            norm_x += R.get_element(i, k) * R.get_element(i, k);
        }
        norm_x = std::sqrt(norm_x);

        if (R.get_element(k, k) < 0) {
            norm_x = -norm_x;
        }

        T rkk = std::sqrt(0.5 * (norm_x * norm_x - R.get_element(k, k) * norm_x));
        if (rkk == 0) {
            continue;
        }

        std::vector<T> u(n, 0);
        u[k] = (R.get_element(k, k) - norm_x) / (2 * rkk);
        for (int i = k + 1; i < n; ++i) {
            u[i] = R.get_element(i, k) / (2 * rkk);
        }

        for (int j = k; j < n; ++j) {
            T sum = 0;
            for (int i = k; i < n; ++i) {
                sum += u[i] * R.get_element(i, j);
            }
            for (int i = k; i < n; ++i) {
                R.set_element(i, j, R.get_element(i, j) - 2 * u[i] * sum);
            }
        }

        for (int j = 0; j < n; ++j) {
            T sum = 0;
            for (int i = k; i < n; ++i) {
                sum += u[i] * Q.get_element(i, j);
            }
            for (int i = k; i < n; ++i) {
                Q.set_element(i, j, Q.get_element(i, j) - 2 * u[i] * sum);
            }
        }
    }

    Q = Q.transpose();
    return R;
}

// QR Algorithm to compute all eigenvalues
template <class T>
std::vector<T> Matrix<T>::eigenvalues() const {
    if (rows != columns) {
        throw std::invalid_argument("Eigenvalues can only be calculated for square matrices");
    }

    Matrix<T> A = *this;
    Matrix<T> Q(rows, columns);
    Matrix<T> R(rows, columns);

    const int max_iter = 1000;
    const T tol = 1e-10;

    for (int iter = 0; iter < max_iter; ++iter) {
        A.QRDecomposition(Q, R);
        A = R * Q;

        bool is_converged = true;
        for (int i = 0; i < rows - 1; ++i) {
            if (std::abs(A.get_element(i + 1, i)) > tol) {
                is_converged = false;
                break;
            }
        }

        if (is_converged) {
            break;
        }
    }

    std::vector<T> eigenvalues;
    for (int i = 0; i < rows; ++i) {
        eigenvalues.push_back(A.get_element(i, i));
    }

    return eigenvalues;
}

template <class T>
Matrix<T> Matrix<T>::CholeskyDecomposition() const {
    if (rows != columns) {
        throw std::invalid_argument("Cholesky Decomposition requires a square matrix");
    }

    Matrix<T> L(rows, columns);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j <= i; ++j) {
            T sum = 0;  // This will hold the sum of L(i, k) * L(j, k) for k = 0 to j-1

            // Sum of L(i, k) * L(j, k) for all k < j
            for (int k = 0; k < j; ++k) {
                sum += L.get_element(i, k) * L.get_element(j, k);
            }

            // For diagonal elements (i == j), calculate L(i, j) = sqrt(A(i, i) - sum)
            if (i == j) {
                L.set_element(i, j, std::sqrt(get_element(i, i) - sum));
            }
            // For off-diagonal elements, calculate L(i, j) = (A(i, j) - sum) / L(j, j)
            else {
                L.set_element(i, j, (get_element(i, j) - sum) / L.get_element(j, j));
            }
        }
    }

    return L;
}

template <class T>
Matrix<T> Matrix<T>::power(int exponent) const {
    if (rows != columns) {
        throw std::invalid_argument("Matrix exponentiation requires a square matrix");
    }

    Matrix<T> result = Matrix<T>::identity_matrix(rows);
    Matrix<T> base = *this;

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = result * base;
        }
        base = base * base;
        exponent /= 2;
    }

    return result;
}

// Product-wise multiplication
template <class T>
Matrix<T> Matrix<T>::hadamard_product(const Matrix<T>& other) const {
    if (rows != other.rows || columns != other.columns) {
        throw std::invalid_argument("Matrices must have the same dimensions for Hadamard product");
    }

    Matrix<T> result(rows, columns);
    for (int i = 0; i < n_elements; ++i) {
        result.matrix_data[i] = matrix_data[i] * other.matrix_data[i];
    }

    return result;
}

template <class T>
Matrix<T> Matrix<T>::operator-() const {
    Matrix<T> result(rows, columns);
    for (int i = 0; i < n_elements; ++i) {
        result.matrix_data[i] = -matrix_data[i];
    }
    return result;
}

template class Matrix<int>;
template class Matrix<float>;
template class Matrix<double>;
