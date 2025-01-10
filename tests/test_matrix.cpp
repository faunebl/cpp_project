// test for question 1 : check if the matrix is invertible and calculate the determinant 
// this checks that the function works
#include "Matrix.h"
#include <iostream>

int main() {
    std::cout << "Testing Matrix class:\n";

    Matrix matrix({{4, 7}, {2, 6}});
    std::cout << "Original matrix:\n";
    matrix.print();

    std::cout << "Determinant: " << matrix.determinant() << "\n";

    if (matrix.is_invertible()) {
        std::cout << "Matrix is invertible.\n";
        Matrix inv = matrix.inverse();
        std::cout << "Inverse matrix:\n";
        inv.print();
    } else {
        std::cout << "Matrix is not invertible.\n";
    }

    Matrix large_matrix({{6, 1, 1}, {4, -2, 5}, {2, 8, 7}});
    std::cout << "\nTesting larger matrix:\n";
    large_matrix.print();

    std::cout << "Determinant: " << large_matrix.determinant() << "\n";

    if (large_matrix.is_invertible()) {
        std::cout << "Matrix is invertible.\n";
    } else {
        std::cout << "Matrix is not invertible.\n";
    }

    return 0;
}