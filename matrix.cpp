// Matrix.cpp
#include "Matrix.h"

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols), data(rows, std::vector<double>(cols)) {}

Matrix::Matrix(const std::vector<std::vector<double>>& data) : data(data), rows(data.size()), cols(data[0].size()) {}

int Matrix::get_rows() const { return rows; }
int Matrix::get_cols() const { return cols; }

std::vector<double>& Matrix::operator[](int index) { return data[index]; }
const std::vector<double>& Matrix::operator[](int index) const { return data[index]; }

Matrix Matrix::inverse() const {
    if (!is_invertible()) {
        throw std::runtime_error("Matrix is not invertible.");
    }

    int n = rows;
    Matrix augmented(n, 2 * n);

    // create augmented matrix [A | I]
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            augmented[i][j] = data[i][j];
        }
        augmented[i][n + i] = 1.0;
    }

    // perform Gaussian elimination
    for (int i = 0; i < n; ++i) {
        // make the diagonal element 1
        double diag_element = augmented[i][i];
        if (std::abs(diag_element) < 1e-9) {
            throw std::runtime_error("Matrix is not invertible.");
        }
        for (int j = 0; j < 2 * n; ++j) {
            augmented[i][j] /= diag_element;
        }

        // make all other elements in column i zero
        for (int k = 0; k < n; ++k) {
            if (k != i) {
                double factor = augmented[k][i];
                for (int j = 0; j < 2 * n; ++j) {
                    augmented[k][j] -= factor * augmented[i][j];
                }
            }
        }
    }

    // extract the inverse matrix
    Matrix inverse(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inverse[i][j] = augmented[i][n + j];
        }
    }

    return inverse;
}

double Matrix::determinant() const {
    if (rows != cols) {
        throw std::runtime_error("Determinant is defined only for square matrices.");
    }

    int n = rows;
    if (n == 1) {
        return data[0][0];
    }
    if (n == 2) {
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    }

    double det = 0.0;
    for (int col = 0; col < n; ++col) {
        // create submatrix
        std::vector<std::vector<double>> submatrix;
        for (int i = 1; i < n; ++i) {
            std::vector<double> row;
            for (int j = 0; j < n; ++j) {
                if (j != col) {
                    row.push_back(data[i][j]);
                }
            }
            submatrix.push_back(row);
        }

        Matrix sub(submatrix);
        det += ((col % 2 == 0 ? 1 : -1) * data[0][col] * sub.determinant());
    }

    return det;
}

bool Matrix::is_invertible() const {
    if (rows != cols) {
        return false;
    }

    double det = determinant();
    return std::abs(det) > 1e-9;
}

void Matrix::print() const {
    for (const auto& row : data) {
        for (const auto& val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<double> Matrix::operator*(const std::vector<double>& vec) const {
    if (vec.size() != cols) {
        throw std::invalid_argument("Matrix and vector dimensions do not match for multiplication.");
    }
    std::vector<double> result(rows, 0.0);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[i] += data[i][j] * vec[j];
        }
    }
    return result;
}

std::vector<double> Matrix::solve(const std::vector<double>& b) const {
    if (rows != cols || b.size() != rows) {
        throw std::invalid_argument("Matrix must be square, and vector dimensions must match.");
    }
    // Make a copy of the matrix and vector for modifications
    Matrix A = *this;
    std::vector<double> x = b;

    // Forward elimination
    for (size_t i = 0; i < rows; ++i) {
        for (size_t k = i + 1; k < rows; ++k) {
            double factor = A.data[k][i] / A.data[i][i];
            for (size_t j = i; j < cols; ++j) {
                A.data[k][j] -= factor * A.data[i][j];
            }
            x[k] -= factor * x[i];
        }
    }

    // Back substitution
    for (int i = rows - 1; i >= 0; --i) {
        for (int j = i + 1; j < cols; ++j) {
            x[i] -= A.data[i][j] * x[j];
        }
        x[i] /= A.data[i][i];
    }

    return x;
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions must match for addition.");
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}