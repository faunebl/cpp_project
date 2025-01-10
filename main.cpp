// main.cpp
#include "Matrix.h"
#include <iostream>

int main() {
    std::cout << "Testing Matrix class:\n";

    Matrix matrix({{4, 7}, {2, 6}});
    std::cout << "Original matrix:\n";
    matrix.print();

    if (matrix.is_invertible()) {
        std::cout << "Matrix is invertible.\n";
        Matrix inv = matrix.inverse();
        std::cout << "Inverse matrix:\n";
        inv.print();
    } else {
        std::cout << "Matrix is not invertible.\n";
    }

    return 0;
}