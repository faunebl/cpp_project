
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

bool Matrix::is_invertible() const {
    if (rows != cols) {
        return false;
    }

    // compute determinant using Laplace expansion for simplicity
    if (rows == 2) {
        double determinant = data[0][0] * data[1][1] - data[0][1] * data[1][0];
        return std::abs(determinant) > 1e-9;
    }

    // for larger matrices, determinant calculation can be added
    throw std::runtime_error("Determinant calculation for size > 2 not implemented.");
}

void Matrix::print() const {
    for (const auto& row : data) {
        for (const auto& val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}
